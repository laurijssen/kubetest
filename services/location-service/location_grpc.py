import proto.service_pb2_grpc
import proto.service_pb2

class Echoer(proto.service_pb2_grpc.EchoServicer):    

    i = 0

    def Reply(self, request, context):
        reply = f'\nYou said: {request.message} {self.i}' * 10
        self.i += 1
        return proto.service_pb2.EchoReply(message=reply)
