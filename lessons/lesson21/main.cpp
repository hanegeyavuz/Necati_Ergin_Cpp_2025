#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "Mint.h"
using namespace std;
#if 0
#include <iostream>
#include <algorithm> // for std::copy
class DynamicArray
{
public:
    // Constructor
    DynamicArray(size_t initCapacity = 2, int val = 0) : capacity(initCapacity), currentSize(0), data{new int[capacity]}
    {
        for (size_t i = 0; i < capacity; i++)
        {
            data[i] = val;
        }
    }

    // Destructor (Crucial to avoid memory leaks)
    ~DynamicArray()
    {
        delete[] data;
    }

    // Access element (Overloading [] operator)
    const int &operator[](size_t idx) const
    {
        return data[idx];
    }
    int &operator[](size_t idx)
    {
        return data[idx];
    }

    size_t size() const { return currentSize; }

private:
    size_t capacity;    // Total space allocated
    size_t currentSize; // Number of elements currently stored
    int *data;          // Pointer to the array on the heap
};

int main()
{
    const DynamicArray arr(6,23);
    cout << "arr.size = " << sizeof(arr) / sizeof(arr[0]) << "\n";
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
        // arr[i] = i;
        cout << arr[i] << " " << "\n";
    }
}

#endif
#if 0
class stringptr
{
public:
    stringptr() = default;
    stringptr(string *p) : mp{p}{}
    ~stringptr(){
        if(mp){
            delete mp;
        }
    }

    stringptr(stringptr && other):mp{other.mp}{
        other.mp = nullptr;
    }
    stringptr& operator=(stringptr &&other){
        mp = nullptr;
        mp = other.mp;
        other.mp = nullptr;
    }

    std::string& operator*(){

        return *mp;
    }
    std::string* operator->(){

        return mp;
    }
private:
    string* mp{nullptr};
};
int main(int argc, char const *argv[])
{
    stringptr sptr(new string("yavuz hanege"));
    cout << *sptr << '\n';

    *sptr = "yusuf yildiz";

    cout << *sptr << '\n';

    cout << sptr->length() << '\n';
}

#endif
#if 0
class A{
public:
	void foo();
};
class B{
public:
	B(A);
	void bar();
};

int main(void){
	B bx(A());
	
	//bx.bar(); /*Bu satirdaki hata nedir?*/ /*Most Vexing Parse Error*/

	B mx{A()};

    mx.bar(); /*LEGAL*/

    B nx((A()));

    nx.bar(); /*LEGAL*/
}
#endif
#if 0
class MyClass{
public:
    operator int()const{
        std::cout << "MyClass::operator(int)" << '\n';
        return 42;
    }

};
int main(int argc, char const *argv[])
{
    int x = 5;
    double y = 5.;

    MyClass m;

    x = m;
    std::cout << "x = " << x << '\n';
}

#endif
#if 0

int main(int argc, char const *argv[])
{
    Mint m(12);

    if(m){
        std::cout << "true";
    }
    else{
        std::cout << "false";
        
    }
}

#endif
#if 0
class MyClass{
public:
    void operator()(){
        cout << "myclass operator()()\n";
        cout << "&m = " << this << '\n';
    }

};

int main(int argc, char const *argv[])
{
    MyClass m;
    m();   
}

#endif
#if 0
class MyClass{
public:
    int operator()(int x = 32);

};

int main(int argc, char const *argv[])
{
    MyClass m;
    m();/*default argument*/
    m.operator()(12);   
    m(12);   
}

#endif
#if 1
class MyClass{
public:
    void operator()(int x, int y); 
    int operator()(int x = 32);
    int operator()(double);

};

int main(int argc, char const *argv[])
{
    MyClass m;
    m();/*default argument*/
    m.operator()(12);   
    m(12);   
    m(15,12);
}

#endif