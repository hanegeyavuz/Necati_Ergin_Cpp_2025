#include <iostream>
#include <cstdio>

using namespace std;

#if 0

class Myclass{
public:
    void foo();
    void g(int);

};

int main(int argc, char const *argv[])
{
    Myclass m;

    m.foo(); /*m nesnesinin adresi fonksiyonun gizli parametresi olarak alınır*/
}

#endif
#if 0

class Myclass{
private:
    int mx = 23;
public:
    void foo();
    void g(int);

};

void Myclass::foo(){
    cout << "mx = " << mx << endl;
    int mx = 32; /*name masking*/
    cout << "mx = " << mx << endl;

}

int main(int argc, char const *argv[])
{
    Myclass m;

    m.foo();
}

#endif
#if 0
int x = 9;

int main(){
	int x = 3;
	cout << "x = " << x << endl;
	cout << "x = " << ::x << endl;
}
#endif

#if 0
class Counter{
private:
    int mval{}; /*parantezi görmezden gel. Sonraki konularda anlatılacak*/
public:
    void set(int val);
    void print();

};

void Counter::set(int val){
    mval = val;
}
void Counter::print(){
    cout << mval << endl;
}

int main(int argc, char const *argv[])
{
    Counter mycounter;

    mycounter.set(33);
    mycounter.print();
    mycounter.set(22);
    mycounter.print();

}
#endif
#if 0
class Counter{
private:
    int mval{}; 
    void print();
public:
    void set(int val);

};

void Counter::set(int val){
    mval = val;
    print();
}
void Counter::print(){
    cout << mval << endl;
}

int main(int argc, char const *argv[])
{
    Counter mycounter;

    mycounter.set(11); /*print fonksiyonu da mycounter objesi ile çağırılır.*/
    mycounter.set(43);

}
#endif
#if 0
class Date{
public:
	void set_year(int y);
	int get_year()const; /* degerini degistirmez */

private:
    int md,mm,my;
};


//cpp

int Date::get_year()const{
    //my = 22; /*ILLEGAL! */
    return my; 
}

#endif

#if 0
class Date{
public:
	void set_year(int y);
	int get_year()const; /* degerini degistirmez */

private:
    int md,mm,my;
};


//cpp

int Date::get_year()const{
    const Date mydate{};
    mydate.set_year(1993); /* ILLEGAL! */ /*the object has type qualifiers that are not compatible with the member function*/
}
#endif