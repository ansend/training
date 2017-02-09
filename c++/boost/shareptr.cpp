#include <stdio.h>
#include <unistd.h>
// shared_ptr::get example
#include <iostream>
#include <memory>
#include <boost/format.hpp>


int main () {
  int* p = new int (10);
  boost::shared_ptr<int> a (p);
  boost::shared_ptr<int> b (a);

  if (a.get()==p)
    std::cout << "a and p point to the same location\n";

  // three ways of accessing the same address:
  int* q = a.get();

  int* y = new int (12);
  //delete q;
  

  std::cout << *a.get() << "\n";
  std::cout << *a << "\n";
  std::cout << *p << "\n";


  std::cout << a.use_count() << "\n";
  std::cout << b.use_count() << "\n";
  b.reset(y);
  std::cout << a.use_count() << "\n";
  std::cout << b.use_count() << "\n";
  return 0;
}
