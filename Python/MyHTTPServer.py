import MyBaseHTTPServer
import os # gọi hàm os.path.exists()

# class HTTP server cài đặt cụ thể các phương thức HTTP
# theo yêu cầu của đề bài.
class MyHTTPServer(MyBaseHTTPServer.MyBaseHTTPServer):
    is_logged_in = False # cờ trạng thái đăng nhập

    # xử lý method GET của request
    def handle_GET(self, request):
        filename = request.uri.strip('/')

        if filename == '': # địa chỉ mặc định khi truy cập vào website
            return self.HTTP_301_handler('/index.html')
        if not os.path.exists('HTML\\' + filename): # không tồn tại file
            return self.HTTP_404_handler()
        # khi người dùng cố gắng truy cập info.html nhưng chưa đăng nhập
        if filename == 'info.html' and not self.is_logged_in:
            return self.HTTP_303_handler('/index.html')
        # người dùng truy cập info.html sau khi đăng nhập
        if filename == 'info.html':
            self.is_logged_in = False # cờ trạng thái trở lại chưa đăng nhập

        response_line = self.response_line(200)
        response_headers = self.response_headers()
        # lấy dữ liệu từ file được yêu cầu
        with open('HTML\\' + filename, 'rb') as f:
            response_body = f.read()

        blank_line = "\r\n"

        response = "%s%s%s" % (
            response_line, 
            response_headers, 
            blank_line
        )
        response = response.encode() + response_body

        return response

    # xử lý method POST của request
    def handle_POST(self, request):
        # lấy username và password từ phần thân của request
        tmp = request.body.split('&')
        username = tmp[0].split('=')[1]
        password = tmp[1].split('=')[1]

        # nếu đúng tài khoản mật khẩu thì redirect đến info.html
        # với cờ trạng thái đăng nhập bật
        if (username, password) == ('admin', 'admin'):
            self.is_logged_in = True
            return self.HTTP_303_handler('/info.html')
        
        # nếu sai tk và mk thì lỗi 404
        return self.HTTP_404_handler()

    # redirect bằng mã lỗi 301 với đường dẫn mới
    def HTTP_301_handler(self, newLocation):
        response_line = self.response_line(301)
        response_headers = self.response_headers({'Location': newLocation})
        blank_line = "\r\n"

        response = "%s%s%s" % (
            response_line, 
            response_headers, 
            blank_line
        )
        response = response.encode()

        return response

    # redirect bằng mã lỗi 303 với đường dẫn mới
    def HTTP_303_handler(self, newLocation):
        response_line = self.response_line(303)
        response_headers = self.response_headers({'Location': newLocation})
        blank_line = "\r\n"

        response = "%s%s%s" % (
            response_line, 
            response_headers, 
            blank_line
        )
        response = response.encode()

        return response

    # báo lỗi 404
    def HTTP_404_handler(self):
        response_line = self.response_line(404)
        response_headers = self.response_headers()
        blank_line = "\r\n"

        with open('HTML\\404.html', 'rb') as f:
            response_body = f.read()

        response = "%s%s%s" % (
            response_line, 
            response_headers, 
            blank_line
        )
        response = response.encode() + response_body

        return response
