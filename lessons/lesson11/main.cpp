#include <iostream>
#include <cstdio>
using namespace std;
#if 0
/*mutable keyword*/
class Fighter{
public:
    void get_name()const{
        m_debug_call_count++; /*LEGAL*/
    };
private:

	mutable int m_debug_call_count;	
};

int main(int argc, char const *argv[])
{
    
}

#endif
#if 0
/*this keyword*/
class MyClass{
public:
    void foo();
private:
	int mx;
};


void MyClass::foo(){
    // this = &gm; /*ILLEGAL */

    /*Same assignments*/
    this->mx = 5;
    mx = 5;
}


#endif
#if 0
/*this keyword*/
class MyClass{
public:
    void foo();
private:
	int mx;
};

void gfunc(MyClass* ptr){
    cout << "ptr = " << ptr << endl;
}

void MyClass::foo(){

    cout << "MyClass::foo() called" << endl;
    cout << "this = " << this << endl;
    gfunc(this);
}

int main(int argc, char const *argv[])
{
    MyClass m11;

    cout << "&m = " << &m11 << endl; 

    m11.foo();
}
#endif
#if 0
/*this keyword*/
class MyClass{
public:
    void foo();
private:
	int mx;
};

void gfunc(MyClass& ptr){

}

void MyClass::foo(){

    gfunc(*this);
}

int main(int argc, char const *argv[])
{
    MyClass m11;

    cout << "&m = " << &m11 << endl; 

    m11.foo();
}
#endif
#if 0
/*this keyword*/
class MyClass
{
public:
MyClass& foo(){
    cout << "Myclass::foo called" << endl;
    cout << "this = " << this << endl;
    return *this;
}
void bar(){
    cout << "Myclass::bar called" << endl;
}

private:

};

int main()
{
    MyClass m;
    m.foo().bar();
}

#endif
#if 0

class MyClass
{
public:
MyClass* foo(){

    cout << "foo called\n";
    return this;
}
MyClass* bar(){
    cout << "bar called\n";
    return this;
}
MyClass* baz(){
    cout << "baz called\n";
    return this;
}

private:

};

int main()
{
    MyClass m1;
    m1.foo()->bar()->baz();
}

#endif
#if 0

class MyClass
{
public:
MyClass* foo(){

    return this; /*LEGAL*/
}
const MyClass* bar()const{

    return this; /*ILLEGAL*/ /*Gizli nesnenin türü `const MyClass*` fakat donus degeri `MyClass*`*/
}
private:
};


int main()
{

}

#endif
#if 0

class MyClass
{
public:
MyClass& foo(){

    return *this; /*LEGAL*/
}
private:
};


int main()
{
    MyClass m;

    MyClass& r = m.foo();
}

#endif

#if 1
class MyClass{
public:
    void func(){ /*INLINE FUNCTION*/

    }
private:
};

int main(){

}

#endif