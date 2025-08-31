## C Dilinde de Bulunan Önemli Terimler

### Undefined Behavior

- Eğer bir kod UB olarak nitelendirilmişse derleyicinin üreteceği kodun nasıl çalışacağı bilinemez.
	- **DOĞRU BİR KOD DEĞİLDİR.**
- Bazı dillerde yokken C/C++ dillerinde olmasının sebebi derleyicinin daha hızlı, daha iyi ve daha verimli kod üretebilmesi için bazı kontrolleri yapmaması ve bunu yazılımcıya bırakmasıdır.

### Unspecified Behavior
- C/C++ standardı bazı durumlar için derleyicilere farklı kod üretebilme şansı tanır.
	- Çoğu zaman 2 şans, bazen 3 şans.
- Her zaman kodun yanlış olduğu anlamına gelmez.
```c++
int g();
int f();

int main(){
	int x;
	
	// some code here
	
	x = f() + 5 * g();

}
```
- Yukarıdaki kodda f ve g fonksiyonlarından hangisinin önce çağırılacağı *Unspecified Behavior*'dur.
- Bu durumda kodumuzu hangi fonksiyonun daha önce çağırılacağına göre yazarsak yanlış çıktı alabiliriz.

```c++
/*Unspecified Behavior*/
int main(){
    
    const char* p1 = "yavuz hanege";
    const char* p2 = "yavuz hanege";

    if(p1 == p2){
        printf("evet dogru\n");
    }
    else{
        printf("hayir yanlis\n");
    }
}
```
- Yukarıdaki kodun çıktısının ne olacağı değişebilir. Unspecified behavior.

### Implementation-Defined Behavior
- Unspecified Behavior ile arasındaki fark, Implementation Defined Behavior'ın **derleyici tarafından dokümante edilmek zorunda olmasıdır.**
- Derleyicinin bazı durumlarda nasıl bir kod üreteceği derleyiciye bağlıdır. Fakat bu davranışın nasıl gerçekleştirileceğine yazılımcı tarafından ulaşılabilir.

---
## C++ Dilinde Name Lookup

- İsim aramada bir isim eğer bulunamamışsa o kod geçersizdir.
- Bir ismin aranması ama bulunamaması hataya sebep olur
- Ambiguity (bir ismin birden fazla yerde olması) name lookup hatasına neden olabilir.
- Genellikle bir sıraya göre işler.

>[!IMPORTANT]
>C'de karakter sabitlerinin türü `int` iken; C++ dilinde karaker sabitleri `char` türüne sahiplerdir.


---

## Value Category Introduction

- C dilinde her ifade R Value ve L Value kategorisinde olmak zorundaydı.
- C++ dilinde ise her ifadenin **primary value category** olmak zorundadır.
	- Lvalue
	- PRvalue
	- Xvalue

>[!IMPORTANT]
>Her ifadenin bir "data type"ı ve bir "value category"si vardır.

- **Combined Value Category** isimli bir kategori daha vardır.
	- GLvalue    -> LValue ya da XValue
	- RValue     -> PRvalue ya da Xvalue

- Bunlar kursun ilerleyen zamanlarında daha detaylı anlatılacaktır.

