# FROM alpine:latest as buildlocation
# LABEL description="Build container location service"
# RUN apk update && apk add --no-cache build-base cmake ninja curl gcc git libgcc libtool linux-headers musl-dev protoc
# RUN git clone https://github.com/Microsoft/vcpkg.git
# RUN vcpkg/bootstrap-vcpkg.sh --useSystemBinaries
# RUN vcpkg/vcpkg install --triplet x64-linux grpc
# COPY lib/*.c /
# COPY lib/*.h /
# COPY location/protocrepo/*.cc /
# COPY location/protocrepo/*.h /protocrepo/
# COPY services/location-service/*.c /
# RUN gcc -o /main *.c -O3

FROM alpine:latest as runtime
LABEL description="Run container location service"
RUN apk update && apk add --no-cache libstdc++
COPY --from=buildlocation /main /
ENTRYPOINT ["/main"]
