
### `Inline` and ODR Relation Cont'd
- Modern C++ dilinde `inline` anahtar sözcüğü ile tanımlanmış global değişkenler ODR Violation sorununa yol açmazlar.
	- Bu çözüm yöntemiyle header file içerisinde global variable tanımlanması yapılabilmektedir.
	
```cpp
inline int x = 10;

```


## Linking C Type Function in C++

- C ve C++ dillerindeki `decorating` yapıları farklı olduğundan `.c` uzantılı dosyalardaki fonksiyonlar linker aşamasında hataya sebep olur.
- Bunu engellemek için C++ dilinde `extern "C"` yapısı kullanılır.
- `.h` header dosyasında aşağıdaki gibi koşullu linkleme işlemi yapılarak derleyiciye eğer c++ derleyiciyse `extern "C"` komutuyla, eğer C derleyicisiyse direkt olarak tanımlatmayı sağlar.
	- Bunun için `__cplusplus` pre-defined constant macrosu kullanılır.

- `yavuz.h`
```cpp
#ifndef YAVUZ_H
#define YAVUZ_H

// __cplusplus symbolic constant

#ifdef __cplusplus
extern "C" {
#endif

int sum_square(int a,int b);

#ifdef __cplusplus
}
#endif


#endif
```
- `yavuz.c`
```cpp
#include "yavuz.h"

int sum_square(int a,int b){
    return a * a + b * b;
}
```

---

## Sınıf Nesneleri

### Constructor Function
- Sınıfın oluşturulmasını sağlayan fonksiyondur.
- Constructor bir non-static member function'dır.
	- Free function olamaz.
	- Static member function olamaz.
- **Sınıf ismi ile aynı ismi taşırlar**
- const üye fonksiyonu olamaz.
- **Geri dönüş değeri kavramına sahip değillerdir.**
	- void function olamaz.
- Gizli parametre değişkeni diğer non-static member function'lar gibi vardır.
	- `this` pointerı kullanılabilir.
- Constructor çalışırken bir exception olursa sınıf nesnesi oluşturulmaz.
- Erişim kontrolüne sahiptir.
	- `public`, `private` ve `protected`
	- %95 `public` olurlar.
- Bir sınıfın birden fazla constructor fonksiyonu olabilir.
	- Constructor **overload** edilebilir.
```cpp
/*constructor*/
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "default ctor called" << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called" << "\n";
    }
private:
};


int main()
{
    MyClass m1;
    MyClass m2(31);
}

/*
out:
default ctor called
int parameter ctor called
*/

```

- Constructor, diğer üye fonksiyonlardan farklı olarak bir sınıf nesnesine `.` veya `->` operatörleri vasıtasıyla çağırılamaz.

### Destructor
- `~` işareti ve sınıf adı ile gösterilir
- Nesnenin hayatını bitiren fonksiyondur.
- bir non-static member function'dır.
	- Free function olamaz.
	- Static member function olamaz.
-  const üye fonksiyonu olamaz.
- Geri dönüş değeri kavramı yoktur.
- Bir sınıfın yalnızca 1 adet destructor fonksiyonu olabilir ve bu fonksiyonun parametre değişkeni olamaz.
	- Overloading yoktur.
- Destructor ismi ile çağırılabilir ama 1 bağlam harici kullanılması asla önerilmiyor.
	- İlerde bu kısma değinilecek(*placement new*)
- Genellikle public olurlar fakat diğer erişim kontrolleri içerisinde de olabilmektedir.


```cpp
/*destructor*/
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "MyClass default ctor called this = " << this << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called this = " << this <<"\n";
    }
    ~MyClass(){/*dtor*/
        cout << "MyClass deconstructor called this = " << this << "\n";
    } 

    void foo(){
        cout << "foo called this = " << this << "\n";
    }
private:
};



int main()
{
    MyClass m;
    cout << "&m = " << &m << "\n";
    m.foo();
}

/*
out:
MyClass default ctor called this = 0xc7951ff9ff
&m = 0xc7951ff9ff
foo called this = 0xc7951ff9ff
MyClass deconstructor called this = 0xc7951ff9ff
*/
```


```cpp
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "MyClass default ctor called this = " << this << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called this = " << this <<"\n";
    }
    ~MyClass(){/*dtor*/
        cout << "MyClass deconstructor called this = " << this << "\n";
    } 

    void foo(){
        cout << "foo called this = " << this << "\n";
    }
private:
};

MyClass m;

int main()
{
    cout << "main started" << "\n";
    cout << "&m = " << &m << "\n";
    m.foo();
    cout << "main ended" << "\n";
}
/*
out:
MyClass default ctor called this = 0x7ff648bb7030
main started
&m = 0x7ff648bb7030
foo called this = 0x7ff648bb7030
main ended
MyClass deconstructor called this = 0x7ff648bb7030
*/
```
-  **Yukarıdaki örnekte görüldüğü üzere global nesneler için Destructor main fonksiyonu sonunda çağırılacaktır.**
	- Statik ömürlü yerel nesneler için ise fonksiyon çağırıldığında *constructor* çağırılır ve programın ömrü tamamlandığında *destructor* çağırılır.

- Otomatik ömürlü yerel değişkenler nesneler için nesnenin çağırıldığı yerde *constructor* çağırılır ve nesnenin olduğu bloğun sonunda *destructor* çağırılır.
```cpp
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "MyClass default ctor called this = " << this << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called this = " << this <<"\n";
    }
    ~MyClass(){/*dtor*/
        cout << "MyClass deconstructor called this = " << this << "\n";
    } 

    void foo(){
        cout << "foo called this = " << this << "\n";
    }
private:
};



int main()
{
    {
    MyClass m;
    cout << "main started" << "\n";
    cout << "&m = " << &m << "\n";
    m.foo();
    }
    cout << "main ended" << "\n";
}
/*
out:
MyClass default ctor called this = 0xcbce1ff9ef
main started
&m = 0xcbce1ff9ef
foo called this = 0xcbce1ff9ef
MyClass deconstructor called this = 0xcbce1ff9ef
main ended
*/
```

- Sınıf nesnelerinin Array halinde de kullanımı mümkündür.
	- Bu durumda constructor ve destructor'lar sırayla çağırılır.


>[!NOTE]
> *destructor* çağrıları ile *constructor* çağrıları ters sırayla yapılır. Yani:
>- Bir sınıf nesnesi arrayi oluşturulduğunda sırasıyla ilk elemandan son elemana doğru ctor çağrıları yapılır fakat ilgili blok sonuna gelindiğinde son elemandan ilk elemana doğru dtor çağrıları yapılır.

```cpp
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "MyClass default ctor called this = " << this << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called this = " << this <<"\n";
    }
    ~MyClass(){/*dtor*/
        cout << "MyClass deconstructor called this = " << this << "\n";
    } 

    void foo(){
        cout << "foo called this = " << this << "\n";
    }
private:
};



int main()
{
    {
    MyClass m[5];
    cout << "main started" << "\n";
    cout << "&m = " << &m << "\n";
    (*m).foo(); /* m[0].foo(); same */
    }
    cout << "main ended" << "\n";
}
/*
out:
MyClass default ctor called this = 0x5ff29ff8fb
MyClass default ctor called this = 0x5ff29ff8fc
MyClass default ctor called this = 0x5ff29ff8fd
MyClass default ctor called this = 0x5ff29ff8fe
MyClass default ctor called this = 0x5ff29ff8ff
main started
&m = 0x5ff29ff8fb
foo called this = 0x5ff29ff8fb
MyClass deconstructor called this = 0x5ff29ff8ff
MyClass deconstructor called this = 0x5ff29ff8fe
MyClass deconstructor called this = 0x5ff29ff8fd
MyClass deconstructor called this = 0x5ff29ff8fc
MyClass deconstructor called this = 0x5ff29ff8fb
main ended
*/
```


- Pointer değişken ve referans kullanılırken tekrar nesne tanımlanmaz.
```cpp
class MyClass{
public:
    MyClass(){ /*default ctor*/
        cout << "MyClass default ctor called this = " << this << "\n";

    }
    MyClass(int){ /*function overloading ctor exmp*/
        cout << "int parameter ctor called this = " << this <<"\n";
    }
    ~MyClass(){/*dtor*/
        cout << "MyClass deconstructor called this = " << this << "\n";
    } 

    void foo(){
        cout << "foo called this = " << this << "\n";
    }
private:
};



int main()
{
    MyClass m;
    MyClass* p = &m;
    MyClass& rm1 = m;
    MyClass& rm2 = m;

}
#endif

/*
out:
MyClass default ctor called this = 0x1b783ffa17
MyClass deconstructor called this = 0x1b783ffa17
*/
```


>[!TIP]
>Aynı kaynak dosyada global olarak `Myclass g1, g2, g3;` tanımlamasında ilgili nesnelerin ctor ve dtor çağrılarının sırasıyla olacağı KESİNDİR. Önce g1 sonra g2 sonra g3 ctor'u çağırılır; önce g3 sonra g2 ve en son g1 dtor'u çağırılır.

>[!NOTE]
>Yukarıdaki örnekte bulunan nesneler farklı kaynak dosyalarında çağırılmış olsaydı bunların hangi sırayla hayata geleceği dil tarafından belirlenmediğinden kesin değildir.


>[!TIP]
>Sınıfların özel üye fonksiyonları bulunmaktadır. Bunlar **special member function(s)** olarak geçer ve ilerde detaylıca incelenecektir fakat sadece kulak aşinalığı için sıralamak gerekirse:
>- default ctor
>- dtor
>- copy ctor
>- move ctor
>- copy assignment
>- move assignment

- Yukarıdaki fonksiyonlara özel fonksiyonlar denmesinin sebebi özel kurallara tabi olmalarıdır.
	- Belirli koşullar sağlandığında derleyici tarafından tanımlanırlar
		- Implicitly Declare
		- Derleyici bu kodu kendisi yazabillir.
	- `default` bildirimi ile derleyiciye yazdırılabilmektedir.


### Sınıf Nesnelerinin Default Constructor Yoluyla Oluşturulması

- Sınıf nesneleri *default initialization* yoluyla oluşturulursa `default ctor` çağırılır.
	- Default initialization -> `T x;`
```cpp
class MyClass{
public:

private:
};

int main()
{
    MyClass m; /*default initialization -> default ctor called*/
}
```

>[!IMPORTANT]
>Eğer kullanıcı user-defined olarak bir constructor bildirirse implicitly default constructor declaration derleyici tarafından yapılmaz.

```cpp
class MyClass{
public:
	MyClass(int);
private:
};

int main()
{
    MyClass m;  /*no default constructor exists for class "MyClass"*/
}
```


>[!ATTENTION]
>Modern C++ ile birlikte herhangi bir fonksiyon için `delete` bildirimi yapılabilir.

```cpp
void foo(int) = delete;

int main(){
	foo(int); /*attempting to reference a deleted function*/
}
```

- İlerde bu konu detaylıca işlenecektir.

- Value initialization ile sınıf nesnesi tanımlanmasında da default ctor çağırılır.
```cpp
class MyClass{
public:
    MyClass(){
        cout << "MyClass::MyClass()\n";
    }
private:
};

int main()
{
    MyClass m1; /*default initialization*/ /*default ctor called*/
    MyClass m2{}; /*value initialization*/ /*default ctor called*/
    MyClass m3(); /*function declaration*/ /*empty parentheses were disambiguated as a function declaration [-Wvexing-parse]*/
}
```

- ctor ile alakalı güzel bir mülakat sorusu:
>[!QUESTION]
>0 ile 100 arasındaki tüm sayıları ekrana yazdırınız. Herhangi bir döngü deyimi kullanmayınız.

```cpp
/*Bassic Interview Quest*/
class MyClass{
public:
    MyClass(){
        static int i = 0;
        cout << i++ << " ";
    }
private:
};

int main()
{
    MyClass m[100]; 
}
```

```cpp
class MyClass{
public:
    MyClass(){
        cout << "MyClass() " << "\n";

    }
    MyClass(int x){
        cout << "MyClass(int x) x = " << x << "\n";

    }
private:
};

int main()
{
    MyClass m0; /*default ctor*/
    MyClass m1; /*default ctor*/
    MyClass m2(10); /*diect init*/
    MyClass m3{ 2 };  
    MyClass m4(1.2); /*narrowing conversion*/
    //MyClass m4{1.2}; /*list init -> no narrowing conversion*/ /*narrowing conversion of '1.2e+0' from 'double' to 'int' [-Wnarrowing]*/
}
/*
out:
MyClass() 
MyClass() 
MyClass(int x) x = 10
MyClass(int x) x = 2
MyClass(int x) x = 1
*/
```

>[!FEAT]
>Constructor fonksiyonlar sınıfın non-static veri elemanlarını initialize etmek zorundadır. 
>Bu initialization özel bir syntax ile yapılır.

```cpp
class MyClass{
public:
    MyClass();
    int mx,my;
private:
};

MyClass::MyClass(){
    mx = 10;
    my = 22;
}

int main()
{


}
```

>[!ERROR]
>Yukarıdaki ifade initialization DEĞİLDİR! Constructor fonksiyonunun içerisine girdiğinde non-static veri elemanları initialized olmuştur. Yukarıdaki durum yalnızca atama(assignment) örneğidir.

### Constructor Initializer List
- Community terimi olarak `member initializer list` okullanılabilir.
- Column(`:`) operatörü vasıtasıyla ctor üzerinde yapılabilir.
	- Comma seperated list şeklinde birden fazla eleman init edilebilir.
- Eğer kullanılmazsa aşağıdaki kodda garbage value olarak init edilmiş değerler görünür.
```cpp
class MyClass{
public:
    MyClass();
    int mx,my;
private:
};

MyClass::MyClass(){
    cout << "mx = " << mx << " my = " << my << "\n";
}

int main()
{
    MyClass m1;

}
/*
out:
mx = -1722457872 my = 604
*/
```

- Ctor Init List kullanılırsa:
```cpp
/*Ctor Init List*/
class MyClass{
public:
    MyClass();
    int mx,my;
private:
};

MyClass::MyClass() : mx(5), my{30}
{
    cout << "mx = " << mx << " my = " << my << "\n"; /*garbage values*/
}

int main()
{
    MyClass m1;

}
/*
out:
mx = 5 my = 30
*/
```

>[!TIP]
> C++11 ile birlikte ctor init list için yalnızca `()` değil, `{}` de kullanılabilmektedir.
> - Küme parantezi kullanılırken narrowing conversion yine geçersizdir.
