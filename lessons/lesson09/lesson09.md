
## Function Overload Resolution Cont'd

>[!ERROR]
>Call by Value ve Call by Reference arasında doğrudan bir seçilebilirlik yoktur.

```cpp
void foo(int);
void foo(int&);
int main(int argc, char const *argv[])
{
    int x{};
    foo(x); /*AMBIGUITY!*/
}
```

>[!INFO]
>Pointer türlerinden `bool` türüne örtülü dönüşüm vardır!

```cpp
void foo(bool);
int main(int argc, char const *argv[])
{
    int x{};
    foo(&x); /*LEGAL*/ /* Implicit Conversion from T* to bool*/
}
```


>[!INFO]
>Tüm pointer türlerinden `void*` türüne dönüşüm vardır!

```cpp
void foo(void*);
int main(int argc, char const *argv[])
{
    int x{};
    foo(&x); /*LEGAL*/ /* Conversion from T* to void* */
}
```

Yukarıdaki iki örneğin birlikte olduğu durumda iki dönüşüm de standard conversion olmasına rağmen `void*` dönüşümü önceliklidir.

```cpp
void foo(bool){
    cout << "foo(bool)" << endl;
}
void foo(void*){
    cout << "foo(void*)" << endl;
}

int main(int argc, char const *argv[])
{
    int x{};
    foo(&x); 
}
/*
out:
foo(void*)
*/
```

- Varsayılan argümanla birlikte yapılan overload'larda ambiguity durumu oluşabilir
```cpp
void foo(int x, int y = 5){}
void foo(int){}

int main(int argc, char const *argv[])
{
    int x{};
    foo(&x); /*AMBIGUITY!! */
}
```

### Function Overload Resolution with Multiple Parameters
- Birden fazla parametreli overloading'ler için:
- Bir Overload'un seçilebilmesi için:
	1. En az bir parametrede diğerlerine üstünlük sağlamalı ve diğer parametrelerde diğer overload'lardan daha kötü olmayacak.

```cpp
/*Function Overload Resolution with Multiple Parameters*/
void foo(int, double, long){cout << "1" << endl;} //  1
void foo(float,unsigned,int){cout << "2" << endl;} // 2
void foo(double,char,int){cout << "3" << endl;} //    3

int main(int argc, char const *argv[])
{
    foo(12,3.4,3.3f); /*1 çağırılır*/
    foo(3.4f,45,7u); /*2 çağırılır*/
    foo(3.4,34,7); /*3 çağırılır*/ /*ilk parametre float olsaydı 2. fonksiyon çağırılırdı*/
}
/*
out:
1
2
3
*/
```

>[!attention]
> Fonksiyonların tüm özellikleri öğrenilmediğinden Function Overload Resolution konusunun devamına ilerleyen haftalarda geçilecektir.


# `auto` Type Deduction Additional

- `auto` anahtar sözcüğü ile tür çıkarımının 3 şekilde olduğundan bahsetmiştik.
- `auto x`
- `auto& x`
- `auto&& x`
- İlk 2 maddeyi görmüştük fakat 3. maddeyi görmemiştik.

## `auto&&` Kullanımı
- Burada 2 farklı kural vardır
	- `auto&&` değişkeni bir R value ile ilk değer almış.
		- `auto` anahtar kelimesi atanan r value değişkenin türüne dönüşür. 
```cpp
auto&& x = 10; /* int&& x = 10; */
```

- `auto&&` değişkeni bir L value ile ilk değer almış.
	- `auto` anahtar kelimesi yerine Left Reference gelecektir.
```cpp
int main(){
	int x = 5;
	auto && r = x; /* int& && r = x; */
}
```

- **Daha önceden de C++ dilinde *reference to reference* diye bir durumun olmadığından bahsetmiştik. **Fakat yukarıdaki gibi durumlarda `reference collapsing` kuralları uygulanmaktadır.

### Reference Collapsing
- Kurallar aşağıdaki gibidir:

| Ref1 | Ref2 | Result |
| ---- | ---- | ------ |
| T&   | &    | &      |
| T&   | &&   | &      |
| T&&  | &    | &      |
| T&&  | &&   | &&     |

- Az önceki örneği tekrar değerlendirirsek:
```cpp
int main(){
	int x = 5;
	auto && r = x; /* int& && r = x; */   /* int& && r = x ----> int & r = x;*/
}
```
- `auto && r = x;` ifadesinde `auto&&` ifadesine L value bir değer atanmıştır.
	- `auto` sözcüğü yerine *sol taraf referansı(&)* gelir.
	- `int& && r = x;` şeklindeki ifade ise **reference collapsing** sebebiyle `int & r = x;` ifadesine dönüşür.

# Type Alias Declaration 

- C++ dilinde C dilinde kullanılan `typedef` anahtar sözcüğüne alternatif olarak `using` sözcüğü bulunmaktadır.
	- Özellikle modern C++ kullanılırken genellikle bu sözcük tercih edilir.

```cpp
typedef int Word;
using Word = int;
```

>[!HATIRLATMA]
>`typedef` bildiriminde zorlanmamak için 3 adımda typedef bildirimi yapılabilir
>1.  İstenen türden bir değişken tanımla
>2. Tanımlamanın başına `typedef` anahtar sözcüğü koy
>3. Değişken ismi yerine tür eş ismini yerleştirin

>[!TIP]
>`using` anahtar sözcüğü kullanılırken ise aşağıdaki adımlarla tanımlama yapılır:
>- `using` anahtar sözcüğünden sonra tür eş ismi yazın
>- eşittir `=` sağ tarafına ise istenen türü yazın

```cpp
int main()
{
/*typedef*/
    typedef int inta10_t[10];
    typedef int (*fp_t)(int);
    typedef int& iref_t;
/*using*/
    using inta10_u = int[10];
    using fp_u = int(*)(int);
    using iref_u = int&;

}
```

# Sınıflar(Classes)

- C++ dilinde User Define Types grubunda C programlamada bulunan `struct` ile birlikte `class` yapısı hayatımıza girmektedir.
- Yapılardan çok daha geniş ve özelliklerle donatılmıştır.
- Problem domaininde bir nesneyi temsil etmenin yoludur.
- Nesne Yönelimli Programlama(OOP) temelini oluşturur.
```cpp
class Data{

};
```

>[!NOTE]
>C programlamadan farklı olarak C++ dilinde hem `struct` hem de `class` definition bloklarının içini boş bırakmak legaldir.


```cpp
class Data; /* class declaration */


class Data{ /* class definition */

	/*class members...*/
	
};

```

- Class definition bloğunun içinde bulunan öğelere **class members** denir.
- Class Members 3 e ayrılır:
	- Data members
	- Member functions
	- Member Types/Type Members/Nested Type

- Sınıfları kullanırken sınıf türüne ait bir nesne tanımlarız. Bu nesneye:
	- Object
	- Instance
- isimlerinden biri denir.

- C++ dilinde fonksiyonlar 2 türe ayrılır:
	- Global Function/Free Function/Stand-alone Function **(C Type Function)**
	- Member Function

>[!faq]
>C++ standardı asla *member* terimi kullanmaz. Bu community içerisindeki bazı kişiler tarafından kullanılan bir terimdir. Standart her zaman **member** kullanır.

 - Data members 2 kategoriye ayrılmaktadır.
	 - Non-Static Data Members
	 - Static Data Members
		- Static data members oluşturmak için değişkenin başına `static` anahtar kelimesinin gelmesi yeterlidir. 
		- Bu elemanlar sınıflar için yekparedir. Her sınıfın ayrı bir static elemanı yoktur. Tüm sınıflar içindir.
		- Sınıf türünden bir obje oluşturulduğunda hafızada kapladığı alanı değiştirmez.
- Member Functions da iki kategoriye ayrılır
	- Non-static member functions
	- Static member functions  
- Bu türlerin *static* olan kısımları **ilerde detaylı olarak ele alınacaktır**



- Member Functions sınıf nesnesi içerisinde **yer almaz**.
>[!Attention]
>C++ dilinde C'de olmayan ayrı bir kapsam(scope) kategorisi vardır. Buna **class scope** denir.

- Scope Categories in C
	1. file scope
	2. Block Scope
	3. Function Scope
	4. Function Prototype Scope
- Scope Categories in C++
	1. namespace scope(file scope u da içine alan bir scope)
	2. Block Scope
	3. Function Scope
	4. Function Prototype Scope
	5. Class Scope

>[!ATTENTION]
>Class Scope da bulunan isimler:
>Ancak aşağıdaki operatörlerin sağ operandı olarak kullanıldıklarında name-lookup ile class definition içinde aranırlar
>- member selection dot operator **(x.a)**
>- member selection arrow operator **(x->a)**
>- Scope Resolution operator **(Myclass::c)**

Nesne yönelimli programlama dillerinde genelde kod compile kontrolü aşağıdaki gibi olur:
1. Name lookup
2. Context control
3. Access Control


## Access Control
- C++ dilinde sınıflar söz konusu olduğunda çoğunlukla sınıfın elemanları, farklı özelliklere sahip 3 erişim kategorisinden birine(*access specifier*) sahiplerdir.
	- public
	- protected
	- private
- Sınıflarda default olarak access kategorisi **private** olmaktadır.
- Yapılarda(**struct**)  default olarak access kategorisi **public** olmaktadır.
```cpp
class Myclass{
	int x; /*private*/
}

struct Myclass{
	int x; /*public*/
}
```


>[!INFO]
>Access Specifier bir sınıf içerisinde yalnızca bir kere kullanılmak zorunda değildir.

### Access Specifiers Ne Anlama Gelmektedir
- **public** specifier'ı o elemanlara dışardan erişilebildiği anlamına gelir.
- **private** sınıfın kendi kodları haricindeki kodlar bu elemanlara erişemez.
>[!INFO]
>C++ dilinde inheritance yani kalıtım işlevi bulunmaktadır.  Bir sınıfın örneğin public interface'ini kendi sınıfına katan bir araçtır.**İlerde çok detaylı işlenecektir.**

- Kalıtım olmayan bir bağlamda **private** ile **protected** arasında bir fark yoktur. **protected** kalıtım yoluyla erişime izin verir.

