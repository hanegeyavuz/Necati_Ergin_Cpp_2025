#include <iostream>

using namespace std;

#if 0

int& foo(int& r1){
    r1 = 99;

    return r1;
}

int main(int argc, char const *argv[])
{
    int x = 3311;

    int& r2 = foo(x);
    cout << "x = " << x << endl;
    cout << "r2 = " << r2 << endl;
}

#endif

#if 0
int main(int argc, char const *argv[])
{
    int x = 3311;
    const int& r1 = x;  /* const reference */
    //int& r2 = x;      /* non-const reference */
    r1 = 22; /* expression must be a modifiable lvalueC/C++(137)
 */

}
#endif

#if 0
int main(int argc, char const *argv[])
{
    int x = 3311;
    const int& r1 = x;  /* const reference */
    
    // r1 = 31; /*illegal*/

    int z = r1; /*legal*/

    cout << "z = " << z << endl;
}

#endif
#if 0
int main(int argc, char const *argv[])
{
    int x = 3311;
    const int& r1 = 18;  /* const reference */ /*R value assignment*/

    int z = r1;
    cout << "z = " << z << endl;
}

#endif

#if 0
/*pointers with arrays*/
int main(int argc, char const *argv[])
{
    int ar[10] = { 0 };
    int* p = ar; /*array'in ilk elemanını gösteren pointer (array decay)*/
    int (*p)[10] = &ar; /* array in kendisiini gösteren pointer*/
}
#endif
#if 0
/*references with arrays*/
int main(int argc, char const *argv[])
{
    int ar[4] = { 1,2,3,4 };
    int(&r1)[4] = ar;

    printf("%p\t%p\n",&r1, &r1 + 1);
    printf("%p\t%p\n",r1, r1 + 1);

}
#endif

#if 0

typedef struct 
{
    int a = 1;
    double d = 31.31;
}data_t;

data_t data_obj;

/* auto type deduction*/
int main(int argc, char const *argv[])
{
    const int ival = 39;
    auto x = 10; /*default init geçerli degildir*/ /*int*/
    int ar[10]{0};
    auto dval = 1.1; /*double*/
    auto data_struct = data_obj; /*data_t*/
    auto p = &ar;
    auto ival_i = ival; /*int*/ /*not const int!!*/
    int& r_i = x;
    auto a_i = r_i; /*int*/
}

#endif

#if 0
/*auto keyword with referance declarator*/
int main(int argc, char const *argv[])
{
    const int x = 5;

    auto& r = x; /*const int*/
}

#endif

#if 0
/*auto keyword with referance declarator*/
int main(int argc, char const *argv[])
{
    int ar[5]{0};

    auto& r = ar; /*int[5]*/
    auto& r_c = "yavuz"; /*const char[6]*/
    const char(&r_c_alt)[6] = "yavuz"; /*r_c and r_c_alt are the same!! */
}

#endif
#if 1
int foo(int){
    return 12;
}

int main(int argc, char const *argv[])
{
    int ar[5]{0};
	auto fp_1 = foo; /* int(*)(int) */
	auto& fp_2 = foo; /* int(&fp_2)(int) */ /* no function to pointer conv. */
}
#endif