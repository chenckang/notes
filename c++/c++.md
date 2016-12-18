# 知识点收集

## 指针

```
int i = 1;
int* a = &i;
fun (int* a) {}
```
a代表指向i的指针，当使用fun(a)时，传入fun的参数实际上是指针代表的值，也就是i的值1，所以此处等同于fun(1)；如果要传入a的应用，则fun的定义需如下：

```
fun(int*& a){}
```

## namespace

用于定义一个命名空间来避免变量冲突。
```
namespace ContosoData
{
  class ObjectManger
  {
    public:
      void DoSomething() {}
  }
  void Func(ObjectManger){}
}

ContosoData::ObjectManger mgr;
mrg.DoSomething();
ContosoData::Func(mgr);
```

将一个变量引入到作用域中：
```
using ContosoData::ObjectManger;
ObjectManger mgr;
mgr.DoSomething();
```

将命名空间的所有内容引入到作用域中：
```
using namespace ContosoData;
ObjectManger mgr;
Func(mgr);
```

### using指令

可以将命名空间的部分变量引入到作用域中，也可以全部引入进来。但是，如果作用域中存在和命名空间同名的变量，则命名空间中的变量会被忽略，如果命名空间的变量和全局变量冲突，则会抛出错误。

一般在cpp文件的开头或者class和function的内部使用using，不要在.h文件中使用避免所以引入.h的文件中造成的变量冲突不可预知。

## template
