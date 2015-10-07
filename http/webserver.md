# 服务器

## 客户端主机名查询

## ident协议查询用户名

支持idnent协议的客户端会在其113端口建立到服务器的连接。
当HTTP的连接在服务器和客户端建立后，服务器打开自己到客户端113端口的连接，并发送请求询问客户端用户名，并从响应中解析用户名。

很显然ident协议支持并好，原因如下：

* ident协议会造成HTTP的时延加大，并且可能严重加大
* 很多客户端并不支持ident协议
* 防火墙会限制ident流量
* ident容易伪造
* ident暴露用户隐私
* ident不支持虚拟ip地址

## 服务器的进程/线程和连接

分为如下几类

* 单线程，一次只处理一个请求
* 多线程，每个请求一个进程/线程，由于大量的进程会导致内存的过多消耗，因此服务器也会设置最大可支持的进程数
* 复用I/O的，保持多个连接，使用一个进程不断的处理这些连接的请求
* 复用的多线程服务器，多个连接，多个进程，但是连接是复用的

## 重定向

当前请求的URL是一个尾部不带斜杠的目录名，大多数服务器会重定向到一个加斜杠的目录上