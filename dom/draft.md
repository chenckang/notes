# Draft

## DOM0 DOM1 DOM1 DOM3
HTMLDOM
XMLDOM

DOM2增加了
    Core:一级核心上添加更多的方法及属性
    Views:基于样式信息的不同视图
    Events:事件与DOM交互
    Style:CSS样式访问记修改
    Traversal and range: 遍历
    HTML: 一级HTML上添加了更多的方法和属性
检测：
    document.implementation.hasFeature("Core", "2.0")

xmlns

    <xhtml:html xmlns:xhtml= "http://www.w3.org/1999/xhtml">


## GlobalEventHandlers

描述了一个mixin适用于Document、Window, HTMLElement。是一个mixin而不是interface。

onabort, onblur, onerror, onfocus, onchange, onclick, onclose, oncontextmenu

ondblclick, onkeydown, onkeyup, onkeypress, onload, onmousedown, onmousemove

onmouseout, onmouseover, onmouseup, onscroll, onselect, onsubmit

* abort事件：当加载事件被取消时触发
* error事件：当js出现运行时异常，在window上触发Error事件，参数依次是errormsg、url、line number、column number、ErrorObject；当脚本或者图片加载失败，在相应的dom元素上触发error事件，且不冒泡
* change事件：针对input, select, textarea元素，但不是每次变化都触发，对输入框input和textarea，当编辑完后元素失去焦点时触发，radio和checkbox及select，Date型的input发生变化就触发
* input事件：同步和input及textarea元素改变一起触发，对contenteditable元素也会触发；designMode控制整个文档的可编辑性，也会触发input
* close事件：window对象的close事件
* contextmenue事件：window上的右键事件，兼容ie8的话需要用document.oncontextmenu，也可以用addEventListener注册到window上
* keypress事件：当按下按键的时候触发，但是不是所有的按键都会触发，webkit不支持方向键，firefox不支持shift键等；不同于onkeydown, onkeyup
* reset事件：表单被reset后触发
* scroll事件：元素滚动后触发
* select事件：选择一段文本后触发
* submit事件：注册在window上

## ParentNode接口

定义了能够包含子元素的特殊Node行为。是一个纯接口，Element、Document、DocumentFragment继承了这个接口。

## Node接口

继承该接口的有：Document、Element、CharacterData(Text, Comment, CDATASection)、ProcessingInstruction、DocumentFragment、DocumentType、Notation、Entity、EntityReference

属性如下：baseURI，
childNodes NodeList
firstChild，lastChild，
nextSibling，
previousSibling，
nodeName 一般是标签的大写形式，document节点为#document, text节点为#text
nodeType1 ELEMENT_NODE, 2 ATTRIBUTE_NODE, 3 TEXT_NODE, 4 CDATA_SECTION_NODE, 9 DOCUMENT_NODE, 10 DOCUMENT_TYPE_NODE, 11 DOCUMENT_FRAGMENT_NODEi
nodeValue 对大多数Node返回null，对Text, Comment等则返回文本内容的数据
ownerDocument 返回Node所属的Document)
parentNode 返回父Node, DocumentFragment及Document返回null
parentElemen 返回父ELement
textContent
    document, doctype, notation返回null，
    CDATA、comment、 text返回node内部的文本内容，
    其他的则返回每个子node的textContent拼接的字符串，
    与IE中innerText的差别，innerText不包含script及style，隐藏的元素，
    与innerHTML


方法：
appendChild(node)
cloneNode(deep) 克隆当前节点，如果deep为true的话，则子节点也拷贝进来，除了内联的事件，其他注册的事件不会被拷贝 
contains(node) 但会当前节点是否包含node节点
compareDocumentPosition(node)
hasChildNodes() 是否有子节点
insertBefore(newNode, refNode) 在refNode之前插入nodeNode，refNode为null时在当前节点的字节点最后插入newNode，此外并没有insertAfter方法，使用insertBefore(newNode, refNode.nextSibling)
isEqualNode() 判断两节点是否是等同的
normalize()清理当前节点下的text节点，移除空text，合并相邻的text节点
removeChild(child) 
replaceChild()

## Element
属性如下：
attributes 为NamedNodeMap对象
childElementCount
children HTMLCollection
classList DOMTokenList
className DOMString
clientHeight
clientWidth
clientLeft
clientTop
firstElementChild
id


## EventTarget



#NamedNodeMap

通过HTMLElement.attributes获取，存储了一个Attr对象的集合。其存储顺序是随机的，并且可以通过数组的形式来访问。
也不继承任何interface

主要方法：
getNamedItem 返回一个Attr对象，参数为属性名
setNamedItem
removeNamedItem
item

## ParentNode




DOM3增加了DTD, Schemas, 及文档验证


## DocumentType

代表一个包含doctype的Node节点

属性有name, publicId, systemId
