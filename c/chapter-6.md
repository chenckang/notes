# 结构

## typedef

用于创建新的数据类型名。

typedef类似于#define，但是由于typedef是有编译器解释的，因此文本替换功能要超过预处理的能力。

```
typedef int (*PEI)(char *, char *);
```
定义了类型PEI，为一个指向函数的指针，该函数具有两个`char *`类型的参数，返回值为int。

```
PEI strcmp, numcmp;
```

另一个原因是，typedef可以使程序参数化，以提高程序的可移植性。如果typedef声明的数据类型同机器相关，那么当程序一直到其他机器上时，改变typedef的定义就好。

一个常用情况是杜宇各种不同大小的整数值来说，通过typedef定义的类型名，然后分别为宿主机器选择一组合适的short、int以及long类型大小。

例如：`site_t`和`ptrdiff_t`

最后typedef可以提供更好的说明性。

## 联合

```
union u_tag {
  int ival;
  float fval;
  char *sval;
} u;
```
那么此类型中的任何一种类型的对象都可以复制给u。

联合就是一个结构，其所有成员相对于基地址的偏移量都是0，此结构空间要大到足够容纳你最宽的成员，并且对于方式要适合于联合中的所有类型成员。

## 位字段
