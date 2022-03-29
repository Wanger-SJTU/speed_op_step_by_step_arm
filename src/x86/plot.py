import os
import json
import subprocess
from collections import defaultdict
import matplotlib

import numpy as np
from matplotlib import markers, pyplot as plt

def exec_cmd(cmd):
    p = subprocess.Popen(cmd.split(' '), stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    res = []
    for line in iter(p.stdout.readline, b''):
        res += [line.decode("utf-8").rstrip()]
    return res

files = [file for file in os.listdir("./") if file.endswith("cpp")]

# key:file_name
# value:[] GFLOPS
bench_res = defaultdict(list)

os.system("make clean")

x = set()
for file in files:
    print(f"----------{file}---------------")
    if file in {"perf.cpp", "eval.cpp", "utils.cpp"}:
        continue
    os.system("make target={}".format(file.split(".cpp")[0]))
    res = exec_cmd("./main")
    for item in res:
        bench_res[file] += [float(item.split(":")[-1])]
        x.add(int(item.split(" ")[0].split(":")[-1]))

json.dump(bench_res, open("bench_res.json", "w"))

x = sorted(list(x))
fig, ax = plt.subplots()
for key, value in bench_res.items():
    ax.plot(x, value, label=key, c=matplotlib.colors.to_hex(np.random.rand(3,)))
    # color=random_color())
plt.legend()
plt.savefig("res.png")