#include <stdio.h>

/* 给 call/ret 用的被调函数 */
int add5(int x){
    return x + 5;
}

int main(void){
    /* 块1: mov + 内存寻址（局部变量 = 栈内存） */
    int a = 90;                 /* mov dword ptr [rbp-4], 0x5A */
    int b = 15;                 /* mov dword ptr [rbp-8], 0x0F */
    a = a + b;                  /* mov eax,[rbp-4]; add eax,[rbp-8]; mov [rbp-4],eax */

    /* 块2: push / pop（观察 RSP 变化 + 栈顶内存） */
    __asm__ volatile(
        "mov $0x11223344, %%rax\n\t"   /* 准备一个特征值 */
        "push %%rax\n\t"               /* RSP -= 8, [RSP] = 0x11223344 */
        "pop %%rcx\n\t"                /* RCX = [RSP], RSP += 8 */
        : : : "rax", "rcx");

    /* 块3: call / ret（调用 add5） */
    int c = add5(a);

    /* 块4: jmp 系列（条件跳转，看标志位） */
    int d;
    if (a > b){                 /* cmp → jg/jle */
        d = 100;
    } else {
        d = 200;
    }

    printf("a=%d b=%d c=%d d=%d\n", a, b, c, d);
    return 0;
}
