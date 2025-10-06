
---
## Introduction to `constexpr` Keyword

- C++11 ile dile eklenmiştir.
- İki ayrı varlığı nitelemek için kullanılır.
	- Değişkenler
	- Fonksiyonlar
- C++ dilinde bir değişkenin `const expression` olabilmesi için başında `const` anahtar sözcüğü olması yeterli değildir. Aynı zamanda ilk değer veren ifadenin de const expression olması gerekmektedir.

```cpp
int foo(){
}
int main(int argc, char const *argv[])
{
    const int x1 = 5;
    const int x2 = foo();

    int ar1[x1]{};
    int ar2[x2]{}; /* Syntax Error*/
}
```

- Eğer bir değişkeni `constexpr` anahtar sözcüğü (specifier) ile tanımlarsak:
	- const bir değişken oluşturmuş oluruz.
	- 
>[!INFO]
>`constexpr` bir tür değildir!!

- `constexpr` anahtar sözcüğü ile tanımlanan bir değişken için şu söylenilebilir:
	- Bu değişken kesinlikle sabit ifadesi gerektiren yerlerde kullanılabilir.
```cpp
int foo(){
}
int main(int argc, char const *argv[])
{
    const int x1 = 5;
    const int x2 = foo();
    
    constexpr int x1 = 5;
    constexpr int x2 = foo(); /*SYNTAX ERROR*/    

}
```

- `const` ile yapılan tüm kontroller `constexpr` için de yapılır.
- Genellikle **Global Değişkenlerde** kullanılır. 
- Fonksiyonlar ile de sabit ifadesi oluşturulabilir.
- Fonksiyon argümanları:
	- Sabit ifadesi olabilir
	- Sabit ifadesi olmayabilir
- Eğer fonksiyon çağrı ifadesi sabit ifadesi gereken bağlamda kullanılmış ise derleme zamanında kullanılır
```cpp
constexpr int square(int x){
	return x*x;
}

int main(){
	int a = 5;
	const int b = 5;
	constexpr int i = square(a); /*ERROR*/
	constexpr int i = square(b);  /*LEGAL*/
}
```

>[!IMPORTANT]
> Argüman const expression değilse, fonksiyon çağrısı ifadesi de değildir!

- C++11 standardında `constexpr` fonksiyonun kullanımında çok fazla kısıtlama vardı fakat zaman geçtikçe bu kısıtlamalar genişletildi.
```cpp
constexpr bool isprime_s(int x){
	if(x < 2) return false;
	if(!(x % 2)) return x == 2;
	if(!(x % 3)) return x == 3;
	if(!(x % 5)) return x == 5;
    for(int i = 7; i * i <= x; i += 2){
        if(!(x % i)){
            return false;
        }
    }
    return true;
}

int main(){

    constexpr bool i_p = isprime_s(32); /* compile time */
}
```

```cpp
constexpr int sbc(int x){ /*counter of set bits*/
    int cnt = 0;

    while(x){
        x &= x-1;
        cnt++;
    }
    return cnt;
}

int main(int argc, char const *argv[])
{
    constexpr auto ss = sbc(255); /* 8  */
}
```

---
## `enum` Types
- Modern C++ öncesinde enum türünde fazlasıyla sorunlar vardı.
	- Modern C++ ile bu enum'lar dilde varlığını korurken farklı bir enum türü daha eklend.
- Eskiden beri kullanılan klasik enum türüne `unscoped enums` denmektedir.(Modern cpp öncesi)
- Dile modern C++ ile birlikte **`scoped enums`** eklendi. (C++ 11)

>[!todo]
>Modern C++ kullanırken eskisi gibi enum türü oluşturmak yerine `Scoped Enums` kullanılması önerilmektedir. Çünkü bu tür *Unscoped Enums* türünün sorunları yüzünden dile eklenmiştir.


```cpp
enum Color{ /* UNSCOPED ENUM */


};

enum struct Color{ /*  SCOPED ENUM */

	
};

enum class Color{ /*  SCOPED ENUM */

	
};

```


### Complete and Incomplete Types
- Genellikle user-defined types ile ilgilidir.
- Eksik herhangi bir bilgi kalmamışsa complete type olur.
- Türün varlığından haberdar fakat türün tanımının tamamını görmemişse compiler için incomplete type olur.
```cpp
struct Nec; /* Incomplete type */


struct Nec{ /* Complete Type */
	int x;

};
```

- **Bazı işlemler complete type zorunluluğuna sahipken bazı işlemler değildir.**
- **Eğer incomplete type işinizi görüyorsa complete type kullanmayın!**
	- Çoğu zaman başlık dosyasını `include` etme yükünü ortadan kaldırır.


### `enum` Türünün 3 Büyük Günahı

1. Eğer derleyici bir enum türüyle ilgili bellekte kaç byte yer ayıracağını bilmiyor oluşu
	- Underlying type derleyiciye bağlı.

```cpp
enum Color; /* Incomplete Type */

struct Nec {
	Color mc; /* Kaç byte?? */

};

```

2. `enum` ==> `int` örtülü dönüşümü olması
	- Kodlama hatalarına davetiye

```cpp
enum Color{White,Yellow,Red,Brown,Blue,Black};

int main(int argc, char const *argv[])
{
    Color c = Yellow;
    int x;

    x = c;

}
```

3. Enumarator sabitlerinin scope'u Enum türünün scope'u ile aynıdır.
	- İsim çakışması
```cpp
enum Color_1{White,Yellow,Red,Brown,Blue,Black};

enum Color_2{White,Yellow,Red,Brown,Blue,Black};


int main(int argc, char const *argv[])
{

}
/* ILLEGAL CODE BECAUSE OF THE NAMES OF ENUMARATORS*/
```

>[!FIX]
>Bu problemle başa çıkmak için dile underlying type belirtme özelliği eklenmiştir. 


```cpp
enum ScreenColor : int {Red,Blue}; 
```

```cpp
enum class Color {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/
```
- Yukarıdaki durumda artık isim çakışması söz konusu değildir.
 - Örtülü dönüşüm yoktur
```cpp
enum class Color_1 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/
enum class Color_2 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/

int main(int argc, char const *argv[])
{
    auto c = Color_1::Blue;
    
    int x;
    // x = c; ILLEGAL
    x = static_cast<int>(c);
    std::cout << "x = " << x << std::endl;

}
/*
out:
x = 4
*/

```

>[!FEATURE]
> C++17 ile birlikte dile Scoped Enums için her seferinde nitelendirilmiş isim kullanmamak için `using enum E` yapısı getirilmiştir.


```cpp
enum class Color_1 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/
enum class Color_2 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/

int main(int argc, char const *argv[])
{
    using enum Color_1; /* CPP20 STANDARD */
     auto c = Blue;
    
    int x;
    // x = c; ILLEGAL
    x = static_cast<int>(c);
    std::cout << "x = " << x << std::endl;

}
```


## `decltype` Type Deduction Keyword

- Bir türün kullanıldığı tüm bağlamlarda `decltype` ile oluşturulan bir tür kullanılabilir.
```cpp
     int x = 5;
     decltype(x);
```

1. `decltype` ile oluşturulan tür hangi anlama gelecek?
	1. operand olan ifadenin bir isim formunda olması
	2. operand olan ifadenin bir isim formunda olmaması
```cpp
decltype(x); /* 1. kural */
decltype(x + 5); /* 2. kural */
```

>[!INFO]
>Operand bir isim formunda ise o isim hangi tür formundan elde ediliyorsa `decltype` da o türden elde edilir.

```cpp
int main(int argc, char const *argv[])
{
     int x = 5;
     decltype(x) y = 5; /* int y = 5; */

}
```

- **`decltype` tür gerektiren her yerde kullanılabilir.**

>[!INFO]
>Operand bir isim formunda olmayan ifade olursa `decltype` ile ifade edilen tür, operandın value category'sine bağlıdır.
>- L Value
>	- Türün referansı olur. `T&`
>- PR Value
>	- Türün kendisi olur. `T`
>- X Value
>	- Türün R Value Referansı olur. `T&&`

```cpp
int main(int argc, char const *argv[])
{
     int x = 5;
     decltype(x) y = 5; /* int y = 5; */
     int* ptr = &x;
     decltype(x + 5) i_a; /*int i_a;*/
     decltype(*ptr) a = x; /*int& a = x;*/

     int ar[10]{};
     decltype(ar[47]) m = ar[3]; /*int& m = ar[3];*/

}
```

>[!IMPORTANT]
>Yukarıdaki örnekte ar dizisinin 47. elemanı olmamasına rağmen UB olmaz. Çünkü `decltype` operandı olan ifade UNEVALUATED CONTEXT olur. 
>- `sizeof` operatörü gibi derleyici burada da işlem ÜRETMEZ!!

```cpp
/*decltype*/
int main(int argc, char const *argv[])
{
     int x = 5;
     int a{};
     decltype(++x) y = a; /* int& y = a; */

    std::cout << "x = " << x << std::endl;

}

/*
out:
x = 5
*/
```