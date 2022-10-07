import socket
HOST = "0.0.0.0"
MYTCP_PORT = 8080
import multiprocessing as mp

if __name__ == '__main__':
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        receivedMsg = ""
        sock.connect((HOST, MYTCP_PORT))
        while receivedMsg != "exit":
            message = input()
            sock.send(message.encode())
            receivedMsg = sock.recv(2048)
            print(receivedMsg)
            if message == "exit":
                break
        sock.close()
        
                