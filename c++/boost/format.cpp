#include <stdio.h>
#include <iostream>
#include <string>
#include <boost/format.hpp>
  
using namespace std;

int main(int argc, char* argv[])
{ 

     // print 字符串里% 是跳出符
     printf("%.2f %% %d \n", 12.5, 100);
     // 使用%序号%的方式给出指示符， 后面用%连接对应的数据。
     cout << boost::format("writing %1%,  x=%2% : %3%-th try") % "toto" % 40.23 % 50 << endl;
     // 输出:writing toto,  x=40.23 : 50-th try
    
     // 可以延迟使用，顺序不必一致
     boost::format fmter("%2% %1%");
     fmter % 36;
     fmter % 77;
     cout << fmter << endl;
     // 输出:77 36
    
     // 可重用
     fmter % 12;
     fmter % 24;
     cout << fmter << endl;
     // 输出:24 12
   
     // 可直接转成字符串
     std::string s = fmter.str();
     std::string s2 = str( boost::format("%2% %1% %2% %1%")%"World"%"Hello");
   
     cout << s << endl << s2 << endl;
     // 输出:
     // 24 12
     // Hello World Hello World
   
     // 可以使用printf指示符
     cout << boost::format("%3.1f - %.2f%%") % 10.0 % 12.5  << endl;
     // 输出:10.0 - 12.50%
   
     // printf指示符里使用N$指定使用第几个参数
     cout << boost::format("%2$3.1f - %1$.2f%%") % 10.0 % 12.5  << endl;
     // 输出:12.5 - 10.00%
   
     cin.get();
     return 0;
} 
