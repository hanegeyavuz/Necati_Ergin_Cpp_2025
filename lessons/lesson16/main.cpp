#include <iostream>

#if 0
/*move only class*/
class Yavuz{
public:
    /*Not Necessary, if move members declared, copy members deleted defaultly*/
    // Yavuz(const Yavuz&) = delete;
    // Yavuz& operator=(const Yavuz&) = delete;

    Yavuz(Yavuz&&);
    Yavuz& operator=(Yavuz&&);

private:

};

#endif
#if 0
/*conversion ctor*/
class Yavuz{
public:
    Yavuz() = default;

    Yavuz(int x): mx_{x}{
        std::cout << "\nYavuz(int) called-----> x = " << mx_ << "\n";  
    }

    Yavuz& operator=(const Yavuz& other){
        std::cout << "Yavuz& operator=(const Yavuz& other) called\n";
        mx_ = other.mx_;
        return *this;
    }

private:
    int mx_;
};



int main(int argc, char const *argv[])
{
    Yavuz Yvz;

    Yvz = 32;
}

#endif
#if 0
/*conversion ctor*/
class Yavuz{
public:
    Yavuz() = default;

    Yavuz(int x): mx_{x}{
        std::cout << "\nYavuz(int) called-----> x = " << mx_ << "\n";  
    }

    Yavuz& operator=(const Yavuz& other){
        std::cout << "Yavuz& operator=(const Yavuz& other) called\n";
        mx_ = other.mx_;
        return *this;
    }

private:
    int mx_;
};



int main(int argc, char const *argv[])
{
    Yavuz Yvz;

    Yvz = 32.32; //double --> int(standard conversion) int--->T Class(User-Defined Conversion) 
}

#endif
#if 0
/*conversion ctor*/
struct A
{
    
};

struct B
{
    B() = default;
    B(A);
};

struct C
{
    C() = default;
    C(B);
};



int main(int argc, char const *argv[])
{
    A ax;
    C cx;

    // cx = ax; /*ud conv + ud conv ERROR!*/
}

#endif
#if 0
/*explicit conv ctor*/

class MyClass
{
public:
    MyClass() = default;
    explicit MyClass(int x): mx_{x}{
        std::cout << "mx_ = " << mx_ << "\n";
    }
private:
    int mx_;
};


int main(int argc, char const *argv[])
{
    MyClass m1;
    /*same*/
    m1 = static_cast<MyClass>(33);
    m1 = MyClass(33);
}

#endif
#if 0
/*explicit conv ctor*/

class MyClass
{
public:
    MyClass() = default;
    explicit MyClass(int x): mx_{x}{
        std::cout << "mx_ = " << mx_ << "\n";
    }
private:
    int mx_;
};


int main(int argc, char const *argv[])
{
    MyClass x{12};      /*LEGAL*/
    MyClass y(23);      /*LEGAL*/
    // MyClass x = 62;     /*ILLEGAL*/
}

#endif
#if 0
/*temporary objects*/

class MyClass
{
public:
    MyClass() = default;
    explicit MyClass(int x);

private:
};

void foo(const MyClass&);

int main(int argc, char const *argv[])
{
    foo(MyClass{243});
}

#endif
#if 0
/*copy elision*/
/*Unmaterialized Object Passing*/
class MyClass
{
public:
    MyClass(){
        std::cout << "default ctor called\n";

    }
    
private:
    MyClass(const MyClass&){
        std::cout << "copy ctor called\n";
    }
};

void foo(MyClass){};

int main(int argc, char const *argv[])
{
    foo(MyClass{}); /*Unmaterialized Object Passing*/
}

#endif
#if 0
/*copy elision*/
/*Return Value Optimization*/
class MyClass
{
public:
    MyClass(){
        std::cout << "default ctor called\n";

    }
    
private:
    MyClass(const MyClass&){
        std::cout << "copy ctor called\n";
    }
};

MyClass foo(){
    return MyClass{};
};

int main(int argc, char const *argv[])
{
    MyClass m = foo(); /*RVO*/
}
#endif
#if 0
/*move semantics*/
class MyClass
{
public:
    MyClass() = default;
    MyClass(const MyClass &) = default;
    MyClass(MyClass &&) = default;

    MyClass &operator=(const MyClass &)
    {
        std::cout << "copy assignment function called!\n";
        return *this;
    }
    MyClass &operator=(MyClass &&)
    {
        std::cout << "move assignment function called!\n";
        return *this;
    }

private:
};

MyClass foo()
{
    MyClass m;

    return m;
}

int main(int argc, char const *argv[])
{
    MyClass mx;

    mx = foo(); /*Move Assignment Function CALL!! NOT COPY ASSIGNMENT*/
}
#endif
#if 0
/*move semantics*/
class MyClass
{
public:
    MyClass()
    {
        std::cout << "default ctor function called!\n";
    }
    ~MyClass()
    {
        std::cout << "dtor function called!\n";
    }
    MyClass(const MyClass &)
    {
        std::cout << "copy ctor function called!\n";
    }
    MyClass(MyClass &&)
    {
        std::cout << "move ctor function called!\n";
    }

    MyClass &operator=(const MyClass &)
    {
        std::cout << "copy assignment function called!\n";
        return *this;
    }
    MyClass &operator=(MyClass &&)
    {
        std::cout << "move assignment function called!\n";
        return *this;
    }

private:
};

MyClass foo()
{
    MyClass m;

    return m;
}

int main(int argc, char const *argv[])
{
    MyClass mx = foo();
}
#endif
#if 1
/*move semantics*/
class MyClass
{
public:
    MyClass()
    {
        std::cout << "default ctor function called!\n";
    }
    // ~MyClass()
    // {
    //     std::cout << "dtor function called!\n";
    // }
    MyClass(const MyClass &)
    {
        std::cout << "copy ctor function called!\n";
    }
    MyClass(MyClass &&)
    {
        std::cout << "move ctor function called!\n";
    }

    MyClass &operator=(const MyClass &)
    {
        std::cout << "copy assignment function called!\n";
        return *this;
    }
    MyClass &operator=(MyClass &&)
    {
        std::cout << "move assignment function called!\n";
        return *this;
    }

private:
};

MyClass foo()
{
    MyClass m;

    return std::move(m); /*pessimistic move!!*/
}

int main(int argc, char const *argv[])
{
    MyClass mx = foo(); /*default ctor + move ctor called*/
}
#endif