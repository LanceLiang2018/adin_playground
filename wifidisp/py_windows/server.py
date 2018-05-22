#coding:utf-8
import cv2
import socket

def pixelToChr(pixels):
    count = 0
    bits = 0
    for pixel in pixels:
        (b, g, r) = pixel
        '''if b < 127:
            p = 128
        else:
            p = 0
        p = p >> count'''
        if b < 127:
            p = 1
        else:
            p = 0
        p = p << count
        bits = bits | p
        count += 1
    #return bits
    return chr(bits)
    
def scanFrame(frame):
    (y, x, channel) = frame.shape
    Str = ''
    chs = []
    for yy in range(y):
        for x0 in range(0, x, 8):
            pixels = []
            for i in range(8):
                pixels.append(frame[yy, x0 + i])
            #chs.append(pixelToChr(pixels))
            Str += pixelToChr(pixels)
        yy += 1
    #return chs
    return Str



#main
filename = input('filename>')
cap = cv2.VideoCapture(r'E:\\orai\\' + filename)

host = socket.gethostname()
port = int(input('port>'))
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host, port))
s.listen(1)
print('waiting for client...')
cliSock, cliAddr = s.accept()
print(str(cliAddr) + ' connected')

t = int(input("number of flames to play>"))
for i in range(t+1):
    ret, frame = cap.read()
    frame = cv2.resize(frame, (128,64))
    #cv2.imshow(filename, frame)
    cliSock.send(scanFrame(frame).encode())
print('goodbye')
    


