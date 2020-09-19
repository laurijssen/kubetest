FROM alpine:latest as build
LABEL description="Build container"
RUN apk update && apk add --no-cache build-base cmake curl gcc git libgcc libtool linux-headers musl-dev
COPY *.cc /
COPY *.h /
RUN gcc -o /main *.cc -O3

FROM alpine:latest as runtime
LABEL description="Run container"
RUN apk update && apk add --no-cache libstdc++
COPY --from=build /main /
ENTRYPOINT ["/main"]
