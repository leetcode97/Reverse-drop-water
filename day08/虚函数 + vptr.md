# 虚函数是干嘛的？
**<font style="color:rgb(51, 51, 51);">"编译时定不了调谁，只能运行时再查" = 虚函数存在的全部原因 = C++ 多态的底层机制。</font>**

# <font style="color:rgb(51, 51, 51);">vptr</font>
对象的开头会多出一个指针（vptr），64位为8个字节，32位为4个字节，这个指针指向这个类的虚表

# 虚表
虚表就是一个函数地址表

# 虚调用
**识别特征（验收核心）：**

|  | 形态 | 判断 |
| --- | --- | --- |
| 普通成员调用 | `mov rcx,this` → `call 固定地址` | 地址写死 = this 调用 |
| 虚调用 | `[this]` 取 vptr → `[vptr]` 取地址 → `call 寄存器` | **两次间接** = 走了虚表 |


# 问答题
1. 为什么 `a->speak()` 编译时定不了 call 谁的地址？→ 多态：a 可能是 Animal 也可能是 Dog，运行时才知道；虚函数就是为此存在的。
2. <font style="color:rgb(51, 51, 51);">类带虚函数后，对象多出什么？占几个字节？→ vptr，指向虚表（64 位 8 字节 / 32 位 4 字节）。</font>
3. <font style="color:rgb(51, 51, 51);">虚表里存什么？Dog 的虚表 speak 和 move 两项分别指向谁？→ 函数地址；speak 指 Dog::speak（覆盖过），move 指 Animal::move（没覆盖）。</font>
4. <font style="color:rgb(51, 51, 51);">构造函数怎么和虚表发生关系？→ 把本类虚表地址写进对象开头的 vptr。</font>
5. <font style="color:rgb(51, 51, 51);">怎么从反汇编认出"走了虚表"？→ 两次间接：</font>`<font style="color:rgb(51, 51, 51);">mov rax,[this]</font>`<font style="color:rgb(51, 51, 51);">（取 vptr）→ </font>`<font style="color:rgb(51, 51, 51);">mov rdx,[rax]</font>`<font style="color:rgb(51, 51, 51);">（查表取地址）→ </font>`<font style="color:rgb(51, 51, 51);">call rdx</font>`<font style="color:rgb(51, 51, 51);">；而普通 this 调用是 </font>`<font style="color:rgb(51, 51, 51);">call 固定地址</font>`<font style="color:rgb(51, 51, 51);">。</font>

