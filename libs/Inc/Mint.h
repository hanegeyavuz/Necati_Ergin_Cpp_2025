#pragma once
#include <iostream>
/*thin wrapper*/

class Mint
{
public:
    Mint() = default;

    explicit Mint(int val) : mval{val} {};

    /*instructor*/
    friend std::ostream &operator<<(std::ostream &os, const Mint &m)
    {
        return os << "[" << m.mval << "]";
    }

    /*extractor*/
    friend std::istream &operator>>(std::istream &is, Mint &m)
    {
        return is >> m.mval;
    }

    Mint &operator+=(const Mint &other)
    {

        mval += other.mval;
        return *this;
    }

    Mint &operator-=(const Mint &other)
    {

        mval -= other.mval;
        return *this;
    }

    friend Mint operator+(const Mint lhs, const Mint rhs)
    {
        return Mint(lhs) += rhs;
    }

    friend Mint operator-(const Mint lhs, const Mint rhs)
    {
        return Mint(lhs) -= rhs;
    }
    /*comparision operators*/
    friend bool operator<(const Mint lhs, const Mint rhs)
    {
        return lhs.mval - rhs.mval < 0 ? true : false;
    }
    friend bool operator>(const Mint lhs, const Mint rhs)
    {
        return rhs < lhs;
    }
    friend bool operator<=(const Mint lhs, const Mint rhs)
    {
        return !(rhs < lhs);
    }
    friend bool operator>=(const Mint lhs, const Mint rhs)
    {
        return !(lhs < rhs);
    }
    friend bool operator==(const Mint lhs, const Mint rhs)
    {
        return (lhs.mval == rhs.mval);
    }
    friend bool operator!=(const Mint lhs, const Mint rhs)
    {
        return !(lhs == rhs);
    }
    // auto operator<=>(const Mint&)const = default; /*c++20 standard feature*/

    Mint& operator++(){
        ++mval;
        return *this;
    }
    Mint operator++(int){
        Mint temp{*this};
        ++mval;
        return temp;
    }

    private:
    int mval{};
};
