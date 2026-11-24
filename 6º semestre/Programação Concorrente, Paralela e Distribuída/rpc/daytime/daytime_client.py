import xmlrpc.client
import sys

if len(sys.argv) != 3:
    print(f"{sys.argv[0]} <ip> <porta>")
    sys.exit(0)

server = xmlrpc.client.ServerProxy("http://{IP}:{PORTA}".format(IP=sys.argv[1], PORTA=sys.argv[2]))
print(f"{server.daytime()}")