#include <iostream>
// using namespace std;

#if 0
/*Ctor Init List*/
class MyClass{
public:
    MyClass();
private:
    int mx,my;
    //const int mcx; /*uninitialized const member in 'const int' [-fpermissive]*/
    //int& mrx; /*uninitialized reference member in 'int&' [-fpermissive]*/
};

MyClass::MyClass() : mx(5), my{30}
{
    cout << "mx = " << mx << " my = " << my << "\n"; /*garbage values*/
}

int main()
{
    MyClass m1;

}
#endif
#if 0
/*Ctor Init List*/
class MyClass{
public:
    MyClass();
private:
    int mx,my;
};

MyClass::MyClass() : my{30}, mx(5) /*once mx, sonra my init edilir.*/
{
    cout << "mx = " << mx << " my = " << my << "\n"; 
}

int main()
{
    MyClass m1;

}
#endif
#if 0
class MyClass{
public:
    MyClass(int a, int b): my_(a), mx_(my_ * b){}; /*UNDEFINED BEHAVIOUR*/
private:
    int mx_,my_;
};

int main()
{
    MyClass m1(3,5);

}
#endif
#if 0
/*KOTU KOD!*/
class MyClass
{
public:
    MyClass(int a, int b) : a(a), b(b) {};

    void print() const
    {
        cout << "a = " << a << "\nb = " << b << "\n";
    }

private:
    int a;
    int b;
};

int main()
{
    MyClass m1(3, 5);
    m1.print();
}
#endif
#if 0
/*FIXED*/
class MyClass
{
public:
    MyClass(int a, int b) : ma_(a), mb_(b) {};

    void print() const
    {
        cout << "ma_ = " << ma_ << "\nmb_ = " << mb_ << "\n";
    }

private:
    int ma_;
    int mb_;
};

int main()
{
    MyClass m1(3, 5);
    m1.print();
}
#endif
#if 0
class MyClass
{
public:
    MyClass(int a, int b) :  mb_(b) {};

    void print() const
    {
        cout << "ma_ = " << ma_ << "\nmb_ = " << mb_ << "\n";
    }

private:
    int ma_ = 31; /*default member Initializer*/
    int mb_;
};

int main()
{
    MyClass m1(3, 5);
    m1.print();
}
#endif
#if 0
class Counter
{
public:
    Counter(int x = 0) : cnt_{x} {}

    ~Counter() = default;
private:
    int cnt_;
};

int main()
{
    Counter cnt;
}

#endif
#if 0
class Counter
{
public:
    Counter(int x = 0) : cnt_{x} {}

    ~Counter() = default;
private:
    int cnt_;
};

int main()
{
    Counter cnt;
}
#endif
#if 0
class Logger
{
public:
    Logger(const char* fname) : f_{std::fopen(fname,"w")} {
        // some codes..
    }

    ~Logger(){
        if(f_){
            std::fclose(f_);
        }
    }
private:
    FILE* f_;
};

int main()
{
    Logger lg("yavuz.txt");
}
#endif
#if 0
/*Special Member Functions*/
class MyClass
{
public:
    MyClass();                              /*default ctor*/
    ~MyClass();                             /*dtor*/
    
    MyClass(const MyClass&);                /*copy ctor*/
    MyClass(MyClass&&);                     /*Move ctor*/
    
    MyClass& operator=(const MyClass&);     /*copy assignment*/
    MyClass& operator=(MyClass&&);          /*move assignment*/
    private:
};

MyClass::MyClass(/* args */)
{
}

MyClass::~MyClass()
{
}


int main()
{

}

#endif
#if 0
class MyClass
{
private:
    /* data */
public:
    MyClass();
    ~MyClass();
};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}


int main()
{
    MyClass m1;         /*default ctor çağırılır*/
    MyClass m2 = m1;    /*copy ctor çağırılır*/
    MyClass m3(m1);     /*copy ctor çağırılır*/
    MyClass m4{m1};     /*copy ctor çağırılır*/
    auto m5 = m1;       /*copy ctor çağırılır*/
    auto m5(m1);        /*copy ctor çağırılır*/
    auto m5{m1};        /*copy ctor çağırılır*/
}
#endif
#if 1
class Nec{
    Nec();
};

class MyClass{
    Nec mynec;
};

int main()
{
    
}


#endif
