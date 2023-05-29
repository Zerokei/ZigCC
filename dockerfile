# 指定基础镜像 
FROM ubuntu:22.04 
# 设置工作目录 
WORKDIR /zigcc 
# 复制应用程序文件到镜像中 
COPY . /zigcc 
# 解决一些问题
# RUN apt-get install -y sed
RUN sed -i 's@//.*archive.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list
# 安装所需的依赖包（示例） 
RUN apt-get update
RUN apt-get install -y llvm
RUN apt-get install -y g++
RUN apt-get install -y gcc
RUN apt-get install -y make
RUN apt-get install -y vim
RUN apt-get install -y gcc-riscv64-linux-gnu gdb-multiarch
RUN apt-get install -y clang qemu-user-static
RUN cp /usr/riscv64-linux-gnu/lib/libc.so.6 /lib/libc.so.6
RUN cp /usr/riscv64-linux-gnu/lib/ld-linux-riscv64-lp64d.so.1 /lib/ld-linux-riscv64-lp64d.so.1


RUN echo "export LD_LIBRARY_PATH=/zigcc/antlr4/dist" >> ~/.bashrc

# 设置环境变量（示例） 
# ENV ENV_VARIABLE=value 
# 定义容器启动时要执行的命令 
# CMD ["make"]
# 暴露容器的端口（示例） 
# EXPOSE 8080
