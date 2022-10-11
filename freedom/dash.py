from base64 import encode
import socket
HOST = "0.0.0.0"
MYTCP_PORT = 8080
import multiprocessing as mp
import struct
GET_OPERATIONG_CODE = 0

nameToIPMap ={
    "harrisDB": {
        "host" : "0.0.0.0",
        "port" : 8080
    }
}

def encode(value):
    if type(value) == str:
        s = bytes(value, 'utf-8') 
        encodedData = struct.pack("%ds" % (len(s),) ,s) + bytes('\x00', 'utf-8')
        return encodedData

class dashDB:
    def __init__(self,dbName):
        self.host = nameToIPMap[dbName]["host"]
        self.port = nameToIPMap[dbName]["port"]
        self.sock = None

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((HOST, MYTCP_PORT))

    def disconnect(self):
        self.sock.close()
        self.sock = None
        
    def get(self, key):
        encodedKey = encode(key)
        data = struct.pack("h",GET_OPERATIONG_CODE) + encodedKey
        dataLength = len(data)
        data = struct.pack("I", dataLength) + data
        if self.sock:
            self.sock.send(data)
        validate = self.sock.recv(1024)
        print(validate)
            
    
    def put(key, value):
        struct.pack()
        print("KEY")

if __name__ == '__main__':
    mydb = dashDB("harrisDB")
    mydb.connect()
    mydb.get("harris")

            
    