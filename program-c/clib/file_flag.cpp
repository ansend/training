#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include <iostream>

using namespace std;
int main()  
{  
    int fd;  
  
    fd = open("new.txt",O_RDWR | O_APPEND);  
  
    off_t Position = lseek(fd,0,SEEK_CUR);  
  
    cout << "1st time check the  Position is : " <<  Position << endl;  
  
    char buf = 'G';  
  
    if(write(fd,&buf,1) == -1)  
    {  
        cout << "write is wrong!" << endl;  
    }  
  
    Position = lseek(fd,0,SEEK_CUR);  
  
    cout << "2nd time check the position after 1 write " << Position<< endl;  
  
  
    Position = lseek(fd,0,SEEK_SET);  
    cout << "3rd time check the positon ,after invoke lseek to set the pos  :" << Position << endl;  
  
    buf = 'P';  
    if(write(fd,&buf,1) == -1)  
    {  
        cout << "wrong" << endl;  
    }  
  
    Position = lseek(fd,0,SEEK_CUR);  
    cout << "4th time check the postion,after 2 write :" << Position << endl;  
  
  
    close(fd);  
    return 0;  
}  
