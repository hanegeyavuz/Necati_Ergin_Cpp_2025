
---

# Classes Cont'd
>[!NOTE]
>Bir üye fonksiyonun `const` veya non-const olduğunu belirlerken kullanılan nesneye bakılır. Fonksiyon nesnenin state'inde değişiklik yapıyorsa `non-const` denebilir. Bu ise tamamen problem domain'inde olan bir karardır. 
>>[!ERROR]
>>Asla bu karar şu şekilde VERİLMEZ:
>>- `sınıfın non-static member'larını değiştiriyorsa non-const, değiştirmiyorsa const.`
>>	- BU ŞEKİLDE BİR SAPTAMA KESİNLİKLE YANLIŞTIR.

>[!QUESTION]
>Diyelim ki elimizde bir sınıf olsun. Bu sınıfın bir fonksiyonu sınıfın state'ini değiştirmiyor. Fakat bir şekilde sınıfın state'inden bağımsız olan bir sınıf elemanını değiştirmesi gerekiyor. Örneğin sınıfın bir elemanı sınıfın üye fonksiyonlarının kaç kez çağırıldığını tutsun. Bu durumda const olan fonksiyonlar da çağırıldıklarında bu değişkeni 1 arttırmalılar. Bu nasıl yapılabilir?

```cpp
class Fighter{
public:
private:

	mutable int m_debug_call_count;	
};
```
- Yukarıdaki `mutable` anahtar sözcüğü derleyiciye şunu söyler:
	- Bu değişkeni değiştirmek sınıfın state'ini **değiştirmez**
```cpp
/*mutable keyword*/
class Fighter{
public:
    void get_name()const{
        m_debug_call_count++; /*LEGAL*/
        //++mx; /*ILLEGAL! ERROR!*/
    };
private:
	int mx;
	mutable int m_debug_call_count;	
};

int main(int argc, char const *argv[])
{
    
}
```

- İlerde ayrıntılı göreceğimiz thread safe yazılım konusunda da `mutable` anahtar sözcüğü aynı işlem için kullanılır.
	- Bir fonksiyon içerisinde mutex i lock ve unlock yapmak isteriz ama fonksiyon ,`const` bir member function ise mutex in tanımlanmasını sınıf içerisinde `mutable` olarak tanımlamalıyız.

## `this` Pointer
- `this` bir keyword'dür.
	- Bir pointer'a karşılık gelir.
- Eğer bir sınıfın non-static üye fonksiyonunda `this` keyword'ü kullanılırsa bu, fonksiyonun çağırılan sınıf nesnesinin adresinin **değerine** karşılık gelir.
	- Başka bir değişle **gizli parametre değişkeninin değerine** karşılık gelir.

>[!IMPORTANT]
>`this` pointer'ının oluşturduğu ifadenin value catergory'si PR Value'dur. 
>- Bu da atama operatörünün sol operandı olamaz demektir.

```cpp
/*this keyword*/
class MyClass{
public:
    void foo();
private:
	int mx;
};


void MyClass::foo(){
    // this = &gm; /*ILLEGAL */

    /*Same assignments*/
    this->mx = 5;
    mx = 5;
}
```

- Yukarıdaki örnekte de görüldüğü üzere sınıfın elemanlarını kullanırken herhangi bir name masking olmaması durumunda direkt değişkenin ismini kullanmak ile değişkeni `this` pointer'ı ile kullanmak arasında bir fark yoktur.

>[!TIP]
>- Necati Ergin, eğer istisnai bir durum yoksa sınıfın veri elemanlarına üye fonksiyonları içerisinde erişirken `this` pointer'ının kullanımını önermiyor. Fakat kullanılırsa yanlış olmaz.

- Bazı durumlarda şöyle ihtiyaçlar olabiliyor:
	- Bu fonksiyon hangi nesne için çağırıldı ise o nesnenin adresini bir free/global function'a göndermek istiyorum
```cpp
/*this keyword*/
class MyClass{
public:
    void foo();
private:
	int mx;
};

void gfunc(MyClass* ptr){
    cout << "ptr = " << ptr << endl;
}

void MyClass::foo(){

    cout << "MyClass::foo() called" << endl;
    cout << "this = " << this << endl;
    gfunc(this);
}

int main(int argc, char const *argv[])
{
    MyClass m11;

    cout << "&m = " << &m11 << endl; 

    m11.foo();
}
#endif

/*
out:
&m = 0xe5515ffcac
MyClass::foo() called
this = 0xe5515ffcac
ptr = 0xe5515ffcac
*/
```

- Bazı fonksiyonlar nesnenin kendisini döndürebilirler. Bunu da `*this` ile yaparlar.

```cpp
/*FLUENT API EXAMPLE*/
class MyClass
{
public:
MyClass& foo(){
    cout << "Myclass::foo called" << endl;
    return *this;
}
void bar(){
    cout << "Myclass::bar called" << endl;
}

private:

};

int main()
{
    MyClass m;
    m.foo().bar();
}
/*
out:
Myclass::foo called
Myclass::bar called
*/
```

- Bazı durumlarda nesnenin kendisini değil, adresini döndürmesi istenebilir.
```cpp
class MyClass
{
public:
MyClass* foo(){

    cout << "foo called\n";
    return this;
}
MyClass* bar(){
    cout << "bar called\n";
    return this;
}
MyClass* baz(){
    cout << "baz called\n";
    return this;
}

private:

};

int main()
{
    MyClass m1;
    m1.foo()->bar()->baz();
}
/*
foo called
bar called
baz called
*/
```

>[!ERROR]
>- Global bir fonksiyon içerisinde(member function olmayan fonksiyonlar) `this` keyword'ü kullanılamaz.
>- Sınıfların **Statik Üye Fonksiyonları** içerisinde `this` keyword'ü kullanılamaz.

```cpp
class MyClass
{
public:
MyClass* foo(){

    return this; /*LEGAL*/
}
MyClass* bar()const{

    return this; /*ILLEGAL*/ /*Gizli nesnenin türü `const MyClass*` fakat donus degeri `MyClass*`*/
}
private:
};
```
- Yukarıdaki kodda this pointerının türü `const MyClass*` iken fonksiyonun dönüş değeri `MyClass*` olduğu için `const T*` -> `T*` dönüşümü illegal olur.

## ODR (One Definition Rule)
- Tek sefer tanımlama kuralı
- Bir projede bir yazılımsal kaynağın birden fazla kez tanımlanması ODR Violation oluşturur.
- Eğer ODR Violation aynı kaynak dosyada ise derleyici hata vermek zorundadır.

```cpp
class Myclass{

};
class Myclass{

};

int main(){

}
```
- Aynı kaynak dosyaya 2 kez aynı sınıfın veya fonksiyonun tanımlanması ODR Violation'a sebep olur.
- Aynı durum global değişkenler için de geçerlidir.

>[!ATTENTION]
>Kural sadece **definition**'ı kapsar. Declaration için geçerli değildir. Örneğin:
>```cpp
>class MyClass;
>class MyClass;
>```


>[!IMPORTANT]
>Bazı istisnai durumlarda ODR Violation söz konusu değildir.
>1. token-by-token (birden fazla kaynak dosyada aynı olursa ODR çiğnenmez.)
>	1. Bu kuraldan dolayı başlık dosyalarında sınıf tanımlamaları yapılabilir çünkü token by token aynı olduğundan ODR Violation olmaz
>2. Inline Functions(aşağıda detaylı anlatılıyor.)

### Inline Expansion
- Derleyicinin yaptığı bir optimizasyondur. Bazı fonksiyonları inline hale getirir.

Yapılabilmesinin bazı şartları vardır:
1. Derleyici fonksiyon çağrısının olduğu noktada çağrılan fonksiyonun tanımını görmek zorundadır. 
	1. (Header file'da bildirimi yapılmış kaynak dosyasında da tanımı yapılan bir header file include edilirse dosya içerisindeki fonksiyona inline expansion yapılamaz.)
2. Derleyicinin yapacağı analizde i.e yapmanın faydalı olacağını görmüş olması gerekiyor.
3. Derleyici yapabilecek yetenekte olmalı

## `Inline` Keyword 

- Inline fonksiyonun geri dönüş değeri türünden önce yazılır.
- `intline int foo(int x, int y)`
- Bu özellik ile derleyiciye **inline expansion** yapabilirsin demiş oluruz.
	- Derleyici yapmak zorunda **DEĞİL!**

>[!question]
>Derleyici `inline` anahtar sözcüğüyle tanımlanmayan bir fonksiyon için inline expansion yapabilir mi?
>>[!ANSWER]
>>Ever yapabilir!

>[!QUESTION]
>O zaman neden `inline` anahtar sözcüğü var?
>>[!ANSWER]
>> ODR konusuna geri dönecek olursak: 
>> - Inline fonksiyonlar ODR'a neden olmazlar!!

>[!NOTE]
>Bir başlık dosyasında bir fonksiyonu `inline` function olarak tanımlarsam ODR violation OLMAZ!!

- Bir fonksiyonun inline fonksiyon olabilmesi için başında `inline` anahtar sözcüğü olmalıdır fakat bunun bazı istisnaları vardır.
	1. Sınıfın içinde tanımı yapılan fonksiyonlar **inline function** olur.

```cpp
/* neco.h */

class MyClass{
public:
    void func(){ /*INLINE FUNCTION*/

    }
private:
};

int main(){

}
```
- Yukarıdaki ifadede header file içerisinde sınıf tanımı olmasına rağmen ODR Violation yoktur.
```cpp
/* neco.h */

class MyClass{
public:
    void func(); /*non-inline function*/
    
    inline void bar();
private:
};

void MyClass::func(){
	
}
void MyClass::bar(){
	
}

int main(){

}
```
- Yukarıdaki ifadede `func` adlı fonksiyon inline fonksiyon olmadığından header file içerisinde tanımının yapılması ODR Violation a yol açar.
- `bar` fonksiyonunun bildiriminde `inline` anahtar sözcüğü olduduğundan inline fonksiyon olarak ele alınır ve ODR violation'a yol açmaz.

```cpp
/* neco.h */

class MyClass{
public:
    void func(); /*non-inline function*/
    
private:
};

inline void MyClass::func(){
	
}


int main(){

}
```

- Fonksiyonun bildiriminde `inline` anahtar sözcüğü yokken tanımında varsa fonksiyon yine `inline` fonksiyon olur ve ODR Violation oluşturmaz.

>[!NOTE]
>`constexpr` fonksiyonlar implicitly inline fonksiyonlardır.

```cpp
/* yavuz.h */
constexpr int yavuz(int a){
}
```
- Yukarıdaki fonksiyon `constexpr` fonksiyon olduğundan inline fonksiyon olur ve ODR Violation oluşturmaz.
