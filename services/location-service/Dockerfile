FROM alpine:latest as buildlocation
LABEL description="Build container location service"
RUN apk update && apk add --no-cache build-base cmake curl gcc git libgcc libtool linux-headers musl-dev protoc
COPY lib/*.c /
COPY lib/*.h /
COPY location/protocrepo/*.cc /
COPY location/protocrepo/*.h /protocrepo/
COPY services/location-service/*.c /
RUN gcc -o /main *.c -O3

FROM alpine:latest as runtime
LABEL description="Run container location service"
RUN apk update && apk add --no-cache libstdc++
COPY --from=buildlocation /main /
ENTRYPOINT ["/main"]
