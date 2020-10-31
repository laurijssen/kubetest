kubectl delete -f create-deployment.yaml 
sudo docker build -t my-http1 -f Dockerfile .
sudo docker tag my-http1 192.168.56.3:5000/my-http1
sudo docker push 192.168.56.3:5000/my-http1
kubectl apply -f create-deployment.yaml 