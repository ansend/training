#include<stdio.h>  
#include<string.h>  

// 将字符串s1中任何与字符串s2中字符匹配的字符都删除。     

//void squeeze(char s1[], char s2[])  
//{  
//    int i = 0;  
//    int j = 0;  
//    int n = 0;  
//    int t;  //表示s1与s2的元素是否相同，1为相同，0为不同  
//    while(s1[i] != '\0')  
//    {  
//        t = 0;  
//        j = 0;  
//        while(s2[j] != '\0')  
//        {  
//            if(s1[i] == s2[j])  
//                t = 1;  
//            j++;  
//        }  
//        if(t == 0)  
//            s1[n++] = s1[i];  
//        i++;  
//    }  
//    s1[n] = '\0';  
//}  
  
void squeeze(char s1[], char s2[])  
{  
    int i, j, k;  
    for(i = k =0; s1[i] != '\0'; i++)  
    {  
        for(j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++)  
            ;  
        if(s2[j] == '\0')  
            s1[k++] = s1[i];  
    }  
    s1[k] = '\0';  
}  
int main()  
{  
    char s1[] = "abgghcbd";  
    char s2[] = "bcd";  
    squeeze(s1,s2);  
    printf("%s", s1);  
    return 0;  
}  
