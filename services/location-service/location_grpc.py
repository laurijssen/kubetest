import proto.service_pb2_grpc
import proto.service_pb2

class Echoer(proto.service_pb2_grpc.EchoServicer):
    def Reply(self, request, context):
        reply = f'\nYou said: {request.message}' * 10
        return proto.service_pb2.EchoReply(message=reply)
