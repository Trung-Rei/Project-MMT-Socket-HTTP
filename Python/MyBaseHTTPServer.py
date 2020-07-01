import MyTCPServer
import MyHTTPRequestParser

# class HTTP server cơ bản kế thừa TCP server class
# cài đặt chi tiết HTTP server, xử lý 1 số response cơ bản
# chưa cài đặt các method cụ thể (cài đặt chi tiết theo yêu cầu cụ thể của server
# ở các class kế thừa)
# không sử dụng trực tiếp class này
class MyBaseHTTPServer(MyTCPServer.MyTCPServer):
    # các header của response
    headers = {
        'Server': 'Rei-Server',
        'Connection': 'close'
    }
    statusCodes = {
        200: 'OK',
        404: 'Not Found',
        400: 'Bad Request',
        501: 'Not Implemented',
        301: 'Moved Permanently',
        303: 'See Other',
    }
    
    # nhận request từ data, trả về response
    def handle_request(self, data):
        try:
            # parse request từ data
            request = MyHTTPRequestParser.HTTPRequestParser(data.decode())
        except:
            return self.HTTP_400_handler() # request ko đúng theo cấu trúc của http

        try:
            # lấy hàm xử lý yêu cầu cụ thể request
            handler = getattr(self, 'handle_%s' % request.method)
        except AttributeError:
            return self.HTTP_501_handler() # method chưa cài đặt xử lý
            
        return handler(request)

    # trả về chuỗi response line theo statusCode
    def response_line(self, statusCode):
        reason = self.statusCodes[statusCode]
        return "HTTP/1.1 %s %s\r\n" % (statusCode, reason)

    # trả về chuỗi response headers
    def response_headers(self, extraHeaders = None):
        headers_copy = self.headers.copy()
        if extraHeaders != None: # thêm các header khác nếu có
            headers_copy.update(extraHeaders)

        headers = ''

        for h in headers_copy:
            headers += "%s: %s\r\n" % (h, headers_copy[h])
        return headers

    # response với statusCode = 400
    def HTTP_400_handler(self):
        response_line = self.response_line(400)
        response_headers = self.response_headers()
        blank_line = "\r\n"

        response = "%s%s%s" % (
            response_line, 
            response_headers, 
            blank_line
        )
        response = response.encode()

        return response

    # response với statusCode = 501
    def HTTP_501_handler(self):
        response_line = self.response_line(501)
        response_headers = self.response_headers()
        blank_line = "\r\n"

        response = "%s%s%s" % (
            response_line, 
            response_headers, 
            blank_line
        )
        response = response.encode()

        return response
