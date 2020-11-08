FROM grpcimage as buildlocation
LABEL description="Build container location service"
RUN apt-get update && apt-get install -y autoconf automake build-essential cmake curl g++ git libtool make pkg-config unzip \
    && apt-get clean

FROM debian:buster-slim as runtime
LABEL description="Run container location service"
RUN apt-get update && apt-get install libstdc++
COPY --from=buildlocation /main /
ENTRYPOINT ["/main"]
