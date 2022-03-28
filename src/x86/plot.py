import os
import subprocess
from collections import defaultdict

import numpy as np
from matplotlib import pyplot as plt

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

for file in files:
    print(f"----------{file}---------------")
    os.system(f"g++ {file}")
    res = exec_cmd("./a.out")
    for item in res:
        bench_res[file] += [float(item.split(":")[-1])]


x = [2**(i+2) for i in range(9)] 

fig, ax = plt.subplots()
for key, value in bench_res.items():
    ax.plot(x, value, label=key, color=np.random.rand(3,1))

plt.show()