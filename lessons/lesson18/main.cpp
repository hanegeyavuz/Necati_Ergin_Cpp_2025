#include <iostream>

#if 0
/*if with initializer*/

int main(int argc, char const *argv[])
{
    if(int x = 10; x > 9){
        std::cout << "TRUE! x = " << x << "\n";
    }
    else{
        std::cout << "FALSE! x = " << x << "\n";

    }

}

#endif
#if 0
/*named ctor idiom*/
class Complex
{
public:
    static Complex create_cartesian(double r, double i)
    {
        return Complex{r, i};
    }
    static Complex create_piler(double angle, double distance)
    {
        return Complex{angle, distance, 0};
    }

private:
    Complex(double r, double i);
    Complex(double angle, double distance, int);/*"int" is a dummy param*/
};

#endif
#if 0
/*basic singleton design type implementation*/
class Singleton{

public:
    void foo();
    void bar(int);
    void baz(double);
    static Singleton& instance(){
        if(!sp){
            sp = new Singleton;
        }
        return *sp;
    }
private:
    inline static Singleton* sp{};
    Singleton();
};

#endif
#if 0
/*Meyers' Singleton implementation*/
class Singleton{

public:
    static Singleton& instance(){
        static Singleton s;

        return s;
    }
private:
    Singleton();

};

#endif

#if 0
/*dynamic objects*/

class MyClass{
public:
    void foo();
    void bar();
    void baz();
private:


};


int main(int argc, char const *argv[])
{
    MyClass* p1 = new MyClass; /*new expression*/
    auto p2 = new MyClass; /*new expression*/
    auto* p3 = new MyClass; /*new expression*/

    p2->bar();
    (*p1).bar();
}

#endif

#if 1
#include <iostream>
#include <new>

class Nec {
public:
	void* operator new(size_t n) //static member function
	{
		std::cout << "Nec::operator::new(size_t n) n = " << n << '\n';
		void* vp = std::malloc(n);
		if (!vp) {
			throw std::bad_alloc{};
		}
		std::cout << "address of allocated block : " << vp << '\n';
		return vp;
	}

	void operator delete(void* vp) //static member function
	{
		std::cout << "Nec::operator delete(void *p) " << vp << '\n';
		std::free(vp);
	}

};

int main()
{
	Nec* p1 = ::new Nec;
	::delete p1;

	Nec* p2 = new Nec;
	delete p2;
}
#endif