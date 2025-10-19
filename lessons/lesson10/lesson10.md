
---
# Classes Cont'd
- Genellikle sınıflar header file içerisinde tanımlanır fakat bazı durumlarda source file içerisinde de tanımlanabilir.

## Member Function of Classes
- Class scope içerisindedir.
- Sınıfların non-static üye fonksiyonlarının gizli bir parametresi vardır. Bu parametre sınıf türünden pointer parametresidir.
- Fonksiyonlar çağırılırken `. -> ::` gibi operatörlerin solundaki nesnenin adresi fonksiyona gönderilir.

```cpp
class Myclass{
public:
    void foo();
    void g(int);

};

int main(int argc, char const *argv[])
{
    Myclass m;

    m.foo(); /*m nesnesinin adresi fonksiyonun gizli parametresi olarak alınır*/
}
```

- **Yani, non-static member functions nesnenin kendisine erişebilmektedir.**

>[!NOTE]
>Sınıfların *private* kısmındaki elemanlara sınıf içerisindeki public fonksiyonlar aracılığıyla erişilebilirken, dışarıdan yani class scope dışından erişim mümkün değildir.

- **Genellikle sınıfın tanımı ve fonksiyon declaration'ları header file içerisinde olurken, fonksiyon tanımlamaları source file içerisinde olur.**

```cpp
//myclass.h

class Myclass{
public:
	void foo(int);
	void bar();

};

//myclass.cpp
#include "myclass.h"

void Myclass::foo(int x){
	//some codes...
}
void Myclass::bar(){
	//some codes...
}

```

>[!TIP] 
>Function definition esnasında fonksiyonun geri dönüş değerinden sonra class resolution operatörü ile class scope bildirimi yapılır.
>- Eğer bu yapılmazsa tanımlanan fonksiyon free function olur.


>[!QUESTION]
>Sınıfın üye fonksiyonlarında bulunan sınıf nesnesi türünden pointer değişkeni gizli parametre ise biz sınıfın private access specifier'ı ile tanımlanan değişkenlerine nasıl erişebiliriz?
>>[!ANSWER]
>>Eğer üye fonksiyonun block scope'u içerisinde aynı isme ait bir değişken yoksa derleyici bu ismi class definition içerisinde arar ve bulunca isim arama sonlanır. Herhangi bir erişim operatörüne ihtiyaç yoktur.


>[!INFO]
>free function ile class member function arasındaki isim arama kuralları farklıdır.
>- Bir unqualified name in bulunamadığı durumda free-function arama kuralları C Programlamadaki gibidir. 
>- Fakat member functions için bu durumda fonksiyon içerisindeki tüm bloklardan bu name bulunamazsa class definition içerisine bakılır.


```cpp
class Myclass{
private:
    int mx = 23;
public:
    void foo();
    void g(int);

};

void Myclass::foo(){
    cout << "mx = " << mx << endl;
    int mx = 32; /*name masking*/
    cout << "mx = " << mx << endl;
	cout << "mx = " << Myclass::mx << endl;
}

int main(int argc, char const *argv[])
{
    Myclass m;

    m.foo();
}

/*
out:
mx = 23
mx = 32
*/
```

>[!NOTE]
>C++ dilinde yerel ismin global ismi maskelediği durumda global ismi kullanmanın bir yolu vardır. **Unary Scope Resolution **`::` operatörü yalın halde kullanıldığında derleyici global namespace'e bakar.

```cpp
int x = 9;

int main(){
	int x = 3;
	cout << "x = " << x << endl;
	cout << "x = " << ::x << endl;
}
/*
out:
x = 3
x = 9
*/
```

>[!IMPORTANT]
>Bir member function içerisinde başka bir member function'ı çağırırsa içerdeki fonksiyona geçilen gizli sınıf pointer parametresi çağırılan fonksiyona geçilen parametre ile aynı olacaktır.

```cpp
class Counter{
private:
    int mval{}; 
    void print();
public:
    void set(int val);

};

void Counter::set(int val){
    mval = val;
    print();
}
void Counter::print(){
    cout << mval << endl;
}

int main(int argc, char const *argv[])
{
    Counter mycounter;

    mycounter.set(11); /*print fonksiyonu da mycounter objesi ile çağırılır.*/
    mycounter.set(43);

}
/*
out:
11
43
*/
```



>[!TIP]
>Java gibi dillerde sınıfa ait fonksiyonların tanımlanması class içerisinde olur. Bunun sebebi bu dillerin Nesne Yönelimli Programlama dilleri olmasından kaynaklanır. Tüm fonksiyonlar bir class fonksiyonu olup, global function diye bir şey yoktur. 
>>[!INFO]
>>C++ dili Nesne Yönelimli Programlama paradigmasını **destekleyen** bir dil olduğundna dolayı hem member function hem de free-function(global) tanımlamalarını destekler.


### Global and In-Class Function Definitions
- Member fonksiyonların class içerisinde ve global olarak tanımlanmasının bir takım farklılıkları vardır.
	- Sınıfın üye fonksiyonunun sınıf tanımlaması içerisinde tanımlanması, fonksiyonu **inline function** yapar. Bunun için *inline* anahtar sözcüğüne ihtiyaç yoktur.
		- C programlama ile C++ arasında *inline functions* arasında farklar vardır.
	- İleride bu fonksiyonlar çok daha detaylı görülecektir.

### `const` Semantics in Member Functions
- Sınıf üye fonksiyonlarının bildiriminde veya tanımında parantez işaretinden hemen sonra `const` anahtar sözcüğü varsa bu fonksiyon nesnenin değerini değiştirmeyen fonksiyondur. (Call by Value gibi)

```cpp
class Date{
public:
	void set_year(int y);
	int get_year()const; /* degerini degistirmez */
};
```

>[!INFO]
>Class member Functions için gizli parametre değişkenlerine sahip olduklarını belirmiştik. Örneğin: `void foo(*/Date* date*/,int y)` gibi. Sınıf üye fonksiyonlarda fonksiyon bildiriminden sonraki `const` anahtar sözcüğü bu gizli parametreyi `const` yapmak için kullanılır. Bu yüzden syntax'ı bu şekildedir.

>[!ERROR]
>`const` anahtar sözcüğü bildirimde varsa tanımda olmak **zorundadır**.

```cpp
class Date{
public:
	void set_year(int y);
	int get_year()const; /* degerini degistirmez */

private:
    int md,mm,my;
};


//cpp

int Date::get_year()const{
    //my = 22; /*ILLEGAL! */
    return my; 
}
```

- C ve C++ dilinde `const T* ==> T*` dönüşümü olmadığı için const sınıf nesnesini kullanarak çağırılan ve `const` olmayan üye fonksiyonlar hatalı kullanımdır.
```cpp
class Date{
public:
	void set_year(int y);
	int get_year()const; /* degerini degistirmez */

private:
    int md,mm,my;
};


//cpp

int Date::get_year()const{
    const Date mydate{};
    mydate.set_year(1993); /* ILLEGAL! */ /*the object has type qualifiers that are not compatible with the member function*/
}
```

- const bir üye fonksiyonu için
	1. Sınıfın non-static veri elemanlarını değiştirmeye yönelik kodlar geçersizdir.
	2. const bir sınıf nesnesi için sınıfın non-const üye fonksiyonlarına çağrı yapmak geçersizidir.
	3. Sınıfında bulunan başka bir non-const üye fonksiyonunu çağıramaz.

