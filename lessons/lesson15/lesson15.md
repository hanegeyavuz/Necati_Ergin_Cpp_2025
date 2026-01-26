## Move Members

- Bu fonksiyonlar *copy ctor* ve *copy assignment* fonksiyonlarının overload'u niteliğindedirler. 
	- R Value Kategorisindeki argümanlar ile çağırılabilirler.
```cpp
MyClass(MyClass&&) /*move ctor*/

MyClass& operator=(MyClass&&); /*move assignment*/
```

- Bu fonksiyonlar kaynağı kopyalamaz, ÇALAR.
	- Alınan kaynak nesnesi alındıktan sonra hayatı biter.

- Bu fonksiyonların detayına inmeden önce bir standart kütüphane fonksiyonunu öğrenelim:

### `std::move` Function

- Aldığı argümanı L value da olsa R value da olsa R Value'ya dönüştüren fonksiyondur.
- Aslında `move` fonksiyonu yerine `static_cast<T&&>(expr)` şeklinde de R value dönüşümü yapılabillmektedir.
	- Çok çok istisna bir durum olmadığı müddetçe bu iki çağrı aynı işlevi sağlar.
- **MOVE DOESN'T MOVE** (Scott Meyers')


```cpp
class MyClass
{
    
public:
    MyClass() = default;
    MyClass(const MyClass&){
        std::cout << "copy ctor called\n";
    }
    MyClass(MyClass&&){
        
        std::cout << "move ctor called\n";
    }
    ~MyClass() = default;
private:

};

void foo(const MyClass&){
    std::cout << "foo(const MyClass&) called\n";
}
void foo(MyClass&&){
    
    std::cout << "foo(MyClass&&) called\n";
}


int main()
{
    MyClass m1;
    MyClass m2 = std::move(m1);
    MyClass m3 = m1;
    foo(std::move(m2));
}

/*
out:
move ctor called
copy ctor called
foo(MyClass&&) called
*/
```


- Tüm fonksiyonların çağrısına bir örnek verirsek:

```cpp
class MyClass
{
    
public:
    MyClass() = default;
    MyClass(const MyClass&){
        std::cout << "copy ctor called\n";
    }
    MyClass(MyClass&&){
        
        std::cout << "move ctor called\n";
    }
    
    MyClass& operator=(const MyClass&){
        std::cout << "copy assignment called\n";
        return *this;
    }
    MyClass& operator=(MyClass&&){
        std::cout << "move assignment called\n";
        return *this;
    }


    ~MyClass() = default;
private:

};

void foo(const MyClass&){
    std::cout << "foo(const MyClass&) called\n";
}
void foo(MyClass&&){
    
    std::cout << "foo(MyClass&&) called\n";
}


int main()
{
    MyClass m1; /*default ctor*/
    MyClass m3 = m1; /*copy ctor*/
    MyClass m2 = std::move(m1); /*move ctor*/
    foo(std::move(m2)); /*move ctor*/
    m3 = m2; /*copy assignment*/
    MyClass m4; /*default ctor*/
    m4 = std::move(m3); /*move assignment*/
}

/*
out:
move ctor called
copy ctor called
foo(MyClass&&) called
copy assignment called
move assignment called
*/
```

### Derleyicinin Yazdığı `move ctor` Fonksiyonu

>[!NOTE]
>Eğer special functions grubundan birbirinin overload'u olan iki fonksiyon varken(örneğin copy ctor ve move ctor) eğer move fonksiyonu yoksa sağ taraf referans ile yapılan çağrılarda yine *copy ctor* çağırılır. 
>- Daha önceden **function overloading** konusunda da görüldüğü üzere `const T&` argümanı sağ taraf referansı da alabilmektedir.

>[!INFO]
>Her sınıfın move ctor veya move assignment fonksiyonu olmak zorunda değildir. 
>- Örneğin içinde 2 adet `int` ve `unsigned char` dizi tutan bir sınıf düşünelim. Bu sınıfın `move ctor` fonksiyonu ile `copy ctor` fonksiyonu aynı kopyalama maliyetine sahiptir.
>- Fakat `String` sınıfı gibi dinamik bellek alanı kullanan yapılarda move işlemi copy işlemine göre ciddi maliyet kazancı elde etmemizi sağlar.

```cpp
/*default implicitly declared move functions*/
class MyClass
{

public:
    MyClass() = default;
    MyClass(const MyClass &)
    {
        std::cout << "copy ctor called\n";
    }
    MyClass(MyClass &&other) : ax(std::move(other.ax)), 
        bx(std::move(other.bx)), cx(std::move(other.cx))
    {

        std::cout << "move ctor called\n";
    }

    MyClass &operator=(const MyClass & other)
    {
        std::cout << "copy assignment called\n";

        if(this == &other) return *this;
        
        ax = other.ax;
        bx = other.bx;
        cx = other.cx;
        
        return *this;
    }
    MyClass &operator=(MyClass && other)
    {
        std::cout << "move assignment called\n";
        
        ax = std::move(other.ax);
        bx = std::move(other.bx);
        cx = std::move(other.cx);

        return *this;

    }

    ~MyClass() = default;

private:
    int ax;
    int bx;
    int cx;
};

void foo(const MyClass &)
{
    std::cout << "foo(const MyClass&) called\n";
}
void foo(MyClass &&)
{

    std::cout << "foo(MyClass&&) called\n";
}

int main()
{
    MyClass m1;                 /*default ctor*/
    MyClass m3 = m1;            /*copy ctor*/
    MyClass m2 = std::move(m1); /*move ctor*/
    foo(std::move(m2));         /*move ctor*/
    m3 = m2;                    /*copy assignment*/
    MyClass m4;                 /*default ctor*/
    m4 = std::move(m3);         /*move assignment*/
}

```


- Eğer kaynak kullanımı varsa:

- *move ctor*

```cpp
    myString(myString&& other) : mp_(other.mp_), mlen_(other.mlen_){
        other.mp_ = nullptr;
        other.mlen_ = 0;
    }
```

- *move assignment*

```cpp
    myString& operator=(myString&& other){
        if(this == &other){return *this;}

        free(mp_);
        mp_ = other.mp_;
        mlen_ = other.mlen_;

        other.mlen_ = 0;
        other.mp_ = nullptr;

        return *this;
    }
```


- Daha önceden yazdığımız string sınıfının son hali:

```cpp
class myString
{
public:
    myString() : mp_{nullptr}, mlen_{0} {}
   
    myString(const char *p);
    
    myString(const myString& other) : mlen_{other.mlen_}, 
    mp_{static_cast<char*>(std::malloc(mlen_ + 1))}
    { 
        
            std::strcpy(mp_,other.mp_);
    }

    myString(myString&& other) : mp_(other.mp_), mlen_(other.mlen_){
        other.mp_ = nullptr;
        other.mlen_ = 0;
    }

    myString& operator=(const myString& other){
        if(this != &other){
            mlen_ = other.mlen_;
            free(mp_);
            mp_ = static_cast<char*>(std::malloc(mlen_+1));

            std::strcpy(mp_,other.mp_);
        }
    }
    
    myString& operator=(myString&& other){
        if(this == &other){return *this;}

        free(mp_);
        mp_ = other.mp_;
        mlen_ = other.mlen_;

        other.mlen_ = 0;
        other.mp_ = nullptr;

        return *this;
    }

    const char *get_str() const
    {
        return mp_;
    }
   
    ~myString()
    {
        if (mp_)
        {
            free(mp_);
        }
    }
    void make_upper(){
        size_t str_len = std::strlen(mp_); 
        for(int i = 0; i < str_len; ++i){
            *(mp_+i) = static_cast<char>(std::toupper(mp_[i]));
        }
    }

private:
    size_t mlen_;
    char *mp_;
};
myString::myString(const char *p) : mlen_{std::strlen(p) + 1}, mp_{static_cast<char *>(malloc(mlen_ * sizeof(char)))}
{
    std::strcpy(mp_, p);
}

```


- Kaynağı move edilen nesnenin hayatı biter ve **destructor** çağırılır.
```cpp
int main()
{
    myString str1{"yavuz hanege"};
    myString str2 = std::move(str1);
    str2.print();
    std::cout << "len = " << str2.get_strlen() << "\n";
    std::cout << "len = " << str1.get_strlen() << "\n";
    // std::cout << "str1 = " << (str1.get_str()) << "\n";
    // std::cout << "str2 = " << (str2.get_str()) << "\n";
    // str1.make_upper();
    // std::cout << "str1 = " << (str1.get_str()) << "\n";
    // std::cout << "str2 = " << (str2.get_str()) << "\n";
    // foo(str1);
    // foo(str2);
}

/*
out:
(yavuz hanege)
len = 13
len = 0
*/
```
- Yukarıdaki örnekte de görüldüğü üzere move ctor ile *str1* nesnesinin kaynağı çalınmıştır ve hayatı tamamlanmıştır. *destructor* çağrısı ile len değişkeni 0 a eşitlenmiştir.



>[!NOTE]
>C++ dilinde community terimi olarak `temporary obje` olarak geçen PR Value olan geçici obje oluşturma yolu vardır.
>

```cpp
// String()
// String{}
```
- Yukarıdaki iki syntax ile temp obje oluşturulabilir.
- **İlerde detaylıca incelenecektir.**


```cpp
int main()
{
    myString str;

    str = myString{"yavuz hanege 23"}; /*move assignment call temp object*/
}
```


>[!NOTE]
>Geri dönüş türü referans olmayan fonksiyonlara yapılan çağrılar R Value kategorisindedir.

```cpp
myclass foo(); /*R Value*/
myclass &bar(); /*L Value */
myclass &&baz(); /*X Value --> R Value*/
```


>[!INFO]
>Kaynağı çalınmış durumdaki nesneye **moved-from state** nesne denir.


```cpp
int main()
{
    myString s1{"necati ergin"};

    myString s2;

    s2 = std::move(s1);

    // s1 ==> moved-from state
}
```


>[!NOTE]
>*moved-from state* nesneler kullanılabilmektedir. Standart Kütüphane bu nesneler için şunu söyler:
>- Bu nesneler valid state durumda olmak zorundadır.
>- Değerinin ne olacağı konusunda garanti verilmez.
>- Tekrar atama yapılabilir.

```cpp
#if 1

int main(int argc, char const *argv[])
{
    using namespace std;

    string s1(100,'a');

    string s2 = move(s1);

    cout << "len s1 = " << s1.length() << "\n";
}

#endif

/*
out:
len s1 = 0
*/
```

>[!IMPORTANT]
>Standart böyle bir garanti vermese de neredeyse derleyicilerin tamamı için *string* sınıfı *moved-from* durumundaki nesneler **boş yazı** nesneleridir. 

- Mesela iki *string* türünden nesneyi swap yapmak istersek bunun için *copy ctor* ve *copy assingment* fonksiyonlarının kullanıldığı senaryoda çok fazla kaynak kullanımı olacaktır. Onun yerine move functions kullanmak çok daha uygundur.

```cpp
void str_swap(std::string &x,std::string &y){

    std::string temp = x;
    
    x = std::move(y);
    y = std::move(temp);
}


int main()
{
    std::string x{"yavuz"};
    std::string y{"hanege"};
    
    std::cout << "x = " << x.c_str() << "\n";
    std::cout << "y = " << y.c_str() << "\n";

    str_swap(x,y);
    
    std::cout << "x = " << x.c_str() << "\n";
    std::cout << "y = " << y.c_str() << "\n";
}
```


>[!HINT]
>Bizim de kendi yazacağımız sınıflarda *moved-from state* nesnelerin geçerli ve idealde değerinin de belli olması gerekmektedir.(Genellikle değeri default ctor init edilmiş değer olması kaubl edilir.)
>- Kendisine atama yapılabilir
>- Kendisine veya kendisinden taşıma yapılabilir.


>[!NOTE]
>En sık karşımıza çıkacak idiomatik yapılardan biri:
>- Bir fonksiyonun kendine gönderilen argümanın R value olması durumunda kaynağını çalması,
>- L value olması durumunda onun kaynağını kopyalamasını isteriz.

```cpp
/*function overloads*/
void foo(const MyClass& r){ /* L Value Args*/
    MyClass m = r;
}
void foo(MyClass&& r){     /* R Value Args*/
    MyClass m = std::move(r);
}
```


```cpp
class MyClass{
public:
    MyClass() = default;
    MyClass(const MyClass&){
        std::cout << "copy ctor. copies the resource\n";
    }
    MyClass(MyClass&&){
        std::cout << "move ctor. steal the resource\n";
    }

    MyClass& operator=(const MyClass&){
        std::cout << "copy assign. copies the resource\n";
        return *this;
    }
    MyClass& operator=(MyClass&&){
        std::cout << "move assign. steals the resource\n";
        return *this;
    }

private:

};


void foo(const MyClass& r){
    MyClass m = r;
    MyClass n;
    n = r;
}
void foo(MyClass&& r){
    MyClass m = std::move(r);
    MyClass n;
    n = std::move(r);
}


int main(int argc, char const *argv[])
{
    MyClass m;
    foo(m);
    foo(MyClass{});

}

/*
out:
copy ctor. copies the resource
copy assign. copies the resource
move ctor. steal the resource
move assign. steals the resource
*/
```


### Çok Sorulan Bir Mülakat Sorusu

```cpp
class MyClass{
public:
    MyClass() = default;
    MyClass(const MyClass&){
        std::cout << "copy ctor. copies the resource\n";
    }
    MyClass(MyClass&&){
        std::cout << "move ctor. steal the resource\n";
    }

    MyClass& operator=(const MyClass&){
        std::cout << "copy assign. copies the resource\n";
        return *this;
    }
    MyClass& operator=(MyClass&&){
        std::cout << "move assign. copies the resource\n";
        return *this;
    }

private:

};


void bar(const MyClass& r){
    std::cout << "bar(const MyClass&)\n";
}
void bar(MyClass&& r){
    std::cout << "bar(MyClass&&)\n";
}
void foo(MyClass&& r){
    bar(r);
}


int main(int argc, char const *argv[])
{
    foo(MyClass{});
}
```
- Yukarıdaki kod çalıştırıldığında hangi *bar* fonksiyonu çağırılır?

>[!ANSWER]
>**Gönderilen argümanın **declaration type**'ı R Value olsa bile  *r* ifadesi L Value olduğundan dolayı `const MyClass& r` fonksiyon çağırılaracaktır.!!!**

- R Value ile çağrı yapılsaydı diğer fonksiyon çağırılırdı.
	- `std::move(r);`


### Önemli Bir Kısım
- Special Member Functions konusunda kullanıcı tanımlaması ile derleyicinin default olarak declare ettiği fonksiyonlar değişebilir.

- **Kullanıcı tarafından bildirilmiş fonksiyonlara göre derleyicinin diğer special member fonksiyonları default declare etme durumu:(Y = YES, N= NO):**

|   User Declared Functions    | default ctor |   dtor    | copy ctor | copy assign | move ctor | move assign |
| :--------------------------: | :----------: | :-------: | :-------: | :---------: | :-------: | :---------: |
|            no spm            |      Y       |     Y     |     Y     |      Y      |     Y     |      Y      |
|          `Nec(int)`          |      N       |     Y     |     Y     |      Y      |     Y     |      Y      |
|           `Nec()`            |  User Dec.   |     Y     |     Y     |      Y      |     Y     |      Y      |
|           `~Nec()`           |      Y       | User Dec. |   Y(!)    |    Y(!)     | NOT DEC.  |  NOT DEC.   |
|      `Nec(const Nec&)`       |   NOT DEC.   |     Y     | User dec. |    Y(!)     | NOT DEC.  |  NOT DEC.   |
| `Nec& operator=(const Nec&)` |      Y       |     Y     |   Y(!)    |  User dec.  | NOT DEC.  |  NOT DEC.   |
|         `Nec(Nec&&)`         |   NOT DEC.   |     Y     |  deleted  |   deleted   | User dec. |  NOT DEC.   |
|   `Nec& operator=(Nec&&)`    |      Y       |     Y     |  deleted  |   deleted   | NOT DEC.  |  User dec.  |
- *(!)* ifadesi şunu gösterir: Bunların *not declared* olması gerekirdi fakat eski kodların çalışabilmesi için default şekilde derleyici tarafından declare ediliyor.
	- Bu çok tehlikeli bir durumdur.

>[!HINT]
>1. Bir sınıfın `default ctor`'u kullanıcı tarafından **herhangi bir ctor** bildirilmezse default declare edilir.
>2. `dtor` fonksiyonu her zaman vardır. Ya *user declared* ya da *implicitly declared* haldedir.
>3. Eski tabirle BIG3 fonksiyonlardan(`dtor`,`copy ctor` ve `copy assign`) herhangi biri bildirilirse `move functions` not declared durumundadır.
>4. Maalesef BIG3 fonksiyonlarından birini kullanıcı bildirirse diğer ikisini derleyici default declare eder.(İyi bir şey değil.)
>5. Move Member Functions herhangi biri kullanıcı tarafından bildirilirse sınıfın copy member fonksiyonları **delete edilir.**


- Genellikle karşımıza 3 tür sınıf çıkacaktır:
	1. copyable and moveable
	2. copyable and non-moveable
	3. non-copyable but moveable
	4. non-copyable and non-moveable
