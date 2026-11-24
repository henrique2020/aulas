import socket

GRUPO = '224.0.0.1'
PORTA = 5000

soquete = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
soquete.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 1)

msg = 'multicast'
soquete.sendto(msg.encode(), (GRUPO, PORTA))

soquete.close()