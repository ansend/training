#! /bin/bash

echo "PID of this script: $$"

#exec  
#exec  1> tmplog
# number operation

#getopts opstring variable

<< end
optstring 值类似于getopt的optstring，有效的option字母都会包含再optstring中，
如果这个option需要一个参数，则在字母后加上一个冒号。 如果需要忽略错误信息
的话可以再optstring前加上一个冒号。

两个全选环境变量OPTARG和OPTIND
如果选项需要跟一个参数值，OPTARG环境变量就会保存这个值
OPTIND环境变量保存了参数列表中getopts正在处理的参数位值。
end
echo "beginning of the option is : $OPTIND"
while getopts :ab:c opt
do
    case "$opt" in
      a)  echo "find -a option at $OPTIND";;
      b)  echo "find -b option at $OPTIND with parameter $OPTARG";;
      c)  echo "find -c option at $OPTIND";;
      *)  echo "find undefined option: $opt $OPTIND";;
    esac
done

shift $[ $OPTIND -1 ]

count=1
for param in "$@"
do
	echo "Parameter $count: $param"
	count=$[ $count + 1]
done



