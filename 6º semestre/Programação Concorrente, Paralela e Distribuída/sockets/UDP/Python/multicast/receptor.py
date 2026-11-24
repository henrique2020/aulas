import socket

GRUPO = '224.0.0.1'
PORTA = 5000

soquete = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
soquete.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
soquete.bind(('', PORTA))

mreq = socket.inet_aton(GRUPO) + socket.inet_aton('0.0.0.0')
soquete.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

while True:
    msg, endereco = soquete.recvfrom(1024)
    print(f"Mensagem: {msg.decode()} ({endereco})")