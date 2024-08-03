import matplotlib.pyplot as plt
import pyaudio
import socket

FORMAT = 32
UDP_PORT = 4321
RATE = 10000

hostname=socket.gethostname()
UDP_IP=socket.gethostbyname(hostname)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

p = pyaudio.PyAudio()
stream = p.open(format=FORMAT, channels=1, rate=RATE, output=True)

def main():
    try:
        while True:
            i=0
            audio = []
            while i<10:
                i+=1
                data = sock.recvfrom(1500)[0]
                _data = [item if item > 70 else 170 for item in data]
                audio.extend(_data)
            stream.write(bytes(audio))
    except Exception as e:
        return f"[ERROR] : {e}"


if __name__ == "__main__":
    main()
    

    

