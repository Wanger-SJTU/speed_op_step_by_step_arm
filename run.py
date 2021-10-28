
import os
from matplotlib import pyplot as plt
import subprocess
import argparse

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


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--platform", "-p", default="armv8a")
    parser.add_argument("--task", "-t", default="perf")
    args = parser.parse_args()

    return args


def main():
    cmd_args = parse_args()

    os.system("make clean -f Makefiles/Makefile.{}".format(cmd_args.platform))

    subprocess.getoutput(
        "make {} -f Makefiles/Makefile.{}".format(cmd_args.task, cmd_args.platform))

    if cmd_args.task == "test":
        os.system("./build/test")

    elif cmd_args.task == "perf":
        dir_path = "build/{}".format(cmd_args.platform)
        for item in os.listdir(dir_path):
            file_path = os.path.abspath(os.path.join(dir_path, item))
            if os.path.isfile(file_path) and "." not in item:
                print("==== run %s ========" % item)
                run_cmd("bash run.sh {} {}".format(
                    cmd_args.platform, file_path), item)
                # res = run_cmd("bash test.sh {}".format(item), item)

        plt.xlabel('m_n_k')
        plt.ylabel('GFLOPS')
        plt.legend()
        plt.savefig('gflops.{}.png'.format(cmd_args.platform), dpi=300)


if __name__ == "__main__":
    main()
