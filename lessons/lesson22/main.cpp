#include <iostream>
#include <string>
using namespace std;

#if 0
using namespace std;

int main(int argc, char const *argv[])
{
    bool flag1{true};    
    bool flag2{true};    

    auto x = flag1 + flag2;

    cout << "x = " << x << "\n";

}

#endif
#if 0

class MyClass{
public:
    MyClass(int x) : mx{x}{};
    operator bool()const{
        return mx;
    }
private:
    int mx{};
};

int main(int argc, char const *argv[])
{
    MyClass m1(13), m2{37};

    auto val = m1 + m2;

}

#endif
#if 0
/*Reference Qualification*/
class MyClass{
public:
    void foo()&{cout << "L Value non-const objects foo()&" << "\n";};
    void foo()const&{cout << "L Value const objects foo()const&" << "\n";};
    void foo()&&{cout << "R Value non-const objects foo()&&" << "\n";};
};

int main(int argc, char const *argv[])
{
    MyClass m1;
    const MyClass m2;

    m1.foo(); /*LEGAL*/
    MyClass{}.foo(); /*LEGAL*/
    m2.foo(); /*LEGAL*/
}

#endif
#if 0
/*namespaces*/
int x;
namespace neco
{
    int x;
}
namespace neco
{
    int x;
}
namespace neco
{
    int x;
}
#endif
#if 0
/*namespaces*/
int x = 32;
namespace neco
{
    int x = 7;

    namespace yavuz{
        int x = 11;
    }
}

int main(int argc, char const *argv[])
{
    cout << "x = " << x << "\n";
    cout << "neco::x = " << neco::x << "\n";
    cout << "neco::yavuz::x = " << neco::yavuz::x << "\n";
}

#endif