# Datagram 报文

## 报文的组成

起始行，首部，主体

### 报文的语法

报文分为两种：请求报文和响应报文

请求报文的格式：

    <method> <request-URL> <version>
    <headers>

    <entity-body>

响应报文的格式：

    <version> <status> <reason-phrase>
    <headers>

    <entity-body>

其中：
`<version>`的格式为：`HTTP/<major>.<minor>`

### 起始行

请求报文的起始行说明要做什么，而响应报文的起始行说明要发生什么。

#### 请求行

请求报文的起始行，依次包含方法、资源URL及HTTP版本。

#### 响应行

响应报文的起始行，依次包含HTTP版本、状态码及状态短语

#### 方法

常见的方法

<table>
    <thead>
        <tr>
            <th>方法</th>
            <th>描述</th>
            <th>是否含有主体</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>GET</td>
            <td>
                获取方法
            </td>
            <td>
                否
            </td>
        </tr>
        <tr>
            <td>HEAD</td>
            <td>
                只返回headers
            </td>
            <td>
                否
            </td>
        </tr>
        <tr>
            <td>POST</td>
            <td>提交修改已有数据</td>
            <td>
                是
            </td>
        </tr>
        <tr>
            <td>PUT</td>
            <td>新增和修改数据</td>
            <td>
                是
            </td>
        </tr>
        <tr>
            <td>TRACE</td>
            <td>
                代理追踪
            </td>
            <td>
                否
            </td>
        </tr>
        <tr>
            <td>OPTIONS</td>
            <td>服务器方法探测</td>
            <td>否</td>
        </tr>
        <tr>
            <td>DELETE</td>
            <td>删除数据</td>
            <td>否</td>
        </tr>
    </tbody>
</table>

#### 状态码

<table>
    <thead>
        <tr>
            <th>范围</th>
            <th>已定义</th>
            <th>分类</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>100-199</td>
            <td>100-101</td>
            <td>信息提示</td>
        </tr>
        <tr>
            <td>200-299</td>
            <td>200-206</td>
            <td>成功</td>
        </tr>
        <tr>
            <td>300-399</td>
            <td>300-305</td>
            <td>重定向</td>
        </tr>
        <tr>
            <td>400-499</td>
            <td>400-415</td>
            <td>客户端错误</td>
        </tr>
        <tr>
            <td>500-599</td>
            <td>500-505</td>
            <td>服务器错误</td>
        </tr>
    </tbody>
</table>

### 首部

首部可以分为如下几种：

* 通用首部，即请求和响应报文中均可出现
* 请求首部
* 响应首部
* 实体首部
* 扩展首部

需要注意的一点：
一个首部也可以占据多行，前提是第二行起，每行的开头必须是一个空格或者制表符。例如
    
    server: test server
        version1.0

### HTTP方法

#### GET方法

请求服务器资源，严格而言在服务器上不产生实际动作，因而是GET方法是一种严格的方法（实际上需要开发者来决定）。

#### HEAD方法

类似于GET方法，但是服务器只返回首部而不返回响应实体。HEAD方法也是安全方法（同样取决于开发者）。

使用场景：探测请求资源的状况，包含资源是否存在、被修改及其他在首部中可以表达的特性。

#### PUT方法

基本语义：在服务器端使用请求URL创建一个文件，如果文件存在则更新文件内容。

从广义的角度讲，PUT方法向服务器端推送资源，要求服务器端更新该资源，如果资源不存在则创建资源。

#### POST方法

向服务器端提交数据以创建数据。

#### TRACE方法

当请求进过多个代理，且每个代理有可能修改报文时，让客户端可以追踪报文经过最后一个服务器的状况，也就是TRACE方法的请求会在最后一个服务器上将请求报文返回给客户端。

#### OPTIONS请求

询问服务器支持哪些方法

例如如下实例
    
请求：
    
    OPTIONS * HTTP/1.1
    Host: host.com
    Accept: *

响应：

    HTTP/1.1 200 OK
    Allow: GET, POST, PUT, OPTIONS
    Content-length: 0

#### DELETE方法

服务器删除请求的URL所指定的资源。

#### 扩展方法

规范定义之外的一些方法，HTTP本身被设计成支持可扩展的，因而新的特性并不会使得老的客户端失效。

例如：

* LOCK方法，允许用户锁定一个资源
* MLCOL方法，允许用户创建资源
* COPY方法，允许用户复制资源
* MOVE方法，允许用户移动资源

### 状态码

状态码总共可以分为五大类。

#### 100-199 信息状态码

HTTP/1.1引入了信息状态码，但由于其复杂性和感知性存在一定的争论，所以受到了一定的限制。

##### 100 Continue

其含义为收到了请求的初始部分，请客户端继续。

客户端与100

客户端发送含首部`Expect: 100 Continue`的请求报文，表明客户端愿意在向服务器发送实体前等待`100 Continue`响应。如果超过一段时间客户端没有接到响应，那么则直接发送实体。

服务器与100

如果服务器收到`Expect: 100 Continue`请求，则要么以`100 Continue`响应，要么返回错误码。

如果在服务器发送响应之前，已经接到实体数据，则说明客户端正在已经决定发送数据，服务器在请求完成之后发送最终状态码（跳过`100 Continue`）。

代理与100

收到`Expect: 100 Continue`的请求，如果下一跳是HTTP/1.1或者未知，则向下转发请求，否则返回`417 Expectation Failed`。

如果客户端仅不兼容HTTP/1.1，那么就不能将`100 Continue`转发给客户端。

#### 200-299 成功状态码

<table>
    <thead>
        <tr>
            <th>状态码</th>
            <th>原因短语（HTTP/1.1建议）</th>
            <th>含义</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>200</td>
            <td>OK</td>
            <td>成功</td>
        </tr>
        <tr>
            <td>201</td>
            <td>Created</td>
            <td>用于创建服务器对象的请求（PUT, POST）,响应的主体部分含引用了创建对象的资源URL，Location首部则指向创建资源的具体地址 </td>
        </tr>
        <tr>
            <td>202</td>
            <td>Accepted</td>
            <td>请求已接受，但是还未执行动作，其看起来是有效的，响应主题部分可含有预期的完成时间</td>
        </tr>
        <tr>
            <td>203</td>
            <td>Non-Authoritative Information</td>
            <td>响应的资源尚未被认证</td>
        </tr>
        <tr>
            <td>204</td>
            <td>No Content</td>
            <td></td>
        </tr>
        <tr>
            <td>205</td>
            <td>Reset Content</td>
            <td>清除当前页面中的所有表单</td>
        </tr>
        <tr>
            <td>206</td>
            <td>Partial Content</td>
            <td>范围请求的响应</td>
        </tr>
    </tbody>
</table>

#### 300-399 重定向

告知客户端使用替代的资源来进行访问。

如果资源已被移走301重定向，通过Location首部告知客户端资源的新位置

如果资源没有被修改，依据请求首部If-Modified-Since来判定资源的修改，并返回304响应而并不是资源本身，客户端从本地缓存副本中获取资源。

具体状态码列表如下

<table>
    <thead>
        <tr>
            <th>状态码</th>
            <th>原因短语</th>
            <th>含义</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>300</td>
            <td>Multiple Choices</td>
            <td>当请求实际指向多个资源的时候，返回该状态码及可选字眼列表，让用户协商去选择哪个资源版本</td>
        </tr>
        <tr>
            <td>301</td>
            <td>Move Permanently</td>
            <td>资源被移除，Location响应指向资源的新位置</td>
        </tr>
        <tr>
            <td>302</td>
            <td>Found</td>
            <td>资源临时被转移，Location指向临时地址，与301的不同之处在于，301是永久转移</td>
        </tr>
        <tr>
            <td>303</td>
            <td>See Other</td>
            <td>告知客户端用另一个URL来获取资源，新URL位于Location首部中</td>
        </tr>
        <tr>
            <td>304</td>
            <td>Not Modified</td>
            <td>响应条件请求</td>
        </tr>
        <tr>
            <td>305</td>
            <td>Use Proxy</td>
            <td>必须通过代理来访问，代理的位置有Location指定</td>
        </tr>
        <tr>
            <td>307</td>
            <td>Temporary Redirect</td>
            <td>同301，主要针对HTTP/1.1客户端</td>
        </tr>
    </tbody>
</table>

302，303，307状态码之间存在交叉。

HTTP/1.0客户端发起一个POST请求，并在响应中收到302重定向，会想Location首部重定向发起GET请求，而不是POST。

但HTTP/1.1使用303来完成同样的动作。因而HTTP/1.1客户端将302保留起来，并且使用307来取代302。
（疑问：既然1.1已经用303实现了302，为啥还要用307来再实现一遍）

首先在HTTP/1.0中，针对POST请求302状态码规范要求是：重定向POST请求时，并询问客户端是否向Location所指定的URL上重发POST请求，但是问题在于当前的HTTP客户端都直接将POST的重定向请求转换为GET请求并向Location首部指向的服务器发送，其行为并不符合规范所定义。无论是询问并重定向POST请求还是将POST请求转换为GET请求都具备其意义。因而HTTP/1.1中定义了303及307状态码来细化含POST请求的重定向，结果就是：303状态码规范行为如302状态码在HTTP客户端的行为，即将POST变为GET的重定向，而307状态码如同302状态码的规范行为，即询问并重定向POST请求。

#### 400-499 客户端错误

意味服务器端无法处理客户端的请求，例如404 Not Found错误码。

状态码列表如下：

<table>
    <thead>
        <tr>
            <th>状态码</th>
            <th>原因短语</th>
            <th>含义</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>400</td>
            <td>Bad Request</td>
            <td>告知客户端发送了一个错误的请求</td>
        </tr>
        <tr>
            <td>401</td>
            <td>Unauthorized</td>
            <td>与认证相关的首部一起返回，用户获取访问权限</td>
        </tr>
        <tr>
            <td>402</td>
            <td>Payment Required</td>
            <td>保留</td>
        </tr>
        <tr>
            <td>403</td>
            <td>Forbidden</td>
            <td>请求被拒绝，原因可能有多种，但是服务器无必要说明</td>
        </tr>
        <tr>
            <td>404</td>
            <td>Not Found</td>
            <td>无法找到资源</td>
        </tr>
        <tr>
            <td>405</td>
            <td>Method Not Allowed</td>
            <td>请求中含有不支持的方法，在该响应中应该Allow的首部，告知客户端被允许的方法</td>
        </tr>
        <tr>
            <td>406</td>
            <td>Not Acceptable</td>
            <td>没有满足可被客户端接受的资源，例如Content-type不匹配</td>
        </tr>
        <tr>
            <td>407</td>
            <td>Proxy Authentication Required</td>
            <td>用于代理服务器对资源的认证</td>
        </tr>
        <tr>
            <td>408</td>
            <td>Request Timeout</td>
            <td>客户端发送请求的时间过长，服务器端关闭连接</td>
        </tr>
        <tr>
            <td>409</td>
            <td>Conflict</td>
            <td>请求可能引发冲突</td>
        </tr>
        <tr>
            <td>410</td>
            <td>Gone</td>
            <td>资源曾近在服务器上，但是现在已经没了，类似于404</td>
        </tr>
        <tr>
            <td>411</td>
            <td>Length-Required</td>
            <td>要求请求报文中含有Content-Length首部</td>
        </tr>
        <tr>
            <td>412</td>
            <td>Precondition Failed</td>
            <td>发起请求的一个条件验证失败，例如Expect首部的请求</td>
        </tr>
        <tr>
            <td>413</td>
            <td>Request Entity Too Large</td>
            <td>请求实体过大超出了服务器的处理能力</td>
        </tr>
        <tr>
            <td>414</td>
            <td>Request URI Too Long</td>
            <td>请求的URL超出了服务器的处理能力</td>
        </tr>
        <tr>
            <td>415</td>
            <td>Unsupported Media Type</td>
            <td>服务器无法识别客户端发送的MIME类型</td>
        </tr>
        <tr>
            <td>416</td>
            <td>Requested Range Not Satisfiable</td>
            <td>范围请求的范围违法满足</td>
        </tr>
        <tr>
            <td>417</td>
            <td>Expectation Failed</td>
            <td>无法满足请求中Expect首部中的条件时</td>
        </tr>
    </tbody>
</table>

#### 500-599 服务器错误

状态码如下：

<table>
    <thead>
        <tr>
            <th>状态码</th>
            <th>原因短语</th>
            <th>含义</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>500</td>
            <td>Internal Server Error</td>
            <td>服务器遇到了一个妨碍请求的问题时返回</td>
        </tr>
        <tr>
            <td>501</td>
            <td>Not Implemented</td>
            <td>客户端的请求超出了服务器的能力范围（例如：不支持的方法）</td>
        </tr>
        <tr>
            <td>502</td>
            <td>Bad Gateway</td>
            <td>代理出现故常，例如无法连接到父网关</td>
        </tr>
        <tr>
            <td>503</td>
            <td>Service Unavailable</td>
            <td>无法为请求提供服务，返回Retry-After告知客户端服务何时变得可用</td>
        </tr>
        <tr>
            <td>504</td>
            <td>Gateway Timeout</td>
            <td>来自网关的代理，在等待另一个服务器响应时超时</td>
        </tr>
        <tr>
            <td>505</td>
            <td>HTTP Version Not Supported</td>
            <td>请求的协议版本不被服务器所支持</td>
        </tr>
    </tbody>
</table>

### 首部

#### 通用首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Connection</td>
            <td>请求和响应连接有关的选项</td>
        </tr>
        <tr>
            <td>Date</td>
            <td>请求或者响应报文的创建时间</td>
        </tr>
        <tr>
            <td>MIME-Version</td>
            <td>发送端使用的MIME版本</td>
        </tr>
        <tr>
            <td>Trailer</td>
            <td></td>
        </tr>
        <tr>
            <td>Transfer-Encoding</td>
            <td>报文的传输编码</td>
        </tr>
        <tr>
            <td>Update</td>
            <td>发送端想要“升级”的版本</td>
        </tr>
        <tr>
            <td>Via</td>
            <td>报文经过的中间节点</td>
        </tr>
    </tbody>
</table>

通用缓存首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Cache-Control</td>
            <td>报文缓存指示</td>
        </tr>
        <tr>
            <td>Pragma</td>
            <td>另一种报文指示，但并不专用于缓存。Pragma实际是请求首部，但是客户端错误的将其应用到了响应首部中，其确切的语义为得到很好的定义，任何情况下Cache-Control优于Pragma</td>
        </tr>
    </tbody>
</table>

#### 请求首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Client-IP</td>
            <td>客户端的IP</td>
        </tr>
        <tr>
            <td>From</td>
            <td>客户端用户的E-mail地址</td>
        </tr>
        <tr>
            <td>Host</td>
            <td>请求的域名和端口</td>
        </tr>
        <tr>
            <td>Referer</td>
            <td>请求的引用URL</td>
        </tr>
        <tr>
            <td>UA-Color</td>
            <td>显示器颜色</td>
        </tr>
        <tr>
            <td>UA-CPU</td>
            <td>CPU</td>
        </tr>
        <tr>
            <td>UA-Disp</td>
            <td>显示器能力</td>
        </tr>
        <tr>
            <td>UA-OS</td>
            <td>客户端操作系统</td>
        </tr>
        <tr>
            <td>UA-Pixels</td>
            <td>显示器像素</td>
        </tr>
        <tr>
            <td>User-Agent</td>
            <td>发起请求的应用名称</td>
        </tr>
    </tbody>
</table>

Accept请求首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Accept</td>
            <td>告知服务器发送哪些媒体类型</td>
        </tr>
        <tr>
            <td>Accept-Charset</td>
            <td>告知服务器发送哪些字符集</td>
        </tr>
        <tr>
            <td>Accept-Encoding</td>
            <td>告知服务器发送哪些编码</td>
        </tr>
        <tr>
            <td>Accept-Language</td>
            <td>告诉服务器发送哪些语言</td>
        </tr>
    </tbody>
</table>

条件请求首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Expect</td>
            <td>列出所要求的服务器行为</td>
        </tr>
        <tr>
            <td>If-Match</td>
            <td>如果实体标记和文档匹配则返回文档</td>
        </tr>
        <tr>
            <td>If-Modified-Since</td>
            <td>资源在指定的日期后修改过，则返回文档</td>
        </tr>
        <tr>
            <td>If-None-Match</td>
            <td>如果实体标记和文档不匹配，则获取文档</td>
        </tr>
        <tr>
            <td>If-Range</td>
            <td>如果允许对文档的某个范围请求</td>
        </tr>
        <tr>
            <td>If-Unmodified-Since</td>
            <td>如果文档在指定的日期之后没被修改过，则返回文档</td>
        </tr>
        <tr>
            <td>Range</td>
            <td>返回文档指定的范围</td>
        </tr>
    </tbody>
</table>

安全请求首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Authorization</td>
            <td>含提供给服务器的身份验证数据</td>
        </tr>
        <tr>
            <td>Cookie</td>
            <td>传送令牌，含安全功能</td>
        </tr>
    </tbody>
</table>

代理请求首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Max-Forward</td>
            <td>将请求转发给其他网关或者代理的最大次数</td>
        </tr>
        <tr>
            <td>Proxy-Authorization</td>
            <td>与代理进行认证时使用</td>
        </tr>
        <tr>
            <td>Proxy-Connection</td>
            <td>与代理建立连接时使用</td>
        </tr>
    </tbody>
</table>

#### 响应首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Age</td>
            <td>响应持续时间</td>
        </tr>
        <tr>
            <td>Retry-After</td>
            <td>此日期后重试请求</td>
        </tr>
        <tr>
            <td>Server</td>
            <td>服务器的软件名称</td>
        </tr>
    </tbody>
</table>

协商响应首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Accept-Range</td>
            <td>服务器可接受的范围类型</td>
        </tr>
        <tr>
            <td>Vary</td>
            <td>服务器查看的其他首部的列表，可能引起相应的变化。例如：Vary: Accept-Encoding，服务器依据请求的Accept-Encoding的不同发送不同的压缩编码的文档版本。</td>
        </tr>
    </tbody>
</table>

安全响应首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Proxy-Authenticate</td>
            <td>来自代理的对客户端质询</td>
        </tr>
        <tr>
            <td>Set-Cookie</td>
            <td>设置Cookie，隐藏安全的功能</td>
        </tr>
        <tr>
            <td>WWW-Authenticate</td>
            <td>来自服务器的对客户端质询</td>
        </tr>
    </tbody>
</table>


#### 实体首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Allow</td>
            <td>列出了可以对实体执行的请求方法</td>
        </tr>
        <tr>
            <td>Location</td>
            <td>列出了实体的所在位置</td>
        </tr>
    </tbody>
</table>

实体内容首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Content-Base</td>
            <td>解析主体相对URL是的基础URL</td>
        </tr>
        <tr>
            <td>Content-Encoding</td>
            <td>主体内容的编码方式</td>
        </tr>
        <tr>
            <td>Content-Language</td>
            <td>主体的语言</td>
        </tr>
        <tr>
            <td>Content-Length</td>
            <td>主体的尺寸</td>
        </tr>
        <tr>
            <td>Content-Location</td>
            <td>资源实际的位置</td>
        </tr>
        <tr>
            <td>Content-MD5</td>
            <td>主体的MD5和</td>
        </tr>
        <tr>
            <td>Content-Range</td>
            <td>实体在资源中的范围</td>
        </tr>
        <tr>
            <td>Content-Type</td>
            <td>实体的MIME类型及字符编码</td>
        </tr>
    </tbody>
</table>

缓存首部

<table>
    <thead>
        <tr>
            <th>首部</th>
            <th>描述</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>ETag</td>
            <td>实体的标记</td>
        </tr>
        <tr>
            <td>Expires</td>
            <td>此日期之后，实体不再有效</td>
        </tr>
        <tr>
            <td>Last-Modified</td>
            <td>实体最后被修改的时间</td>
        </tr>
    </tbody>
</table>


