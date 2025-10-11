#include <cstdio>
#include <iostream>
using namespace std;
#if 0
/*Function Overloading*/

void foo(int){cout << "int" << endl;}
//void foo(int,int = 0){cout << "int,int=";}
void foo(double){cout << "double" << endl;}
void foo(long double){cout << "long double" << endl;}


int main(int argc, char const *argv[])
{
    foo(10);
    // foo(10,11);
    foo(10.1);
    foo(10.2l);

}

#endif
#if 0
/*more than 1 viable std. conv. function case*/
void foo(double){cout << "double" << endl;}
void foo(long double){cout << "long double" << endl;}
void foo(int){cout << "int" << endl;}
void foo(bool){cout << "bool" << endl;}


int main(int argc, char const *argv[])
{
    foo(10.31f); /*Exact match*/
    foo(true); /*promotion*/

}
#endif
#if 0
/*more than 1 viable std. conv. function case AMBIGUITY*/

void foo(char){cout << "double" << endl;}
void foo(long double){cout << "long double" << endl;}


int main(int argc, char const *argv[])
{
    foo(10.31f); /*AMBIGUITY!*/

}
#endif
#if 0
/*AMBIGUITY example 2*/

void foo(unsigned int){cout << "double" << endl;}
void foo(long double){cout << "long double" << endl;}


int main(int argc, char const *argv[])
{
    foo(10); /*AMBIGUITY!*/

}
#endif
#if 0
/*AMBIGUITY example 3*/

void foo(unsigned int){cout << "double" << endl;}
void foo(long double){cout << "long double" << endl;}


int main(int argc, char const *argv[])
{
    foo(10.1f); /*AMBIGUITY!*/ /*no promotion from float to long double*/

}
#endif
#if 0
/*Special Case 1*/
void foo(int x, int y = 0);
void foo(int x);

int main()
{
    foo(5); /*AMBIGUITY!*/
}

#endif
#if 0
/*Special Case 2*/
void foo(int&);
void foo(int x);

int main()
{
    int x = 6;
    foo(x); /*AMBIGUITY!*/
    foo(6); /* NO AMBIGUITY!*/ /*Parameter is not L Value, "6" is PRvalue*/
}

#endif
#if 0
/*Special Case 3*/
void foo(const int&);
void foo(int x);

int main()
{
    int x = 6;
    foo(x); /*AMBIGUITY!*/
    foo(6); /* AMBIGUITY!*/ /*const reference can refere to PRvalues*/
}

#endif
#if 0
/*Special Case 3*/
void foo(const int&);
void foo(int x);

int main()
{
    int x = 6;
    foo(x); /*AMBIGUITY!*/
    foo(6); /* AMBIGUITY!*/ /*const reference can refere to PRvalues*/
}

#endif
#if 0
/*Special Case 4*/
void foo(const int*); /*This function will call*/
void foo(int* ); 

int main()
{
    const int y = 10;
    foo(&y); 
}

#endif
#if 1
/*Special Case 5*/
void foo( int&){ /*L Value Reference*/
    cout << "int&" <<endl;
}
void foo(const int&){ /*const L Value Reference*/
    cout << "const int&" <<endl;
}
void foo(int&&){ /*R value Reference*/
    cout << "int&&" <<endl;
}

int main()
{
    const int y = 0;
    int x{};
    foo(x); 
    foo(15);
    foo(y);
}

#endif