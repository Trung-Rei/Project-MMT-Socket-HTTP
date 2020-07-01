import socket

# server TCP
# cài các chức năng cơ bản của 1 TCP server
# không sử dụng trực tiếp class này, sử dụng các class kế thừa
class MyTCPServer:
    # khởi tạo để lắng nghe tại (HOST, PORT)
    def __init__(self, host = '', port = 80):
        self.host = host
        self.port = port

    def start(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.bind((self.host, self.port))
        s.listen(100) # Nhận tối đa 100 kết nối

        print('Listening at ', s.getsockname())

        while True:
            conn, addr = s.accept() # chấp nhận kết nối
            print('Connected by ', addr)
            data = conn.recv(1024) # nhận dữ liệu từ client

            response = self.handle_request(data) # xử lý dữ liệu

            conn.sendall(response) # gửi dữ liệu đã xử lý về Client và đóng kết nối
            conn.close()

    # Xử lý request từ client (cài đặt chi tiết ở các class kế thừa)
    def handle_request(self, data):
        return data