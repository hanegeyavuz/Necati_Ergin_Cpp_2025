#include <iostream>
#include <stdio.h>

#if 0
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

    // std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
}
#endif


#if 1
/*undefined behavior yok, sizeof operandındaki ifadeler için derleyici kod uretmez*/
/*Unevaluated Context*/
int main(){
    
    int x = 20;
    int y = 0;
    printf("sizeof sz = %zu\n",sizeof(x / y));

    // std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
}
#endif



