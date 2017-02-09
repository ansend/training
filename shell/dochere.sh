#!/bin/bash


TEST="ansen"
cat<<'$TEST'
this is a doc here
text block in with a '
quote, all char will
print directly without 
any escape or interpreter
/ \n \t  $TEST	${TEST}
" test "
$TEST

cat<<TEST
this is a doc here
text block in with a '
quote, all char will
print directly without 
any escape or interpreter
/ \n \t  $TEST  ${TEST}
"test "
TEST

cat<<"TEST"
this is a doc here
text block in with a '
quote, all char will
print directly without 
any escape or interpreter
/ \n \t  $TEST  ${TEST}
"test "
TEST

echo "creating hello.c..."  
echo  
cat <<'EOF' > hello.c  
#include <stdio.h>  
 
int main()  
{  
    printf("Hello world!\n");  
    return 0;  
}  
EOF
 
echo "compiling hello.c..."  
echo  
#compile hello.c,create the excutable file  
gcc -o hello hello.c  
 
#if compile successfully,then excute it  
if [ $? -eq 0 ];then  
    echo "excute hello..."  
    echo  
    chmod u+x hello  
    ./hello  
else  
    echo 'Compile Error:hello.c'  
fi  
