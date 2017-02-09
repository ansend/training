#include <iostream>
#include <vector>
#include <algorithm>
#include "boost/function.hpp"
#include "boost/bind.hpp"

void print_new_value(int i) {
  std::cout <<\
    "The value has been updated and is now " << i << "\n";
}

void interested_in_the_change(int i) {
  std::cout << "Ah, the value has changed./n";
}

class notifier {
  typedef boost::function<void(int)> function_type;
  std::vector<function_type> vec_;
  int value_;
public:
  template <typename T> void add_observer(T t) {
    //function_type ff(t);
    //vec_.push_back(function_type(ff));
    
    //function_type * test = new function_type(t);
    vec_.push_back(function_type(t));
  }

  void change_value(int i) {
    value_=i;
    for (std::size_t i=0;i<vec_.size();++i) {
      vec_[i](value_);
   }
  }
};

class knows_the_previous_value {
  int last_value_;
  bool first_time;
public:
  knows_the_previous_value(int def=0):last_value_(def),first_time(true){};
  void operator()(int i) {
    if (first_time) {
      last_value_=i;
      std::cout << 
        "This is the first change of value, \
so I don't know the previous one.\n";
      first_time=false;
      return;
    }
    std::cout << "Previous value was " << last_value_ << '\n';
    last_value_=i;
  }
};

class knowvalue1 {

   public:
   int cur_value;
   knowvalue1(int value=0):cur_value(value){};

   void setvalue(int v){
	   std::cout<< "before cur value is " << cur_value << '\n';
	   cur_value = v;
	   std::cout<< "1cur value is " << cur_value << '\n';
   }
};

class knowvalue2 {

   public:
   int cur_value;
   knowvalue2(int value=0):cur_value(value){};

   void setvalue(int v){
	   cur_value = v;
	   std::cout<< "2cur value is " << cur_value << '\n';
   }
};



int main() {
  notifier n;
  //n.add_observer(&print_new_value);
  //n.add_observer(&interested_in_the_change);
  //n.add_observer(knows_the_previous_value());

  knows_the_previous_value * test = new knows_the_previous_value();
 
  knowvalue1 v1(10);

  boost::bind(&knowvalue1::setvalue, &v1,_1) (11);
  n.add_observer(boost::bind(&knowvalue1::setvalue, &v1, _1));

 
  n.add_observer(*test);
  n.change_value(30);
  n.change_value(42);

  (*test)(50);
  (*test)(52);

  knows_the_previous_value ff;
  ff(100) ;
  ff(101) ;
  std::cout << '\n';
}
