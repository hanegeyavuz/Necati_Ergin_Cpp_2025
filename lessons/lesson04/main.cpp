#include <iostream>
using namespace std;
#if 0
int main(){

    std::cout << "lesson04" << std::endl;

}
#endif

#if 0
int main(int argc, char const *argv[])
{
    int x1; /* default init -> garbage value */
    int x2{}; /* value init -> zero initialization */

    //std::cout << x1; /*UNDEFINED BEHAVIOR*/
    std::cout << x2; /*LEGAL -> value = 0*/


}

#endif


#if 0
int main(int argc, char const *argv[])
{
    double dval = 3.5;
    int x1 = dval;
    int x2(dval);
    int x3{dval}; /*Geçersiz. No implicit conversion in value initialization*/
}

#endif

#if 0
int main(int argc, char const *argv[])
{
    int x = 5;
    int* ptr = &x;
    int ar[10]{};
    
    int& r1 = x;
    int& r2 = *ptr;
    int& r3 = ar[3];
    //int& r4 = ar; /*invalid.  error: cannot bind rvalue '(int)((int*)(& ar))' to 'int&'*/
    //int& r4 = ptr; /*error: cannot bind rvalue '(int)ptr' to 'int&'*/
    int*& r = ptr; /*legal*/
}

#endif

#if 0

int main(int argc, char const *argv[])
{
    using namespace std;
    int x = 31;
    int* ptr = &x;
    int& r1 = x;
    
    cout << "x = " << x << '\n'<< "*ptr = "<< *ptr << '\n' << "r1 = " << r1 << '\n'<< endl;

}

#endif
#if 0

int main(int argc, char const *argv[])
{
    using namespace std;
    int x = 31;
    int y = 69;
    int* ptr = &x;
    int& r1 = x;
    
    cout << "x = " << x << '\n'<< "*ptr = "<< *ptr << '\n' << "r1 = " << r1 << '\n'<< endl;

    r1 = y; /* x e y değerini atar. x = y ile eşdeğerdir. Rebind etmez!!*/
    cout << "x = " << x << '\n'<< "*ptr = "<< *ptr << '\n' << "r1 = " << r1 << '\n'<< endl;

    r1 = 21;
    cout << "x = " << x << '\n'<< "*ptr = "<< *ptr << '\n' << "r1 = " << r1 << '\n'<< endl;

}

#endif

#if 0

int main(int argc, char const *argv[])
{
    using namespace std;
    int x = 31;
    int& r1 = x;
    int& r2 = r1;
    int& r3 = r2;
    ++r1;
    ++r2;
    ++r3;

    cout << "x = " << x << '\n'<< "*r1 = "<< r1 << '\n' << "r2 = " << r2 << '\n'<< endl;
    cout << "r3 = " << x << '\n'<< endl;

}

#endif

#if 0

int main(int argc, char const *argv[])
{
    using namespace std;
    int ar[4]{1,2,3,4};
    int* ptr = ar;
    int*& r1 = ptr;
    ++r1;

    cout << "*ptr = " << *ptr << endl;
    cout << "*r1 = " << *r1 << endl;

}

#endif
#if 0
/*reference initialization*/
int main(int argc, char const *argv[])
{
    using namespace std;
    int x = 5;
    int& r1 = x; /*copy initialization*/
    int& r2(x);  /*direct initialization*/
    int& r3{x};  /*direct list initialization*/

    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "r3 = " << r3 << endl;

}

#endif
#if 0
int main(int argc, char const *argv[])
{
    using namespace std;
    int x = 5;
    int& r1 = x; /*copy initialization*/
    int& r2(x);  /*direct initialization*/
    int& r3{x};  /*direct list initialization*/

    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "r3 = " << r3 << endl;

}

#endif

#if 0

void foo(int x){
    x = 12;
}
void bar(int* p){
    *p = 123;
}
void baz(int& r){
    r = 1234;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    int x = 0;
    cout << "x = " << x << endl;
    foo(x);
    cout << "x = " << x << endl;
    bar(&x);
    cout << "x = " << x << endl;
    baz(x);
    cout << "x = " << x << endl;
}

#endif

#if 1

void swap(int& r1,int& r2){
    int temp = r1;
    r1 = r2;
    r2 = temp;
}

int main(int argc, char const *argv[])
{
    int x = 30;
    int y = 19;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    swap(x,y);
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

}

#endif