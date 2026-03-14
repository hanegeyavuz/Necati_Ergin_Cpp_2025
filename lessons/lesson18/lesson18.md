
---

## Scope Leakage In C++
- C++ dilinde scope leakage çok önemlidir. 
	- Scope leakage bir değişkenin işlevini tamamladıktan sonra bile diğer yerlerde kullanılabilmesi durumudur.
		- En bariz örneği kaynak kullanımı yapan bir değişkenin işinin bittikten sonra hala kullanılabilmesi durumudur.
- Bu nedenden dolayı c++ dilinde `if`, `switch` ve `while` koşul ve döngü deyimleri içerisinde değişken tanımlanabilmesi özelliği bulunmaktadır.

`if(void* p = malloc(4000))`
- Yukarıdaki ifadede p değişkeninin scope'u yalnızca if-else bloğu içerisindedir.
- C programlamada bu durum yalnızca `for` döngüsü için geçerliydi.
- Logic yorumlamaya tabi tutulur.
`while(int i = foo())`
`switch(int x = foo())`

### If with Initializer
- Bu özellik dile c++17 standardı ile gelmiştir. Tamamen ayrı bir deyimdir. 
	- Yukarıdaki if yapısına benzer fakat aynı şey değildir.
```cpp
if(int x = foo(); x > 10) /*If with Initializer*/
```


### Named Constructor Idiom

- Nesneyi doğrudan ctor ile oluşturmak yerine nesne oluşturan bir fonksiyon aracılığıyla ctor çağrısı yapılan sınıf idiomudur.
	- Sadece belirli nitelikteki nesnelerin oluşumuna izin vermek
	- Nesne oluşturmayı tek bir yöne çekmek

```cpp
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
```
- Yukarıdaki örnekte 2. ctor fonksiyonundaki son parametre function overload resolution için koyulmuş dummy bir parametredir.
### Singleton Design Pattern

**Singleton**, bir sınıftan **yalnızca tek bir adet nesne** oluşturulmasını garanti eden tasarım desenidir.

Yani:
- aynı sınıftan birden fazla obje oluşturulamaz,
- programın her yerinden **aynı tek nesneye** erişilir.

Singleton üç şeyi garanti eder:
1. Sınıftan **yalnızca 1 tane** nesne oluşturulur.
2. O nesneye **global erişim noktası** sağlanır.
3. Nesnenin ne zaman oluşturulacağı **kontrol altındadır** (genelde ilk kullanımda).

#### Basit Singleton Implementasyonu
- Bu yapı günümüzde kullanılmaz çünkü *raw pointer* kullanılmaktadır.
	- **Raw pointer**: C type pointer
	- **Smart Pointer**: Aslında kendisi bir sınıf nesnesi olan ama bir pointer gibi kullanılabilen ve genellikle dinamik ömürlü nesneleri kontrol etmek için kullanılan sınıflardır. (İleride detaylıca anlatılacaktır.)

```cpp
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
```

### Meyers' Singleton
```cpp
class Singleton{

public:
    static Singleton& instance(){
        static Singleton s;

        return s;
    }
private:
    Singleton();

};
```

---
## Introduction to Dynamic Memory Allocation

- Dinamik Ömürlü nesne nedir?
	- İstenildiği zaman başlatılıp bitirilebilen nesnelerdir.
- Dinamik ömürlü nesneler genellikle kullanımı tehlikelidir.
	- Management düzgün yapılmalıdır.
	- Kullanıcı tarafından son tercih olmalıdır.
- Dinamik bir nesne oluşturmayı sağlayan ifadelere **new expression(s)** denir.
- Dinamik bir nesnenin ömrünü bitirmeyi sağlayan ifadelere **delete expression(s)** denir.
>[!NOTE]
>- *new operator(expression)* ile *operator new* farklı anlamlara sahiptir.
>- *delete operator(expression)* ile *operator delete* farklı anlamlara sahiptir.

>[!INFO]
> ***Operator new*** ve ***operator delete*** aslında standardın sunduğu ve C programlama dilindeki `malloc` ve `free` fonksiyonlarına karşılık gelen overload fonksiyonlardır.

>[!QUESTION]
>Neden `malloc` yerine operator new fonksiyonları kullanılıyor?
>>[!ANSWER]
>>- Çünkü `malloc` fonksiyonunu overload etmek mümkün değildir.
>>- `malloc` fonksiyonu başarısız olduğunda *NULL* döndürürken **operator new** fonksiyonları exception handling yapısını kullanır.(ilerde detaylıca öğrenilecek.)

- Bu operator fonksiyonların en çok kullanılan overload fonksiyonu `malloc` ve `free` ile aynı işleve sahiptir.

```cpp
int main(int argc, char const *argv[])
{
    new MyClass /*new expression*/
    // static_cast<MyClass*>(operator new(sizeof(MyClass))).MyClass());
}

```
- new expression kullanımında ise derleyici operator new fonksiyonuna çağrı yapar.


>[!ERROR]
>C ve C++ gibi dillerde garbage collector olmadığından dolayı dinamik ömürlü bir nesne `delete` edilmezse **resource leak** oluşur.
>- **Yalnızca memory leak oluşur demek doğru değildir. Memory Leak, Resource Leak'in yalnızca bir parçasıdır**

```cpp
string* p = new string(100'000,'A');
```
- Yukarıdaki ifadede eğer nesnenin hayatını ilgili delete ifadesi ile sonlandırmaz isek:
	1. Destructor çağırılmayacak.
	2. operator delete çağırılmayacak.

>[!INFO]
>*delete expression* ve *new expression* aslında *delete operator* ve *new operator* ile birlikte dtor ve ctor çağrısı yapan ifadelerdir.

>[!NOTE]
>Kullanıcı operator new ve operator delete fonksiyonlarına overload yazabilir ve bu durumda overload'lar çağırılır.


```cpp
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
```