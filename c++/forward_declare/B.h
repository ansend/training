#ifndef B_INCLUDE_H
#define B_INCLUDE_H

// 前向声明：可以声明一个类而不定义它。这个声明被称为前向声明(forward declaration)。例如：class name。在声明之后，定义之前，类name是一个不完全类型(incompete type)，即已知name是一个类型，但不知道包含哪些成员。不完全类型只能以有限方式使用，不能定义该类型的对象，不完全类型只能用于定义指向该类型的指针及引用，或者用于声明(而不是定义)使用该类型作为形参类型或返回类型的函数。
// 类的前向声明之适用于指针和引用的定义，如果是普通类类型就得使用include了。 
// 两个类之前的相互引用包含问题。   
//





//#include "A.h"
class A;
class B
{
    A   *a;
    int b;
};







#else


#endif

