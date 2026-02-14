#include <iostream>
#include <cstdlib>

#if 0
/*delegating ctor*/
class Myclass
{
public:
    Myclass(int x) : Myclass(x,x,x){} /*delegating ctor*/
    Myclass(int x,int y): Myclass(0,y,x){}
    Myclass(int,int,int);
    Myclass(const char* p) : Myclass(std::atoi(p)){}
private:
    void init();
};

#endif

#if 0
/*static data members*/
class Myclass{
public:

private:
    static int mx;

};

#endif
#if 0
/*static data members*/
class Myclass{
public:

private:
    int mx{};
    static int x;
    static int y;
    static int z;
};

int main(int argc, char const *argv[])
{
    Myclass m;
    std::cout << "size of class = " << sizeof(m) << "\n";
}
#endif
#if 0
/*static data members*/
class Myclass
{
public:
    static int z;

private:
};

int Myclass::z{};

int main(int argc, char const *argv[])
{
    Myclass m1, m2, m3;
    m1.z = 5;

    std::cout << "\nm1.z = " << m1.z << " m2.z = " << m2.z << " m3.z = " << m3.z << "\n";
}
#endif
#if 0
/*static data members*/
class Myclass
{
public:
    inline static int z = 5;

private:
};

int main(int argc, char const *argv[])
{
    Myclass m1, m2, m3;
    std::cout << "\nm1.z = " << m1.z << " m2.z = " << m2.z << " m3.z = " << m3.z << "\n";
}
#endif
#if 1
/*static data members*/
class Myclass
{
public:
    
private:
    int mx;
    int foo();
    static void func();
private:
};

void Myclass::func(){
    Myclass m;

    m.foo();
    m.mx = 30;
}



int main(int argc, char const *argv[])
{
    Myclass m1, m2, m3;
    std::cout << "\nm1.z = " << m1.z << " m2.z = " << m2.z << " m3.z = " << m3.z << "\n";
}
#endif