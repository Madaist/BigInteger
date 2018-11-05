#ifndef BIGINTEGER_HPP_INCLUDED
#define BIGINTEGER_HPP_INCLUDED
#include <iostream>
#include<vector>
#include<string>
#include<stdexcept>

class BigInteger
{
public:
    BigInteger(int number = 0, unsigned char base = 10);
    BigInteger(long long int number, unsigned char base = 10);
    BigInteger(const std::string& digits, unsigned char base = 10);

    unsigned char get_base() const;
    unsigned char get_sign() const;

    BigInteger& operator+=(const BigInteger& ob);
    BigInteger& operator+=(int a);

    BigInteger& operator-=(const BigInteger& ob);
    BigInteger& operator-=(int a);

    BigInteger& operator*=(const BigInteger& ob);
    BigInteger& operator*=(int a);

    BigInteger& operator/=(const BigInteger& ob);
    BigInteger& operator/=(int a);

    BigInteger& operator%=(const BigInteger& ob);
    BigInteger& operator%=(int a);

    friend std::istream& operator>>(std::istream& stream, BigInteger& ob);
    friend std::ostream& operator<<(std::ostream& stream, BigInteger& ob);

    friend BigInteger operator+(const BigInteger& ob);
    friend BigInteger operator-(BigInteger ob);

    friend BigInteger operator+(const BigInteger& ob, int a);
    friend BigInteger operator+(int a, const BigInteger& ob);
    friend BigInteger operator+(const BigInteger& ob1, const BigInteger& ob2);

    friend BigInteger operator-(const BigInteger& ob, int a);
    friend BigInteger operator-(int a, const BigInteger& ob);
    friend BigInteger operator-(const BigInteger& ob1, const BigInteger& ob2);

    friend BigInteger operator*(const BigInteger& ob, int a);
    friend BigInteger operator*(int a, const BigInteger& ob);
    friend BigInteger operator*(const BigInteger& ob1, const BigInteger& ob2);

    friend BigInteger operator/(const BigInteger& ob, int a);
    friend BigInteger operator/(int a, const BigInteger& ob);
    friend BigInteger operator/(const BigInteger& ob1, const BigInteger& ob2);

    friend BigInteger operator^(const BigInteger& ob, int a);

    friend BigInteger operator%(const BigInteger& ob1, const BigInteger& ob2);
    friend BigInteger operator%(const BigInteger& ob, int a);
    friend BigInteger operator%(int a, const BigInteger& ob);

    friend bool operator==(const BigInteger& ob1, const BigInteger& ob2);
    friend bool operator==(const BigInteger& ob, int a);
    friend bool operator==(int a, const BigInteger& ob);

    friend bool operator!=(const BigInteger& ob1, const BigInteger& ob2);
    friend bool operator!=(const BigInteger& ob, int a);
    friend bool operator!=(int a, const BigInteger& ob);

    friend bool operator<(const BigInteger& ob1, const BigInteger& ob2);
    friend bool operator<(const BigInteger& ob, int a);
    friend bool operator<(int a, const BigInteger& ob);

    friend bool operator<=(const BigInteger& ob1, const BigInteger& ob2);
    friend bool operator<=(const BigInteger& ob, int a);
    friend bool operator<=(int a, const BigInteger& ob);

    friend bool operator>(const BigInteger& ob1, const BigInteger& ob2);
    friend bool operator>(const BigInteger& ob, int a);
    friend bool operator>(int a, const BigInteger& ob);

    friend bool operator>=(const BigInteger& ob1, const BigInteger& ob2);
    friend bool operator>=(const BigInteger& ob, int a);
    friend bool operator>=(int a, const BigInteger& ob);
    friend BigInteger min(const BigInteger& a, const BigInteger& b);

private:
    std::vector<unsigned char> m_digit;
    unsigned char m_sign;
    unsigned char m_base;
};


#endif // BIGINTEGER_HPP_INCLUDED
