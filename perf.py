
import os
from matplotlib import pyplot as plt
import subprocess


fig = plt.figure(figsize=(8, 5))


def run_cmd(cmd, name):
    output = subprocess.getoutput(cmd)
    mnk = []
    gflops = []
    for line in output.split("\n"):
        if "GFLOPS" not in line:
            continue
        items = line.split(" ")
        mnk.append(int(items[0].split(":")[1]))
        gflops.append(float(items[3].split(":")[1]))
        print(line)
    plt.plot(mnk, gflops, label=str(name))


def main():
    subprocess.getoutput("make")
    for item in os.listdir("build"):
        file_path = os.path.abspath(os.path.join("build", item))
        if os.path.isfile(file_path) and "." not in item:
            print("==== run %s ========" % item)
            res = run_cmd("bash push.sh {}".format(file_path), item)

    plt.xlabel('m_n_k')
    plt.ylabel('GFLOPS')
    plt.legend()
    plt.savefig('gflops.png', dpi=300)


if __name__ == "__main__":
    main()
