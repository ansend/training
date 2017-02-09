#include <stdio.h>
#include <stdint.h>
#include <string>
#include <iostream>

template<typename T>       

int min(T &x, T &y)
{ 
    printf(" in min template function\n");
    return (x<y)?x:y; 
}

int min(int x , int y)
{
    printf(" in min normal functin\n ");
    return  x;
}

void func(int i, char j)

{

   min(i, i);

   min(j, j);

   min(i, j);

   min(j, i);

}

int main (int argc, char** argv)
{
  func(5, 'c');
  return  0;

}

// the static link sequence for this senario please check below link
// http://blog.csdn.net/beyondhaven/article/details/4204345
