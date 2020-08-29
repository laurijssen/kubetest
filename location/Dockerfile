FROM alpine:latest as buildlocation
LABEL description="Build container location service"
RUN apk update && apk add --no-cache build-base cmake curl gcc git libgcc libtool linux-headers musl-dev
COPY ../lib/*.c /
COPY ../lib/*.h /
COPY *.c /
COPY *.h /
RUN gcc -o /main *.c -O3
#COPY CMakeLists.txt /
#RUN cd /
#RUN cmake -DCMAKE_BUILD_TYPE=Release .
#RUN cmake --build .

FROM alpine:latest as runtime
LABEL description="Run container location service"
RUN apk update && apk add --no-cache libstdc++
COPY --from=buildlocation /main /
ENTRYPOINT ["/main"]
