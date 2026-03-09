import os, sys
from http.server import HTTPServer, CGIHTTPRequestHandler

# Настройки сервера
webdir = '.'  # Каталог с файлами HTML и подкаталогом cgi-bin
port = 80     # Порт по умолчанию (http://localhost/)

# Аргументы командной строки
if len(sys.argv) > 1: webdir = sys.argv[1]    # Каталог
if len(sys.argv) > 2: port = int(sys.argv[2]) # Порт

print(f'webdir "{webdir}", port {port}')
os.chdir(webdir)  # Перейти в корневой веб-каталог

# Запуск сервера
srvraddr = ('', port)
srvrobj = HTTPServer(srvraddr, CGIHTTPRequestHandler)
srvrobj.serve_forever()  # Сервер работает до завершения