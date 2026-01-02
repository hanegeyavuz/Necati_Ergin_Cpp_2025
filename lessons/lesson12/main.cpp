#include <iostream>
using namespace std;
#if 0
#include "yavuz.h"


int main()
{
    int a = 5;
    int b = 33;
    
    cout << "sum square: "<< sum_square(a,b) << "\n";
}


#endif

#if 0
/*constructor*/
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "default ctor called" << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called" << "\n";
    }
private:
};


int main()
{
    MyClass m1;
    MyClass m2(31);
}

#endif
#if 0
/*destructor*/
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "default ctor called" << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called" << "\n";
    }
    ~MyClass(){/*dtor*/
        cout << "deconstructor called" << "\n";
    } 
private:
};


int main()
{
    MyClass m1;
    MyClass m2(31);
}

#endif
#if 0
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "MyClass default ctor called this = " << this << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called this = " << this <<"\n";
    }
    ~MyClass(){/*dtor*/
        cout << "MyClass deconstructor called this = " << this << "\n";
    } 

    void foo(){
        cout << "foo called this = " << this << "\n";
    }
private:
};

MyClass m;

int main()
{
    cout << "main started" << "\n";
    cout << "&m = " << &m << "\n";
    m.foo();
    cout << "main ended" << "\n";
}
#endif
#if 0
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "MyClass default ctor called this = " << this << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called this = " << this <<"\n";
    }
    ~MyClass(){/*dtor*/
        cout << "MyClass deconstructor called this = " << this << "\n";
    } 

    void foo(){
        cout << "foo called this = " << this << "\n";
    }
private:
};



int main()
{
    {
    MyClass m;
    cout << "main started" << "\n";
    cout << "&m = " << &m << "\n";
    m.foo();
    }
    cout << "main ended" << "\n";
}
#endif
#if 0
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "MyClass default ctor called this = " << this << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called this = " << this <<"\n";
    }
    ~MyClass(){/*dtor*/
        cout << "MyClass deconstructor called this = " << this << "\n";
    } 

    void foo(){
        cout << "foo called this = " << this << "\n";
    }
private:
};



int main()
{
    {
    MyClass m[5];
    cout << "main started" << "\n";
    cout << "&m = " << &m << "\n";
    (*m).foo(); /* m[0].foo(); same */
    }
    cout << "main ended" << "\n";
}
#endif
#if 0
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "MyClass default ctor called this = " << this << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called this = " << this <<"\n";
    }
    ~MyClass(){/*dtor*/
        cout << "MyClass deconstructor called this = " << this << "\n";
    } 

    void foo(){
        cout << "foo called this = " << this << "\n";
    }
private:
};



int main()
{
    MyClass m;
    MyClass* p = &m;
    MyClass& rm1 = m;
    MyClass& rm2 = m;

}
#endif
#if 0
class MyClass{
public:

private:
};



int main()
{
    MyClass m; /*default initialization -> default ctor called*/
}
#endif
#if 0
class MyClass{
public:
	MyClass(int);
private:
};

int main()
{
    //MyClass m;  /*no default constructor exists for class "MyClass"*/
}
#endif
#if 0
/*Bassic Interview Quest*/
/*0 ile 100 arasindaki sayilari dongu deyimi kullanmadan yazdiriniz.*/
class MyClass{
public:
    MyClass(){
        static int i = 0;
        cout << i++ << " ";
    }
private:
};

int main()
{
    MyClass m[100]; 
}
#endif
#if 0
class MyClass{
public:
    MyClass(){
        cout << "MyClass() " << "\n";

    }
    MyClass(int x){
        cout << "MyClass(int x) x = " << x << "\n";

    }
private:
};

int main()
{
    MyClass m0; /*default ctor*/
    MyClass m1; /*default ctor*/
    MyClass m2(10);/*direct init*//*MyClass(int)*/   
    MyClass m3{ 2 };/*direct list init*//*MyClass(int)*/  
    MyClass m4(1.2); /*narrowing conversion*/
    //MyClass m5{1.2}; /*list init -> no narrowing conversion*/ /*narrowing conversion of '1.2e+0' from 'double' to 'int' [-Wnarrowing]*/
    MyClass m6 = 6; /*copy init*/ /*MyClass(int)*/

}
#endif
#if 0
class MyClass{
public:
    MyClass();
    int mx,my;
private:
};

MyClass::MyClass(){
    mx = 10; /*assignment*/
    my = 22; /*assignment*/
}

int main()
{


}
#endif
#if 0
class MyClass{
public:
    MyClass();
    int mx,my;
private:
};

MyClass::MyClass(){
    cout << "mx = " << mx << " my = " << my << "\n"; /*garbage values*/
}

int main()
{
    MyClass m1;

}
#endif
#if 1
/*Ctor Init List*/
class MyClass{
public:
    MyClass();
private:
    int mx,my;
};

MyClass::MyClass() : mx(5), my(30)
{
    cout << "mx = " << mx << " my = " << my << "\n"; /*garbage values*/
}

int main()
{
    MyClass m1;

}
#endif
