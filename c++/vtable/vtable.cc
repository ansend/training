#include <iostream>
using namespace std;
class Base {

     public:

     virtual void f() { cout << "Base::f" << endl; }

     virtual void g() { cout << "Base::g" << endl; }

     virtual void h() { cout << "Base::h" << endl; }
};

class Derived {

     public:

     virtual void f() { cout << "Derived::f" << endl; }

     virtual void g() { cout << "Derived::g" << endl; }

     virtual void h() { cout << "Derived::h" << endl; }
};


typedef void(*Fun)(void);

Base b;
Derived d;

int main(int argc, char** argv)
{
   Fun pFun = NULL;
   Fun pFun1 = NULL; 
   Fun pFun2 = NULL; 
   cout << "虚函数表地址：" << (int*)(&b) << endl;
  
   cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&b) << endl;
  
   // ptr[0]   equal *ptr, ptr[1] equal *(ptr+1)
  
   int ** pVtable = (int**)&b;
   

   // Invoke the first virtual function 
  
   //pFun = (Fun) *(int*)(*(int*)&b);


   // pFun = (Fun)pVtable[0][0];
   
     
   pFun = (Fun) *(int*)(*(int*)&b);
   pFun();
  
   pFun1 = (Fun) *((int*)(*(int*)&b) + 1);
   pFun1();

   pFun2 = (Fun) *((int*)(*(int*)&b) + 1);
   pFun2();

   pFun = (Fun) *(int*)(*(int*)&d);
   pFun();
  
   pFun1 = (Fun) *((int*)(*(int*)&d) + 1);
   pFun1();

   pFun2 = (Fun) *((int*)(*(int*)&d) + 1);
   pFun2();



}  
