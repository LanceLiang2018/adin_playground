#coding:utf-8
import cv2

def pixelToChr(pixels):
    count = 0
    bits = 0
    for pixel in pixels:
        (b, g, r) = pixel
        if b < 127:
            p = 128
        else:
            p = 0
        p = p >> count
        bits = bits | p
        count += 1
    #return bits
    return chr(bits)
    
def scanFrame(frame):
    (y, x, channel) = frame.shape
    Str = ''
    #chs = []
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
cap = cv2.VideoCapture(r'E:\\orai\test.mp4')
t = int(input("number of flames to play>"))
for i in range(t+1):
    ret, frame = cap.read()
    


