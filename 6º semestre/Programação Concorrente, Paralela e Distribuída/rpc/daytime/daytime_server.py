import xmlrpc.server
from datetime import datetime
import sys

def daytime():
    return datetime.today()

if len(sys.argv) != 2:
    print(f"{sys.argv[0]} <porta>")
    sys.exit(0)

PORTA = int(sys.argv[1])
server = xmlrpc.server.SimpleXMLRPCServer(('', PORTA))
server.register_function(daytime, 'daytime')
server.serve_forever()
