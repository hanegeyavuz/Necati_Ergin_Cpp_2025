
---

## C++ Standartları

- C++23 standardı 2104 sayfa iken C23 standardı 758 sayfadır. 
	- Bu da C++ dilinin C diline göre ne kadar kapsamlı bir dil olduğunu göstermektedir.

## C++ Nasıl Bir Dildir
- İçerisinde C dilini barındıran bir dildir.
- C dili ile belirli noktalarda farklılıkları vardır.
- C++ çok paradigmalı bir programlama dilidir.
	- Paradigma: Programı yazarken kullanılacak metodoloji
		- OOP
		- Object Based Programming
		- Generic Programming
		- etc...

## C Programlama Dili ile C++ İçerisindeki C Arasındaki Farklılıklar

- Terminolojide çeşitli farklılıklar vardır. (diagnostic / no diagnostic req. etc...)

>[!NOTE]
>Farklı derleyiciler aynı kodu kullanarak aynı makine kodu çıktısı elde etmek zorunda değillerdir. Bunun sebebi C/C++ derleyicilerinin optimizasyon tabanlı olmasıdır.

- C99 standardı ile dile eklenen anahtar sözcükler vardır:
	- `_Alignas, _Alignof, _Atomic, _Noreturn, _Static_assert, _Thread_local`
	- Bu keyword'ler C++'da geçerli değildir.

### Old Style Function Definition

- C++ dilinde *old style function definition* hiçbir zaman geçerli değildir. C programlama dilinde ise 23 standardı ile kaldırılmıştır.

```c
int func(x,y) /* OLD STYLE FUNCTION DEFINITION */
double x,y;
{
}
```


### Implicit Int Rule

- Örtülü, gizli, kapalı int demektir.
- C Programlamanın kurallarında bazı yerlerde hiçbir tür yazılmadığı zaman **int** olarak kabul edilmesidir.
	- C99 ile dilden kaldırılmıştır.
	
```c
func(int)

foo(int a, int b){

	return a + b; //Geri donus degeri yazilmadigi icin int olarak değerlendirilir
}
```

- Implicit int kuralı hiçbir zaman C++'da geçerli olmamıştır.

### Implicit Function Declaration

- Eğer derleyici bir fonksiyon çağrısı gördüğünde o fonksiyonun declaration'ını bulamazsa aşağıdaki gibi bir declaration olduğunu varsayar.

```c
// int f(); /* warning C4013: 'f' undefined, assuming extern returning int '' */

int main(){
	
	f();
}

```


- Hiçbir zaman C++ dilinde geçerli olmamıştır.


### Empty Function Parameters

- C dilinde bir fonksiyonun parametresinin boş olması **fonksiyonun parametresi olmadığını anlamına GELMEZ.** Fonksiyonun parametreleri hakkında bilgi sahibi olunmadığı anlamına gelir.
- C++ dilinde ise **fonksiyonun parametresi olmadığı anlamına GELİR**
```C++

int foo();
//int foo(void); /* Same */

int main(void){
	
	int x;
	foo(x); /* ERROR too many arguments*/

}
```

- Aynı durum function pointer'lar için de geçerlidir.

```c++

int (*fp)();
int (*fp)(void);

/* Yukaridaki iki ifade C++ dilinde tamamen ayni anlamlara gelir. C dilinde ise farklı seylerdir!! */

```

### Logic Veri Türü

- C dilinde 99 standardı sonrasında `_Bool` veri türü dile eklenmiştir fakat yaygın kullanımı yotkur.
	- `stdbool.h` kütüphanesindeki makrolar sayesinde C dilinde `Bool flag = true;` gibi tanımlamalar yapılabilmektedir.
- C++ dilinde ise direkt olarak dilde **Bool** türü vardır. Bu türün kendine has özellikleri bulunmaktadır.

#### C++  Dilindeki Bool Türü

- Doğrudan bir keyword'dür.
- En az 1 byte olmak zorundadır fakat storage 1 byte olmak zorunda değildir.
	- Bu önemli bir farktır.
	- Karşılaştırma operatörleri C dilinde **int** türünden değer üretirken C++ dilinde Bool türünden değer üretirler. 


>[!QUESTION]
>Neden C ve C++ dilindeki bazı kurallar birbirinden farklıdır?

>[!ANS]
>- Bazı kurallar C diline, bazı kurallar C++ diline daha uygundur.
>- C dilinin loose type control bir dil olması
>- C++ dilinde derleme aşamasında tür kontrolü çok daha sıkı bir şekilde yapılır











































