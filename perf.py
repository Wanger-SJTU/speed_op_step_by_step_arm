
import os
from matplotlib import pyplot as plt
import subprocess


def run_cmd(cmd):
    output = subprocess.getoutput(cmd)
    for line in output.split("\n"):
        if "GFLOPS" not in line:
            continue
        print(line)
    # return output

# TODO


def draw():
    pass


def main():
    os.system("make")
    for item in os.listdir("build"):
        file_path = os.path.abspath(os.path.join("build", item))
        if os.path.isfile(file_path) and "." not in item:
            res = run_cmd("bash push.sh {}".format(file_path))
            # print(res)


if __name__ == "__main__":
    main()
