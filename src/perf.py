
import os
import pdb


root_dir = os.path.dirname(os.path.abspath(__file__))

def get_perf_tasks():
    opt_dir = os.path.join(root_dir, "opt_gemm")
    files = os.listdir(opt_dir)
    split = lambda x: x.split(".")[0]
    return map(split, files)

def main():
    task_files = get_perf_tasks()
    last_task = ""
    for item in task_files:
        cmd = f"sed -i 's/matmul_opt_2/{item}/g' Makefile"
        os.system(cmd)
        
        for i in range(4, 11):
            cmd = f"./run_arm.sh {2**i} {2**i} {2**i}"

    cmd = f"sed -i 's/{item}/matmul_opt_2/g' Makefile"
    os.system(cmd)


if __name__ == "__main__":
    main()