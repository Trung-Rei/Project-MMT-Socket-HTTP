# class parse request từ chuỗi
class HTTPRequestParser:
    def __init__(self, data):
        self.method = None # phương thức
        self.uri = None # đường dẫn yêu cầu
        self.query_string = None # chuỗi query
        self.http_version = '1.1' # mặc định là HTTP/1.1 nếu request ko để
        self.headers = {} # các header
        self.body = None # phần thân request

        # call self.parse method to parse the request data
        self.parse(data)

    def parse(self, data):
        lines = data.split('\r\n', 1)

        request_line = lines[0]
        self.parse_request_line(request_line)
        
        lines = lines[1].split('\r\n\r\n')
        if lines[1] != '':
            self.body = lines[1]

    # parse dòng đầu của request
    def parse_request_line(self, request_line):
        words = request_line.split(' ')
        self.method = words[0]
        self.uri = words[1].split('?')
        if len(self.uri) > 1:
            self.query_string = self.uri[1]
        self.uri = self.uri[0]

        if len(words) > 2:
            self.http_version = words[2]