# 指定基础镜像 
FROM ubuntu:22.04 
# 设置工作目录 
WORKDIR /zigcc 
# 复制应用程序文件到镜像中 
COPY . /zigcc 
# 解决一些问题
# RUN apt-get update
# RUN apt-get install -y gnupg 
# 更换 Tsinghua 镜像软件源
# RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 3B4FE6ACC0B21F32
# RUN echo "deb http://mirrors.zju.edu.cn/ubuntu/ bionic main restricted universe multiverse" > /etc/apt/sources.list
# RUN echo "deb http://mirrors.zju.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse" >> /etc/apt/sources.list
# RUN echo "deb http://mirrors.zju.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse" >> /etc/apt/sources.list
# RUN echo "deb http://mirrors.zju.edu.cn/ubuntu/ bionic-security main restricted universe multiverse" >> /etc/apt/sources.list
# ADD docker/sources.list /etc/apt
# 安装所需的依赖包（示例） 
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y llvm
RUN apt-get install -y gcc
RUN apt-get install -y g++
RUN apt-get install -y vim
	
# 设置环境变量（示例） 
# ENV ENV_VARIABLE=value 
# 定义容器启动时要执行的命令 
# CMD ["/app/myapp"] 
# 暴露容器的端口（示例） 
# EXPOSE 8080
