import socket
import sys
import time
MAQUINA = 'vb-debian'

if len(sys.argv) != 2:
    print(f"{sys.argv[0]} <porta>")
    sys.exit(0)

ip    = 'localhost'
porta = int(sys.argv[1])

soquete = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
soquete.bind((ip, porta))
soquete.listen(50)  # Fila de conexão



while True:
    s, _ = soquete.accept() #socket de conexção, cliente (não utilizado no TCP)

    msg = s.recv(1024).decode()
    print(f"Recebi: {msg}")
    s.send(f"Recebido por [{MAQUINA}]".encode())
    s.close()

soquete.close()