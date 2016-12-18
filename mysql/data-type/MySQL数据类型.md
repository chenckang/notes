# 12 MySQL数据类型

MySQL支持多种类别的SQL数据类型：数字类型，日期和时间类型，字符串（字符和字节）类型，空间类型以及JSON数据类型。本章包含这些数据类型的概览、每个类别的数据类型的详细属性描述以及数据类型的存储要求。概览部分很简单直白的。本章后面的详细描述可用于查看特定类型的额外信息，例如你所指定的值的可行格式。

数据类型描述包含如下规则：

* M为整形类型的最大显示长度。对于浮点型以及固定浮点类型，M能够存储住的总共长度（精度）。对于字符串类型，M是最大的长度。M的最大值取决于数据类型
* D用于浮点型和固定浮点型，为小数点后面的数字的长度。最大值为30，但是不能大于M-2。
* fsp用于TIME、DATETIME以及TIMESTAMP类型表示秒的精度。也即是秒的小数点后面的数字的个数。fsp的值必须自0到6之间。0表示没要小数部分。如果忽略未赋值，默认值为0（和标准的SQL默认为6不同，主要为了和之前的MySQL版本兼容）。
* 方括号（[和]）表明类型定义的可选部分。

## 12.1 数据类型概述

### 12.1.1 数字类型

如下是数字类型的总结。关于属性和存储要求的额外信息，查看12.2以及12.8。

M表示整数型的最大显示长度。最大值为255。显示长度和数据类型值的范围并不相关，如12.2中的描述。对于浮点型以及固定浮点型，M表示能够存储的数字总个数。

如果对数据列指定了ZEROFILL，MySQL会自动给列加上UNSIGNED属性。

允许属性UNSIGNED的数字类型同样会允许SIGNED。然而，对于数据类型默认是有符号的，SIGNED属性并无特殊的作用。

SERIAL是BIGINT UNSIGNED NOT NULL AUTO_INCREMENT UNIQUE的同义词。

SERIAL DEFAULT VALUE用于整形数据列的定义时为NOT NULL AUTO_INCREMENT UNIQUE的同义词。

* BIT[(M)]

> 比特类型。M表示每个值的比特数，从1到64。默认是1。

* TINYINT[(M)] [UNSIGNED] [ZEROFILL]

> 小整数。有符号时范围为-128到127。无符号是为0到255。2^8。

* BOOL, BOOLEAN

> TINYINT(1)的同义词。零表示false。非零值表示true：

```
mysql > SELECT IF(O, 'true', 'false');

mysql > SELECT IF(1, 'true', 'false');

mysql > SELECT IF(2, 'true', 'false');
```

> 然而，TRUE和FALSE的值也正是1和0的，如下所示：

```
mysql > SELECT IF(0 = FALSE, 'true', 'false');

mysql > SELECT IF(1 = TRUE, 'true', 'false');

mysql > SELECT IF(2 = TRUE, 'true', 'false');

false

mysql > SELECT IF(2 = FALSE, 'true', 'false');

false
```

* SMALLINT[(M)] [UNSIGNED] [ZEROFILL]

> 小整数。有符号时范围为-32768到32767。无符号是为0到65535。2^16。

* MEDIUMINT[(M)] [UNSIGNED] [ZEROFILL]

> 中型整数。有符号版为-8388608到8388607。无符号时为0到16777215。2^24

* INT[(M)] [UNSIGNED] [ZEROFILL]

> 普通整形。有符号时范围为-2147483648到2147483647。无符号时范围为0到4294967295。2^32。

* INTEGER[(M)] [UNSIGNED] [ZEROFILL]

> 同INT

* BIGINT[(M)] [UNSIGNED] [ZEROFILL]

> 长整形。有符号时范围为-2^63到2^63-1，无符号时为0到2^64。
> SERIAL为BIGING UNSIGNED NOT NULL AUTO_INCREMENT UNIQUE的同义词。
> 针对BIGINT数据列需要注意的是：

> * 所有的算术运算是通过有符号的BIGINT或者DOUBLE值来完成的，所以不应该使用无符号且其值大于2^63的长整形，除非使用函数。如果不小心错误的执行了，尾部的数字部分可能会错误，这是因为将BIGINT转换为DOUBLE时的四舍五入问题导致的。MySQL可以按如下的方式处理BIGINT:
> 
> > * 当使用整形来在BIGINT列中存储无符号长整形值
> > * 在MIN(col_name)或者MAX(col_name)中使用，col_name指列名
> > * 在操作数都是整数时使用操作符（+，-，*等）
> 
> * 你可以在BIGINT列通过字符串来存储一个确切的整数值。这种情况下，MySQL会执行字符串转换为整形操作而不会产生任何双精度的中间体。
> 
> * 当两个操作数都是整形时，-、+、*操作符会使用BIGINT来进行算数运算。也就是如果你将两个长整形相乘（或者有函数返回的长长整形数），你可能会得到意外的结果，也即是大于2^63的情况。

* DECIMAL[M[,D]] [UNSIGNED] [ZEROFILL]

> 固定长度浮点型数。M是数位的具体总数（精度），D是小数点后面的位数个数（刻度）。对于十进制小数点以及负数符号并不包含在M中。如果D为0，则值没有十进制小数点或者小数部分。针对十进制数M最大为65。小数部分的数位个数最大为30。如果没有指定D，则默认值为0。如果没有指定M，则默认值为0。
> 

* DEC[(M[,D])] [UNSIGNED] [ZEROFILL], NUMERIC[(M[,D])] [UNSIGNED] [ZEROFILL], FIXED[(M[,D)] [UNSIGNED] [ZEROFILL]
>
> DECIMAL的同义词。FIXED形式也和其他的数据库系统兼容。

* FLOAT[(M,D)] [UNSIGNED] [ZEROFILL]
> 单精度浮点型。基于IEEE标准，存储范围存在理论上的限制。实际的范围依据硬件和操作系统的不同会略小一点。
> 
> M是全部的数位个数，D是小数点后面的数位个数。如果没有指定M和D，存储的值会受限于具体的硬件。单精度浮点型实际上接近7个小数位。
> 
> UNSIGNED，如果指定，则不允许为负。
> 
> 使用FLOAT可能会带来一定的问题，因为MySQL中的多有的计算都是使用双精度浮点型的。查看5.4.7。
> 

* DOUBLE[(M,D)] [UNSIGNED] [ZEROFILL]
> 双精度浮点型。依据IEEE标准，存储范围存在理论上的限制。实际的范围依据硬件和操作系统的不同会略小一点。
> 
> M是全部的数位个数，D是小数点后面的数位个数。如果没有指定M和D，存储的值会受限于具体的硬件。单精度浮点型实际上接近7个小数位。
> 
> UNSIGNED，如果指定，则不允许为负。

* DOUBLE_PRECISION[(M,D)] [UNSIGNED] [ZEROFILL], REAL[(M,D)] [UNSIGNED] [ZEROFILL]
> DOUBLE的同义词。例外：如果开启了REAL_AS_FLOAT，REAL就是FLOAT的同义词而不是DOUBLE。

* FLOAT(P) [UNSIGNED] [ZEROFILL]
> 浮点型。p代表精度，但是MySQL使用这个值仅仅用于决定知否使用FLOAT或者DOUBLE来用做结果数据类型。如果p是0到24，数据类型为未指定M和D的FLOAT类型。如果p是25到53，数据类型为未指定M和D的DOUBLE。结果类型的范围和之前所说的单精度FLOAT和双精度DOUBLE相同。
> FLOAT(p)主要目的在于兼容ODBC标准。


### 12.1.2 日期和时间类型概览

时间数据类型总结如下。对于属性的额外信息和存储要求参见12.3和12.8。对于操作时间值的函数参见13.7。

对于DATE和DATETIME范围的描述，“支持”意思是不一定能够支持较早的值。

MySQL运行对TIME、DATETIME以及TIMESTAMP值指定小数部分，知道微妙（六个小数位）精度。要定义秒的小数部分，使用type\_name(fsp)语法，其中type\_name为TIME、DATETIME以及TIMESTAMP，fsp是秒的小数部分的精度。例如：

```
CREATE TABLE t1 (t TIME(3), dt DATETIME(6));
```

如果指定fsp的值，则必须在0到6之间。0表示其中没有小数部分。如果忽略这个值，则默认为0。（这和标注的SQL默认指定为6不同，是为了兼容一起的MySQL版本）

表中的TIMESTAMP以及DATETIME列可以有动态的初始和更新属性。

* DATE

> 日期。支持范围为‘1000-01-01’到‘9999-12-31’。MySQL通过‘YYYY-MM-DD’的格式来显示DATE，但是运行将字符串和数字类型的值赋予到DATE列上

* DATETIME[(fsp)]

> 日期和时间的结合。支持的范围为‘0000-01-01 00:00:00.000000’到‘9999-12-31 23:59:59.999999’。MySQL通过‘YYYY-MM-DD HH:MM:SS[.fraction]’显示DATETIME，但是运行通过字符串和数字的方式来赋值。
> 
> 可选项fsp的范围为0到6用于指定秒的小数部分的精度。0表示没有小数部分。如果忽略则默认为0。
> 
> 自动初始化和更行当前的日期和时间，可以通过使用DEFAULT和ON UPDATE列定义来完成，如12.3.5中。

* TIMESTAMP[(fsp)]

> 时间戳。范围为‘1970-01-01 00:00:01.000000’UTC时间到'2038-01-19 03:14:07.999999'UTC时间。TIMESTAMP的存储值为从新纪元时间（‘1970-01-01 00:00:00’ UTC)开始的秒数。TIMESTAMP不能表示‘1970-01-01 00:00:00’，因为这个时间是从新纪元开始的0秒，0为‘0000-00-00 00:00:00’而保留。
>
> 可选的fsp部分范围为0到6，用于指定秒的小数部分。0表示没有小数。如果忽略，则默认值为0。
> 
> 服务器处理TIMESTAMP的定义是依据`explicit_defaults_for_timestamp`系统变量的值（查看6.1.5）。默认，`explicit_defaults_for_timestamp`是关闭，服务器按如下方式来处理TIMESTAMP：
> 
> 除非特别指定，表中的第一个TIMESTAMP列在没有赋值时自动的设置醉经的日期和时间。这在记录INSERT和UPDATE操作是会很有用。可以赋给TIMESTAMP列NULL值来指定为当前的时间，除非通过NULL的列属性来指定可以有NULL值。
> 
> 自动初始化和更新到当前时间和日期可以通过`DEFAULT CURRENT_TIMESTAMP`和`UPDATE CURRENT_TIMESTAMP`列定义来开启。默认，第一个TIMESTAMP列中有这些属性，就如之前所属。然而，任何表中的TIMESTAMP列都可以指定这些属性。
> 
> 如果开启`explicit_defaults_for_timestamp`，则不会自动将`DEFAULT CURRENT_TIMESTAMP`和`UPDATE CURRENT_TIMESTAMP`属性赋给TIMESTAMP列。他们必须在列定义中明确的指定。同样，任何没有明确指定`NOT NULL`的列会允许NULL值。

* TIME[(fsp)]

> 时间。有效值范围为“-834:59:59.000000”到“838:59:59.000000”。MySQL通过‘HH:MM:SS[.fraction]’的格式显示时间，但是运行通过字符串和数字来赋值。

* YEAR[(4)]

> 四位数的年份。MySQL通过‘YYYY’的格式来显示YEAR，但是允许通过字符串和数组来赋值到YEAR列。显示范围为1901到2155以及0000。

> 关于显示年的其他格式以及输入数值的解析，参见12.3.3

SUM()和AVG()聚合函数无法再时间值上使用。（他们将时间转换为数字，在第一个非数组字符后就丢失了所有的信息）。要解决这个问题，可以先转换为数字单元，然后进行聚合操作，在还原为时间值，例如：

```
SELECT SEC_TO_TIME(SUM(TIME_TO_SEC(time_col))) FROM tbl_name;
SELECT FROM_DAYS(SUM(TO_DAYS(date_col))) FROM tbl_name;
```

### 12.1.3 字符串类型概览

字符串类型概览如下。对于属性的额外信息以及存储要求参见12.4以及12.8。

在一些情况下，MySQL可以将字符串列转换为不同于`CREATE TABLE`以及`ALTER TABLE`表达式中指定的类型。查看14.1.18.6。

MySQL使用在列定义中指定的字符长度来解析字符单元。这适用于`CHAR`、`VARCHAR`以及`TEXT`。

对于很多字符串数据类型的列定义包含指定字符集以及字符校对的信息。这些属性适用于`CHAR`、`VARCHAR`、`TEXT`、`ENUM`和`SET`数据类型。

* `CHARACTER SET`属性指定字符集，`COLLATE`属性指定字符集的校对。例如：

```
CREATE TABLE T
(
	c1 VARCHAR(20) CHARACTER SET utf8,
	c2 TEXT CHARACTER SET latin1 COLLATE latin1_general_cs
);
```

这个表定义定义了c1列，并且字符集为utf8，以及这个字符集下的默认字符校对，和以c2列，其字符集为latin1以及大小写敏感的校对。

当同时未指定`CHARACTER SET`以及`COLLATE`时的赋值规则查看11.1.3.5。

* 针对字符数据类型指定`CHARACTER SET binary`属性会让列按照相应的二进制数据类型来被创建：CHAR成为BINARY，VARCHAR成为VARBINARY，TEXT成为BLOB。对于ENUM和SET数据类型，则不会如此。

例如通过入戏定义创建表格：

```
CREATE TABLE t
(
	c1 VARCHAR(10) CHARACTER SET binary,
	c2 TEXT CHARACTER SET binary,
	c3 ENUM('a', 'b', 'c') CHARACTER SET binary
);
```
结果就是如下：

```
CREATE TABLE t
(
	c1 VARBINARY(10),
	c2 BLOB,
	c3 ENUM('a', 'b', 'c') CHARACTER SET binary
);
```

* BINAY属性是指定表的默认字符集以及二进制校对（_bin)的快捷方式。这样，对比和排序就是基于数字字符的值来进行。
* ASCII属性是`CHARACTER SET latin1`的快捷方式。
* UNICODE属性是`CHARACTER SET ucs2`的快捷方式。

字符列的对比和排序是基于赋予列上的校对属性来进行的。对于`CHAR`，`VARCHAR`，`TEXT`，`ENUM`以及`SET`数据类型，可以通过二进制校对（_bin）来声明或者`BINARY`属性来让对比和排序依赖于潜在的字符码而不是单词顺序。

对于使用字符集的使用额外信息，参见11.1。

* [NATIONAL] CHAR[(M)] [CHARACTER SET charset\_name] [COLLATE collation\_name]

固定长度的字符串，右边总是存在空格来补充到指定的长度。M表示列的字符串的长度。范围是0到255。如果未指定则为1。

CHAR是CHARACTER的简写。NATIONAL CHAR(或者其对等体，NCHAR)是使用一些预定义的字符集定义列的标准SQL方式。MySQL使用utf8作为预定义的字符集。

CHAR BYTE数据类型是BINARY数据类型的对等体。这是一个兼容特性。

MySQL允许创建CHAR(0)的列。这主要用于当你要兼容老的应用，这些应用依赖于一个列的存在而不实际使用其值。CHAR(0)在你要让一个列只能接受两个值是也很有用：使用CHAR(0) NULL定义的列仅仅占用一个比特，所以可以赋值NULL或者''(空字符串)。

* [NATIONAL] VARCHAR(M) [CHARACTER SET charset_name] [COLLATE collation_name]

可变长度字符串。M表示列中的字符最大长度。M的范围为0到65535。VARCHAR的有效最大长度依赖于列的最大大小（65535字节，这在所有列中都是一致的）以及字符集的使用。例如，使用utf8字符最大可占用三个字节，所以使用utf8的VARCHAR列可以声明为最大长度为21844。查看10.4。

MySQL将VARCHAR字符存储为1字节或者2字节前缀加上数据。长度前缀表明值的字节个数。VARCHAR列在值占用大小不大于255字节时使用一个长度字节前缀，大于255字节时使用两个长度字节前缀。

VARCHAR是`CHARACTER VARING`的简写。`NATIONAL VARCHAR`是定义一个含有预定义的字符集的VARCHAR列的标准SQL方法。MySQL使用utf8作为预定义的字符集，查看11.1.3.7。NVARCHAR是`NATIONAL VARCHAR`的简写。

* BINARY(M)

BINARY类型类似于CHAR类型，但是存储二进制字符串而不是非二进制的。M代表列的字节数。

* VARBINARY(M)

类似于VARCHAR类型，但是存储二进制字符串而不是非二进制的。M代表列的最大宽度。

* TINYBLOB

最大长度为255的BLOB列。每个TINYBLOB值使用一个字节的前缀来表示值的最大字节个数。

* TINYTEXT [CHARACTER SET charset\_name] [COLLATE collation\_name]

最大长度为255的TEXT列。如果值包含多字节字符则有效的长度会更小。每个TINYTEXT值通过一个字节的前缀来表示值的字节个数。

* BLOB[(M)]

最大长度为65535的BLOB列。每个BLOB值存储会有一个两个字节的前缀来表示值中所含的字节个数。

可选参数M可以用于这个类型。MySQL会创建能够存储M字节长度的最小BLOB类型的列。

* TEXT[(M)] [CHARACETR SET charset_name] [COLLATE collation_name]

最大长度为65535的TEXT列。如果值包含多字节字符则有效长度会更小。每个TEXT值会使用两个长度的前缀来存储用于表明值的字节个数。

可选参数M可以用于这个类型。MySQL会创建能够包含M个字符长度的最小TEXT类型列。

* MEDIUMBLOB

最大长度为2^24-1字节的BLOB列。每个MEDIUMBLOB值使用三个字节的前缀来表示值中含有的字节个数。

* MEDIUMTEXT [CHARACTER SET charset_name] [COLLATE collation_name]

最大长度为2^24-1字节的TEXT列。如果值中包含多字节的字符则有效长度会更小。每个MEDIUMTEXT值使用三个字节的前缀来存储表示值的字节个数。

* LONGBLOB

最大长度为2^32-1字节的BLOB列。最大的有效长度依赖于客户端和服务器协议中配置的最大数据包尺寸以及可用的内存。每个LONGBLOB值使用4个字节的前缀来存储以表示值的字节数。

* LONGTEXT [CHARACTER SET charset_name] [COLLATE collation_name]

最大长度为2^32-1或者包含4GB字符大小的TEXT列。如果值中包含多字节字符则有效的最大长度会更小。LONGTEXT的有效最大长度也依赖于客户端和服务端配置的最大数据包尺寸以及可用的内存。每个LONGTEXT值有4个字节前缀来表示来表示值所包含的自己个数。

* ENUM('value1', 'value2',...) [CHARACTER SET charset_name] [COLLATE collation_name]

枚举类型。仅有一个值的字符串对象，这个值从'value1', 'value2'...NULL或者特殊的错误值''中选取。ENUMS值内部是通过整数来表示的。

ENUM列最大可以有65535个不同的元素。（实际的限制是要小于3000）。

* SET('value1', 'value2',...) [CHARACTER SET charset_name] [COLLATE collation_name]

集合类型。一个可以有一个和多个值的字符串对象，每一个都必须从'value1', 'value2',...中选取，SET类型内部是通过整数来表示的。

SET类型可以有64个不同的成员。

