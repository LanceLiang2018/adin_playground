import socket
host = socket.gethostname()
port = int(input('port>'))
sendStr = input('msg to be sent>')
buffsize = 1024
#print(socket.gethostbyname(socket.getfqdn(socket.gethostname())))
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host, port))
s.listen(5)
cliSock, cliAddr = s.accept()
print('connet from:', cliAddr)
while True:
    data = cliSock.recv(buffsize).decode('utf-8')
    if not data:
        break
    cliSock.send(sendStr.encode('utf-8'))
cliSock.close()
print('goodbye')
s.close()
