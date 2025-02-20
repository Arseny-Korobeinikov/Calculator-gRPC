# Руководство по использованию 
## 1. Настройте своё окружение
Инструкция для Windows (через vcpkg):
### Шаг 1. Установка vcpkg:
Откройте PowerShell от имени администратора и выполните:
```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```
После этого в папке ```vcpkg/``` появится исполняемый файл ```vcpkg.exe```.
### Шаг 2: Установите gRPC
```
.\vcpkg install grpc:x64-windows
```
Это скачает и соберет gRPC вместе со всеми необходимыми библиотеками (protobuf, abseil, openssl и т. д.).
## 2. Создайте проект с помощью ```CMake```
1. Настройте сборку
```
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=C:/Users/arsen/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```
