FROM debian:buster-slim as buildlocation
LABEL description="Build container location service"
RUN apt-get update && apt-get install -y autoconf automake build-essential cmake curl g++ git libtool make pkg-config unzip \
    && apt-get clean

ENV GRPC_RELEASE_TAG v1.16.0
ENV LOCATION_BUILD_PATH /usr/local/location

RUN git clone -b ${GRPC_RELEASE_TAG} https://github.com/grpc/grpc /var/local/git/grpc && \
    cd /var/local/git/grpc && \
    git submodule update --init --recursive

RUN echo "-- installing protobuf" && \
    cd /var/local/git/grpc/third_party/protobuf && \
    ./autogen.sh && ./configure --enable-shared && \
    make -j$(nproc) && make -j$(nproc) check && make install && ldconfig

RUN echo "-- installing grpc" && \
    cd /var/local/git/grpc && \
    make -j$(nproc) && make install && ldconfig

COPY *.cc /
COPY *.h /
RUN g++ -o /main *.cc

FROM debian:buster-slim as runtime
LABEL description="Run container location service"
RUN apt-get update && apt-get install libstdc++
COPY --from=buildlocation /main /
ENTRYPOINT ["/main"]
