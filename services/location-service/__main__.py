from concurrent import futures
import grpc

from proto.service_pb2_grpc import add_EchoServicer_to_server
from location_grpc import Echoer

class Server:

    @staticmethod
    def run():
        server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
        add_EchoServicer_to_server(Echoer(), server)
        server.add_insecure_port('[::]:8081')
        server.start()
        server.wait_for_termination()


if __name__ == '__main__':
    print("start server")
    Server.run()