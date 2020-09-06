#!/bin/bash

#eval $(minikube docker-env)

protoc -I ./protocrepo --grpc_out=location --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./protocrepo/locationservice.proto 
protoc -I ./protocrepo --cpp_out=location ./protocrepo/locationservice.proto

for dir in services/*/ ; do
    if [ -f "$dir/Dockerfile" ]; then
        imagename=$(echo $dir | sed 's/\/$//
                                     s/services\///')
        echo "Building $imagename"
        pushd services/$imagename
        sudo docker build -t $imagename -f Dockerfile .
        popd
    fi
done
