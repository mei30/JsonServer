import socket
import threading
import json

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 2000  # The port used by the server


data = ""
with open('sample.json', "r") as fp:
    data = json.load(fp)
    print(data)

    


def send_data():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(json.dumps(data, indent=2).encode('utf-8'))
        s.close()

if __name__ == "__main__":
    threads = []

    for i in range(1, 10):
        thread = threading.Thread(target=send_data())
        threads.append(thread)

    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()
