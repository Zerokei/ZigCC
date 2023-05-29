# ZigCC: A Simplified C++ Compiler using antlr4 and llvm
## 2022-2023学年春夏学期浙江大学编译原理课程 Project

## 项目架构
- antlr4：前端 antlr4 相关库
    - ZigCCLexer/ZigCCParser.g4：antlr4 官方提供的 C++14 的词法分析和语法分析文件
    - generated：antlr4 生成的词法分析、语法分析 C++ 代码（部分已经移入 src/include 文件夹的 grammar 子文件夹下使用）
    - dist/libantlr4-runtime.so.4.12.0：通过编译上述运行时文件得到的动态链接库，实际程序运行依靠此文件
    - include：项目需要使用的 antlr4 运行时库
- include：项目所需头文件
    - ObjectEmitter.h 将 AST 转化得到的内存中的 llvm IR 转换为可读的 llvm IR 以及目标文件 .o
    - JIT.h：JIT 实现对 .o 文件的链接，生成可执行文件
- src：项目源代码
    - main.cpp：主函数，读入输入的文件，处理输入参数，调用函数完成整体流程生成目标文件后退出
    - grammar：antlr4 生成的词法分析和语法分析代码以及 AST 转 llvm IR 的代码
        - Visitor.h/cpp：功能请参考 Java 访问者模式，注意其中每个函数与 parser 中一个语法规则对应，通过 visitor 遍历语法树，在每个节点上进行特定操作生成 llvm IR
    - semantic：
        - Scope.h/cpp：定义了 Scope 存放每个大括号内的局部变量等，同时也管理当前函数以及全局定义的类、结构体、联合等结构
- test：测试文件

## 编译运行

```bash
# 根据 dockerfile 生成运行时环境
$ docker build -t zigcc:v1.0 .
# 进入 docker 镜像进行调试
$ docker run -it -v ~/ZigCC:/zigcc --rm zigcc:v1.0
# 编译 zigcc
$ make clean && make -j
# 编译 riscv 可执行文件
$ bin/debug/zigcc test/quicksort/quicksort.c
# qemu 运行可执行文件
$ qemu-riscv64-static a.out
```
