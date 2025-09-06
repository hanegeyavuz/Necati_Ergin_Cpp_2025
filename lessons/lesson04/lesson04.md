
---

>[!NOTE]
>C++ dilinde gerek C++ kütüphaneleri gerekse C'den gelen kütüphaneler artık `.h` uzantılı değildir. Artık `#include` ile kütüphane eklerken uzantı kullanmamıza gerek yotkur.

>[!NOTE]
>C kütüphaneleri include ederken başına `c` harfi getirilerek include edilir. Örneğin `cstdio`


```C++
#include <iostream>
#include <cstdio>
```

---
## C++ Giriş

### Initialization

- C++ dilinde bir değişkene ilk değer vermenin bir çok yolu vardır.
	- Default Init
	- Direct Init
	- List Init
	- Copy Init
	- Copy List Init
	- Aggregate Init
	- etc...

```c++
int i1; /* default initialization*/
```

```c++
int i2 = 10; /* copy init */
```

```c++
int i3(7); /* direct Init */
```

```c++
int i4{ 9 }; /* direct list init */
```

```c++
int i5{}; /* value init */
```


### Bir değişkeni **default init** edersem ne olur?
- değişken aritmetik türden mi?
- değişken pointer türden mi?
- değişken sınıf türden mi?
	- Storage Duration'a bağlı olarak:
		- Eğer değişken *global variable* veya *static local variable* ise **zero initialization** kuralı uygulanır ve değşkene pointer türünden ise null pointer, aritmetik türden ise *0* değeri atanır.

>[!TIP]
>Aritmetik türden değişkenler ve pointer'ların local bir şekilde *default init* edilmesi çoğu zaman kötü kod örneğidir.
>

>[!WARNING]
>C programlamada hala kabul gören *önce değişkeni tanımla, sonra atama yap* şeklindeki kod yazım biçimi iyi bir kod yazma biçimi değildir. Çünkü scope leakage'a neden olabilmektedir.

 
>[!NOTE]
>Value initialization durumunda da *zero initialization* uygulanır.

```c++
int main(){
	int x{}; /* zero initialization */
	int y; /* garbage value */
}
```

- Neden Modern C++ ile küme parantezi kullanılarak ilk değer verme özelliği eklendi?
	1.  Uniform olması
	2.  Invalid narrowing conversion
		- implicit conversion
```c++
int main(int argc, char const *argv[])
{
    double dval = 3.5;
    int x1 = dval;
    int x2(dval);
    int x3{dval}; /*Geçersiz. No implicit conversion in value initialization*/
}

```

- Yukardaki kodun aldığı warning mesajı:
	- `narrowing conversion of 'dval' from 'double' to 'int' [-Wnarrowing]GCC`

	3.  Most Vexing Parse
		- Bir fonksiyon prototipi ile bir değişkene ilk değer verme eğer aynı durumdaysa parsing aşamasında fonksiyon prototipinin seçilmesidir.
		- Direct Init durumunda yaşanabilir. İleride daha detaylı ele alınacaktır.


---
## References and Reference Semantics

- C'de pointerlar var, C++'da da pointer'lar var ama Modern C++ ile birlikte artık pointer'ların kullanıldığı çoğu yerde **referanslar** kullanılmaktadır.
- **Referans, dil katmanındaki bir araçtır. Nerdeyse hiçbir durumda Pointer ile Referans arasındaki assembly kodunun farkı  yoktur. **

- Neden C++'da referans diye bir şey var? 
	- C++'da olup C'de olmayan bazı araçlar kullanıldığında pointerlar yeterli olmadığı için böyle bir kavram vardır.

>[!TIP]
>Aksi bir durum olmadıkça 1. tercihimiz referans olacaktır. Pointer'ı yalnızca gerekli yerlerde kullanmalıyız.

- Modern C++ ile birlikte referanslar 3 ayrı kategoriye ayrılmıştır:
	- L Value Reference
	- R Value Reference
	- Forwarding Reference

>[!NOTE]
>Modern C++ öncesi yalnızca L Value Ref. vardı...


### L Value Reference

- Referans değişkenleri ampersand sembolü kullanılır.
- Referans değişkenler init edilirken bir L value ifade ile initialize edilir.
---
### Value Category Remind

>[!INFO]
>L Value:
>- L value ifadeler nesnelere karşılık gelir. Bellekte yer kaplayan ifadelerdir.

```c++
int x = 5;
x // -> value cat = L Value
int* ptr = &x;

ptr //L Value
*ptr // L value
```

##### Bazı C ve C++ arasındaki Value Categoryleri

|         | C   | C++ |
| ------- | --- | --- |
| `a = 5` | R   | L   |
| `++x`   | R   | L   |
| `--x`   | R   | L   |
| `x++`   | R   | R   |
| `x--`   | R   | R   |


---

>[!Error]
>C++ dilince bazı değişkenlere default initialization yapmak geçersizdir.
>- Referans değişkenler
>- `const` değişkenler
>- etc...

```C++
int main(){
	int& r; /* Invalid */
}
```


```c++
int main(int argc, char const *argv[])
{
    int x = 5;
    int* ptr = &x;
    int ar[10]{};
    
    int& r1 = x;
    int& r2 = *ptr;
    int& r3 = ar[3];
    //int& r4 = ar; /*invalid.  error: cannot bind rvalue '(int)((int*)(& ar))' to 'int&'*/
    //int& r4 = ptr; /*error: cannot bind rvalue '(int)ptr' to 'int&'*/
    int*& r = ptr; /*legal*/
}
```

- Eğer bir referans bir değişkene bağlanmışsa, referansın kullanılması o değişkenin kullanıldığı anlamına gelir.
```c++
int main(){
	int x = 5;
	int* ptr = &x;
	int& r1 = x;
	*ptr /* = x */
	r /* = x */
}

```

```c++
int main(int argc, char const *argv[])
{
    int x = 31;
    int* ptr = &x;
    int& r1 = x;
    
    std::cout << "x = " << x << '\n'<< "*ptr = "<< *ptr << '\n' << "r1 = " << r1 << '\n'<< std::endl;

}

/*
out:
x = 31
*ptr = 31
r1 = 31
*/
```

>[!NOTE]
>- Referans değişkenleri pointer'lar gibi rebindable değildir. 
>	- Bir referans bir scope'da bir nesneye bağlanırsa artık başka bir nesneye bağlanamaz.


```c++
int main(int argc, char const *argv[])
{
    using namespace std;
    int x = 31;
    int y = 69;
    int* ptr = &x;
    int& r1 = x;
    
    cout << "x = " << x << '\n'<< "*ptr = "<< *ptr << '\n' << "r1 = " << r1 << '\n'<< endl;

    r1 = y; /* x e y değerini atar. x = y ile eşdeğerdir. Rebind etmez!!*/
    cout << "x = " << x << '\n'<< "*ptr = "<< *ptr << '\n' << "r1 = " << r1 << '\n'<< endl;

    r1 = 21;
    cout << "x = " << x << '\n'<< "*ptr = "<< *ptr << '\n' << "r1 = " << r1 << '\n'<< endl;

}
/*
out:
x = 31
*ptr = 31
r1 = 31

x = 69
*ptr = 69
r1 = 69

x = 21
*ptr = 21
r1 = 21
*/
```


- Öğrenilenleri pekiştirme
```c++
int main(){
	using namespace std;
	int x = 5;
	int& r = x;
	
	int* ptr = &r; // int* ptr = &x; ile aynı anlamdadır.
	
	int*& r2 = ptr;
	++*r2; // ++*ptr; ile aynı anlamdadır.
}
```

```c++
int main(int argc, char const *argv[])
{
    using namespace std;
    int x = 31;
    int& r1 = x;
    int& r2 = r1;
    int& r3 = r2;
    ++r1;
    ++r2;
    ++r3;

    cout << "x = " << x << '\n'<< "*r1 = "<< r1 << '\n' << "r2 = " << r2 << '\n'<< endl;
    cout << "r3 = " << x << '\n'<< endl;

}
```
- Yukarıdaki kodda 3 referans değişkeni de `x`'e bağlanmıştır.

>[!NOTE]
>Referans değişkenler için linkage, lifetime, storage duration özellikleri dilin kurallarıyla aynıdır. Pointer değişkenler gibidir.

>[!TIP]
>- Genellikle referans değişkenler yerel  veya global değişken olarak tanımlanmaz. 
>- Genellikle **fonksiyon parametreleri** olarak kullanılırlar.
>	- *Call By Reference* kullanılan fonksiyonlar için daha yüksek seviye bir syntax kullanmak için önemlidir


```c++
void foo(int x){ /* Call by Value*/
    x = 12;
}
void bar(int* p){ /* Call by Reference with Pointer Semantics*/
    *p = 123;
} 
void baz(int& r){ /* Call by Reference with Reference Semantics*/
    r = 1234;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    int x = 0;
    cout << "x = " << x << endl;
    foo(x);
    cout << "x = " << x << endl;
    bar(&x);
    cout << "x = " << x << endl;
    baz(x);
    cout << "x = " << x << endl;
}

/*
out:
x = 0
x = 0
x = 123
x = 1234
*/
```

- Swap function with reference semantics
```C++
void swap(int& r1,int& r2){
    int temp = r1;
    r1 = r2;
    r2 = temp;
}

int main(int argc, char const *argv[])
{
    int x = 30;
    int y = 19;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    swap(x,y);
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

}

/*
out:
x = 30
y = 19
x = 19
y = 30
*/
```

>[!ERROR]
>- C programlamada pointer'ların gösterdiği nesnelerin ömrü bitince **dangling pointer** durumuna düşerler ve kullanılmaları UB olur.
>- C++ da aynı şey referanslar için de geçerlidir.
