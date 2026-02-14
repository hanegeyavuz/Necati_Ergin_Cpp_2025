
---

## Delegating Ctor

- C++11 standardı sonrası bir sınıfın birden fazla ctor fonksiyonunun kod tekrarına düşmemesi için gelen bir özelliktir.

```cpp
/*delegating ctor*/
class Myclass
{
public:
    Myclass(int x) : Myclass(x,x,x){} /*delegating ctor*/
    Myclass(int x,int y): Myclass(0,y,x){}/*delegating ctor*/
    Myclass(int,int,int);
    Myclass(const char* p) : Myclass(std::atoi(p)){}/*delegating ctor*/
private:
    void init();
};
```

>[!ERROR]
>Bir ctor initializer ctor list ile delegating yapıyorsa artık başka bir elemanı init edemez!

---
# Static Data Members and Member Functions

- Statik veri elemanlarının bildirimi sınıf içerisinde yapılmak zorundadır
	- Tanımda `static` anahtar sözcüğü kullanılmaz, bildirimde kullanılır.
```cpp
//myclass.h
class Myclass{
	static int x;

};

//myclass.cpp

int Myclass::x;

```

- Sınıfın statik veri elemanları sınıf nesnesi içerisinde değildir.
```cpp
class Myclass{
public:

private:
    int mx{};
    static int x;
    static int y;
    static int z;
};

int main(int argc, char const *argv[])
{
    Myclass m;
    std::cout << "size of class = " << sizeof(m) << "\n";
}

/*
out:
size of class = 4
*/
```

- Sınıfların statik veri elemanları global değişkenlere çoğu zaman bir alternatiftir.
	- İkisi de statik ömürlüdür.
	- Static Data Members scope'u class scope olur.
```cpp
class Myclass{
	static int s;
};

int g{};

int main(){
	g = 5; /*LEGAL*/
	g = s; /* ILLEGAL! s in the class scope! */
	g = Myclass::s; /*LEGAL*/
}

```



```cpp
/*static data members*/
class Myclass
{
public:
    static int z;

private:
};

int Myclass::z{};

int main(int argc, char const *argv[])
{
    Myclass m1, m2, m3;
    m1.z = 5;

    std::cout << "\nm1.z = " << m1.z << " m2.z = " << m2.z << " m3.z = " << m3.z << "\n";
}

/*
out:
m1.z = 5 m2.z = 5 m3.z = 5

*/
```

- Nesneye değil sınıfa aittir.
- Yukarıdaki örnekteki sınıf nesneleri sadece name-lookup içindir. Hiçbir nesneye ait `z` değişkeni bulunmaz.
 - const ve non-const üye fonksiyonlar sınıfın non-static veri elemanını set edebilir.

```cpp
class Myclass
{
    static int z;
    
    void foo()const{
	    ms = 68; /*VALID CODE!*/
    }
};
```

>[!ERROR]
>Ctor Initializer List ile static data members init edilemez!!

>[!TIP]
> C++99 dan beri sınıfın statik veri elemanlarına sınıf içerisinde değer verebilmek için 2 şart vardır:
> - `const` olmalı
> - integral type(tam sayı türü) olmalı

```cpp
class Myclass{
	constexpr static double x = 1.6;
};
```

>[!NOTE]
>C++17 sonrası `inline` anahtar sözcüğü header file içerisinde değişken tanımına izin verebilmektedir. Aynı zamanda sınıfların statik veri elemanları için de const olmamasına rağmen bu durum geçerli olmuştur.

```cpp
/*static data members*/
class Myclass
{
public:
    inline static int z = 5;

private:
};

int main(int argc, char const *argv[])
{
    Myclass m1, m2, m3;
    std::cout << "\nm1.z = " << m1.z << " m2.z = " << m2.z << " m3.z = " << m3.z << "\n";
}

/*
out:
m1.z = 5 m2.z = 5 m3.z = 5
*/
```

>[!WARNING]
>Sınıfın statik üye fonksiyonlarının gizli parametresi yoktur. (this pointer)

```cpp
Myclass::foo(); /*LEGAL*/
```

- Class scope'da bulunurlar.
- erişim kontrolüne tabidir.

```cpp
class Nec{
public:
	static int foo()const{ /*ILLEGAL*/
	}

};
```

- non-static veri elemanlarına atama geçersizdir.

```cpp
class Nec{
public:
	static int foo(){ 
		mx = 5; /*ILLEGAL*/
		my = 5; /*LEGAL*/
	}
	int mx;
	static int my;
};
```

- Statik Üye fonksiyonları sınıfın private üyelerine erişebilir.
	- Bu durum global functions için geçerli değildir.
```cpp
/*static data members*/
class Myclass
{
public:
    
private:
    int mx;
    int foo();
    static void func();
private:
};

void Myclass::func(){
    Myclass m;

    m.foo();
    m.mx = 30;
}
```

>[!NOTE]
>1. Ctor/dtor static üye fonksiyon olamaz
>2. Operator fonksiyonları statik  üye fonksiyon olamaz
>3. Sanal fonksiyonlar static olamaz

