#include <iostream>
#include <string>
#include <vector>
#include "Mint.h"
using namespace std;

#if 0

int main(int argc, char const *argv[])
{
    Mint m1, m2{45};
    cout << "m1 = " << m1 << "\nm2 = " << m2 << "\n";

    for (size_t i = 0; i < 10; i++)
    {
        cout << Mint(i) << ' ';
    }
    
}

#endif
#if 0

int main(int argc, char const *argv[])
{
    Mint m1, m2{};
    cout << "m1 = " << m1 << "\nm2 = " << m2 << "\n";
    
    cout << "iki tam sayi giriniz: ";
    cin >> m1 >> m2;
    
    cout << "m1 = " << m1 << "\nm2 = " << m2 << "\n";

    m1 += m2;
    cout << "m1 = " << m1 << "\n";

    Mint m3 = m1 + m2;
    cout << "m3 = " << m3 << "\n";
    
}

#endif
#if 0

int main() {
    std::vector<std::string> names = {"Hüseyin", "Ali", "Ayşe"};

    // Using const auto& to avoid copying the strings
    for (const auto& name : names) {
        std::cout << "Hello, " << name << "!" << std::endl;
    }

}

#endif
#if 0
int main(int argc, char const *argv[])
{
    Mint m1, m2{};
    cout << "m1 = " << m1 << "\nm2 = " << m2 << "\n";

    cout << "iki tam sayi giriniz: ";
    cin >> m1 >> m2;

    cout << "m1 = " << m1 << "\nm2 = " << m2 << "\n";

    // m1 += m2;
    // cout << "m1 = " << m1 << "\n";

    Mint m3 = m1 + m2;
    cout << "m3 = " << m3 << "\n";

    cout << "m1 > m2 = " << (m1 > m2) << "\n";
    cout << "m1 < m2 = " << (m1 < m2) << "\n";
    cout << "m1 >= m2 = " << (m1 >= m2) << "\n";
    cout << "m1 <= m2 = " << (m1 <= m2) << "\n";
    cout << "m1 == m2 = " << (m1 == m2) << "\n";
    cout << "m1 != m2 = " << (m1 != m2) << "\n";
}
#endif
#if 1
int main(int argc, char const *argv[])
{
    Mint m1, m2{};
    cout << "m1 = " << m1 << "\nm2 = " << m2 << "\n";

    cout << "prefix tam sayi giriniz: ";
    cin >> m1;

    cout << "++m1 = " << ++m1 << "\n";
    cout << "m1 = " << m1 << "\n";

    cout << "posfix tam sayi giriniz: ";
    cin >> m2;

    cout << "m2++ = " << m2++ << "\n";
    cout << "m2++ = " << m2 << "\n";
}

#endif
#if 1

#endif