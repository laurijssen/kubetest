# kubetest

* kubectl create deployment http-deployment --image=my-http
* kubectl expose deployment http-deployment --type=NodePort --port=8080
* kubectl edit deployment http-deployment: ImagePullPolicy: never

-----

* vboxmanage list (running)vms
* vboxmanage showvminfo minikube | grep [pP]ort
* vboxmanage controlvm minikube natpf1 "port30092,tcp,,30092,,30092"

-----

* g++ -o main *.cc $HOME/.local/lib/*.a -I$HOME/.local/include -I$HOME/kubetest/location -L$HOME/.local/lib -lprotobuf -lcrypto -lpthread -lgpr -labsl_str_format_internal -labsl_base -labsl_int128 -labsl_strings -labsl_time -labsl_time_zone -lcares -labsl_log_severity -labsl_raw_logging_internal -lupb -laddress_sorting -labsl_throw_delegate -labsl_strings_internal
