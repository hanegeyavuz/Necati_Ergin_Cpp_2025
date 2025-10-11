
---

>[!EXAMPLE]
>`decltype(x)` ifadesi `int` döndürürken `decltype((x))` ifadesi `int&` döndürür çünkü 2. ifade artık isim olarak değil ifade olarak değerlendirilir.
>

## Function Overloading
- Birden fazla fonksiyonun aynı isme sahip olmasına olanak tanıyan bir özelliktir.
- C programlamada bulunmamaktadır.
- Runtime maliyeti yoktur, derleme zamanına ait bir özelliktir.
- Function Overload Resolution -> yüklenmiş fonksiyonun çözümlenmesidir. (Hangi fonksiyon kullanılacak)
### Function Overloading var mı yok mu?

- Function Overloading oluşması için aşağıdaki kuralların sağlanması gerekmektedir:
	1. Birden fazla fonksiyonun ismi aynı olacak
	2. Aynı isimli fonksiyonlar aynı scope'ta olacak
	3. Aynı isimli fonksiyonların imzaları **farklı** olacak

>[!INFO]
> **Imza**: Fonksiyonun geri dönüş türü **haricindeki** parametrik yapısı

```cpp
int foo(int);
int foo(double);
double foo(double);
```

```cpp
typedef int Mint;

void foo(int);
void foo(Mint);
/* No Overloading! Function Re-Definition*/

```

>[!NOTE]
>Parametre değişkeninin `const` olması hem C hem C++ programlamada re-declaration olmaktadır.

- Aşağıda 3 adet overload vardır.
```cpp
void f(char);
void f(signed char);
void f(unsigned char);
```

- Varsayılan argümanın overloading ile bir ilgisi yoktur. Aşağıdaki örnek overloading örneğidir.
```cpp
int foo(int);
int foo(int, int = 0);

```

```cpp
int foo(int (*p)[10]); /*overload*/
int foo(int (*p)[12]); /*overload*/
```

>[!HATIRLATMA]
>
>`void foo(int(*)(int));` ile void `foo(int(int));` aynı şeydir!!

### Function Overload Resolution
- 2 durum vardır. 
	- Geçersiz kod
	- Overloading ile birlikte geçerli kod

```cpp
void foo(char);
void foo(int);
void foo(long double);


int main(){
	foo(12.3); /*AMBIGUITY*/
}

```

- Yukarıdaki örnekte compiler fonksiyon çağrısında hangi overload'u kullanacağını bilemez. Çünkü `double->char` örtülü dönüşümü legal olduğundan 1. ve 3. fonksiyonların ikisi de uygundur.
	- Bu duruma ikililik çatışması anlamında **ambiguity** denir.

>[!INFO]
>Çoğu programlama dilinde bir fonksiyon çağrısında hangi fonksiyonun çağrılacağı 2 şekilde olabilir:
>- Derleme zamanında (Static Binding - Early Binding)
>- Çalışma zamanında (Dynamic Binding - Late Binding)

- Candidate function görülen scope'da görülen fonksiyonların her biri birer adaydır.
- Viable Function: Uygun Overload Fonksiyonu
- Eğer 1 tane viable function varsa overload işlemi biter ve o fonksiyon çağırılır
- Hiç viable fonksiyon yoksa overload biter ve no-match durumu oluşur.
- Eğer birden fazla viable function varsa:
	1. **Ambiguity** oluşur
	2.  Derleyici birazdan anlatılacak kurallara göre birini seçer (**Best Match**)

### Best Match Kuralları
- Derleyici bir öncelik belirler.
- Öncelik sıralaması şöyledir:
	1. Standard Conversion
	2. User-Defined Conversion
	3. Variadic Conversion

#### Standart Conversion 
- Dil tarafından tanımlı dönüşümlerdir.
```cpp
//int ==> double
//double ==> int
//int* ==> void*
//unscoped enums ==> int
//etc...
```
#### User Defined Conversion
- C'de olmayan ama C++ dilinde olan bazı araçlarla programcının bir fonksiyon bildirmesiyle ve derleyicinin bu fonksiyona çağrı yapmasıyla gerçekleşebiliyor.

```cpp
class Nec{
public:
	operator int()const;

};

void foo(...); /* Variadic Conversion */
void foo(int); /* User-Defined Conversion */ /* This function will call */

int main(){
	Nec mynec;
	
	foo(mynec);
}

```

- **Yukarıdaki kodu anlamaya çalışmayın. İlerde detaylıca işlenecektir.**

- Birden fazla viable function için dönüşümler std. conv. ise?
Örneğin:

```cpp
/*more than 1 viable std. conv. function case*/
void foo(double){cout << "double" << endl;}
void foo(long double){cout << "long double" << endl;}
void foo(int){cout << "int" << endl;}
void foo(bool){cout << "bool" << endl;}


int main(int argc, char const *argv[])
{
    foo(10.31f);

}

/*
out:
double
*/
```

- Birden fazla viable fonksiyon için dönüşüm std. conv. ise:
- Derleyici argümandan parametreye yapılan std. conversion'ı kategorize eder.
- Aşağıdaki öncelik sıralaması uygulanır
	1. exact match
	2. promotion
	3. conversion

>[!ERROR]
>Birden fazla conversion varsa ambiguity oluşur.

- **Exact Match:** Tam uyumdur. Örneğin `double -> double`, `long double -> long double` etc...
	- `T* -> const T*` tam dönüşüm sayılır.
	- Array Decay dönüşümü tam dönüşüm sayılır.
	- function decay(`int(int) -> int(*)(int)`) dönüşümü tam dönüşüm sayılır.
- **Promotion:** 
	- Integral Promotion
		- Integer'dan küçük türlerin aritmetik operatörün operandı olması sonucu `int` değer oluşması olayıdır.
	- `float -> double` Promotion
		- `float->double`
		- **NOT:** `float->long double` veya `double->long double` birer promotion **DEĞİLDİR**


#### Özel Durumlar
- Function Overload Resolution with Default Argument 
	- AMBIGUITY
```cpp
/*Special Case 1*/
void foo(int x, int y = 0);
void foo(int x);

int main()
{
    foo(5); /*AMBIGUITY!*/
}
```

- With Reference parameter
```cpp
/*Special Case 2*/
void foo(int&);
void foo(int x);

int main()
{
    int x = 6;
    foo(x); /*AMBIGUITY!*/
    foo(6); /* NO AMBIGUITY!*/ /*Parameter is not L Value, "6" is PRvalue*/
}
```
- With const reference
```cpp
/*Special Case 3*/
void foo(const int&);
void foo(int x);

int main()
{
    int x = 6;
    foo(x); /*AMBIGUITY!*/
    foo(6); /* AMBIGUITY!*/ /*const reference can refere to PRvalues*/
}
```

- `const` Overloading
```cpp
#if 1
/*Special Case 4*/
void foo(const int*);
void foo(int* ); /*This function will call*/

int main()
{
    int x = 6;
    foo(&x); 
}

#endif
```
- Yukarıdaki örnekte iki fonksiyon da *exact match* olmasına rağmen argüman `const` nesne adresi olmadığından ikinci fonksiyon çağırılacaktır.
```cpp
/*Special Case 4*/
void foo(const int*); /*This function will call*/
void foo(int* ); 

int main()
{
    const int y = 10;
    foo(&y); 
}
```

- Fonksiyonlardan biri const referans biri R value referans olursa?
```cpp
/*Special Case 5*/
void foo( int&){ /*L Value Reference*/
    cout << "int&" <<endl;
}
void foo(const int&){ /*const L Value Reference*/
    cout << "const int&" <<endl;
}
void foo(int&&){ /*R value Reference*/
    cout << "int&&" <<endl;
}

int main()
{
    const int y = 0;
    int x{};
    foo(x); 
    foo(15);
    foo(y);
}
/*
out:
int&
int&&
const int&
*/
```
- Yukarıdaki örnekte iki fonksiyon da R value argüman kabul etmesine rağmen R value bir argüman ile `int&&` fonksiyonu çağırılır.
