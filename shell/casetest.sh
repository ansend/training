#! /bin/bash

echo "PID of this script: $$"

#exec  
#exec  1> tmplog
# number operation

while [ -n "$1" ]
do
    case "$1" in
      -a | --all)  echo "find -a option";;
      -b | --bin)  echo "find -b option";;
      -c | --conf) echo "find -c option";;
         *)        echo "find undefined option: $1";;
    esac
    shift    
done





