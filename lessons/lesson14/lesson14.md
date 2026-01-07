
## Special Member Functions Cont'd

- Eğer bir special member function'ı derleyici örtülü olarak oluşturuyorsa bu fonksiyon her zaman sınıfın non-static public inline fonksiyonudur.

### Copy Ctor Cont'd

>[!QUESTION]
>Sınıfın copy constructor'ı hangi durumlarda çağırılır?
>>[!ANSWER]
>>1. Bir sınıf nesnesini başka bir sınıf nesnesine assign edilerek **initialize** edilmesi
>>2. call by value fonksiyon çağrıları
>>3. geri dönüş değeri sınıf türünden olan bir fonksiyona ileride anlatılacak bazı optimizasyonlar yapılmadığı durumda fonksiyon çağrısı sonucunda copy ctor kullanılır.



>[!HINT]
>Kullanıcının kendi tanımlayacağı *copy ctor* fonksiyonu ile default implicitly olarak derleyicinin tanımlayacağı fonksiyon çoğu zaman aynı olacağından çok büyük çoğunlukla *copy ctor* tanımlamasını derleyiciye bırakmalıyız.

```cpp
/*copy ctor*/
class Date
{
public:
    Date() = default;
    Date(int d,int m,int y):md{d}, mm(m), my{y} {}
    ~Date(){};

    void print()const
    {
        std::cout << md << "-" << mm << "-" << my << "\n";
    }
private:
    int md{1}, mm{1}, my{1900};
};

int main(){

    Date d1;
    d1.print();
    Date d2(5,1,2026);
    d2.print();
    Date d3 = d2;
    d3.print();
}
```

- Yukarıdaki kodda da görüldüğü üzere copy ctor derleyici tarafından yazılmış haldedir.
```cpp
/*copy ctor*/
class Date
{
public:
    Date() = default;
    Date(int d,int m,int y):md{d}, mm(m), my{y} {}
    ~Date(){};
    Date(const Date& other): md(other.md),mm(other.mm),my(other.my) {
        /*user defined copy ctor*/
        std::cout << "copy ctor called!\n";
        std::cout << "this = " << this << "\n";
        std::cout << "other& = " << &other << "\n";

    } 

    void print()const
    {
        std::cout << md << "-" << mm << "-" << my << "\n";
    }
private:
    int md{1}, mm{1}, my{1900};
};

int main(){

    Date d1;
    d1.print();
    Date d2(5,1,2026);
    d2.print();
    Date d3 = d2;
    std::cout << "d3& = " << &d3 << "\n";
    std::cout << "d2& = " << &d2 << "\n";    
    d3.print();
}
/*
out:
1-1-1900
5-1-2026
copy ctor called!
this = 0x4bf63ff81c
other& = 0x4bf63ff828
d3& = 0x4bf63ff81c
d2& = 0x4bf63ff828
5-1-2026
*/
```

- Yukarıdaki kodda user-defined olarak copy ctor u biz tanımladık ve debug için ekrana this pointer'ını ve copy ctor'un aldığı parametrenin adresini bastırdık. 
	- Çıktıdan da anlaşılacağı üzere d3 için copy ctor çağırılır fakat argüman olarak d2 gönderilir.

>[!NOTE]
>Öyle sınıflar olacak ki bu sınıfların nesnelerinin kopyalanması istenmeyecek. Bu gibi sınıflarda copy ctor fonksiyonunu kullanıcı yazması gerekecektir.(non-copyable) 



```cpp
class MyClass{
public:
	MyClass(const MyClass&) = delete; /*non-copyable*/
private:
};
```



>[!QUESTION]
>Ne zaman copy ctor fonksiyonunu kullanıcı tanımlamalıdır?
>>[!ANSWER]
>>- Bazı sınıfların elemanlarından biri kaynak gösteren bir pointer veya referans nesnesi olur. Bu nesnelere **handler** denir. Bu nesneler bir varlığın adresini gösterir. Eğer biz bu gibi sınıfların nesnelerini default copy ctor ile kopyalarsak elde edeceğimiz yeni nesne ile eski nesne aynı varlığı gösterir ve bu da istenmeyen bir durumdur.


>[!EXAMPLE]
>Mesela string sınıfını düşünelim:
>- Sınıfın  non-static veri elemanlarından biri yazı gösteren bir pointer olduğundan eğer kopyalama yapılırsa diğer nesne de aynı yazıyı gösterecek ve biri değiştirildiğinde diğeri de değişmek zorunda kalacak. 
>	- Aynı zamanda bu durumda dtor çağırıldığında nesnelerden önce biri free edilip sonra diğeri free edileceğinden ilk kaynak geri verme sonrası ikinci free işlemi Undefined behavior olarak anlandırılır.



```cpp
class myString
{
public:
    myString() : mp_{nullptr}, mlen_{0} {}
    myString(const char *p);
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

void foo(myString str)
{
    std::cout << "foo function str = " << (str.get_str()) << "\n"; /*DANGLING POINTER!!! UB!!*/
}

myString::myString(const char *p) : mlen_{std::strlen(p) + 1}, mp_{static_cast<char *>(malloc(mlen_ * sizeof(char)))}
{
    std::strcpy(mp_, p);
}


int main()
{
    myString str1{"yavuz hanege"};
    myString str2 = str1;
    std::cout << "str1 = " << (str1.get_str()) << "\n";
    std::cout << "str2 = " << (str2.get_str()) << "\n";
    str1.make_upper();
    std::cout << "str1 = " << (str1.get_str()) << "\n";
    std::cout << "str2 = " << (str2.get_str()) << "\n";
}
/*
out:
str1 = yavuz hanege
str2 = yavuz hanege
str1 = YAVUZ HANEGE
str2 = YAVUZ HANEGE
*/
```

- Yukarıdaki kodda görüldüğü üzere str1 için `make_upper` fonksiyonu çağırılmasına rağmen str2 nesnesi de değişti. Çünkü aynı nesneyi gösteren sınıf objeleri bunlar.

>[!ERROR]
>Yukarıdaki kodda aynı zamanda önce s2 için destructor çağırılacak sonrasında s1 için dtor çağırılacak. İlk dtor çağrısı sonrası aynı nesne tekrar delete edilmeye çalışılacağından UNDEFINED BEHAVIOUR!!

Bu sorunu engellemek için copy ctor fonksiyonunu kendimiz implemente edersek:

```cpp
#include <cstring>
#include <cctype>
class myString
{
public:
    myString() : mp_{nullptr}, mlen_{0} {}
    myString(const char *p);
    myString(const myString& other) : mlen_{other.mlen_}, mp_{static_cast<char*>(std::malloc(mlen_ + 1))}
    { 
        
            std::strcpy(mp_,other.mp_);
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

void foo(myString str)
{
    std::cout << "foo function str = " << (str.get_str()) << "\n"; 
}



int main()
{
    myString str1{"yavuz hanege"};
    myString str2 = str1;
    std::cout << "str1 = " << (str1.get_str()) << "\n";
    std::cout << "str2 = " << (str2.get_str()) << "\n";
    str1.make_upper();
    std::cout << "str1 = " << (str1.get_str()) << "\n";
    std::cout << "str2 = " << (str2.get_str()) << "\n";
}
/*
out:
str1 = yavuz hanege
str2 = yavuz hanege
str1 = YAVUZ HANEGE
str2 = yavuz hanege
*/
```

- Bu şekilde kopyalamaya **deep copy** denmektedir. 
	- Derleyicinin default olarak yaptığı kopyalamaya ise **shallow copy** veya **member wise copy** denmektedir.

>[!NOTE]
>Bu durumlar kullanacağımız sınıfların %2 si gibi düşük bir miktarda geçerli olacak. Çünkü genellikle derleyicinin yazdığı copy ctor fonksiyonu bizim için yeterli olacaktır.
>- Çünkü genellikle sınıflarımızda kullanacağımız ve bir kaynak adresi tutan değişkenleri hazır kütüphaneler vasıtasıyla kullanacağız ve bu hazır kütüphanelerdeki sınıfların copy ctor fonksiyonları yazılması gerektiği gibi yazılmış olacak. 
> 	 - Örneğin `std::string`, `std::vector`



## Copy Assignment Function

- Atama operatörü `=` ile aynı sınıf türünden iki nesnenin atama yapılması ile bu fonksiyon çağırılır.

>[!NOTE]
>Burada bir initialization, hayata gelme durumu söz konusu değildir. Bu yüzden *copy ctor* fonksiyonu ile karıştırılmamalıdır.

```cpp
/*copy assignment*/
class MyClass{

public:
    MyClass& operator=(const MyClass& other);

private:

};

int main()
{
    MyClass m1,m2;

    m1 = m2; /*no initialization, copy assignment function call*/
    m1.operator=(m2); /*same function call*/
}
```

- Yukarıda görüldüğü üzere daha önceden hayata gelmiş nesneler birbirlerine assign edilirken *copy assignment* fonksiyonu çağırılır.

>[!NOTE]
>Tıpkı *copy ctor* gibi **yazdığımız sınıfların neredeyse %98'inde *copy assignment* fonksiyonunun implementasyonunu derleyiciye bırakacağız.**

- Derleyici tarafından yazılan *copy assignment* fonksiyonu:
```cpp
/*default implicitly declared copy assignment function*/
class MyClass{

public:
    MyClass(int a,int b,int c):ma_{a},mb_{b},mc_{c}{} 

    MyClass& operator=(const MyClass& other){
        ma_ = other.ma_;
        mb_ = other.mb_;
        mc_ = other.mc_;
        return *this;
    }
    void print_members()const{
        std::cout << "ma_ " << ma_ << " mb_ " << mb_ << " mc_ " << mc_ << "\n";
    }

private:
    int ma_,mb_,mc_;
};

int main()
{
    MyClass m1{1,2,3};
    MyClass m2{10,11,12};
    m1.print_members();
    m2.print_members();
    m1 = m2; /*no initialization, copy assignment function call*/
    m1.print_members();
    m2.print_members();
}
/*
out:
ma_ 1 mb_ 2 mc_ 3
ma_ 10 mb_ 11 mc_ 12
ma_ 10 mb_ 11 mc_ 12
ma_ 10 mb_ 11 mc_ 12
*/
```

>[!QUESTION]
>Ne zaman *copy assignment* fonksiyonunun kodunu biz yazmalıyız?
>>[!ANSWER]
>>*copy ctor* fonksiyonundaki gibi eğer bir sınıfın non-static veri elemanlarından biri pointer ise biz daha önceden hayata gelmiş 2 nesneyi birbirine assign etmeye çalışırsak pointer adress assignment yaptığımızdan dolayı assign edilen nesnenin bir önceki adresinin delete edilmesi mümkün olmayacaktır(resource leak). Bu durum da UNDEFINED BEHAVIOUR sonucunu doğurur.


- Bundan kurtulmak için yapılması gereken **deep copy** *copy assignment* fonksiyonu:
```cpp
MyClass& operator=(const MyClass& other){
	mlen = other.mlen;
	free(mp);
	mp = static_cast<char*>(std::malloc(mlen + 1));
	std::strcpy(mp,other.mp);
	
	return *this;
}
```

- *copy assignment* fonksiyonunun *copy constructor* fonksiyonundan farkı önce **free resources** yapıp sonrasında **deep copy** yapmasıdır.

>[!ERROR]
>Eğer bir nesne kendine atanırsa `s = s` gibi, yukarıda yazılan deep copy assignment fonksiyonu yine UB durumuna yol açar. Bu yüzden atama operatörünün sağ tarafındaki nesne ile sol tarafındaki nesnenin aynı olup olmadığı kontrolü yapılmalıdır.

```cpp
MyClass& operator=(const MyClass& other){
	if(&other != this){ /*self-assignment protection*/
		mlen = other.mlen;
		free(mp);
		mp = static_cast<char*>(std::malloc(mlen + 1));
		std::strcpy(mp,other.mp);
	}
	return *this;
}
```

>[!ATTENTION]
>Özellikle Modern C++ öncesinde **Big3** denilen bir kural vardı:
>- Bu kural bir sınıf için `destructor` fonksiyonunu kendimizin yazması gerektiği durumlarda  `copy ctor` ve `copy assignment` fonksiyonlarının implementasyonunu da yapmamız gerektiğini gösteriyordu. 
> 	 - Bu kuralın sebebi örneğin *dtor*'u kendimiz yazdıysak bir resource usage var demektir. Bu durumda *shallow copy* yerine *deep copy* yapmamız gerektiğinden diğer 2 fonksiyonu da kendimizin implemente etmemiz gerektiğiydi.
> 	 - **Bu kural çok çok büyük olasılıkla tüm durumlar için geçerlidir.**
>  - Bu terim genellikle kullanımdan düşmüştür.
> 	 - Çünkü Modern C++ öncesinde *move ctor* veya *move assignment* fonksiyonları yoktu.
>  - Artık bu terim yerine **Big5** terimi kullanılmaktadır.


---
## Introduction to Move Assignment and Move Constructor

- Öyle durumlar var ki biz bir sınıf nesnesini aynı sınıf türünden başka bir nesne ile hayata getirmek istiyoruz fakat kopyalanan/atanan nesnenin işlem sonrasında hayatının bitmesi gerektiğinden eminiz.
	- Bu durumlarda `copy ctor` veya `copy assignment` fonksiyonları ekstra maliyet getirmektedir. Bu durumlarda *move* fonksiyonları devreye girer.
- Modern C++ öncesi bu özelliklerin olmama sebebi dilin araçlarının yetersiz olmasıydı.
	- Modern C++ ile bu özellik için bir sürü farklı şey dile eklenmiştir.
		- R Value Category
			- R Value Category sahip nesneler kullanıldıktan sonra ömrü bitecek ifadelerdir.
- `move` fonksiyonları tabiri caizse kaynağı kopyalamaz **ÇALAR**.