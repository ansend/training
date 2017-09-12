#! /bin/bash

# number operation
counter=10
echo $counter   
((counter=counter+2))   
echo $counter

let "counter=$counter+4" 
echo $counter

counter=`expr $counter + 3`  
echo $counter

counter=$[$counter-2]  
echo $counter

#loop 
while [ $counter -gt 0 ] 
do

	counter=$[$counter-2]  
	echo $counter


done

for i in `seq 1 10`
do
	echo $i
done


for (( a=1, b=10; a<=10; a++, b-- ))  
do  
    ((c=a*b))  
    echo $c  
done 


list="server1 server2 server3 server4 server5"
# here  equal to for i in server1 server2 server3 server4 server5
for i in $list
do
	echo $i
done

#all the character in quote mark are treated as a single varable.
for i in "server1 server2 server3 server4 server5"
do
	echo $i
done


#all the character in quote mark are treated as a single varable.
for i in server1 server2 server3 server4 server5
do
	echo $i
done

