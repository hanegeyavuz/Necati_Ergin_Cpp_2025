#include <iostream>
#include <cstdio>

#if 0
int foo(){
}
int main(int argc, char const *argv[])
{
    const int x1 = 5;
    const int x2 = foo();

    int ar1[x1]{};
    int ar2[x2]{}; /* Syntax Error*/
}

#endif
#if 0
int foo(){
}
int main(int argc, char const *argv[])
{
    const int x1 = 5;
    const int x2 = foo();

    constexpr int x1 = 5;
    // constexpr int x2 = foo(); /*SYNTAX ERROR*/    

}

#endif
#if 0

constexpr int square(int x){
	return x*x;
}

int main(){
	int a = 5;
	const int b = 5;
	constexpr int i = square(a); /*ERROR*/
	constexpr int i = square(b);  /*LEGAL*/
}
#endif
#if 0
constexpr bool isprime_s(int x){
	if(x < 2) return false;
	if(!(x % 2)) return x == 2;
	if(!(x % 3)) return x == 3;
	if(!(x % 5)) return x == 5;
    for(int i = 7; i * i <= x; i += 2){
        if(!(x % i)){
            return false;
        }
    }
    return true;
}

int main(){

    constexpr bool i_p = isprime_s(32); /* compile time */
}
#endif

#if 0

constexpr int sbc(int x){ /*counter of set bits*/
    int cnt = 0;

    while(x){
        x &= x-1;
        cnt++;
    }
    return cnt;
}

int main(int argc, char const *argv[])
{
    constexpr auto ss = sbc(255);
}

#endif

#if 0
/*örtülü tür dönüşümü*/
enum Color{White,Yellow,Red,Brown,Blue,Black};

int main(int argc, char const *argv[])
{
    Color c = Yellow;
    int x;

    x = c;

}

#endif
#if 0
// enum Color_1{White,Yellow,Red,Brown,Blue,Black};
// enum Color_2{White,Yellow,Red,Brown,Blue,Black};

enum class Color_1 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/
enum class Color_2 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/

int main(int argc, char const *argv[])
{
    auto c = Color_1::Yellow;
    
    int x;
    // x = c; ILLEGAL

}

#endif
#if 0

enum class Color_1 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/
enum class Color_2 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/

int main(int argc, char const *argv[])
{
    auto c = Color_1::Blue;
    
    int x;
    // x = c; ILLEGAL
    x = static_cast<int>(c);
    std::cout << "x = " << x << std::endl;

}

#endif
#if 0

enum class Color_1 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/
enum class Color_2 {White,Yellow,Red,Brown,Blue,Black}; /*Scoped Enums*/

int main(int argc, char const *argv[])
{
    using enum Color_1; /* CPP20 STANDARD */
     auto c = Blue;
    
    int x;
    // x = c; ILLEGAL
    x = static_cast<int>(c);
    std::cout << "x = " << x << std::endl;

}

#endif
#if 0
/*decltype*/
int main(int argc, char const *argv[])
{
     int x = 5;
     decltype(x) y = 5; /* int y = 5; */
     int* ptr = &x;
     decltype(x + 5) i_a; /*int i_a;*/
     decltype(*ptr) a = x; /*int& a = x;*/

     int ar[10]{};

     decltype(ar[47]) m = ar[3]; /*int& m = ar[3];*/


}

#endif
#if 1
/*decltype*/
int main(int argc, char const *argv[])
{
     int x = 5;
     int a{};
     decltype(++x) y = a; /* int& y = a; */

    std::cout << "x = " << x << std::endl;

}

#endif