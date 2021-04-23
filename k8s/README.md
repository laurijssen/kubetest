# geofriends

* kubectl create deployment http-deployment --image=my-http
* kubectl expose deployment http-deployment --type=NodePort --port=8080
* kubectl edit deployment http-deployment: ImagePullPolicy: never

-----

* vboxmanage list (running)vms
* vboxmanage showvminfo minikube | grep [pP]ort
* vboxmanage controlvm minikube natpf1 "port30092,tcp,,30092,,30092"

-----

* protoc -I protocrepo --grpc_out=/location --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` locationservice.proto
* protoc -I protocrepo --cpp_out=location locationservice.proto
* g++ -o main *.cc -I$HOME/geofriends/location $(pkg-config --cflags --libs grpc++) -lpthread -lprotobuf

-----

create database manually with Azure data studio

Build job createdatabase
build normal docker image
tag for repository
push to repository

* sudo docker build -t createdatabase -f Dockerfile .
* sudo docker tag createdatabase 192.168.56.3:5000/createdatabase
* sudo docker push 192.168.56.3:5000/createdatabase

-----

rewrite history with removed file

* git filter-branch --force --index-filter "git rm --cached --ignore-unmatch Projects/RopsDAL/FFIG/dealer.xml" HEAD
* git push -f
