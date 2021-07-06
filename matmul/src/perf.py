
import os

def perf():
    task_files = [
        "matmul_raw",
        "gemm_4x4x1",
        "matmul_opt_2",
        "matmul_transpose",
        "gemm_1x4x1_row",
        "gemm_4x4x4",
        "matmul_opt_1",
        "matmul_raw"
    ]
    last_task = ""
    for item in task_files:
        cmd = "sed -i 's/clang++/\$\{NDK_CXX\}/g' Makefile"
        



def main():
    pass