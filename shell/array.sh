if [ $# -lt 1 ];then
        echo "usage:$0 cmd"
        exit 1
fi

allsvrs=('hadoop-svr1' 'hadoop-svr2' 'hadoop-svr3' 'hadoop-svr4' 'hadoop-svr5' 'hadoop-svr6')
echo ${allsvrs[@]} #both ${array[*]} and  ${array[@]} represent the entire array.
echo ${allsvrs[*]} #aka the ${array[*}} is the same thing with ${array[@]}

for i in `seq 0 5`
do
	echo ${allsvrs[$i]}
done
len=${#allsvrs[@]}
echo "array len is " $len
for svr in ${allsvrs[@]}
do
        echo $svr
	
        #ssh -p32200 $svr "$@"
done
