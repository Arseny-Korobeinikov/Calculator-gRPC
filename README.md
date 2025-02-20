# Руководство по использованию 
## 1. Настройте своё окружение
```
<b><pre>gRPC</pre></b>
```
Инструкция для Windows (через vcpkg):
### Шаг 1. Установка vcpkg:
Откройте PowerShell от имени администратора и выполните:
```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkgcmake --build . --config Release
.\bootstrap-vcpkg.bat
```
После этого в папке ```vcpkg/``` появится исполняемый файл ```vcpkg.exe```.
### Шаг 2: Установите gRPC
```
.\vcpkg install grpc:x64-windows
```
Это скачает и соберет gRPC вместе со всеми необходимыми библиотеками (protobuf, abseil, openssl и т. д.).
## 2. Сгенерируйте C++ файлы с помощью ```protoc```:
```
protoc --grpc_out=. --cpp_out=. --plugin=protoc-gen-grpc=C:/path/to/vcpkg/installed/x64-windows/tools/grpc/grpc_cpp_plugin.exe calculator.proto
```
C:/path/to/ нужно заменить на путь до vcpkg! (У меня это "C:/Users/arsen/vcpkg/")

Это создаст файлы ```calculator.pb.cc```, ```calculator.pb.h```, ```calculator.grpc.pb.cc```, ```calculator.grpc.pb.h```.
## 3. Создайте проект с помощью ```CMake```
1. Настройте сборку:
```
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```
C:/path/to/ нужно заменить на путь до vcpkg!

2. Создайте проект:
```
cmake --build . --config Release
```
После успешной сборки в ```build/Release/``` появятся исполняемые файлы ```server.exe``` и ```client.exe```.
## 4. Запуск сервера:
Открой терминал в папке ```/build/Release``` и введи:
```
./server
```
Если все в порядке, сервер выведет:
```
The server is running on 0.0.0.0:50051
```
## 5. Запуск клиента:
Открой второй терминал в папке ```/build/Release``` и введи:
```
./client
```
Можно начинать работу!
