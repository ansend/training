#include <iostream>
using namespace std;

class A
{
public:
    virtual void out1()=0;  ///由子类实现
    virtual ~A(){};
    virtual void out2() ///默认实现
    {
        cout<<"A(out2)"<<endl;
    }
    void out3() ///强制实现
    {
        cout<<"A(out3)"<<endl;
    }
};

class B:public A
{
public:
    virtual ~B(){};
     void out1()
    {
        cout<<"B(out1)"<<endl;
    }
    void out2()
    {
        A::out2();
        cout<<"B(out2)"<<endl;
    }
    void out3()
    {
        cout<<"B(out3)"<<endl;
    }
};
class C:public B
{
public:
    virtual ~C(){};
    void out1()
    {
        cout<<"C(out1)"<<endl;
    }
    void out2()
    {
        cout<<"C(out2)"<<endl;
    }
    void out3()
    {
        cout<<"C(out3)"<<endl;
    }
};


int main()
{
    A *ab=new B;
    ab->out1();
    ab->out2();
    ab->out3();
    cout<<"************************"<<endl;
    B *bb=new B;
    bb->out1();
    bb->out2();
    bb->out3();
    cout<<"************************"<<endl;
    A *bc=new C;
    bc->out1();
    bc->out2();
    bc->out3();


    cout<<"object not pointer*********"<<endl;
    B obb;
    obb.out1();
    obb.out2();
    obb.out3();

    B().out1();
    B().out2();
    B().out3();

    delete ab;
    delete bb;
    delete bc;
    return 0;
}
