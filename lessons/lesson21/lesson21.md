
---
### Subscript Operator Function
- Member operator function olmak zorundadır.
- const overloading mekanizmasından faydalanılır.

```cpp
    // Access element (Overloading [] operator)
    const int &operator[](size_t idx) const
    {
        return data[idx];
    }
    int &operator[](size_t idx)
    {
        return data[idx];
    }
```

### Dereferencing and Member Selection Arrow Operator Overloading

- Pointer-like sınıflar için genellikle kullanılırlar.
```cpp
    std::string& operator*(){

        return *mp;
    }
```

>[!IMPORTANT]
>arrow operatörü binary bir operatör olmasına karşın unary olarak overload edilir!


```cpp
    std::string* operator->(){

        return mp;
    }
```

```cpp
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
```

---

### Bir Mülakat Sorusu

```cpp
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
	
	bx.bar(); /*Bu satirdaki hata nedir?*/
}
```

- **Most Vexing Parse**
	- Yukarıdaki ifadede `bx.bar()` ifadesi aslında bir fonksiyon bildirimi olarak algılanır.
		- *Geri dönüş değeri N türü olan parametre türü `A(*)()`* olan bir fonksiyon bildirimidir.
- `A()` ifadesi geri dönüş değeri `A` türü olan ve parametresi olmayan bir **function type** olarak değerlendirilir.
	- `void foo(int())` = `void foo(int(*)())`

>[!ANSWER]
>En basit çözümü `{}` kullanılarak initialization yapmaktır.

>[!NOTE]
>Modern C++ öncesi `{}` ile initialization olmadığından öncelik parantezi kullanılarak bu sorun engellenebilirdi.

```cpp
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
```


---

## Type Cast Operator Functions Overloading

- Genellikle semantik açıdan `const` fonksiyonlardır.
- **Global Function olamazlar. Member function olmak zorundadırlar.**
- Geri dönüş değeri yazılmaz.
```cpp
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
```


- `Mint` sınıfı için bool cast operator overloading fonksiyonu yazalım:
```cpp
/*Mint.h*/
    operator bool() const
    {
        return mval != 0;
    }
```

```cpp
/*main.cpp*/
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
```

## Function Call Operator Function

- Özellikle generic programming için çok büyük önem taşımaktadır.

```cpp
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
/*
out:
myclass operator()()
&m = 0xa0611ff9ff
*/
```

- Geri dönüş değeri de olabilir. `void` olmak zorunda değildir.

>[!TIP]
>Varsayılan argüman alabilecek tek operatör fonksiyonu function call operatör fonksiyonudur.


```cpp
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
```

- Overload edilebilirler.
