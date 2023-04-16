
from curses import keyname
import os
from socket import timeout
import time
from timeit import repeat
import numpy as np

import tvm
from tvm import te
from tvm import auto_scheduler

from tvm.contrib import ndk
from tvm import rpc
from tvm.contrib.utils import tempdir

target = "llvm -device=arm_cpu -mtriple=aarch64-linux-gnu -mattr=+neon"


@auto_scheduler.register_workload
def matmul(m, k, n):
    A = te.placeholder([m, k])
    B = te.placeholder([k, n])
    k = te.reduce_axis((0, k), name="k")
    C = te.compute([m, n], lambda i, j: te.sum(A[i, k] * B[k, j], axis=k))
    return C, A, B


sch_map = {}


def register(func):
    sch_map[func.__name__] = func
    return func


def upload(lib, filename = "net.so"):
    host = os.getenv("TVM_TRACKER_HOST")
    port = int(os.getenv("TVM_TRACKER_PORT"))
    tracker = rpc.connect_tracker(host, port)
    remote = tracker.request("android", session_timeout=0)
    tmp = tempdir()
    lib.export_library(tmp.relpath(filename), ndk.create_shared)
    remote.upload(tmp.relpath(filename))
    rlib = remote.load_module(filename)
    return rlib, remote


@register
def vanlian_mnk_sch(C, A, B):
    sch = te.create_schedule(C.op)
    f = tvm.build(sch, [A, B, C], target=target)
    return upload(f)

@register
def vanlian_mkn_sch(C, A, B):
    sch = te.create_schedule(C.op)
    i, j, k = sch[C].all_iter_vars
    sch[C].reorder(i, k, j)
    f = tvm.build(sch, [A, B, C], target=target)
    return upload(f)

def eval():
    m, k, n = (512, ) * 3
    C, A, B = matmul(m, k, n)
    for name, func in sch_map.items():
        rlib, remote = func(C, A, B)
        dev = remote.cpu()
        a = tvm.nd.array(np.random.random([m, k]).astype(np.float32), dev)
        b = tvm.nd.array(np.random.random([k, n]).astype(np.float32), dev)
        c = tvm.nd.array(np.random.random([m, n]).astype(np.float32), dev)
        time_f = rlib.time_evaluator(rlib.entry_name, dev, number=1, repeat=10)
        print("{} {:.2f} ms".format(name, time_f(a,b,c).mean * 1e3))

if __name__ == "__main__":
    eval()
