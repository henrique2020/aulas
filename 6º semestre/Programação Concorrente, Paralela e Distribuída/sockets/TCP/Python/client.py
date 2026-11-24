import socket
import sys

if len(sys.argv) != 4:
    print(f"{sys.argv[0]} <ip> <porta> \"<mensagem>\"")
    sys.exit(0)

ip    = sys.argv[1]
porta = int(sys.argv[2])
msg   = sys.argv[3] 

soquete = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
soquete.connect((ip, porta))

soquete.send(msg.encode())

msg = soquete.recv(1024).decode()
print(msg)

soquete.close()