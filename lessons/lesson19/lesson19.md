
---
## `friend` Declarations

- Bazı kodların ilgili sınıfın private bölümüne erişimini sağlaması için kullanılan bir bildirimdir.
- Genellikle sınıfın kendi kodlarında kullanılmaktır.
	- Global functions
	- Yardımcı sınıflar vs..
- Kullanım alanları:
	- Bir global fonksiyon için
	- Bir başka sınıfın member function için
	- Bir sınıfın tüm kodları için

```cpp
class myclass{
public:
    friend void gfunc(myclass);

private:
    void foo();
    int x_{};

};


void gfunc(myclass x){
    x.foo(); /*LEGAL*/
    myclass m;
    m.x_ = 5; /*LEGAL*/
}

void sfunc(myclass x){
    x.foo(); /*ILLEGAL*/
    myclass m;
    m.x_ = 5; /*ILLEGAL*/
}
```

>[!NOTE]
>`friend` bildirimi sınıfın `private` kısmında yapılabilir ve herhangi bir fark olmaz. Bu durum açısından nadir örneklerden biridir.

 >[!ERROR]
 >Eğer `friend` declared fonksiyonun parametresi sınıf türünden bir parametre ise namespace içerisinde çağırılabilir fakat parametresi farklı bir türden ise çağrılması hataya sebep olur.
 >- Bu kuralın sebebi ilerde **namespaces** konusunda detaylı işlenecek olan **ADL** akronimidir.
 >	- Argument Dependent Lookup
 
 
 ```cpp
 /*friend decleration*/
class myclass{
public:
    friend void gfunc(myclass);
    friend void mfunc(int);

private:
    void foo();
    int x_{};

};


int main(int argc, char const *argv[])
{
    myclass m;
    
    mfunc(23); /*ILLEGAL*/

    gfunc(m); /*LEGAL*/
}
 ```


- Bir üye fonksiyona da friend özelliği verilebilir.

```cpp
#if 1
/*friend decleration*/

class Nec{
public:
    void bar(int);
private:
};

class myclass{
public:

    friend void Nec::bar(int);

private:

    void foo();
    int x_{};

};

void Nec::bar(int x){
    myclass m;
    m.x_ = x;
}

int main(int argc, char const *argv[])
{

}

#endif
```

>[!IMPORTANT]
>Yukarıdaki kodun geçerli olması için ilgili sınıfın(Nec sınıfı) tanımının derleyici tarafından görülmesi zorunludur.


- Bir sınıfın tamamına `friend` bildirimi yapılabilir

```cpp
/*friend decleration*/
class myclass
{
public:
    friend class Nec;

private:
    void foo() {}
    int x_{};
};

class Nec
{
    void f1()
    {
        myclass m;

        m.x_ = 22;

        m.foo();
    }

private:
public:
};

int main(int argc, char const *argv[])
{
}

```


>[!NOTE]
>Aşağıdaki durumlar geçersizdir:
>- Arkadaş sınıfın arkadaş sınıfı, ilk sınıfın private bölümüne erişemez.
>- Kalıtım kullanılırken `base` sınıfın private bölümüne `friend` declaration ile erişen sınıf, `child` sınıfının private bölümüne erişemez.

---
# Operator Overloading

### Nedir ve Ne işe Yarar?
- C dilinde sınıflara en yakın user defined types olan *struct* yapısı bulunmaktaydı.
	- Bu yapı yalnızca belirli başlı şeylerin operandı olabiliyordu.
		- Örneğin sizeof operatörü, atama operatörü vs..
- Fakat C++ dilinde **Operator Overloading** mekanizması sayesinde sınıf türleri normalde C dilinde *structs* için illegal olan operatörlerin operandı olabilmektedir.
	- Bu sayede bu derleyici bu yapıyı bir fonksiyon çağrısına dönüştürmektedir.
```cpp
int main(int argc, char const *argv[])
{
    using namespace std;

    string str{"yavuz"};

    str += "hanege"; /*operator overloading*/

    cout << " str = " << str << endl;
}
```

### Operator Overloading General Rules
1. Operator overloading kullanılabilmesi için operand olarak en az 1 adet sınıf veya enum türünden nesne gerekir.
2. Olmayan bir operatörün overload u da olmaz.
3. C++ dilinin tüm operatörleri bu mekanizmayı desteklemez.
	1. Scope Resolution Operator `::` 
	2. Member Selection Dot `.`
	3. `sizeof`
	4. Ternary Operator `? :`
	5. Member `.*` operator
	6. typeid
	7. alignof
	8. cast operators
4. Bir operatör fonksiyonu yalnızca 2 tip fonksiyon olabilir
	1. global function (global operator function)
	2. Non-Static member function (member operator function)
5. Bir sınıfın `static` üye fonksiyonu olamaz.
6. Bazı operatörler için yalnızca member operator function oluşturulabilir.
	1. Assignment Operator Function
	2. `[]` operator function
	3. `->` operator function
	4. `()` operator function
	5. type-cast operator functions
7. Operator functions keyfi bir şekilde isimlendirilemez.
	1. `operator` keyword sonrasında ilgili operatörün tokeni olmak zorundadır.
		1. `operator+`
		2. `operator<`
8. Tüm operator fonksiyonları isimleriyle birlikte de çağırılabilir.
```cpp
	   /*Operator Overloading*/
int main(int argc, char const *argv[])
{
    int x = 32;

    std::cout << x << std::endl;
    std::cout.operator <<(x);
}
```

```cpp
/*Operator Overloading*/
int main(int argc, char const *argv[])
{
    string s1{"yavuz"};
    string s2{"yavuz"};

    if (operator==(s1, s2))
    {
        cout << "esittir";
    }
    else
    {
        cout << "esit degildir";
    }
}

#endif

/*
out:
esittir
*/
```

9. Bu mekanizmada operatörlerin "arity"si değiştirilemez.
	1. Unary operatorler unary, binary operatorler binary olarak overload edilmek zorundadır.
10. Dilin tanımladığı operator önceliği değiştirilemez.
11. Operator fonksiyonları da overload edilebilir(function overloading)

```cpp
class MyClass{
public:
    MyClass operator+(const MyClass)const;
    MyClass operator+(int)const;
    MyClass operator+(double)const;
private:
    
};
```

12. Geri dönüş değeri türünün ne olduğu sınıfın türü ve operator türüne göre değişir.
	1. Karşılaştırma operatörlerinin geri dönüş değeri genellikle `bool` olur


>[!HINT]
>Simetrik binary operatörler genellikle global operator function olarak kullanılmalıdır.


