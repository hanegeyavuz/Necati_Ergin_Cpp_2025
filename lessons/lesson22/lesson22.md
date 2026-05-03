

---

### Tipik Bir Operator Overloading Mülakat Sorusu

```cpp
class MyClass{
public:
    MyClass(int x) : mx{x}{};
    operator bool()const{
        return mx;
    }
private:
    int mx{};
};

int main(int argc, char const *argv[])
{
    MyClass m1(13), m2{37};

    auto val = m1 + m2;

}

```
Kod legal midir?
- Evet legaldir. Tür değiştirme operatör overloading sayesinde m1 ve m2 bool tipine dönüşür.


---

### Reference Qualification

- Eğer bir fonksiyonu R value değerler için ayrı, L value değerler için ayrı bir şekilde çağırmak için overload etmek isterseniz kullanılabilecek bir yöntemdir.

- Bir fonksiyonun bildiriminde parantezden sonra `&` deklaratörü gelirse bu fonksiyon yalnızca L value olan sınıf nesneleri için çağırılabilir.
```cpp
/*Reference Qualification*/
class MyClass{
public:
    void foo()&{cout << "L Value non-const objects foo()&" << "\n";};
    void foo()const&{cout << "L Value const objects foo()&" << "\n";};
    void foo()&&{cout << "R Value non-const objects foo()&&" << "\n";};
};

int main(int argc, char const *argv[])
{
    MyClass m1;
    const MyClass m2;

    m1.foo(); /*LEGAL*/
    MyClass{}.foo(); /*LEGAL*/
    m2.foo(); /*LEGAL*/
}
```


---
## Namespace(s)

- İsimlerin birbirleri ile karışmasını engelleyen, birbirinden ayırt edilebilmesini sağlayan bir araçtır.

### Syntax
```cpp
namespace neco{
    
}
```

- Bizim namespace oluşturmadan oluşturduğumuz isimler de aslında global namespace içerisinde bulunmaktadır.
```cpp
int x; /*global namespace*/
namespace neco
{
    int x;
}
namespace yavuz
{
    int x;
}
namespace hande
{
    int x;
}
```

- Bu durumda ODR çiğnenmemiş olur.
- Eğer böyle bir özellik olmasaydı farklı kütüphanelerde bulunan aynı isimler çakışacaktı.


>[!ERROR]
>Bir fonksiyon içerisinde *namespace* oluşturulamaz.

- Nested namespace legaldir.
- Erişim kontrolü bulunmamaktadır.

```cpp
/*namespaces*/
int x = 32;
namespace neco
{
    int x = 7;
}

int main(int argc, char const *argv[])
{
    cout << "x = " << x << "\n";
    cout << "neco::x = " << neco::x << "\n";
}
```

```cpp
/*namespaces*/
int x = 32;
namespace neco
{
    int x = 7;

    namespace yavuz{
        int x = 11;
    }
}

int main(int argc, char const *argv[])
{
    cout << "x = " << x << "\n";
    cout << "neco::x = " << neco::x << "\n";
    cout << "neco::yavuz::x = " << neco::yavuz::x << "\n";
}
```

>[!IMPORTANT]
>Derleyici bir namespace bildiriminden sonra aynı isimli bir namespace ile karşılaşırsa bunu aynı namespace olarak sayar. 
>- Bu bildirimler adeta kümülatif hale gelir.

 
- **Bir isim bir namespace içerisinde olmasına karşın nitelenmeden kullanılıp yine o namespace içinde bulunmuşsa aşağıdaki 3 araçtan biri vasıtasıyla bu durum sağlanmıştır.**
	- **`using` declaration**
	- **`using` directive**
	- **ADL**

### Using Declaration
- `using` anahtar sözcüğünden sonra bir namespace ismi gelir ve sonrasında scope resolution operatörü ile o namespace içindeki bir isim yazılarak oluşturulur.
```cpp
#include <iostream>
using std::cout;
```

- Modern C++ öncesinde `using` bildirimleri comma-seperated list ile yapılamazken Modern C++'da legaldir.
