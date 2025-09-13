
---
# References and Reference Semantics Cont'd
---

>[!info]
>- Bir ifadenin türü pointer türü olabilir
>- Bir ifadenin türü referans türü olamaz


```c++
int main(){
	int x = 10;
	int& r1 = x;
	
	r1
}
```

- Yukarıdaki ifadede `r1` referans değişkeninin türü `int` olur.
- Value Category ise L Value'dur.

>[!INFO]
>C++'da fonksiyonların geri dönüş değeri de referans olabilmektedir.

---
## `const` Semantics in References

- Referanslar *rebindable* olmadıkları için kendilerini `const` olarak tanımlamanın bir anlamı yoktur. 
	- Pointer değişkenlerde asteriks sembolünden sonra getirilen `const` sözcüğüne referans kullanımında gerek yoktur.
```c++
 int x = 10;
 int& const r1 = x; /*const gereksizdir.*/
```

> [!warning]
> Asla yukarıdaki gibi kullanılmamalıdır.

- **const reference** ve **non-const reference** olmak üzere 2 çeşit referans vardır.

### *const* References

- Bir referans `const` referans olarak tanımlandığında tıpkı pointer'larda olduğu gibi bağlandığı nesneye salt okuma amaçlı erişim sağlamaktadır. 

```c++
int main(int argc, char const *argv[])
{
    int x = 3311;
    const int& r1 = x;  /* const reference */
    //int& r2 = x;      /* non-const reference */
    r1 = 22; /* expression must be a modifiable lvalueC/C++(137) */
}
```


```c++
int main(int argc, char const *argv[])
{
    int x = 3311;
    const int& r1 = x;  /* const reference */
    
    // r1 = 31; /*illegal*/

    int z = r1; /*legal*/

    cout << "z = " << z << endl;
}
/*
out:
z = 3311
*/

```

>[!CAUTION]
>- non-const Lvalue referans değişkenler yalnızca L value ifadelere bağlanabilirler
>- const Lvalue referans değişkenler her value kategorisine bağlanabilirler.

```c++
int main(int argc, char const *argv[])
{
    int x = 3311;
    const int& r1 = 18;  /* const reference */ /*R value assignment*/

    int z = r1;
    cout << "z = " << z << endl;
}
/*
out:
z = 18
*/
```

- Referanslara r value assign edildiğinde derleyici temporary bir değişken yaratıp referansı bu değişkene atamaktadır.
```c++
const int& r = 10;
// int temp = 10
//const int&r = temp;

```

- non-const bir referansa farklı türden bir atama yapılamazken const referanslara örtülü dönüşümün geçerli olduğu bir türden atama yapılabilmektedir.
	- Bu da derleyici tarafından temporary oluşturulan değişkenin implicit conversion ile tür dönüşümü yaşamasından kaynaklanmaktadır.
	
```c++
double dval = 345.345;
const int& r = dval;
// int temp = dval;
// const int&r = temp;

```

---

## Pointers vs References in C++

- Referanslar rebindable değildir.
- Referanslar default initialization ile init edilemezler.
- Referanslar için pointer mantığındaki gibi *reference to reference* YOKTUR!
```c++
int&& r
```
- Yukarıdaki ifade *R Value Reference* olarak geçer ve mantığı tamamen farklıdır.
- *reference to reference* C++ dilinde tamamen farklı bir anlama gelmektedir.


>[!CAUTION]
>`nullptr` yani NULL Pointer kullanılan durumlarda referans kullanma şansımız yoktur. Çünkü *Null Reference* diye bir şey **YOKTUR**

>[!HATIRLATMA]
>`int[10]` dizisini gösteren pointer değişken `int*` ile değil, `int (*p)[10]` ile gösterilir. Çünkü dizinin türü , `int` değil, `int[10]` dur.


```c++
/*references with arrays*/
int main(int argc, char const *argv[])
{
    int ar[4] = { 1,2,3,4 };
    int(&r1)[4] = ar;

    printf("%p\t%p\n",&r1, &r1 + 1);
    printf("%p\t%p\n",r1, r1 + 1);

}

/*out:*/
/*
000000ac4b1ff6f0        000000ac4b1ff700
000000ac4b1ff6f0        000000ac4b1ff6f4
*/

```


## Introduction to Type Deduction

- Derleyicinin koda bakarak tür çıkarımı yapmasıdır.
- C programlamada yoktur.
- Birden çok şekilde kullanılabilirken, ilk tanışmada `auto` keyword'ü ile yapılan type deduction işlenecektir.
- Modern C++ ile birlikte `auto` keyword'ünün anlamı değişmiştir ve type deduction işlevini almıştır.

### `auto` Type Deduction

- Kendisi bir tür değildir fakat derleyici çıkarımıyla tür çıkarımı yapılmasını sağlar.
- Tür çıkarımı belirli kurallara bağlı olarak gerçekleşir.
- Üç çeşit `auto` kullanımı vardır
	- `auto x = `
	- `auto& x = `
	- `auto&& x = `
		- forwarding reference
- Bu derse ilk 2 halini göreceğiz.
- İlk durum için:
	- **Derleyici birkaç özel durum hariç ilk değer verilen ifadeye bakar ve ona göre tür çıkarımı yapar.**
```c++
typedef struct 
{
    int a = 1;
    double d = 31.31;
}data_t;

data_t data_obj;

/* auto type deduction*/
int main(int argc, char const *argv[])
{
    auto x = 10; /*default init geçerli degildir*/ /*int*/
    auto dval = 1.1; /*double*/
    auto data_struct = data_obj; /*data_t*/

}
```

#### `auto` Type Deduction Hangi Faydaları Sağlar
- C++ dilinde bazı tür bilgileri faylasıyla karışıktır.
	- `auto` anahtar sözcüğü ile bu karmaşanın önüne geçilebilmektedir.
	- Yanlış kod yazmanın önüne geçilmesinde fayda sağlar.


>[!IMPORTANT]
> `auto` anahtar sözcüğü kullanıldığında `const` gibi özellikleri beraberinde çıkarım yapmaz.

```c++
int main(int argc, char const *argv[])
{
    const int ival = 39;
    auto ival_i = ival; /*int*/ /*not const int!!*/
}
```

- Herhangi bir değişkenin türü referans olamayacağından dolayı auto sözcüğü bir değişkenin türünü referans YAPAMAZ!
```c++
int main(int argc, char const *argv[])
{
    auto x = 10; /*default init geçerli degildir*/ /*int*/
    int& r_i = x;
    auto a_i = r_i; /*int*/
}
```

>[!NOTE]
>C programlamada olduğu gibi C++ dilinde de *function to pointer conversion* özelliği bulunmaktadır. Bu özelliği tür çıkarımında da kullanabiliriz.


```c++

int foo(int){
}

int main(int argc, char const *argv[])
{
    auto fp_1 = &foo; /*function with adress of operator*/
    auto fp_2 = foo; /*function to pointer conversion*/
	/* 2 expression at the above are the same */
}
```

#### `auto` Anahtar Sözcüğünün Referans Declarator ile Kullanılması

- Referans deklaratörü ile kullanıldığında `const` anahtar sözcüğü düşmez ve değişken const T olarak tanımlanır.
```cpp
int main(int argc, char const *argv[])
{
    const int x = 5;

    auto& r = x; /*const int*/
}
```

- **Tür çıkarımı array decay olmadan yapılır**!
```cpp
/*auto keyword with referance declarator*/
int main(int argc, char const *argv[])
{
    int ar[5]{0};

    auto& r = ar; /*int[5]*/
}
```
```cpp
int main(int argc, char const *argv[])
{
    int ar[5]{0};

    auto& r = ar; /*int[5]*/
    auto& r_c = "yavuz"; /*const char[6]*/
    const char(&r_c_alt)[6] = "yavuz"; /*r_c and r_c_alt are the same!! */
}
```
- string literalleri `const char*` türüne array decay ile dönüşür. Fakat `auto&` kullanımında array decay yapılmadığından(daha sonra yapıldığından) dolayı türü `const char[]` olmuştur.
```cpp
int foo(int);

int main(int argc, char const *argv[])
{
    int ar[5]{0};
	auto fp_1 = foo; /* int(*)(int) */
	auto& fp_2 = foo; /* int(&fp_2)(int) */ /* no function to pointer conv. */
}
```

- function pointers için de aynı durum söz konusudur. Function to pointer conversion'dan önce ele alındığından referans ile bilrikte kullanılan auto sözcüğü `int(*)(int)` türünden olamayacaktır.

- `auto` anahtar sözcüğü ile bilrikte *direct initialization* yapılabilir.
	- `auto x(10)`
- `auto` anahtar sözcüğü ile beraber `const` gibi anahtar sözcükler de kullanılabilir.

```cpp
int main(int argc, char const *argv[])
{
    int x = 5;
	const auto y = x; /* int to const int */
}
```