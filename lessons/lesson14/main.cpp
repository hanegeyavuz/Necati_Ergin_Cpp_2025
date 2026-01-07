#include <iostream>

#if 0
/*copy ctor*/
class MyClass
{
public:
    MyClass(/* args */);
    ~MyClass();
private:

};

void foo(MyClass);

int main(){
    MyClass m1;
    MyClass m2 = m1;            /*copy ctor call for m2*/
    foo(m2);                    /*copy ctor call*/

}

#endif
#if 0
/*copy ctor*/
class Date
{
public:
    Date() = default;
    Date(int d,int m,int y):md{d}, mm(m), my{y} {}
    ~Date(){};
    Date(const Date& other): md(other.md),mm(other.mm),my(other.my) {
        /*user defined copy ctor*/
        std::cout << "copy ctor called!\n";
        std::cout << "this = " << this << "\n";
        std::cout << "other& = " << &other << "\n";

    } 

    void print()const
    {
        std::cout << md << "-" << mm << "-" << my << "\n";
    }
private:
    int md{1}, mm{1}, my{1900};
};

int main(){

    Date d1;
    d1.print();
    Date d2(5,1,2026);
    d2.print();
    Date d3 = d2;
    std::cout << "d3& = " << &d3 << "\n";
    std::cout << "d2& = " << &d2 << "\n";    
    d3.print();
}

#endif
#if 0
#include <cstring>

class myString
{
public:
    myString() : mp_{nullptr}, mlen_{0} {}
    myString(const char *p);
    const char *get_str() const
    {
        return mp_;
    }
    ~myString()
    {
        if (mp_)
        {
            free(mp_);
        }
    }

private:
    size_t mlen_;
    char *mp_;
};

void foo(myString str)
{
    std::cout << "foo function str = " << (str.get_str()) << "\n"; /*DANGLING POINTER!!! UB!!*/
}

myString::myString(const char *p) : mlen_{std::strlen(p) + 1}, mp_{(char *)malloc(mlen_ * sizeof(char))}
{
    std::strcpy(mp_, p);
}

int main()
{
    myString str1{"yavuz hanege"};

    std::cout << "str1 = " << (str1.get_str()) << "\n";

    foo(str1); /*undefined behaviour!!! copy ctor called*/
}

#endif
#if 0
#include <cstring>
#include <cctype>
class myString
{
public:
    myString() : mp_{nullptr}, mlen_{0} {}
    myString(const char *p);
    const char *get_str() const
    {
        return mp_;
    }
    ~myString()
    {
        if (mp_)
        {
            free(mp_);
        }
    }
    void make_upper(){
        size_t str_len = std::strlen(mp_); 
        for(int i = 0; i < str_len; ++i){
            *(mp_+i) = static_cast<char>(std::toupper(mp_[i]));
        }
    }

private:
    size_t mlen_;
    char *mp_;
};

void foo(myString str)
{
    std::cout << "foo function str = " << (str.get_str()) << "\n"; /*DANGLING POINTER!!! UB!!*/
}

myString::myString(const char *p) : mlen_{std::strlen(p) + 1}, mp_{static_cast<char *>(malloc(mlen_ * sizeof(char)))}
{
    std::strcpy(mp_, p);
}


int main()
{
    myString str1{"yavuz hanege"};
    myString str2 = str1;
    std::cout << "str1 = " << (str1.get_str()) << "\n";
    std::cout << "str2 = " << (str2.get_str()) << "\n";
    str1.make_upper();
    std::cout << "str1 = " << (str1.get_str()) << "\n";
    std::cout << "str2 = " << (str2.get_str()) << "\n";
}

#endif
#if 0
#include <cstring>
#include <cctype>
class myString
{
public:
    myString() : mp_{nullptr}, mlen_{0} {}
    myString(const char *p);
    myString(const myString& other) : mlen_{other.mlen_}, mp_{static_cast<char*>(std::malloc(mlen_ + 1))}
    { 
        
            std::strcpy(mp_,other.mp_);
    }
    const char *get_str() const
    {
        return mp_;
    }
    ~myString()
    {
        if (mp_)
        {
            free(mp_);
        }
    }
    void make_upper(){
        size_t str_len = std::strlen(mp_); 
        for(int i = 0; i < str_len; ++i){
            *(mp_+i) = static_cast<char>(std::toupper(mp_[i]));
        }
    }

private:
    size_t mlen_;
    char *mp_;
};
myString::myString(const char *p) : mlen_{std::strlen(p) + 1}, mp_{static_cast<char *>(malloc(mlen_ * sizeof(char)))}
{
    std::strcpy(mp_, p);
}

void foo(myString str)
{
    std::cout << "foo function str = " << (str.get_str()) << "\n"; /*DANGLING POINTER!!! UB!!*/
}



int main()
{
    myString str1{"yavuz hanege"};
    myString str2 = str1;
    std::cout << "str1 = " << (str1.get_str()) << "\n";
    std::cout << "str2 = " << (str2.get_str()) << "\n";
    str1.make_upper();
    std::cout << "str1 = " << (str1.get_str()) << "\n";
    std::cout << "str2 = " << (str2.get_str()) << "\n";
    foo(str1);
    foo(str2);
}

#endif
#if 0
/*copy assignment*/
class MyClass{

public:
    MyClass& operator=(const MyClass& other);

private:

};

int main()
{
    MyClass m1,m2;

    m1 = m2; /*no initialization, copy assignment function call*/
    m1.operator=(m2); /*same function call*/
}
#endif
#if 0
/*default implicitly declared copy assignment function*/
class MyClass{

public:
    MyClass(int a,int b,int c):ma_{a},mb_{b},mc_{c}{} 

    MyClass& operator=(const MyClass& other){
        ma_ = other.ma_;
        mb_ = other.mb_;
        mc_ = other.mc_;
        return *this;
    }
    void print_members()const{
        std::cout << "ma_ " << ma_ << " mb_ " << mb_ << " mc_ " << mc_ << "\n";
    }

private:
    int ma_,mb_,mc_;
};

int main()
{
    MyClass m1{1,2,3};
    MyClass m2{10,11,12};
    m1.print_members();
    m2.print_members();
    m1 = m2; /*no initialization, copy assignment function call*/
    m1.print_members();
    m2.print_members();
}
#endif
#if 1
/*copy assignment function*/
class MyClass{

public:
    MyClass(int a,int b,int c):ma_{a},mb_{b},mc_{c}{} 

    void print_members()const{
        std::cout << "ma_ " << ma_ << " mb_ " << mb_ << " mc_ " << mc_ << "\n";
    }

private:
    int ma_,mb_,mc_;
};

int main()
{
    MyClass m1{1,2,3};
    MyClass m2{10,11,12};
    m1.print_members();
    m2.print_members();
    m1 = m2; /*no initialization, copy assignment function call*/
    m1.print_members();
    m2.print_members();
}
#endif
