import socket
import time
import json

if __name__ == '__main__':

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #

    server.bind(("localhost",8888))
    #

    server.listen(0)
    #backlog指定最多允许多少个客户连接到服务器。
    #backlog应该理解为阻塞队列的长度，总共与服务器连接的客户端一共有 backlog + 1 个。
    #收到连接请求后，这些请求需要排队，如果队列满，就拒绝请求

    connection , address = server.accept()
    #

    print(connection ,address)
    num = 0
    while True:

        recv_data = connection.recv(1024).decode('UTF-8', 'ignore').strip(b'\x00'.decode())
        if not recv_data:
            break
        num = num + 1
        print("接受到的数据")
        print(recv_data)


        #解析接收到的json格式的文件
        data_json = json.loads(recv_data)
        print("解析后的数据")
        print(data_json)
        print(data_json['name'])


        #打包文件发送到C++环境

        #将数据打包为json
        FlyCtrlCmd={
            "fStickLat": 0.5,
            "fStickLon": 0.5,
            "fThrottle": 0.5,
            "m_fRudder": 0.5,
        }
        FlyCtrlCmd_json = json.dumps(FlyCtrlCmd)
        print("发送的数据")
        print(FlyCtrlCmd_json)

        #发送数据
        #将数据由str编码为bytes字节流 encode()
        FlyCtrlCmd_json_bytes = FlyCtrlCmd_json.encode('UTF-8', 'ignore')
        connection.send(FlyCtrlCmd_json_bytes)


        time.sleep(0.5)

    connection.close()