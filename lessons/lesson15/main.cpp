#include <iostream>

#if 0
class MyClass
{

public:
    MyClass() = default;
    MyClass(const MyClass &)
    {
        std::cout << "copy ctor called\n";
    }
    MyClass(MyClass &&)
    {

        std::cout << "move ctor called\n";
    }

    MyClass &operator=(const MyClass &)
    {
        std::cout << "copy assignment called\n";
        return *this;
    }
    MyClass &operator=(MyClass &&)
    {
        std::cout << "move assignment called\n";
        return *this;
    }

    ~MyClass() = default;

private:
};

void foo(const MyClass &)
{
    std::cout << "foo(const MyClass&) called\n";
}
void foo(MyClass &&)
{

    std::cout << "foo(MyClass&&) called\n";
}

int main()
{
    MyClass m1;                 /*default ctor*/
    MyClass m3 = m1;            /*copy ctor*/
    MyClass m2 = std::move(m1); /*move ctor*/
    foo(std::move(m2));         /*move ctor*/
    m3 = m2;                    /*copy assignment*/
    MyClass m4;                 /*default ctor*/
    m4 = std::move(m3);         /*move assignment*/
}

#endif
#if 0
/*default implicitly declared move functions*/
class MyClass
{

public:
    MyClass() = default;
    MyClass(const MyClass &)
    {
        std::cout << "copy ctor called\n";
    }
    MyClass(MyClass &&other) : ax(std::move(other.ax)), 
        bx(std::move(other.bx)), cx(std::move(other.cx))
    {

        std::cout << "move ctor called\n";
    }

    MyClass &operator=(const MyClass & other)
    {
        std::cout << "copy assignment called\n";

        if(this == &other) return *this;
        
        ax = other.ax;
        bx = other.bx;
        cx = other.cx;
        
        return *this;
    }
    MyClass &operator=(MyClass && other)
    {
        std::cout << "move assignment called\n";
        
        ax = std::move(other.ax);
        bx = std::move(other.bx);
        cx = std::move(other.cx);

        return *this;

    }

    ~MyClass() = default;

private:
    int ax;
    int bx;
    int cx;
};

void foo(const MyClass &)
{
    std::cout << "foo(const MyClass&) called\n";
}
void foo(MyClass &&)
{

    std::cout << "foo(MyClass&&) called\n";
}

int main()
{
    MyClass m1;                 /*default ctor*/
    MyClass m3 = m1;            /*copy ctor*/
    MyClass m2 = std::move(m1); /*move ctor*/
    foo(std::move(m2));         /*move ctor*/
    m3 = m2;                    /*copy assignment*/
    MyClass m4;                 /*default ctor*/
    m4 = std::move(m3);         /*move assignment*/
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

    myString(const myString &other) : mlen_{other.mlen_},
                                      mp_{static_cast<char *>(std::malloc(mlen_ + 1))}
    {

        std::strcpy(mp_, other.mp_);
    }

    myString(myString &&other) : mp_(other.mp_), mlen_(other.mlen_)
    {
        other.mp_ = nullptr;
        other.mlen_ = 0;
    }

    myString &operator=(const myString &other)
    {
        if (this != &other)
        {
            mlen_ = other.mlen_;
            free(mp_);
            mp_ = static_cast<char *>(std::malloc(mlen_ + 1));

            std::strcpy(mp_, other.mp_);
        }
        return *this;
    }

    myString &operator=(myString &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        free(mp_);
        mp_ = other.mp_;
        mlen_ = other.mlen_;

        other.mlen_ = 0;
        other.mp_ = nullptr;

        return *this;
    }

    const char *get_str() const
    {
        return mp_;
    }
    void print() const
    {
        if (mp_)
        {
            std::cout << "(" << mp_ << ")\n";
        }
    }

    size_t get_strlen()
    {
        return mlen_;
    }

    ~myString()
    {
        if (mp_)
        {
            free(mp_);
        }
    }
    void make_upper()
    {
        size_t str_len = std::strlen(mp_);
        for (int i = 0; i < str_len; ++i)
        {
            *(mp_ + i) = static_cast<char>(std::toupper(mp_[i]));
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
    std::cout << "foo function str = " << (str.get_str()) << "\n";
}

int main()
{
    myString str1{"yavuz hanege"};
    myString str2 = std::move(str1);
    str2.print();
    std::cout << "str2 len = " << str2.get_strlen() << "\n";
    std::cout << "str1 len = " << str1.get_strlen() << "\n";
    // std::cout << "str1 = " << (str1.get_str()) << "\n";
    // std::cout << "str2 = " << (str2.get_str()) << "\n";
    // str1.make_upper();
    // std::cout << "str1 = " << (str1.get_str()) << "\n";
    // std::cout << "str2 = " << (str2.get_str()) << "\n";
    // foo(str1);
    // foo(str2);
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

    myString(const myString &other) : mlen_{other.mlen_},
                                      mp_{static_cast<char *>(std::malloc(mlen_ + 1))}
    {

        std::strcpy(mp_, other.mp_);
    }

    myString(myString &&other) : mp_(other.mp_), mlen_(other.mlen_)
    {
        other.mp_ = nullptr;
        other.mlen_ = 0;
    }

    myString &operator=(const myString &other)
    {
        if (this != &other)
        {
            mlen_ = other.mlen_;
            free(mp_);
            mp_ = static_cast<char *>(std::malloc(mlen_ + 1));

            std::strcpy(mp_, other.mp_);
        }
        return *this;
    }

    myString &operator=(myString &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        free(mp_);
        mp_ = other.mp_;
        mlen_ = other.mlen_;

        other.mlen_ = 0;
        other.mp_ = nullptr;

        return *this;
    }

    const char *get_str() const
    {
        return mp_;
    }
    void print() const
    {
        if (mp_)
        {
            std::cout << "(" << mp_ << ")\n";
        }
    }

    size_t get_strlen()
    {
        return mlen_;
    }

    ~myString()
    {
        if (mp_)
        {
            free(mp_);
        }
    }
    void make_upper()
    {
        size_t str_len = std::strlen(mp_);
        for (int i = 0; i < str_len; ++i)
        {
            *(mp_ + i) = static_cast<char>(std::toupper(mp_[i]));
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
    std::cout << "foo function str = " << (str.get_str()) << "\n";
}

int main()
{
    myString str;

    str = myString{"yavuz hanege 23"}; /*move assignment call temp object*/
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

    myString(const myString &other) : mlen_{other.mlen_},
                                      mp_{static_cast<char *>(std::malloc(mlen_ + 1))}
    {

        std::strcpy(mp_, other.mp_);
    }

    myString(myString &&other) : mp_(other.mp_), mlen_(other.mlen_)
    {
        other.mp_ = nullptr;
        other.mlen_ = 0;
    }

    myString &operator=(const myString &other)
    {
        if (this != &other)
        {
            mlen_ = other.mlen_;
            free(mp_);
            mp_ = static_cast<char *>(std::malloc(mlen_ + 1));

            std::strcpy(mp_, other.mp_);
        }
        return *this;
    }

    myString &operator=(myString &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        free(mp_);
        mp_ = other.mp_;
        mlen_ = other.mlen_;

        other.mlen_ = 0;
        other.mp_ = nullptr;

        return *this;
    }

    const char *get_str() const
    {
        return mp_;
    }
    void print() const
    {
        if (mp_)
        {
            std::cout << "(" << mp_ << ")\n";
        }
    }

    size_t get_strlen()
    {
        return mlen_;
    }

    ~myString()
    {
        if (mp_)
        {
            free(mp_);
        }
    }
    void make_upper()
    {
        size_t str_len = std::strlen(mp_);
        for (int i = 0; i < str_len; ++i)
        {
            *(mp_ + i) = static_cast<char>(std::toupper(mp_[i]));
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
    std::cout << "foo function str = " << (str.get_str()) << "\n";
}

int main()
{
    myString s1{"necati ergin"};

    myString s2;

    s2 = std::move(s1);

    // s1 ==> moved-from state
}

#endif
#if 0

int main(int argc, char const *argv[])
{
    using namespace std;

    string s1(100,'a');

    string s2 = move(s1);

    cout << "len s1 = " << s1.length() << "\n";
    
    s1 = string("necati ergin");

    cout << "len s1 = " << s1.length() << "\n";
}

#endif
#if 0

void str_swap(std::string &x,std::string &y){

    std::string temp = std::move(x);
    
    x = std::move(y);
    y = std::move(temp);
}


int main()
{
    std::string x{"yavuz"};
    std::string y{"hanege"};
    
    std::cout << "x = " << x.c_str() << "\n";
    std::cout << "y = " << y.c_str() << "\n";

    str_swap(x,y);

    std::cout << "x = " << x.c_str() << "\n";
    std::cout << "y = " << y.c_str() << "\n";
}

#endif
#if 0
class MyClass{
public:
    MyClass() = default;
    MyClass(const MyClass&){
        std::cout << "copy ctor. copies the resource\n";
    }
    MyClass(MyClass&&){
        std::cout << "move ctor. steal the resource\n";
    }

    MyClass& operator=(const MyClass&){
        std::cout << "copy assign. copies the resource\n";
        return *this;
    }
    MyClass& operator=(MyClass&&){
        std::cout << "move assign. copies the resource\n";
        return *this;
    }

private:

};


void foo(const MyClass& r){
    MyClass m = r;
    MyClass n;
    n = r;
}
void foo(MyClass&& r){
    MyClass m = std::move(r);
    MyClass n;
    n = std::move(r);
}


int main(int argc, char const *argv[])
{
    MyClass m;
    foo(m);
    foo(MyClass{});

}
#endif
#if 1
class MyClass{
public:
    MyClass() = default;
    MyClass(const MyClass&){
        std::cout << "copy ctor. copies the resource\n";
    }
    MyClass(MyClass&&){
        std::cout << "move ctor. steal the resource\n";
    }

    MyClass& operator=(const MyClass&){
        std::cout << "copy assign. copies the resource\n";
        return *this;
    }
    MyClass& operator=(MyClass&&){
        std::cout << "move assign. copies the resource\n";
        return *this;
    }

private:

};


void bar(const MyClass& r){
    std::cout << "bar(const MyClass&)\n";
}
void bar(MyClass&& r){
    std::cout << "bar(MyClass&&)\n";
}
void foo(MyClass&& r){
    bar(r);
}


int main(int argc, char const *argv[])
{
    foo(MyClass{});
}
#endif