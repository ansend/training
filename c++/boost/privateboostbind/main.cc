#include <iostream>
using namespace std;

class copyable
{
    public:
       virtual ~copyable(){};

};

template<class ret_type, class arg_type>
class function_base: public copyable
{
   public:
      virtual ~function_base() {}
      virtual ret_type operator() (arg_type arg) = 0;
};

template<class ret_type, class arg_type>
class function1: public function_base<ret_type, arg_type>
{
       public:
        
          typedef ret_type (* NORM_PROC) (arg_type);
        
          function1(NORM_PROC proc = 0): fun_(proc){}

          //ret_type operator() (arg_type arg) { fun_->operator()(arg); }
          ret_type operator() (arg_type arg) { fun_(arg); }
	  
        
      private:
        
          NORM_PROC fun_;
 
};

template<class CS, class ret_type, class arg_type>
class function2: public function_base<ret_type, arg_type>
{
    public:
        typedef ret_type (CS::* MEM_PROC)(arg_type);
        function2(CS* obj, MEM_PROC proc): obj_(obj), proc_(proc) {}
        ret_type operator() (arg_type arg) { return (obj_->*proc_)(arg); }

    private:
        CS* obj_;
        MEM_PROC proc_;
};

template<class ret_type, class arg_type>
class function: public copyable
{
   public:
     
     function(function_base<ret_type, arg_type>* pf): obj_(pf) {;}
     ret_type operator()(arg_type arg){obj_->operator()(arg);}

   private:
      function_base<ret_type, arg_type>* obj_;
};

template<class CS, class ret_type, class arg_type> 
//Here the first parameter of the template function 'bind'
//is actually a function pointer called 'proc', proc is member
//function of class CS , and it's return type is ret_type 
//and it's only parameter's type is arg_type. 
function<ret_type, arg_type> bind(ret_type (CS::* proc)(arg_type), CS* pc)
{
    return new function2<CS, ret_type, arg_type>(pc, proc);
}


//another bind for function1 for function pointer.
template< class ret_type, class arg_type>
function<ret_type, arg_type> bind(ret_type (* proc)(arg_type))
{
    return new function1<ret_type, arg_type>(proc);
}




class cs
{
   public:
      
       int proc(double d) { cout << "mem func proc:" << d << endl; return (int)d;}
};


int Proc(double d)
{
   cout << "normal proc:" << d << endl;
   return (int)d;
}


int main()
{
   //function fun = &Proc;
   //fun(2.3);
   bind(&Proc)(2.3);
 
   cs c;
   bind(&cs::proc, &c)(3.3);
   //fun = bind(&cs::proc, &c);
   //fun(3.3);

   return 0;
}
