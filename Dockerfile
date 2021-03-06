FROM ubuntu:20.04

# to prevent tzdata from requiring user input
# https://askubuntu.com/a/1013396/415610
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y git gcc g++ cmake
RUN ln -s /usr/lib/x86_64-linux-gnu/libgraphblas.so.3 /usr/lib/x86_64-linux-gnu/libgraphblas.so

WORKDIR /opt
RUN git clone --depth 1 --branch v3.3.1 https://github.com/DrTimothyAldenDavis/GraphBLAS
WORKDIR /opt/GraphBLAS/build
RUN cmake .. -DGBCOMPACT=1
RUN JOBS=$(nproc) make install
RUN ldconfig

WORKDIR /opt
RUN git clone https://github.com/GraphBLAS/LAGraph

WORKDIR /opt/LAGraph/build
RUN cmake ..
RUN JOBS=$(nproc) make install
RUN ldconfig

COPY . /opt/sigmod14-pc
WORKDIR /opt/sigmod14-pc/cpp

RUN export CPATH=/opt/GraphBLAS/Include/ && mkdir -p cmake-build-release && cd cmake-build-release && cmake -DCMAKE_BUILD_TYPE=Release .. && make
#RUN ./sigmod2014pc_cpp
