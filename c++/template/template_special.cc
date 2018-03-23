#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>

using namespace std;

template <class T> T GetMax (T a, T b) {
    T result;
    result = (a>b)? a : b;
    return (result);
}


template <class T> 
class Tpair {
    T value1, value2;
public:
    Tpair (T first, T second){
        value1=first;
        value2=second;
    }

    T module () {return 0;}
};


template <>
class Tpair <int> {
	int value1, value2;
	public:
        Tpair (int first, int second){
	        value1=first;
	        value2=second;
	}
        int module ();
};

//A full class template specialization is not a template any more, it is a regular class. Hence you don't need template<> when defining its members:

//template <> 

int Tpair<int>::module() {
    return value1%value2;
}



//template class for function object
//actually function object is to overrid operator()
template<typename T> struct A
{
   T operator()(const T& lhs, const T& rhs){ return lhs-rhs; }
};


int main () {
    int i=5, j=6, k;
    long l=10, m=5, n;
    k=GetMax(i,j);
    n=GetMax(l,m);
    cout << k << endl;
    cout << n << endl;


   Tpair <int> myints (100,75);
   Tpair <float> myfloats (100.0,75.0);
   cout << myints.module() << '\n';
   cout << myfloats.module() << '\n';


   A<int>  afunc;

   int ret = afunc(100, 40);

   printf(" a function result is %d \n", ret);



   uint32_t a1 = 32134;
   uint32_t a2 = 0XFFEEFFFF;
   uint32_t a3 = a1 - a2;
   printf(" a3 result is %u \n", a3);



   return 0;


  

}
