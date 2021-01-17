import pyodbc
import proto.service_pb2_grpc
import proto.service_pb2

class Locator(proto.service_pb2_grpc.LocationServicer):    

    i = 0

    def Reply(self, request, context):
        reply = f'\nYou said: {request.message} {self.i}' * 10
        self.i += 1
        return proto.service_pb2.EchoReply(message=reply)

    def Store(self, request, context):
        reply = f'\n: {request.lon} {request.lat}'

        server = '192.168.56.3,31433' 
        database = 'geocachefriends' 
        username = 'sa' 
        password = os.getenv('SA_PASSWORD')

        cnxn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER='+server+';DATABASE='+database+';UID='+username+';PWD='+ password)
        cursor = cnxn.cursor()

        return proto.service_pb2.PositionReply(message=reply)

