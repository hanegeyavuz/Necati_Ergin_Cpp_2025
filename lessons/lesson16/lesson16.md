
---

- Hatırlatma amacıyla bir önceki derste işlenen special member functions declaration için fonksiyon spesifik diğer fonksiyonların default tanımlanma durumları tablosu aşağıdaki gibidir.

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

### Move Only Sınıf Oluşturulması

- Eğer bir sınıfın move member'ları declare edilirse copy member'ları delete edilir.

```cpp
/*move only class*/
class Yavuz{
public:
    /*Not Necessary, if move members declared, copy members deleted defaultly*/
    // Yavuz(const Yavuz&) = delete;
    // Yavuz& operator=(const Yavuz&) = delete;

    Yavuz(Yavuz&&);
    Yavuz& operator=(Yavuz&&);

private:

};

```

>[!ERROR]
>Hiçbir durumda move members `delete` edilmesi doğru değildir. Copyable and not moveable bir class oluşturmak için yalnızca copy member declare edilmesi yeterlidir. move members not defined duruma geçer.
>- Herhangi bir move constructor veya move assignment operator kullanıcı tarafından **delete edilir** veya tanımlanırsa compiler copy ctor ve copy assignment'ı da otomatik üretmez.


## Conversion Constructor

- Sınıfın tipik olarak tek parametreli ctor fonksiyonlarının obje oluşturmak dışında bir işlevi daha vardır
	- Örtülü Dönüşüm Oluşturmak

```cpp
class Yavuz{
public:
    Yavuz() = default;

    Yavuz(int x): mx_{x}{
        std::cout << "\nYavuz(int) called-----> x = " << mx_ << "\n";  
    }

private:
    int mx_;
};



int main(int argc, char const *argv[])
{
    Yavuz Yvz;

    Yvz = 32; /* conv ctor implicitly conversion*/
}
```

- Yukarıdaki kod parçacığında eğer user defined ctor olmasaydı `Yvz = 32;` çağrısı syntax error a sebep olurken ctor sebebiyle derleyici örtülü olarak dönüşüm yaparak user defined ctor çağrısı yaptı.
- Derleyici burada temporary bir obje(PRValue) oluşturur ve bu objeyi assign ettiğimiz sınıf nesnesine move veya copy yöntemleri ile assign eder.
	- move assignment varsa move assignment yoksa copy assignment kullanılır.

- Eğer copy assignment veya copy ctor fonksiyonu tanımlanırsa move members not defined olacağından copy assignment fonksiyonu çağırılır.
```cpp
/*conversion ctor*/
class Yavuz{
public:
    Yavuz() = default;

    Yavuz(int x): mx_{x}{
        std::cout << "\nYavuz(int) called-----> x = " << mx_ << "\n";  
    }

    Yavuz& operator=(const Yavuz& other){
        std::cout << "Yavuz& operator=(const Yavuz& other) called\n";
        mx_ = other.mx_;
        return *this;
    }

private:
    int mx_;
};



int main(int argc, char const *argv[])
{
    Yavuz Yvz;

    Yvz = 32;
}
/*
out:
Yavuz(int) called-----> x = 32
Yavuz& operator=(const Yavuz& other) called
*/
```

>[!QUESTION]
>Bu dönüşüm iyi bir şey mi? (T -> class T)
>>[!ANSWER]
>>Çoğunlukla istenmez. Kafa karıştırıcıdır.

>[!INFO]
>Eğer bir dönüşüm örtülü olarak standard conversion + user-defined conversion veya user-defined conversion  + standard conversion olarak yapılabiliyorsa derleyici bunu yapmak zorundadır.

```cpp
int main(int argc, char const *argv[])
{
    Yavuz Yvz;

    Yvz = 32.32; //double --> int(standard conversion) int--->T Class(User-Defined Conversion) 
}
```

>[!ERROR]
>Derleyici asla User-Defined Conversion + User-Defined art arda Conversion YAPMAZ!!

```cpp
struct A
{
    
};

struct B
{
    B() = default;
    B(A);
};

struct C
{
    C() = default;
    C(B);
};



int main(int argc, char const *argv[])
{
    A ax;
    C cx;

    cx = ax; /*ud conv + ud conv ERROR!*/
}

```


## Explicit Constructor

- `explicit` anahtar sözcüğü ile oluşturulan ctor fonksiyonlardır.
	- `explicit` anahtar sözcüğü bu fonksiyonun tür dönüşümü yaparken tür dönüşüm operatörünün kullanımını zorunlu kılar.
	- Örtülü Dönüşüme izin vermez.
```cpp
class MyClass
{
public:
    MyClass() = default;
    explicit MyClass(int x): mx_{x}{
        std::cout << "mx_ = " << mx_ << "\n";
    }
private:
    int mx_;
};


int main(int argc, char const *argv[])
{
    MyClass m1;

    m1 = 33.3; /* ILLEGAL!! explicit keyword!*/
}
```

- `explicit` keyword'u yüzünden aşağıdaki gibi bir dönüşümü kullanıcının yapması gerekmektedir.
```cpp
int main(int argc, char const *argv[])
{
    MyClass m1;

    /*same*/
    m1 = static_cast<MyClass>(33); /*Static Cast*/
    m1 = MyClass(33); /*PR Value Expression*/
    m1 = (MyClass)33 /*C Type Cast*/
}
```

>[!HINT]
>Çoğu durumda tek parametreli ctor fonksiyonu `explicit` TANIMLANMALIDIR. Yukarıdaki conversion sorunları sebebiyle.
>- `string` sınıfı gibi bu örtülü dönüşümü bilerek isteyen sınıflarda kullanılabilir fakat bu durumlar daha nadir görülür.


>[!ERROR]
>Eğer sınıfın tek parametreli ctor fonksiyonu `explicit` olarak tanımlanmışsa copy initialization da artık geçersizdir.

```cpp
int main(int argc, char const *argv[])
{
    MyClass x{12};      /*LEGAL*/
    MyClass y(23);      /*LEGAL*/
    MyClass x = 62;     /*ILLEGAL*/
}
```

>[!ERROR]
>`explicit` anahtar sözcüğü bildirimde var ise tanımda OLMAZ!


## Temporary Objects

- C++17 öncesinde ismi olmayan fakat runtime aşamasında bir nesneye karşılık gelen objelere temporary object deniliyordu.

```cpp
MyClass foo(); /* function call, MyClass type object(temporary) */
```

>[!IMPORTANT]
>Eğer bir sınıf türünden bir nesneye ihtiyacımız varsa ve bu nesneyi isimlendirmeden kullanabiliyorsak isimlendirmeden kullanmak her zaman daha iyidir.

- Sınıf türünden bir geçici objeyi aşağıdaki gibi oluşturabiliriz:
```cpp
foo(MyClass{122});
```


>[!INFO]
>C++17 standardına göre PRValue olan sınıf ifadeleri artık doğrudan bir nesne değildir. Doğrudan nesne olabilmesi için temporary materialization olması gerekmektedir.
>


- Temporary Materialization gerçekleşmesi zorunlu durumlar
	- PRValue expression discard edilirse
	- Bir referansa bağlandığı zaman

## Copy Elision

- C++17 öncesinde bir kopyalamanın yapılmaması compiler optimizasyonu olarak geçiyordu.
	- C++17 sonrasında bazı durumlarda copy elision mecburi(mandatory) hale gelmiştir.
- C++17 öncesinde bir sınıfın kopyalama için copy ctor fonksiyonunu çağıramadığı durumda örneğin copy ctor fonksiyonunun private veya delete edilmesi halinde kod geçersiz sayılırdı.
	- Fakat C++17 ve sonrasında bu işlem bir compiler optimization olmaktan çıkıp bir kural haline gelmiştir.
```cpp
/*copy elision*/

class MyClass
{
public:
    MyClass(){
        std::cout << "default ctor called\n";

    }
    
private:
    MyClass(const MyClass&){
        std::cout << "copy ctor called\n";
    }
};

void foo(MyClass){};

int main(int argc, char const *argv[])
{
    foo(MyClass{});
}

/*
out:
default ctor called
*/
```

>[!IMPORTANT]
>Mandatory Copy Elision Durumları:
>-  Unmaterialized Object Passing
>	- Bir fonksiyonun parametresi bir sınıf türünden ise ve fonksiyonu bir PRValue expression argüman ile çağırırsam derleyici kopyalama yapılmadan derleyici direkt bu argümanı doğrudan fonksiyonun parametre değişkenini initialize etmek için kullanılacaktır.
>		- Burada COPY ELISION olmak ZORUNDA!
>- Return Value Optimization(RVO/URVO)
>	- 


```cpp
/*copy elision*/
/*Return Value Optimization*/
class MyClass
{
public:
    MyClass(){
        std::cout << "default ctor called\n";

    }
    
private:
    MyClass(const MyClass&){
        std::cout << "copy ctor called\n";
    }
};

MyClass foo(){
    return MyClass{};
};

int main(int argc, char const *argv[])
{
    MyClass m = foo(); /*RVO*/
}

/*
out:
default ctor called
*/
```

- Yukarıdaki örneklerde sadece `default ctor` çağırılmasının sebebi copy elision olmasıdır.
```cpp
int main(int argc, char const *argv[])
{
    MyClass m; /* default ctor*/
    m = foo();  /*move assignment*/
}
```
- Yukarıdaki ifadede obje oluşumu olmadığından copy elision yoktur.


>[!NOTE]
>- Geçici nesne bir referansa bağlanmazsa ifadenin yürütülmesi bittiğinde geçici nesnenin dtor fonksiyonu çağırılır ve hayatı biter.
>- Eğer PRValue bir sınıf nesnesi bir referansa bağlanırsa referansın scope'unun sonuna kadar geçici nesnenin dtor fonksiyonu çağırılmaz.

### Hatırlatmalar

- Sınıfları oluştururken çoğu zaman L Value ve R Value ifadelerin ayrılması için aşağıdaki gibi bir yapıya ihtiyaç duyulur

```cpp
/*move semantics*/
class MyClass
{};

void foo(const MyClass& r){ /*for L Value Args.*/
    MyClass m = r; /*copy*/
}

void foo(MyClass&& r){ /*for R Value Args.*/
    MyClass m = std::move(r); /*move*/
    
}


int main(int argc, char const *argv[])
{
    
}
```


>[!NOTE]
>Otomatik ömürlü bir nesne bir fonksiyonun return ifadesi olursa derleyici burada L Value to X Value dönüşümünü yapmak zorundadır.

```cpp
/*move semantics*/
class MyClass
{
public:
    MyClass() = default;
    MyClass(const MyClass &) = default;
    MyClass(MyClass &&) = default;

    MyClass &operator=(const MyClass &)
    {
        std::cout << "copy assignment function called!\n";
        return *this;
    }
    MyClass &operator=(MyClass &&)
    {
        std::cout << "move assignment function called!\n";
        return *this;
    }

private:
};

MyClass foo()
{
    MyClass m;

    return m;
}

int main(int argc, char const *argv[])
{
    MyClass mx;

    mx = foo(); /*Move Assignment Function CALL!! NOT COPY ASSIGNMENT*/
}
/*
out:
move assignment function called!
*/
```
- Yukarıdaki örnekte otomatik ömürlü nesne return edildiğinden `move assignment` fonksiyonu çağırılır.

### Named Return Value Optimization

- Eğer sınıf nesnesi oluşturulurken otomatik ömürlü sınıf nesnesi döndüren bir fonksiyon ile nesne oluşumu yaparsanız derleyici önce fonksiyon içerisindeki otomatik ömürlü nesneyi sonra da  oluşturulan nesneyi hayata getirmek yerine tek bir nesne hayata getirir. Bu derleyici optimizasyonudur, mandatory değildir.
```cpp
class MyClass
{
public:
    MyClass()
    {
        std::cout << "default ctor function called!\n";
    }
    ~MyClass()
    {
        std::cout << "dtor function called!\n";
    }
    MyClass(const MyClass &)
    {
        std::cout << "copy ctor function called!\n";
    }
    MyClass(MyClass &&)
    {
        std::cout << "move ctor function called!\n";
    }

    MyClass &operator=(const MyClass &)
    {
        std::cout << "copy assignment function called!\n";
        return *this;
    }
    MyClass &operator=(MyClass &&)
    {
        std::cout << "move assignment function called!\n";
        return *this;
    }

private:
};

MyClass foo()
{
    MyClass m;

    return m;
}

int main(int argc, char const *argv[])
{
    MyClass mx = foo();
}

/*
out:
default ctor function called!
dtor function called!
*/
```

- Her derleyici bu optimizasyonu yapmaya çalışır.

```cpp
MyClass foo()
{
    MyClass m;

    return std::move(m); /*pessimistic move!!*/
}

int main(int argc, char const *argv[])
{
    MyClass mx = foo(); /*default ctor + move ctor called*/
}
/*
out:
default ctor function called!
move ctor function called!
*/
```
- Yukarıdaki örnek yeni başlayanların çok sık yaptığı bir verimsiz kod örneğidir. Burada geri dönüş değeri `std::move` ile yapıldığından derleyici RVO yapmayacaktır ve fazladan move ctor fonksiyonu çağırılacaktır. 
	- Bu duruma community terimi olarak **Pessimistic Move** denmektedir.