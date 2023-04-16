import os

import numpy as np
import tvm
from tvm import te, auto_scheduler

import matplotlib
from matplotlib import markers, pyplot as plt


@auto_scheduler.register_workload  # Note the auto_scheduler decorator
def matmul(M, K, N, dtype="float32"):
    A = te.placeholder((M, K), name="A", dtype=dtype)
    B = te.placeholder((K, N), name="B", dtype=dtype)
    k = te.reduce_axis((0, K), name="k")

    matmul = te.compute(
        (M, N),
        lambda i, j: te.sum(A[i, k] * B[k, j], axis=k),
        name="matmul",
        # attrs={"layout_free_placeholders": [B]},  # enable automatic layout transform for tensor B
    )
    return [A, B, matmul]


target = tvm.target.Target("llvm -mcpu=core-avx2")

log_file = "matmul.json"
tune_option = auto_scheduler.TuningOptions(
    num_measure_trials=100,
    measure_callbacks=[auto_scheduler.RecordToFile(log_file)],
    verbose=2,
)

x = []
y = []
for i in range(64):
    M = K = N = 32 * (i+1)
    task = tvm.auto_scheduler.SearchTask(func=matmul, args=(M, K, N, "float32"), target=target)
    task.tune(tune_option)
    sch, args = task.apply_best(log_file)
    func = tvm.build(sch, args, target)
    a_np = np.random.uniform(size=(M, K)).astype(np.float32)
    b_np = np.random.uniform(size=(K, N)).astype(np.float32)
    out_np = a_np.dot(b_np)

    dev = tvm.cpu()
    a_tvm = tvm.nd.array(a_np, device=dev)
    b_tvm = tvm.nd.array(b_np, device=dev)
    out_tvm = tvm.nd.empty(out_np.shape, device=dev)
    func(a_tvm, b_tvm, out_tvm)

    evaluator = func.time_evaluator(func.entry_name, dev, min_repeat_ms=500)
    time = np.min(evaluator(a_tvm, b_tvm, out_tvm).results) * 1000
    print("mkn %d : GFLOPS %f".format(M, task.compute_dag.flop_ct*1e-9 / (time / 1000)))

    x.append(M)
    y.append(task.compute_dag.flop_ct*1e-9 / (time / 1000))


fig, ax = plt.subplots()
for key, value in zip(x, y):
    ax.plot(x, value, label=key, c=matplotlib.colors.to_hex(np.random.rand(3,)))
    # color=random_color())
plt.legend()
plt.savefig("res_tvm.png")
