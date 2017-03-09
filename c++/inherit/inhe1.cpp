#include <iostream>
using namespace std;  


class Base
{
  public:
	 virtual void function4()=0;
	 virtual void function5()=0;

};


class A : Base 
{  
public:  
    int m;  
    int n;  
public:  
   virtual void function1()  
    {  
        cout<<"这是基类的普通函数function1\n";  
	function4();
    }  
    void virtual function2()  
    {  
        cout<<"这是基类的虚函数function2\n";  
    }  
    static void function3()  
    {  
        cout<<"这是基类静态成员函数function3\n";  
    }  
    void function4()
    {
        cout<<"this is in Base A function4\n"<<endl;
    }

    void function5()
    {
       cout<<"这是A基类的普通函数function\n";
       function4();
    }

};  
  
class B:public A  
{  
public:  
   /*
    virtual void function1()  
    {  
        A::function1();  
    }
   */  
    void  function2()  
    {  
        cout<<"这是派生类的函数function2\n";  
        A::function2();  
    }  
    void function4()
    {
        cout<<"this is in Base B function4\n"<<endl;
    }


};  
  
  
int main()  
{  
 //   B b;  
  //  b.function1(); // (1)  
   // b.function2(); // (2)  
   // A::function3();// (3)  
  
    A *a;  
    a=new B;  
    a->function5(); // (4)   
    a->function2(); // (5)  
    a->function3(); // (6)
}
