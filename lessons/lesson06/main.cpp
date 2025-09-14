#include <iostream>
#include <cstdio>
#include <ctime>

#if 0
class Myclass {};

Myclass foo();
Myclass& bar();
Myclass&& baz();

int main(int argc, char const *argv[])
{
    foo(); /* PRValue */
    bar(); /* L Value */
    baz(); /* X Value */
}
#endif
#if 0
/*default arguments*/

int foo(int, int, int = 10){

}

int main(int argc, char const *argv[])
{
    
}

#endif

#if 0
/*default arguments*/
using namespace std;

void process_date(int day = -1, int mon = -1, int year = -1){
    time_t sec;
    time(&sec);
    struct tm* p = localtime(&sec);
    if(year == -1){
        year = p->tm_year + 1900;
    }
    if(mon == -1){
        mon = p->tm_mon + 1;
    }
    if(day == -1){
        day = p->tm_mday;
    }
    cout << "date: " << day << "." << mon << "." << year << endl;
    
}

int main(int argc, char const *argv[])
{
    process_date(15,6);
    process_date(15,6,2025);
    process_date(2,4);
    process_date(5);
    process_date();
}

void process_date(int day, int mon, int year);
#endif

#if 0
/* static type-conversion */
int main(int argc, char const *argv[])
{
    int i1 = 5, i2 = 3;

    double div = static_cast<double>(i1) / i2;
    std::cout << i1 << " / " << i2 << " = " << div << std::endl;

}

#endif

#if 0
/* static type-conversion */
enum color {white,red,blue,brown};

int main(int argc, char const *argv[])
{
    color mycolor = { red };
    int x = static_cast<int>(mycolor);
    int z = 3;
    printf("x = %d\n",x);
    
    mycolor = static_cast<color>(z);
    printf("mycolor = %d\n",mycolor);
}

#endif
#if 0
/* static type-conversion */
int main(int argc, char const *argv[])
{
    int x = 10;
    void* vptr = &x;

    int* iptr = static_cast<int*>(vptr);
    std::cout << "*iptr = " << *iptr << std::endl;
}

#endif
#if 0
/* const type-conversion */
int main(int argc, char const *argv[])
{
    const int x = 30;
    const int* cptr = &x;

    int* iptr = const_cast<int*>(cptr);
    // *iptr = ... /* UNDEFINED BEHAVIOUR!!! */
    std::cout << "iptr = " << *iptr << std::endl;

}

#endif


#if 0

char* my_Strchr(const char* str, char ch){
    while (*str)
    {
        if(*str == ch){
            return const_cast<char*>(str);
        }
        ++str;
    }
    if (ch == '\0')
    {
        return const_cast<char*>(str);
    }
    

    return nullptr;

    
}

int main(int argc, char const *argv[])
{
    char* p = my_Strchr("yavuz",'y');
    std::cout << "*p = " << *p << std::endl;

}

#endif

#if 1
/*reinterpreter type-cast*/
int main(int argc, char const *argv[])
{
    int x = 22;
    char* ch = reinterpret_cast<char*>(&x);

    printf("ch = %d\n",*ch);
    
}
#endif