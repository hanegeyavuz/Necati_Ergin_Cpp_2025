
---

## Introduction Rvalue References 

- Terminolojinin R ve L gibi ayrılmasının sebebi Lvalue Referansların Lvalue expression'lar bağlanabilmesi, Rvlalue referansların da Rvalue ifadelere bağlanabilmesinden dolayıdır.
- Declarator olarak `&&` deklaratörü kullanılmaktadır.
	- **`auto` keyword'ü ile birlikte kullanıldığında Rvalue referans olmaz, universal referance olur!!**

```cpp
Myclass& r = /* Lvalue Reference */
Myclass&& r = /* Rvalue Reference */
auto&& r =  /* Universal(Forwarding) Reference*/ 
```

>[!attention]
>Bir değişkenin data type'ı ile value category'si farklı şeylerdir. Değişken isminin oluşturduğu ifadeler her zaman Lvalue'dur.

- RValue referansların ne işe yaradığı, nerelerde kullanıldığı vs. ilerleyen haftaların konuları olduğundan bu kadarlık bilgi şimdilik yeterlidir.

### Value Category of Function Call Expressions

>[!NOTE]
>- Eğer fonksiyonun geri dönüş değeri non-reference type ise fonksiyon çağrı ifadesi her zaman PRvalue kategorisindedir.
>- Eğer geri dönüş değeri Lvalue reference type ise function call ifadesi her zaman Lvalue kategorisindedir.
>- Eğer geri dönüş değeri Rvalue reference type ise function call ifadesi her zaman Xvalue kategorisindedir.

---
## Default Arguments

- Normal koşullarda bir fonksiyona parametre sayısından daha fazla veya daha az argüman göndermek hatalı bir kullanımdır. Syntax error'a neden olur.
- **Default arguments özelliği ile birlikte bir fonksiyona parametre sayısından daha az sayıda argüman gönderilebilmektedir.**
	- Fonksiyonun parametresinin default argument olarak tanımlanması gerekmektedir.


>[!QUESTION]
>Neden böyle bir araç var?
>>[!ANSWER]
>> - Bazı fonksiyonlarda bir parametreye çoğunlukla aynı argüman gönderiliyorsa, bunun için default argument kullanılabilir.
>> - Zaman içinde bir fonksiyonun parametre sayısını arttırırken eski kodların da çalışır hale hayatına devam etmesini sağlamak



>[!QUESTION]
>Bunu kullanmanın programın çalışma zamanına ilave bir maliyeti var mıdır?
>>[!ANSWER]
>>Yoktur. Bu tamamen derleme zamanı ile ilgilidir.

### Syntax
- Genellikle fonksiyon bildiriminde(header file içerisinde) karşımıza çıkmaktadır.

```cpp
/*default arguments*/

int foo(int, int, int = 10){
    
}

int main(int argc, char const *argv[])
{
    
}
```
 
>[!IMPORTANT]
>- Bir parametre varsayılan argüman alıyorsa o parametrenin sağındaki tüm parametreler varsayılan argüman almak zorundadır.
>- Bildirimde parametre değişkenlerine isim vermek veya vermemek durumu değiştirmez

```cpp
int foo(int x = 1, int y = 3, int z = 10){
    
}

int main(int argc, char const *argv[])
{
	foo(2,5,13); // not used default argument
    foo(2,5); /* foo(2,5,10) */
    foo(); /* foo(1,3,10) */
}
```

>[!ERROR]
>Bildirimde default argument varsa tanımda kesinlikle tekrar edilmemesi gerekir!!

- Tüm değişken türleri Default parametre olabilir.(pointer, ref etc...)

```cpp
int g = 56;

void foo(int* = &g);
```


>[!TIP]
>Başka bir kütüphanede bildirilmiş fonksiyona default argüman vermek sentaks hatası değildir. Sık kullanılan bir idiomdur.

```c++
// yavuz.h
void foo(int, int, int);

//necati.c
#include "yavuz.h"

void foo(int, int, int = 0)

int main(){
	foo(1,4); /* LEGAL */
}

```


- Bazen fonksiyona default argument geçilmesinin tek sebebi çağrı yapan kodun argüman gönderip göndermediğini saptamaktır.

```cpp
int process_date(int day = -1, int mon = -1, int year = -1){

}

int main(int argc, char const *argv[])
{
    process_date(15,6);
}

```
- Mesela bu durumda 3. parametre verilmediğinde bulunduğumuz yıl argüman olarak alınacaktır.
```cpp
/*default arguments*/
using namespace std;

void process_date(int day = -1, int mon = -1, int year = -1){
    time_t sec;
    time(&sec);
    struct tm* p = localtime(&sec);
    if(year == -1){
        year = p->tm_year + 1900;
    }
    if(mon == -1){
        mon = p->tm_mon + 1;
    }
    if(day == -1){
        day = p->tm_mday;
    }
    cout << "date: " << day << "." << mon << "." << year << endl;
    
}

int main(int argc, char const *argv[])
{
    process_date(15,6);
    process_date(15,6,2025);
    process_date(2,4);
    process_date(5);
    process_date();
}

#endif
void process_date(int day, int mon, int year);

/*
out:
date: 15.6.2025
date: 15.6.2025
date: 2.4.2025
date: 5.9.2025
date: 14.9.2025
*/
```

---
## Type Conversion in C++

- İki çeşit conversion vardır
	- Implicit type-conversion
	- Explicit type-conversion
- C programlamada explicit tür dönüşümü için tek bir araç vardır:
	- `(target-type)` şeklinde tür dönüşümü yapılabilir.
	- **Bu dönüşüm C++ için legal olsa da yeterli değil ve çok uygun değildir.**
		1. Koda bakar bakmaz tür dönüşümünün sebebi belli olmuyor
		2. Farklı amaçlar için yapılan dönüşümler farklı amaçlarla yapılmadığından geçersiz kod oluşumu olmamaktadır.
		3. Birden fazla kaynak dosyada tür dönüşümü hatasının aranmasını zorlaştırması sebebiyle karmaşaya sebep olmaktadır.

- C++ dilinde 4 farklı tür dönüştürme operatörü vardır.
	- `static_cast`
		- Hali hazırda yapılabilen dönüşümler için kullanılır.
			- int to double
			- double to int
			- void* to T* etc..
	- `const_cast`
		- `const T*` -> `T*` türüne dönüşümlerin yapılabilmesinin tek yolu bu operatördür.
	- `reinterpret_cast`
		- Farklı adres türleri arasındaki dönüşümü sağlar
			- `int*` -> `char*`
			- `uint*` -> `int*` etc..
	- `dynamic_cast`
		- Daha sonra işlenecek. Nesne yönelimli programlamaya uygun dillerde kullanılır.
- Syntax:
	- **`xxxx_cast<target_type>(operand)`**
		- `static_cast<int>(dval)`


### User-Defined Conversion
- udc
- Dilin kuralları gereği legal olarak nitelendirilmiş dönüşümlere standard-conversion denir.
	- `int` to `double`
	- `double` to `int`
	- `enum` to `int`
	- `int*` to `void*`
	- etc..
- UDC, C programlamada olmayan ve C++ diline ait bir özelliktir.
- Bazı dönüşümler dil tarafından legal olmasa da bazı fonksiyonlara çağrı yapılarak dönüşüm gerçekleştirilebilir.
	- Fonksiyonların çoğu ilerde işlenecektir.





#### `static_cast` Dönüşümü

```cpp
/* type-conversion */
int main(int argc, char const *argv[])
{
    int i1 = 5, i2 = 3;

    double div = static_cast<double>(i1) / i2;
    std::cout << i1 << " / " << i2 << " = " << div << std::endl;

}
/*
out:
5 / 3 = 1.66667
*/
```

```cpp
/* static type-conversion */
int main(int argc, char const *argv[])
{
    int x = 10;
    void* vptr = &x;

    int* iptr = static_cast<int*>(vptr);
    std::cout << "*iptr = " << *iptr << std::endl;
}
/*
out:
*iptr = 10
*/
```

```cpp
/* static type-conversion */
enum color {white,red,blue,brown};

int main(int argc, char const *argv[])
{
    color mycolor = { red };
    int x = static_cast<int>(mycolor);
    int z = 3;
    printf("x = %d\n",x);
    
    mycolor = static_cast<color>(z);
    printf("mycolor = %d\n",mycolor);
}
/*
out:
x = 1
mycolor = 3
*/
```

#### `const_cast` Dönüşümü
- `const T*` türünden `T*` türüne yapılan dönüşümdür.
```CPP
/* const type-conversion */
int main(int argc, char const *argv[])
{
    const int x = 30;
    const int* cptr = &x;

    int* iptr = const_cast<int*>(cptr);
    // *iptr = ... /* UNDEFINED BEHAVIOUR!!! */
    std::cout << "iptr = " << *iptr << std::endl;

}
/*
out:
iptr = 30
*/
```


```cpp
char* my_Strchr(const char* str, char ch){
    while (*str)
    {
        if(*str == ch){
            return const_cast<char*>(str);
        }
        ++str;
    }
    if (ch == '\0')
    {
        return const_cast<char*>(str);
    }
    

    return nullptr;

    
}

int main(int argc, char const *argv[])
{
    char* p = my_Strchr("yavuz",'y');
    std::cout << "*p = " << *p << std::endl;

}
```

#### `reinterpret_cast` Dönüşümü

- İki farklı adres türü arasında dönüşüm yapmak için kullanılır.
	- Oldukça risklidir, dikkatli kullanılmalıdır.
	- Birçok durumda farklı adres türleri arası dönüşüm UB olmakla birlikte, bazı durumlarda legaldir. 
- UB olmayan adres türleri dönüşümlerinden bazıları:
	1. Nesne adreslerinden `char*`, `unsigned char*`, `signed char*` türlerine yapılan dönüşümler.
	2. Aynı tam sayı türlerinin işaretlisi ve işaretsizi arasındaki dönüşümler.

```cpp
/*reinterpreter type-cast*/
int main(int argc, char const *argv[])
{
    int x = 22;
    char* ch = reinterpret_cast<char*>(&x);

    printf("ch = %d\n",*ch);
    
}
/*
out:
ch = 22
*/
```