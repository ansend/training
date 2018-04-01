#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>


using namespace std;  

class A  
{  
public:  
    int m;  
    int n;  
public:  
    int get_pri_age()
    {
        return pri_age;
    }
    void set_pri_age(int age)
    {
        pri_age = age;
    }

    inline void hello()
    {
        cout << "inline function does not be impactted with private inherit"<<endl;
    }
 
private:
    int pri_age;
};  


void lock(A* a)
{
    a->hello();
}



class B:private A  
{  
public:  
    void  function2()  
    {  
        cout<<"这是派生类的函数function2\n";  
        //cout << pri_age << endl;  so , it's not accessible in derived class.
        //but we can use public interface to access it  to work around.
    }  
    // using private inherit:
    // all public and protected member function  in base class become private
    // in derived class, so you can access them in member function of derived
    // class, but it can not be accessed using derived class object.
    int b_get_pri()
    {
        return get_pri_age(); // here get_pri_age become private in derived class.
    }
    int b_set_pri(int age)
    {
        set_pri_age(age);
    }

    int b_hello()
    {
        //lock(this);
        hello();// inline function is not impactted by private inherit 
    }
};  
  
int main()  
{  
    B b;  
    b.b_set_pri(10);
    int age = b.b_get_pri();
    //b.set_pri_age(12); //error with private inherit.

    
    printf(" get age from object %d \n", age);
    b.b_set_pri(100);
    age = b.b_get_pri();
    printf(" get age from object again %d \n", age);

    //lock(&b);
    b.b_hello();
}
