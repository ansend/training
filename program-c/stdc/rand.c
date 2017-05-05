#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv)
{

// if srand is not called before rand()
// system will call srand(1) automatically.


//srand();

for(int i=0; i< 10; i++)
{
	printf("%d  ",rand());
}

	printf("\n");


srand(1);
for(int i=0; i< 10; i++)
{
	printf("%d  ",rand());
}

	printf("\n");


}
