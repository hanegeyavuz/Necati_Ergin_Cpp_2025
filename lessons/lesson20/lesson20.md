---
tags:
  - cpp
  - operator_overloading
---
## Operator Overloading Cont'd

### Thin Wrapper Class of `int` Type 

#### Insertion
```cpp
/*Mint.h file*/
/*thin wrapper*/

class Mint
{
public:
    Mint() = default;

    explicit Mint(int val) : mval{val} {};

    friend std::ostream &operator<<(std::ostream &os, const Mint &m)
    {
        return os << "[" << m.mval << "]";
    }

private:
    int mval{};
};

```

>[!NOTE]
>Operator overloading mekanizmasını kullanırken global veya member function olarak kullanmak önemlidir. Buradaki fark kodun yapısını değiştirebilir


```cpp
class Ostream
{
public:
    Ostream& operator<<(int);
    Ostream& operator<<(unsigned int);
    Ostream& operator<<(long);
    Ostream& operator<<(void*);

};

Ostream& operator<<(Ostream& os, const char*);
```


- Yukarıda `Ostream` sınıfının basic bir implementasyon yapısı gösterilmiştir. Eğer member function olarak farklı bir parametre girilirse sonuç değişecektir.

```cpp
    cout.operator<<('A'); /*member*/
    operator<<(cout,'A'); /*global*/
    
/*
out:
65A
*/
```

>[!WARNING]
>`endl` bir fonksiyonun ismidir.(ostream manipulator)
>- **Sadece stream e new line vermekle kalmaz, strem i flush eder!!**
>- Sadece new line vermek için kullanılmamalıdır.

1.02.00

#### Extraction
```cpp
    /*extractor*/
    friend std::istream &operator>>(std::istream &is, Mint &m)
    {
        return is >> m.mval;
    }
```

#### Sum
```cpp
    Mint &operator+=(const Mint &other)
    {

        mval += other.mval;
        return *this;
    }
    friend Mint operator+(const Mint m1, const Mint m2)
    {
        return Mint(m1) += m2;
    }
```

### Sub
```cpp
    Mint &operator-=(const Mint &other)
    {

        mval -= other.mval;
        return *this;
    }
    friend Mint operator-(const Mint m1, const Mint m2)
    {
        return Mint(m1) -= m2;
    }
```

### Comparison Operators Overloading

```cpp
    /*comparision operators*/
    friend bool operator<(const Mint lhs, const Mint rhs){
        return lhs.mval-rhs.mval < 0 ? true : false;
    }
    friend bool operator>(const Mint lhs, const Mint rhs){
        return rhs < lhs ;
    }
    friend bool operator<=(const Mint lhs, const Mint rhs){
        return !(rhs < lhs);
    }
    friend bool operator>=(const Mint lhs, const Mint rhs){
        return !(lhs < rhs);
    }
    friend bool operator==(const Mint lhs, const Mint rhs){
        return (lhs.mval == rhs.mval);
    }
    friend bool operator!=(const Mint lhs, const Mint rhs){
        return !(lhs == rhs);
    }

```

>[!NOTE]
>C++20 standardı ile dile `<=>` spaceship operatörü eklenmiştir. Bu operatöre `default` bildirimi yapılabilmektedir. Bu bildirim sonrasında herhangi bir karşılaştırma operatörünün implementasyonuna ihtiyaç yoktur.
>- `auto operator<=>(const Mint&)const = default`

### Pre-Fix and Pos-Fix Increment-Decrement Operators

>[!HINT]
>Bu operatörlerin implementasyonunda prefix ve posfix fonksiyonlarının aynı olmasından dolayı pos-fix fonksiyonlara dummy parametre atanır.

```cpp
    Mint& operator++(){
        ++mval;
        return *this;
    }
    Mint operator++(int){
        Mint temp{*this};
        ++mval;
        return temp;
    }
```

---