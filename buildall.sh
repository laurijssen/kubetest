#!/bin/bash

export PKG_CONFIG_PATH=/home/laurijssen/.local/lib/pkgconfig

for dir in services/*/ ; do
    if [ -f "$dir/Dockerfile" ]; then
        imagename=$(echo $dir | sed 's/\/$//
                                     s/services\///')

        echo "Building $imagename"

        pushd services/$imagename

        if [ -f ./proto/service.proto ]; then
            python3 -m grpc_tools.protoc proto/*.proto --python_out=. --proto_path=. --grpc_python_out=.
            if [ $? -ne 0 ]; then
                echo "Build grpc server failed"
                exit 1
            fi

            sed -i -E 's/^import.*_pb2/from . \0/' ./proto/*.py
        fi
       
        if [ -f Dockerfile ]; then
            sudo docker build -t $imagename -f Dockerfile .
            sudo docker tag $imagename 192.168.56.3:5000/$imagename
            sudo docker push 192.168.56.3:5000/$imagename
        fi

        popd
    fi
done

for dir in jobs/*/ ; do
    echo $dir
    if [ -f "$dir/Dockerfile" ]; then
        imagename=$(echo $dir | sed 's/\/$//
                                     s/jobs\///')

        echo "Building $imagename"

        pushd jobs/$imagename

        if [ -f Dockerfile ]; then
            sudo docker build -t $imagename -f Dockerfile .
            sudo docker tag $imagename 192.168.56.3:5000/$imagename
            sudo docker push 192.168.56.3:5000/$imagename
        fi

        popd
    fi
done
