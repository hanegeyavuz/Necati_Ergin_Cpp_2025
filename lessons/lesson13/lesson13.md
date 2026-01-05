
---

## Initialization Types Remind

|Kod|Tür|Sonuç|
|---|---|---|
|`int x;`|Default|❌ UB|
|`int x{};`|Value|0|
|`int x = 5;`|Copy|5|
|`int x(5);`|Direct|5|
|`int x{5};`|List|5|
|`int x = {5};`|Copy List|5|
|`int x{3.14};`|❌|Narrowing|

---

## Constructor Initializer List Cont'd

- Eğer bir nesne ctor ile init edilmezse o nesne default initialize edilir. 

>[!ERROR]
>`const` değişkenler ve referans değişkenleri default init edilemeyeceğinden dolayı hata ile karşılaşılır.

```cpp
class MyClass{
public:
    MyClass();
private:
    int mx,my;
    const int mcx; /*uninitialized const member in 'const int' [-fpermissive]*/
    int& mrx; /*uninitialized reference member in 'int&' [-fpermissive]*/
};

MyClass::MyClass() : mx(5), my{30}
{
    cout << "mx = " << mx << " my = " << my << "\n";
}

int main()
{
    MyClass m1;

}
```


>[!TIP]
>Bir community konvansiyonu olarak sınıfın non-static veri elemanları isimlendirilirken *m* harfi ile başlar ya da sonunda `_` işareti bulundurur. Zorunlu değildir.
>


>[!NOTE]
>Ctor Init List ile initialization yapılırken sınıfın içerisindeki değişken sırasından farklı olarak init yapılsa bile initialization sırası değişmez.
>- Her zaman elemanların bildirilme sırası esas alınır.



```cpp
class MyClass{
public:
    MyClass();
private:
    int mx,my;
};

MyClass::MyClass() : my{30}, mx(5) /*once mx, sonra my init edilir.*/
{
    cout << "mx = " << mx << " my = " << my << "\n"; 
}

int main()
{
    MyClass m1;

}
```

>[!TIP]
>Sırayı değiştirince bile sıra değişmiş olmadığından dolayı ctor init list esnasında sırayı değiştirmeye gerek yoktur. Sırayı değiştirmemeliyiz.

```cpp
class MyClass{
public:
    MyClass(int a, int b): my_(a), mx_(my * b); /*UNDEFINED BEHAVIOUR*/
private:
    int mx_,my_;
};

int main()
{
    MyClass m1(3,5);

}
```


- Sınıfın non-static data member isimleri ile ctor parametre isimlerini aynı yapmak her ne kadar hatalı olmasa da kötü bir kullanımdır.
```cpp
class MyClass
{
public:
    MyClass(int a, int b) : a(a), b(b) {};

    void print() const
    {
        cout << "a = " << a << "\nb = " << b << "\n";
    }

private:
    int a;
    int b;
};

int main()
{
    MyClass m1(3, 5);
    m1.print();
}
```

- Yukarıdaki kod yerine non-static veri elemanlarına `mx_,my_` gibi isimlendirmeler vermek çok daha okunabilir bir kod oluşumu sağlar.

```cpp
class MyClass
{
public:
    MyClass(int a, int b) : ma_(a), mb_(b) {};

    void print() const
    {
        cout << "ma_ = " << ma_ << "\nmb_ = " << mb_ << "\n";
    }

private:
    int ma_;
    int mb_;
};

int main()
{
    MyClass m1(3, 5);
    m1.print();
}
```


## Default Member Initializer

- Eğer sınıf içerisinde bir non-static veri üyesine atama operatörü ile değer verilmişse bunun anlamı şudur:
	- EĞER CONSTRUCTOR INIT LIST ILE INITIALIZE YAPILMAZSA BU DEĞER ILE INIT ET!
```cpp
class MyClass
{
public:
    MyClass(int a, int b) :  mb_(b) {};

    void print() const
    {
        cout << "ma_ = " << ma_ << "\nmb_ = " << mb_ << "\n";
    }

private:
	/*Default Member Initializer*/
    int ma_ = 31; /*ma_ degiskeni 31 degeri ile hayatina baslar */ 
     
    int mb_;
};

int main()
{
    MyClass m1(3, 5);
    m1.print();
}
/*
out:
ma_ = 31
mb_ = 5
*/
```

- Eğer ctor init list ile init edilirse ctor init list değeri ile hayatına başlar.

```cpp
class MyClass
{
public:
    MyClass(int a, int b) : ma_(a), mb_(b) {};

    void print() const
    {
        cout << "ma_ = " << ma_ << "\nmb_ = " << mb_ << "\n";
    }

private:
    int ma_ = 31;
    int mb_;
};

int main()
{
    MyClass m1(3, 5);
    m1.print();
}

/*
out:
ma_ = 3
mb_ = 5
*/
```


>[!IMPORTANT]
>Special Member Functions listesinde bulunan fonksiyonlara `= default;` anahtar sözcüğü ile atama yapıldığından derleyiciye **"Bu fonksiyonun kodunu default olarak sen yaz"** demiş oluruz.
>- `default` anahtar sözcüğü ilerde çok daha detaylı işlenecektir.

```cpp
class Counter
{
public:
    Counter(int x = 0) : cnt_{x} {}

    ~Counter() = default;
private:
    int cnt_;
};

int main()
{
    Counter cnt;
}
```


## RAII (Resource Acquisition is Initialization)
### Destructor neden var?

- Çoğu zaman dtor fonksiyonu içeriği boştur fakat bazı durumlarda bu fonksiyonun içeriğini doldurmamız gerekmektedir.


- C++ dilinde yüzlerce idiom vardır. Bu idiomların başında gelen ise **RAII** idiomudur.
	- RAII (Resource Acquisition is Initialization) kaynak edinimi initialization yoluyla olur anlamına gelmektedir.
		- C++ dilinde bazı sınıfların kullanımı için kaynak kullanımı gerekmektedir. Bu kaynakların kullanım sonrası geri verilmesi gerekmektedir.
			- Bu kaynaklar sadece memory olarak düşünülmemelidir: dosya açılımı, memory allocate edilmesi gibi gibi birçok resource olabilmektedir.
- Sınıf nesnelerinin hayatı bittiğinde *destructor* çağırılmaktadır ve bu kaynak geri verme işlemi destructor ile gerçekleştirilebilmektedir.

- Tipik bir **RAII** örneği:
```cpp
class Logger
{
public:
    Logger(const char* fname) : f_{std::fopen(fname,"w")} {
        // some codes..
    }

    ~Logger(){
        if(f_){
            std::fclose(f_);
        }
    }
private:
    FILE* f_;
};

int main()
{
    Logger lg("yavuz.txt");
}
```

- Yukarıdaki örnekte ilgili kaynağı destructor geri verir.  



## Special Member Functions

- Derleyici tarafından yazılabilme özelliğine sahip fonksiyonlardır.

1. default ctor
2. dtor
3. copy ctor
4. move ctor
5. copy assignment
6. move assignment

- `default` bildirimi yalnızca sınıfın bu fonksiyonları için yapılabilir.

```cpp
class MyClass
{
public:
    MyClass();                              /*default ctor*/
    ~MyClass();                             /*dtor*/
    
    MyClass(const MyClass&);                /*copy ctor*/
    MyClass(MyClass&&);                     /*Move ctor*/
    
    MyClass& operator=(const MyClass&);     /*copy assignment*/
    MyClass& operator=(MyClass&&);          /*move assignment*/
    private:
};
```
- Son 2 fonksiyonda Operator overloading kullanılır. Bu konu ilerde detaylıca anlatılacaktır.

- **copy ctor** fonksiyonu ile **move ctor** fonksiyonu function overloading ile 2 ayrı overload'dur. 
	- L Value argümanlar için *copy ctor*; R Value argümanlar için *move ctor* çağırılır.


###  Copy Ctor
- Bir sınıf nesnesinin aynı türden başka bir sınıf nesnesi ile kopyalanarak hayata getirilmesi durumunda hayata gelen nesne için sınıfın copy ctor fonksiyonu çağırılacaktır.

```cpp
int main()
{
    MyClass m1;         /*default ctor çağırılır*/
    MyClass m2 = m1;    /*copy ctor çağırılır*/
    MyClass m3(m1);     /*copy ctor çağırılır*/
    MyClass m4{m1};     /*copy ctor çağırılır*/
    auto m5 = m1;       /*copy ctor çağırılır*/
    auto m5(m1);        /*copy ctor çağırılır*/
    auto m5{m1};        /*copy ctor çağırılır*/
}
```

- Sınıf içerisinde copy ctor fonksiyonunun bildirimi olmasa bile bu fonksiyon derleyici tarafından implicitly declared olarak bildirilir.
>[!NOTE]
>**Bir Sınıfın copy ctor'ı bildirilmiş olmak zorundadır.**

- Special Member Functions aşağıdaki durumlardan birine ait olmak zorundadır:
	1. not-declared(special member function yok)
	2. User-declared
		1. `MyClass();`
		2. `MyClass() = delete;`
		3. `MyClass() = default;`
	3. Implicitly-declared
		1. Defaulted
		2. Deleted

>[!INFO]
>Derleyicinin implicitly declaration'ı nasıl yapacağı dilin kuralları çerçevesinde bellidir.

Örneğin:
- Default ctor declare edilirken eğer sınıfta bir veya birden fazla non-static const member var ise default ctor delete bildirimi ile bildirilir.
- Sebebi ise derleyici implicitly-declared defaulted şekilde default ctor bildirimi yaparken tüm elemanların **default initialize** edileceğini varsayar. Eğer edilemiyorsa fonksiyonu delete bildirimi ile delete eder.

```cpp
class MyClass{
public:

private:
	const int x;

};
```

- Burada derleyici örtülü olarak `MyClass() = delete;` bildirimi yapar ve main içerisinde `MyClass m1;` ifadesi hatalıdır çünkü default ctor delete edilmiştir.

- Başka bir örnek olarak aşağıdaki ifadede Nec sınıfının default ctor'u yine çağırılamaz çünkü *private* olduğundan erişim kontrolüne takılır. Bu yüzden `MyClass` sınıfının default ctor fonksiyonu deleted durumdadır.
```cpp
class Nec{
    Nec();
};

class MyClass{
    Nec mynec;
};

```


>[!WARNING]
>Derleyici sınıfın içinde declaration yaparken `default` bildirimi yapmayıp fonksiyonun tanımının olduğu dosyada sonradan tekrar `MyClass:MyClass() = default` gibi bir bildirimle default özelliğini ekleyebilirken; `delete` işlevi için aynı durum söz konusu DEĞİLDİR!

