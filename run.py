
import os
from matplotlib import pyplot as plt

import subprocess
import argparse

fig = plt.figure(figsize=(8, 5))


def run_perf_cmd(cmd, name):
    output = subprocess.getoutput(cmd)
    mnk = []
    gflops = []
    for line in output.split("\n"):
        print(line)
        if "GFLOPS" not in line:
            continue
        items = line.split(" ")
        mnk.append(int(items[0].split(":")[1]))
        gflops.append(float(items[3].split(":")[1]))
    plt.plot(mnk, gflops, label=str(name))


def run_test_cmd(cmd):
    output = subprocess.getoutput(cmd)
    for line in output.split("\n"):
        if ".Error" in line:
            return False
    return True


def run_test(platform):
    dirs = ["src/common", "src/{}/opt".format(platform)]
    os.system("make clean -f Makefiles/{}.Makefile".format(platform))
    all_pass = True
    for dir in dirs:
        for file in sorted(os.listdir(dir)):
            # subprocess.getoutput(
            if "trans" in file:
                continue
            cmd = "make test -f Makefiles/{}.Makefile TEST_ITEM={}".format(
                platform, file.split(".")[0])
            subprocess.getoutput(cmd)

            if platform == "x86":
                if not run_test_cmd("./build/{}/test".format(platform)):
                    print("run for {} Error".format(file))
                    all_pass = False
            else:
                pass
    if all_pass:
        print("all pass")


def run_perf(platform):
    dirs = ["src/common", "src/{}/opt".format(platform)]
    os.system("make clean -f Makefiles/{}.Makefile".format(platform))

    for dir in dirs:
        for file in sorted(os.listdir(dir)):
            if "trans" in file:
                continue
            file = file.split(".")[0]
            cmd = f"make perf -f Makefiles/{platform}.Makefile PERF_ITEM={file}"
            subprocess.getoutput(cmd)

            if platform == "x86":
                run_perf_cmd(f"./build/{platform}/{file}", file)
            else:
                run_perf_cmd(f"bash run.sh ./build/{platform}/{file}", file)


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--platform", "-p", default="x86")
    parser.add_argument("--task", "-t", default="perf")
    args = parser.parse_args()

    return args


def main():
    cmd_args = parse_args()

    if cmd_args.task == "test":
        run_test(cmd_args.platform)
        return
    elif cmd_args.task == "perf":
        run_perf(cmd_args.platform)
        plt.xlabel('m_n_k')
        plt.ylabel('GFLOPS')
        # plt.legend(bbox_to_anchor=(1.3, 0.6), loc='center left')
        # plt.tight_layout()
        plt.savefig('gflops.{}.png'.format(cmd_args.platform), dpi=300)


if __name__ == "__main__":
    main()
