#! /bin/bash

:<<COMMENT
　test 和 [ 命令
　　虽然 Linux 和 UNIX 的每个版本中都包含 test 命令，但该命令有一个更常用的别名 — 左方括号：[。test 及其别名通常都可以在 /usr/bin 或 /bin （取决于操作系统版本和供应商）中找到。
　　当您使用左方括号而非 test 时，其后必须始终跟着一个空格、要评估的条件、一个空格和右方括号。右方括号不是任何东西的别名，而是表示所需评估参数的结束。条件两边的空格是必需的，这表示要调用 test，以区别于同样经常使用方括号的字符/模式匹配操作。
　　test 和 [ 的语法如下：
　　test expression
　　[ expression ]
　　在这两种情况下，test 都评估一个表达式，然后返回真或假。如果它和 if、while 或 until 命令结合使用，则您可以对程序流进行广泛的控制。不过，您无需将 test 命令与任何其它结构一起使用；您可以从命令行直接运行它来检查几乎任何东西的状态。
　　因为它们彼此互为别名，所以使用 test 或 [ 均需要一个表达式。表达式一般是文本、数字或文件和目录属性的比较，并且可以包含变量、常量和运算符。运算符可以是字符串运算符、整数运算符、文件运算符或布尔运算符 — 我们将在以下各部分依次介绍每一种运算符。
COMMENT

if test 1 -gt 0; then echo "it's true"; echo 'we need a semicolon here' # 'test 1 -gt 0' is one line, and then echo "it's true" is next line, so a semicolon is need"
fi

if test 1 -gt 0 
then
	echo "it's true"
fi
 
