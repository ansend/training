#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>                                          
#include <boost/format.hpp>
class A                                                      
{  
public: 
   A()                                                       
   {
     printf("construct class A\n");                             
   } 
   virtual ~A()                                               
   {                                                         
     printf("destruct class A\n");                              
   }
};                                                            
  
class B                                                      
{ 
	public:
  B(boost::shared_ptr<A> pa):a(pa)                                             
  {                                                          
     printf("consturce class B\n");                             
  }                                                          
     
  virtual ~B()                                               
  {                                                          
     printf("descuruse class B\n");                            
  }
                                                             
private:                                                     
  boost::shared_ptr<A> a;
};
  
class C
{  
        public:
  C(A*pa):a(pa)
  {            
     printf("consturce class C\n");
  }                               
    
  virtual ~C()
  {
     printf("descuruse class C\n");
  }
               
private:                          
   A *a;
};
                                                         
A * pa;   
int main(int argc, char ** argv)                             
{           
   boost::shared_ptr<A> pp (new A());
   pp.reset();
   if (pp == NULL)
  {
    std::cout << "pp is null" << std::endl;
  }
  else                                                                                                                      
  {
    std::cout << "pp is not null" << std::endl;
  }

  boost::shared_ptr<A> nil;
   if (nil == NULL)
  {
    std::cout << "nil is null" << std::endl;
  }
  else                                                                                                                      
  {
    std::cout << "nil is not null" << std::endl;
  }


   pa = new A();
   boost::shared_ptr<A> spa(pa);
   
   B b(spa);
   A * pa1 = new A();
   C c(pa1); // pa1 will not be deleted auto without smart pointer.
   while(1)
	   sleep(5);
}

