# Glibc 2.27源码分析

---

&emsp;&emsp;继分析过stack相关知识后，我们只能算是基本了解了二进制漏洞利用的最最基本的原理。其实我们的最终流程都是要想办法控制IP寄存器，进而修改程序执行流程。事实上stack上的漏洞利用往往比较单一粗暴，基本都是靠padding一直怼到ret的位置，然后进行rop。但是随着现代程序保护措施的发展，canary、NX和ASLR等保护能够很大程度的缓解针对stack的攻击。这个时候机器似乎已经很大程度的帮我们规避了许多危险，但是，最容易出漏洞的地方往往是程序员处理复杂逻辑的环节。显然，内存管理是一个及其复杂的任务，不正确编程习惯往往会导致内存管理出现漏洞。我来据一个很简单的例子，下面这个程序是大多数程序员的写法：

```c++
int main() {
    char *ptr = (char *)malloc(10);
    strcpy(ptr, "aaa");
    printf("%p\n", ptr);
    free(ptr);
    printf("%p", ptr);
    return 0;
}
```
这个时候程序会有如下输出：
```shell
root@Aurora:/home/code/pwn/Just-pwn/practice(master⚡) # ./a
0x5625cf5a1260
aaa
---- Free ----
0x5625cf5a1260
bbb                                                                     root@Aurora:/home/code/pwn/Just-pwn/practice(master⚡) # 
```

&emsp;&emsp;这是一个经典的UAF(Use-After-Free),这个时候我们发现即使我们已经free掉了malloc的内存，我们依然能够控制那片区域，这正因为free后**没有将ptr设置为NULL**。这正是由于不良好的编程习惯造成的。
&emsp;&emsp;你或许知道malloc所分配的内存在Heap段，那么你了解其背后的细节吗，在heap上是不是会有更加华丽的漏洞利用方式呢？接下来我来分享一下我阅读linux下内存管理器ptmalloc源码的理解，以及部分Heap段漏洞利用的方式的总结。

## 堆相关结构
&emsp;&emsp;首先我们来介绍一下堆相关的基本结构，




























