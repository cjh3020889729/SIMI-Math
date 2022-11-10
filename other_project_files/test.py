import numpy as np
import cv2

if __name__ == "__main__":
    cap = cv2.VideoCapture("rtsp://admin:123456@192.168.137.2:554/stream1")
    while cap.isOpened():
        flag, frame = cap.read()
        if not flag:
            print("cap can't read frame.")
        
        # frame = cv2.resize(frame, (1080, 960))
        # print(frame.shape)
        cv2.imwrite(frame, 'temp.png')
        if cv2.waitKey(1)&0xFF==ord('q'):
            break
    print("finished opencv video.")
    cap.release()
    cv2.destroyAllWindows()