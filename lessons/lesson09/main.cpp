#include <iostream>
#include <cstdio>

using namespace std;

#if 0

class Myclass{};

void foo( Myclass&){ /*non-const L Value Reference*/
    cout << "Myclass&" <<endl;
}
void foo(const Myclass&){ /*const L Value Reference*/
    cout << "const Myclass&" <<endl;
}
void foo(Myclass&&){ /*R value Reference*/
    cout << "Myclass&&" <<endl;
}

int main()
{
    Myclass class_obj{};
    const Myclass const_class_obj{};
    foo(class_obj); 
    foo(const_class_obj);
    foo(Myclass{});
}
#endif

#if 0
void foo(int);
void foo(int&);
int main(int argc, char const *argv[])
{
    int x{};
    foo(x); /*AMBIGUITY!*/
}
#endif

#if 0
void foo(bool);
int main(int argc, char const *argv[])
{
    int x{};
    foo(&x); /*LEGAL*/ /* Implicit Conversion from T* to bool*/
}
#endif

#if 0
void foo(void*);
int main(int argc, char const *argv[])
{
    int x{};
    foo(&x); /*LEGAL*/ /* Conversion from T* to void* */
}
#endif

#if 0
void foo(bool){
    cout << "foo(bool)" << endl;
}
void foo(void*){
    cout << "foo(void*)" << endl;
}

int main(int argc, char const *argv[])
{
    int x{};
    foo(&x); 
}
#endif

#if 0
void foo(int x, int y = 5){}
void foo(int){}

int main(int argc, char const *argv[])
{
    int x{};
    foo(&x); /*AMBIGUITY!! */
}
#endif
#if 0
/*Function Overload Resolution with Multiple Parameters*/
void foo(int, double, long){cout << "1" << endl;} //  1
void foo(float,unsigned,int){cout << "2" << endl;} // 2
void foo(double,char,int){cout << "3" << endl;} //    3

int main(int argc, char const *argv[])
{
    foo(12,3.4,3.3f); /*1 çağırılır*/
    foo(3.4f,45,7u); /*2 çağırılır*/
    foo(3.4,34,7); /*3 çağırılır*/ /*ilk parametre float olsaydı 2. fonksiyon çağırılırdı*/
}
#endif

#if 0
int foo(int){cout << "foo cagirildi" << endl;}
int main()
{
    typedef int inta10_t[10];
    typedef int (*fp_t)(int);
    typedef int& iref_t;

    using inta10_u = int[10];
    using fp_u = int(*)(int);
    using iref_u = int&;

}

#endif

#if 0
/*Classes*/

int bar(int); /*global function-Free Function*/

class Data{
    /*Data members*/
    int x;
    int(*fp)(int); 
    float fval;
    double dval;
    /*member function*/
    void foo(int); 
};

int main()
{
    
}

#endif
#if 0
/*Classes*/

int bar(int); 

struct Data{
    /*default access -> public*/
    int x;
    int(*fp)(int); 
    float fval;
    double dval;
    void foo(int); 
};

int main()
{
    Data mydata;
    Data* ptr = &mydata;
    mydata.dval = 31.0f;
    mydata.foo(31);
    ptr->x = 12;

}

#endif
#if 0
/*Classes*/

int bar(int); 

class Data{
    /*default access -> private*/
    int x;
    int(*fp)(int); 
    float fval;
    double dval;
    void foo(int); 
};

int main()
{
    Data mydata;
    Data* ptr = &mydata;
    mydata.dval = 31.0f;
    mydata.foo(31);
    ptr->x = 12;

}

#endif

#if 1
/*access specifiers*/
class Myclass{
                // Private Field
public:         // Public Field
    int ax;
private:        // Private Field
    int bx;
};

int main(int argc, char const *argv[])
{
    Myclass mclass;
    mclass.ax = 11; /*LEGAL*/
    //mclass.bx = 11; /*ILLEGAL*/
}

#endif