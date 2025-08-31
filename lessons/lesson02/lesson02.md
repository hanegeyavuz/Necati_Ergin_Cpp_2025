
---

### Logic Türler Cont'd

- C++ dilinde *bool* türü increment veya decrement edilemez.
- Aritmetik dillerden bool türüne örtülü dönüşüm C++ dilinde de mevcuttur.
	- non-zero -> true
	- zero -> false
	
>[!WARNING]
>C++ dilinde pointer türlerinden bool türüne örtülü dönüşüm vardır.
>- Pointer NULL Pointer ise zero, NULL Pointer değilse true'ya dönüşür

### Tür Dönüşümleri Farklılıkları

Aşağıdaki dönüşümler C++'da tamamen yanlıştır ve hata ile sonuçlanır.
- farklı adres türleri arasındaki 
- adres türleri ile tam sayı türleri arasındaki 

- C++ dilinde string literals türü **const char[]** olmaktadır.
- Array decay dolayısıyla da **const char* türüne** dönüşmektedir.

```c++
int main(void){
	char* str1 = "yavuz"; //ERROR!
	const char* str2 = "yavuz" //LEGAL
}
```


### `const` Farklılıkları

- C ve C++ dilleri arasında öncelikle constant expression kısmında ciddi değişiklikler vardır.
	- Constant Expression: Derleyicinin bulunduğu yerde kesinlikle sabit bir ifadeye ihtiyaç duyduğu ifadelerdir.

- C++ dilinde statik ömürlü değişkenlere verilen ilk değerin cons. exp. olma zorunluluğu yoktur.
```c++
int x = 20; 
int y = x + 3; //LEGAL
int z = foo(x + y); //LEGAL
```

- C++ dilinde ilk değerini `const` olarak almış değişkenler const. exp. gerekli olduğu yerlerde kullanılabilmektedir.

```c++
int main(){
	const int x = 5;
	int ar[x]; /* LEGAL */

}
```

- C++ dilinde const global değişkenler **internal linkage**'a sahiptir!!

>[!ERROR]
>Hem C hem C++ programlama dillerinde `const T*` türünden `T*` türüne dönüşümler illegaldir.

- **Her iki dilde de `*T` türünden `void*` türüne dönüşüm legaldir.**
- **C++** dilinde `void*` türünden `*T` türüne dönüşüm **İLLEGALDİR**.
	- C dilinde legaldir.

### User Defined Types Farklılıkları

- C dilinde user defined types kullanılırken tag ile obje tanımlaması yapılamaz.
- Fakat C++ dilinde tag ile tanımlama yapılabilir.

```c
struct Point{
	double x,y;
};

int main(){

	Point mypoint = {2.,6.}; //ILLEGAL in C Programming, LEGAL in C++
}

```


>[!NOTE]
>C++ dilinde `typedef` hala bulunsa da modern C++ kullanılırken genel kullanım daha çok `using` keyword'ünü kullanmaktır.


- C++'da elemanı olmayan yapı kullanımı yaygındır.

- C++ da iki adet Enum yapısı vardır.
	- Scoped Enums(C++11)
	- Unscoped Enums
- C programlama dilinde Enum elemanlarının türü `int` olurken; C++ dilinde enumaratörlerin türü `compatible int` olmalıdır.
- C++ dilinde underlying type ifadesi vardır. Enums için de kullanılabilmektedir.
```C++
enum Color : unsigned char {White,Yellow,Red,Bronw};
```

>[!ERROR]
>C dilinde:
>- Farklı enum türleri arasında
>- enum türleri ile aritmetik türler arasında
>	- Örtülü dönüşüm vardır
>	
>C++ Dilinde:
>- İki durum da scoped enums için illegaldir.


- C++ dilinde unscoped enums -> aritmetik türler örtülü dönüşümü legaldir.
	- Bu kullanılmaması gereken bir özelliktir. Keşke geçerli olmasaymış.

```c++

enum Color {White, Yellow, Brown, Red}; 

int main(){
	Color mycolor = Yellow;
	int x = mycolor;

}

```


### Char Dizi Atamaları
- C dilinde char dizilerin boyutu kadar dizilere atama yapılabilir fakat sonunda null terminated character bulunmaz. 
```c
char str[6] = "hanege"; //LEGAL in C but no Null term. chr.
```


- C++ dilinde ise bu durum doğrudan sentaks hatasıdır.

```c++
char str[6] = "hanege"; //ILLEGAL in C++
```

### `for` döngüleri

- C dilinde for döngü parantezi içinde değişken tanımlanınca bu değişkenin scope'u gizli bir blok varmış gibi değerlendirilirdi. 
```c
for(int i = 0; i < 10; ++i){
	{
	} // i değişkeninin scope'unun bittiği yer
}

```

- C++ da ise bu durum böyle değildir. Döngü içerisinde `i` adında bir değişken tanımlanırsa bu sentaks hatası olacaktır.

### `auto` Keyword

- C dilinde bir değişkenin ömrünün otomatik ömür olmasına yarayan ve C dilinin ilk zamanlarından gelen bir özelliktir.
- Modern C++ dilinden önce C++ daki anlamı da C dilindeki gibiydi.
- Modern C++ dilinde `auto` keyword'üne çeşitli anlamlar yüklenmiştir ve dilin temel anahtar sözcüklerinden biri haline gelmiştir.
	- C++ dilinde C dilinden farklı olarak anahtar sözcüklerin birden fazla anlamı olabilir.(C dilinde yalnızca `static` sözcüğünde bu durum vardır.)
- Modern C++ dilinde `auto` anahtar sözcüğü **tür çıkarımı** işlevi için kullanılabilir.



### C99 Özellikleri
- C diline C99 standardıyla bir çok özellik eklenmiştir. Bu özelliklerin bir çoğu C++ da geçerli değildir.
	- Compound Literals
	- VLA
	-  restrict 
	- Flexible Array Member
- Bazı derleyiciler *compiler extention* olarak bazı özellikleri verebilirler.
- C++ dilinde `register` anahtar sözcüğü dilde ilerleyen zamanlarda farklı bir anlam yüklenmesi üzerine yedekte tutulmaktadır. Atıl durumdadır.


