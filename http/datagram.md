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

#### 响应行

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

状态码

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