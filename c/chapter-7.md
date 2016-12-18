# 输入和输出

<stdio.h>

unix中一般位于/usr/include中。

## 标准输入和输出

getchar()每次被调用是返回下一个输出字符，若遇到文件结尾则返回EOF，EOF位于<stdio.h>中，一般为-1。

putchar()将字符输出到标准输出上，默认情况下标准输出为屏幕显示，如果发生错误将返回EOF。

函数prinft也向标准输出设备上输出数据。

## 格式化输出

## 变长参数

```
int printf(char * fmt, ...)
```

## 格式化输出——scanf

```
int scanf(char *format, ...)
```

## 文件访问

```
FILE *fp;
FILE *fopen(char *name, char *mode);
```

## 错误处理——stderr, exit
