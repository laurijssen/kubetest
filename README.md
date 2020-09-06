# kubetest

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
* g++ -o main *.cc -I$HOME/kubetest/location $(pkg-config --cflags --libs grpc++) -lpthread -lprotobuf
