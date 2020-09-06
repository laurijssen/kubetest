# FROM alpine:latest as buildlocation
# LABEL description="Build container location service"
# RUN apk update && apk add --no-cache build-base curl g++ git libgcc libtool linux-headers musl-dev
# COPY *.cc /
# COPY *.h /
# RUN g++ -o /main *.cc -I/home/laurijssen/.local/include/google/protobuf

FROM alpine:latest as runtime
LABEL description="Run container location service"
RUN apk update && apk add --no-cache libstdc++
COPY bin/main /
ENTRYPOINT ["/main"]
