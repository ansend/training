#include <stdio.h>
#include <assert.h>

#include <memory>
#include <iostream>
#include <vector>

#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;

class Int 
{
public:
   Int( int i ) 
   {
      x = i;
      cout << "Constructing " << ( void* )this << " Value: " << x << endl; 
   };
   ~Int( ) 
   {
      cout << "Destructing " << ( void* )this << " Value: " << x << endl; 
   };

   int x;
};

int main( ) 
{
   scoped_ptr<Int> pi ( new Int( 5 ) );
   scoped_ptr<Int> pg ( new Int( 8 ) );

   if (pi)
   {
        cout << "pi value is " << pi->x << endl;
        cout << "pi value is " << (*pi).x << endl;
        //cout << "pi value is " << *pi.x << endl;
   }
   pi.reset( new Int( 6 ) );
   cout << "pi is reset to new int 6 " << endl;
   Int* pi2 = pi.get ( );

   //pi == pg ;//should cause compile error since "==" and "!=" operation are both private between scoped_ptr.
   
       pi.reset();
   assert(pi == 0);
   //Int* pi3 = pi.release ( );
   /*
   if ( pi2 == pi3 )
      cout << "pi2 == pi3" << endl;
   */
   //delete pi3;
   
}
