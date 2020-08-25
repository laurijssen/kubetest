FROM alpine:latest as build2
LABEL description="Build container"
RUN apk update && apk add --no-cache build-base cmake curl gcc git libgcc libtool linux-headers musl-dev
COPY *.c /
COPY *.h /
COPY CMakeLists.txt /
#RUN gcc -o /main *.c -O3
RUN cd /
RUN cmake -DCMAKE_BUILD_TYPE=Release .
RUN cmake --build .

FROM alpine:latest as runtime
LABEL description="Run container"
RUN apk update && apk add --no-cache libstdc++
COPY --from=build2 /main /
ENTRYPOINT ["/main"]
