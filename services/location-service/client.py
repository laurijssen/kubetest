from __future__ import print_function
import logging
import socket

import grpc

from proto.service_pb2 import EchoRequest
from proto.service_pb2_grpc import EchoStub

ip = [i[4][0] for i in socket.getaddrinfo('kubemaster', None)][0]

def run():
    with grpc.insecure_channel(f'{ip}:30700') as channel:
        stub = EchoStub(channel)
        response = stub.Reply(EchoRequest(message='Hoppa'))
    print("Echo client received: " + response.message)


if __name__ == '__main__':
    logging.basicConfig()
    run()