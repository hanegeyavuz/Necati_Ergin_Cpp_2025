#include <iostream>
#include <string>
using namespace std;
#if 0
/*friend decleration*/
class myclass{
public:
    friend void gfunc(myclass);

private:
    void foo();
    int x_{};

};


void gfunc(myclass x){
    x.foo(); /*LEAGAL*/
    myclass m;
    m.x_ = 5; /*LEAGAL*/
}

void sfunc(myclass x){
    x.foo(); /*ILLEAGAL*/
    myclass m;
    m.x_ = 5; /*ILLEAGAL*/
}


int main(int argc, char const *argv[])
{

}

#endif

#if 0
/*friend decleration*/
class myclass{
public:
    friend void gfunc(myclass);
    friend void mfunc(int);

private:
    void foo();
    int x_{};

};


int main(int argc, char const *argv[])
{
    myclass m;
    
    mfunc(23);

    gfunc(m);
}

#endif
#if 0
/*friend decleration*/
class myclass{
public:

private:
    /*hidden friend*/
    friend void gfunc(myclass m){
        m.foo();
        m.x_ = 33;
    }

    void foo();
    int x_{};

};


int main(int argc, char const *argv[])
{

}

#endif
#if 0
/*friend decleration*/

class Nec{
public:
    void bar(int);
private:
};

class myclass{
public:

    friend void Nec::bar(int);

private:
    /*hidden friend*/

    void foo(){}
    int x_{};

};

void Nec::bar(int x){
    myclass m;
    m.x_ = x;
    std::cout << "x_ = "<< m.x_ << "\n";
}

int main(int argc, char const *argv[])
{
    Nec m1;

    m1.bar(22);
}

#endif
#if 0
/*friend decleration*/
class myclass
{
public:
    friend class Nec;

private:
    void foo() {}
    int x_{};
};

class Nec
{
    void f1()
    {
        myclass m;

        m.x_ = 22;

        m.foo();
    }

private:
public:
};

int main(int argc, char const *argv[])
{
}

#endif
#if 0
/*Operator Overloading*/
int main(int argc, char const *argv[])
{
    using namespace std;

    string str{"yavuz"};

    str += "hanege"; /*operator overloading*/

    cout << " str = " << str << endl;
}

#endif
#if 0
/*Operator Overloading*/
int main(int argc, char const *argv[])
{
    int x = 32;
    /*identical*/
    std::cout << x << std::endl;
    std::cout.operator <<(x);
}

#endif
#if 0
/*Operator Overloading*/
int main(int argc, char const *argv[])
{
    string s1{"yavuz"};
    string s2{"yavuz"};

    if (operator==(s1, s2))
    {
        cout << "esittir";
    }
    else
    {
        cout << "esit degildir";
    }
}

#endif
#if 1
/*Operator Overloading*/

class MyClass{
public:
    MyClass operator+(const MyClass)const;
    MyClass operator+(int)const;
    MyClass operator+(double)const;
private:
    
};


int main(int argc, char const *argv[])
{
    string s1{"yavuz"};
    string s2{"yavuz"};

    if (operator==(s1, s2))
    {
        cout << "esittir";
    }
    else
    {
        cout << "esit degildir";
    }
}

#endif