import socket
import sys

if len(sys.argv) != 2:
    print(f"{sys.argv[0]} <porta>")
    sys.exit(0)

ip    = ''
porta = int(sys.argv[1])

soquete = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
soquete.bind((ip, porta))

while True:
    msg, cliente = soquete.recvfrom(1024)
    print(f"Recebi: {msg.decode()} | Origem: {cliente}")
    soquete.sendto("Recebi confia".encode(), cliente)

soquete.close()