#from __future__ import print_function
import logging
import socket

import grpc

from proto.service_pb2 import EchoRequest
from proto.service_pb2 import Position
from proto.service_pb2_grpc import LocationStub

ip = [i[4][0] for i in socket.getaddrinfo('kubemaster', None)][0]

def run():
    with grpc.insecure_channel(f'{ip}:30700') as channel:
        stub = LocationStub(channel)

        response = stub.Reply(EchoRequest(message='Hoppa'))
        print("Client received: " + response.message)

        response = stub.Store(Position(userid=1, lon=4.12342, lat=51.14566))
        print("Store received " + response.message)



if __name__ == '__main__':
    logging.basicConfig()
    run()