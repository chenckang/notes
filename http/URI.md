# URI

URI中文全称为**统一资源标识符**，其具体作用就是用于定位资源所在的位置。URI存在2类子集——URL及URN。HTTP仅处理URI中的URL子集。

## URL

URL全称统一资源定位符，且几乎所有的URI都是URL。URL提供定位因特网上所有资源的方式。存在多种不同的URL方案，每种方案的语法又不尽相同。通用的URL语法如下：
    
    <scheme>://<user>:<password>@<host>:<port>/<path>;<param>?<query>#<frag>

其中共含有九个组件，但是并不存在一种特定的URL完全包含上面的所有组件，一般仅仅包含其中的几个部分而已。



## URN

URN全称统一资源名

例如，RFC 2141文档的用URN的表示方法：urn:ietf:rfc:2141。无论该文档位于何处，使用和URL表示，URN表示法都可以定位到该文档。


