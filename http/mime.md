# MIME

多用途英特网邮件扩展，最初为了在多邮件系统间共享文件而设计。由于其在邮件系统中表现优异，HTTP协议也用此来标记多媒体内容。

Web服务器会在每一个响应报文的__Content-type__消息头部上表明返回的资源的MIME类型，浏览器或者其他的客户端会议及**Content-type**的值来适当的处理返回资源。具体而言，也就是图片、html、多媒体等资源的解析及处理方法。譬如，声音资源会调用声卡播放。

MIME的格式为：主对象/子类型

例如：

* html的MIME为text/html
* jpeg的MIME为image/jpeg
* js的MIME类型为text/javascript或者application/x-javascript



