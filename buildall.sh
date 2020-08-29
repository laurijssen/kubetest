#!/bin/bash

# must be sudo so images is taken from local machine not minikube
sudo docker run -v `pwd`:/defs namely/protoc-all -f protocrepo/*.proto -l cpp -o location

eval $(minikube docker-env)

for dir in services/*/ ; do
    if [ -f "$dir/Dockerfile" ]; then
        imagename=$(echo $dir | sed 's/\/$//' | sed 's/services\///')
        echo "Building $imagename"
        docker build -t $imagename -f services/$imagename/Dockerfile .
    fi
done
