
import tvm
import tvm.te as te
import tvm.auto_scheduler as auto_scheduler

from tvm import tir

@auto_scheduler.register_workload
def matmul(M, K, N):
    A = tvm.te.PlaceholderOp([M, K])
    B = tvm.te.PlaceholderOp([K, N])
    C = tvm.te.compute([A,B], lambda i,j: C[i,j] = )