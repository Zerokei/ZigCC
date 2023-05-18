# ZigCC: A Simplified C++ Compiler using antlr4 and llvm
## 2022-2023学年春夏学期浙江大学编译原理课程 Project

## 项目架构
- antlr4：前端 antlr4 相关库
    - ZigCCLexer/ZigCCParser.g4：antlr4 官方提供的 C++14 的词法分析和语法分析文件
    - generated：antlr4 生成的词法分析、语法分析 C++ 代码（部分已经移入 src/include 文件夹的 grammar 子文件夹下使用）
    - include：项目需要使用的 antlr4 运行时库
- include：项目所需头文件
- src：项目源代码
    - main.cpp：主函数，读入输入的文件，处理输入参数，调用函数完成整体流程生成目标文件后退出
    - utils.h/cpp：对 terminal 的处理函数以及 container_cast utility
    - StaticAnalysis.h/cpp：
    - Visitor.h/cpp：功能请参考 Java 访问者模式，注意其中每个函数与 parser 中一个语法规则对应，并且与 SyntaxModel 文件夹中一个文件对应
    - grammar：antlr4 生成的词法分析和语法分析代码
    - IR：
    - SyntaxModel：
        - Program.h/cpp：对整个文件的分解（包括 include、function 和 definition）
- test：测试文件

## 编译运行

```bash
# 根据 dockerfile 生成运行时环境
$ docker build -t zigcc:v1.0 .
```
