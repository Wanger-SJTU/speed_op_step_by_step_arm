

# matmul 计算

矩阵乘法的定义

![](http://latex.codecogs.com/gif.latex?\\mathbf{C}=\\mathbf{A}\\mathbf{B};\\mathbf{A}\\in\\mathbf{R}^{M*K},\\mathbf{B}\\in\\mathbf{R}^{K*N},\\mathbf{C}\\in\\mathbf{R}^{M*N})

![](http://latex.codecogs.com/gif.latex?\\mathbf{C}_{m,n}=\\sum_{k=1}^{K}\\mathbf{A}_{m,k}*\\mathbf{B}_{k,n})

其中 𝐴、𝐵、𝐶 三者的形状分别为 𝑀×𝐾 、 𝐾×𝑁 、 𝑀×𝑁。图一是矩阵乘的可视化展示，和计算时为得到一个输出点所要使用的输入数据。

![](../asserts/matmul.png)

根据定义实现的代码：

```cpp
for (i = 0; i < m; i++) {   /* Loop over the rows of C */
    for (j = 0; j < n; j++) { /* Loop over the columns of C */
      for (p = 0; p < k; p++) {
        /* Update C(i,j) with the inner
            product of the ith
            row of A and the jth column of B */
        C(i, j) = C(i, j) + A(i, p) * B(p, j);
      }
    }
  }
```

上述代码在M=3，K=512，N=512时，在Cortex-A75(2200 MHz)上的运行时间为1.5ms，GFLOPS为1.048。实测A75的单核GFLOPS为17.176333。硬件有效利用率仅为 6.1%。优化空间很大。


对这样的矩阵乘的算法优化可分为两类：
- 基于算法分析的方法：根据矩阵乘计算特性，从数学角度优化，典型的算法包括 Strassen 算法和 Coppersmith–Winograd 算法。
- 基于软件优化的方法：根据计算机存储系统的层次结构特性，选择性地调整计算顺序，主要有循环拆分向量化、内存重排等。

# 基于软件优化的方法

##
## 内存对齐
Cache可以更好的利用局部性原理，减少CPU访问主存的次数。局部性原理就是优先从留CPU近的存储结构中去寻找当前需要查找的数据，加快数据访问速度从而减少程序中各个变量的存取时间。

“假设 cache line 为 32B。待访问数据大小为 64B，地址在 0x80000001，则需要占用 3 条 cache 映射表项；若地址在 0x80000000 则只需要 2 条。内存对齐变相地提高了 cache 命中率。” 假定kernel一次计算执行 大小的block, 根据MMult_4x4_7.c (https://github.com/flame/how-to-optimize-gemm/blob/master/src/MMult_4x4_7.c)和 MMult_4x4_8.c (https://github.com/flame/how-to-optimize-gemm/blob/master/src/MMult_4x4_8.c)代码，可以看出MMult_4x4_8.c使用了偏移量完成内存对齐。

这样我们就可以参考工程的MMult_1x4_3.c改写出一个FLOPs还不错的分块的矩阵乘法，代码实现如下，为了缩短代码长度，隐去了注释，如果有什么疑问欢迎留言区讨论：



# 基于算法分析的方法

# TVM 自动优化


##  auto-tvm template-based 手写schedule

##  ansor template-free


# 效果对比

