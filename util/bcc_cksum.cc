#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>


//convert the char string in the hex mode , to a byte of array.
//the lengh of string must be times of 2.
//such as , string "FD33BA2012", will convert to char array of size 5.
//char  array[5] = {0xFD, 0X33, 0XBA, 0X20, 0X12}

//para pstr, the origin string
//para rlen, the length of char array
//return the address of the array
char* str_to_hex( char *pstr, int & rlen)
{

    int len = strlen(pstr);
    rlen = len / 2;
    if (len%2 != 0)
    {
        printf(" Wrong length of string, Must be times of 2\n");
        return NULL;
    }

    char *pt;
    pt = pstr;
    if( !pstr )
    {
        return NULL;
    }
    char * rdata = (char*)malloc(rlen * sizeof(char));
    char * iter = rdata; 
    
    unsigned char ans = 0; // value of byte
    int meet2 = 0;

    while( *pt )
    {
        ans = ans << 4;

        if( ( *pt >=  'A' && *pt <=  'F' ) || ( *pt >=  'a' && *pt <=  'f' ) )  {
               ans =  ans | ((*pt & 0x5f) -0x37);
        }
        else {
               ans  = ans | (*pt) -0x30;
        }

        pt++;
        meet2 ++;
        if(meet2 % 2 == 0)
        {
             *iter++ = ans;
	     ans = 0; // reset ans to 0 for next byte.
        }
    }
    return rdata;
}

//caculate the bcc checksum , the parameter is a string in hex mode
void check_bcc(char * hex_str)
{

   int rlen;
   char * data = str_to_hex(hex_str, rlen);

   unsigned char bcc = 0;

   for(int i = 0; i < rlen; i++)
   {
       bcc^=data[i];
   }

   printf("bcc in hex is %X \n", bcc);
}

int main (int argc, char ** argv)
{
    if(argc < 2)
    {
        printf("usage %s [string in hex mode]\n", argv[0]);
               return 0;
    }
/*
    printf("the origin string in hex mode is %s \n", argv[0]);
    int rlen;
    char * result = str_to_hex(argv[1], rlen);
    char * iter = result;
    while(rlen > 0)
    {
        char tmp = *iter++;
        printf(" %d  ", tmp);
        rlen--;
    }

    printf("\n");
*/

    check_bcc(argv[1]);

}
