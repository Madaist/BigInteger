#include <iostream>
#include<vector>
#include<string>
#include<string.h>
#include<stdexcept>
#include<algorithm>
#include<cstdlib>
#include "BigInteger.hpp"

BigInteger::BigInteger(std::string digits, unsigned char base)
    : m_base(base)
{
    try
    {
        if(digits[0] == '-') m_sign = '-';
        else if(digits[0] == '+')  m_sign = '+';
        else throw std::runtime_error
            ("Prima pozitie a string-ului trebuie sa fie reprezentata de semn (+ sau -).");
    }
    catch(std::runtime_error& e)
    {
        std::cout<<e.what();
        exit(0);
    }

    for(int i = digits.length()-1; i >= 1; i--)
    {
        try
        {
            if(strchr("0123456789", digits[i])==NULL)
                throw std::runtime_error("String-ul nu reprezinta un numar");
        }
        catch(std::runtime_error& e)
        {
            std::cout<<e.what();
            exit(0);
        }
        m_digit.push_back(digits[i]);
    }
}

BigInteger::BigInteger(int number, unsigned char base)
    : m_base(base)
{
    if(number >= 0) m_sign = '+';
    else m_sign = '-';
    if(number == 0) m_digit.push_back('0');

    number = std::abs(number);
    while(number != 0)
    {
        int a = number %10;
        m_digit.push_back(a + '0');
        number /= 10;
    }
}

BigInteger::BigInteger(long long int number, unsigned char base)
    : m_base(base)
{
    if(number >= 0) m_sign = '+';
    else m_sign = '-';
    number = std::abs(number);
    while(number != 0)
    {
        int a = number %10;
        m_digit.push_back(a + '0');
        number /= 10;
    }
}

unsigned char BigInteger::get_base() const
{
    return m_base;
}

unsigned char BigInteger::get_sign() const
{
    return m_sign;
}

BigInteger BigInteger::operator+=(const BigInteger& ob)
{
    try
    {
        if(m_base != ob.m_base)
            throw std::runtime_error("Numerele sunt in baze diferite. Nu se pot face operatii.");
    }
    catch(std::runtime_error& e)
    {
        std::cout<<e.what();
        exit(0);
    }

    int carry = 0, sum, i;
    BigInteger min_number = min(*this, ob);
    BigInteger max_number = (min_number == ob) ? *this : ob;
    int min_size = min_number.m_digit.size();
    int max_size = max_number.m_digit.size();
    m_digit.clear();

    if(m_sign == ob.m_sign)
    {
        if(m_digit.size() != ob.m_digit.size())
        {
            for(i = min_size; i < max_size; i++)
                min_number.m_digit.push_back('0');
        }
        for( i = 0; i < max_size; i++)
        {
            sum = (min_number.m_digit[i] - '0') + (max_number.m_digit[i] - '0') + carry;
            carry = 0;
            m_digit.push_back((sum % 10) + '0');
            if(sum >= 10 )
                carry = sum / 10;
        }
        if(carry != 0)
            m_digit.push_back(carry + '0');
        m_sign = ob.m_sign;
        return *this;
    }

    if(get_sign() != ob.get_sign())
    {
        m_sign = max_number.m_sign;
        int diff;
        carry = 0;
        for(int i = 0; i < min_size; i++)
        {
            diff = (max_number.m_digit[i] - '0') - (min_number.m_digit[i] - '0') - carry;
            if(diff < 0)
            {
                diff = diff + 10;
                carry = 1;
            }
            else
                carry = 0;
            m_digit.push_back(diff + '0');
        }
        for(int i = min_size; i < max_size; i++)
        {
            diff = (max_number.m_digit[i] - '0') - carry;
            if(diff < 0)
            {
                diff = diff + 10;
                carry = 1;
            }
            else
                carry = 0;
            m_digit.push_back(diff + '0');
        }
    }
    return *this;
}

BigInteger BigInteger::operator+=(int a)
{
    BigInteger temp;
    temp.m_digit.clear();
    if( a >= 0 )
        temp.m_sign = '+';
    else temp.m_sign = '-';
    if(a == 0) temp.m_digit.push_back('0');
    if(a < 0 ) a = std::abs(a);
    while(a != 0)
    {
        temp.m_digit.push_back((a % 10) + '0');
        a = a / 10;
    }
    *this += temp;
    return *this;
}

BigInteger BigInteger::operator-=(const BigInteger& ob)
{
    *this += (-ob);
    return *this;
}

BigInteger BigInteger::operator-=(int a)
{
    *this += (-a);
    return *this;
}

BigInteger BigInteger::operator*=(const BigInteger& ob)
{
    if(m_sign == ob.m_sign) m_sign = '+';
    else m_sign = '-';

    int size1 = m_digit.size();
    int size2 = ob.m_digit.size();
    std::vector<int> result(size1 + size2, 0);
    int i_n1 = 0;
    int i_n2 = 0;

    for (int i=0; i < size2; i++)
    {
        int carry = 0;
        int digit2 = ob.m_digit[i] - '0';
        i_n1 = 0;
        for (int j=0; j < size1; j++)
        {
            int digit1 = m_digit[j] - '0';
            int sum = digit1 * digit2 + result[i_n1 + i_n2] + carry;
            carry = sum / 10;
            result[i_n1 + i_n2] = sum % 10;
            i_n1++;
        }
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        i_n2++;
    }
    unsigned int i = 0;
    while (i < result.size() && result[i] == 0)
        i++;

    if (i == result.size())
    {
        m_digit.clear();
        m_digit.push_back('0');
        return *this;
    }

    m_digit.clear();
    for(unsigned int i = 0; i < result.size(); i++)
        m_digit.push_back(result[i] +'0');

    return *this;
}

BigInteger BigInteger::operator*=(int a)
{
    BigInteger temp;
    temp.m_digit.clear();
    if( a >= 0 )
        temp.m_sign = '+';
    else temp.m_sign = '-';
    if(a == 0) temp.m_digit.push_back('0');
    if(a < 0 ) a = std::abs(a);
    while(a != 0)
    {
        temp.m_digit.push_back((a % 10) + '0');
        a = a / 10;
    }
    *this *= temp;
    return *this;
}

BigInteger BigInteger::operator/=(int a)
{
    try
    {
        if(a == 0)
            throw std::runtime_error("Impartire la 0.");
    }
    catch(std::runtime_error& e)
    {
        std::cout<<e.what();
        exit(0);
    }

    int divisor = a;
    BigInteger big_a;
    big_a.m_digit.clear();
    if( a > 0 )
        big_a.m_sign = '+';
    else big_a.m_sign = '-';
    if(a < 0 ) a = std::abs(a);
    while(a != 0)
    {
        big_a.m_digit.push_back((a % 10) + '0');
        a = a / 10;
    }
    if(big_a > *this)
    {
        m_digit.clear();
        m_digit.push_back('0');
        return *this;
    }

    if(m_sign == big_a.m_sign)
        m_sign = '+';
    else m_sign = '-';

    std::vector<unsigned char> result;
    unsigned int idx = m_digit.size()-1;
    int temp = m_digit[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (m_digit[--idx] - '0');

    while (m_digit.size() > idx)
    {
        result.push_back((temp / divisor) + '0');
        temp = (temp % divisor) * 10 + m_digit[--idx] - '0';
    }
    m_digit.clear();
    std::reverse(result.begin(),result.end());
    m_digit = result;
    return *this;
}

BigInteger operator+(const BigInteger& ob)
{
    return ob;
}

BigInteger operator-(BigInteger ob)
{
    if(ob.m_sign == '+')
        ob.m_sign = '-';
    else
        ob.m_sign = '+';
    return ob;
}

BigInteger operator+(const BigInteger& ob1, const BigInteger& ob2)
{
    BigInteger temp(ob1);
    temp += ob2;
    return temp;
}

BigInteger operator+(const BigInteger& ob, int a)
{
    BigInteger temp(ob);
    temp += a;
    return temp;
}

BigInteger operator+(int a, const BigInteger& ob)
{
    BigInteger temp(ob);
    temp += a;
    return temp;
}

BigInteger operator-(const BigInteger& ob1, const BigInteger& ob2)
{
    BigInteger temp(ob1);
    temp += (-ob2);
    return temp;
}

BigInteger operator-(const BigInteger& ob, int a)
{
    BigInteger temp(ob);
    temp -= a;
    return temp;
}

BigInteger operator-(int a, const BigInteger& ob)
{
    BigInteger temp, result;
    temp.m_digit.clear();
    result.m_digit.clear();
    if( a >= 0 )
        temp.m_sign = '+';
    else temp.m_sign = '-';
    if(a == 0) temp.m_digit.push_back('0');
    if(a < 0 ) a = std::abs(a);
    while(a != 0)
    {
        temp.m_digit.push_back((a % 10) + '0');
        a = a / 10;
    }
    result = temp - ob;
    return result;
}

BigInteger operator*(const BigInteger& ob1, const BigInteger& ob2)
{
    BigInteger temp(ob1);
    temp *= ob2;
    return temp;
}

BigInteger operator*(const BigInteger& ob, int a)
{
    BigInteger temp(ob);
    temp *= a;
    return temp;
}

BigInteger operator*(int a, const BigInteger& ob)
{
    BigInteger temp(ob);
    temp *= a;
    return temp;
}

BigInteger operator/(int a, const BigInteger& ob)
{
    int ok = 0;
    for (auto i = ob.m_digit.rbegin(); i != ob.m_digit.rend(); ++i)
        if(*i != '0') ok = 1;
    try
    {
        if(ok == 0)
            throw std::runtime_error("Impartire la 0.");
    }
    catch(std::runtime_error& error)
    {
        std::cout<<error.what();
        exit(0);
    }

    int b = a;
    unsigned int counter = 0;
    BigInteger temp;
    temp.m_digit.clear();
    while(b != 0)
    {
        counter++;
        b = b / 10;
    }
    if(ob.m_digit.size() > counter)
    {
        temp.m_digit.push_back('0');
        return temp;
    }

    std::string digit;
    for (auto i = ob.m_digit.rbegin(); i != ob.m_digit.rend(); ++i)
        digit += *i;
    int x = atoi(digit.c_str());
    int result = a / x;
    if( (a >= 0 && ob.m_sign == '+') || (a <= 0 && ob.m_sign == '-'))
        temp.m_sign = '+';
    else temp.m_sign = '-';
    if(result == 0) temp.m_digit.push_back('0');
    if(result < 0 ) result = std::abs(result);
    while(result != 0)
    {
        temp.m_digit.push_back((result % 10) + '0');
        result = result / 10;
    }
    return temp;
}

BigInteger operator/(const BigInteger& ob, int a)
{
    BigInteger temp(ob);
    temp /= a;
    return temp;
}

BigInteger operator^(const BigInteger& ob, int a)
{
    BigInteger temp;
    temp.m_digit.clear();
    if( a == 0)
    {
        temp.m_digit.push_back('1');
        return temp;
    }
    if(a < 0)
    {
        temp.m_digit.push_back('0');
        return temp;
    }
    temp = ob;
    for(int i = 1; i < a; i++)
        temp *= ob;
    return temp;

}

bool operator==(const BigInteger& ob1, const BigInteger& ob2)
{
    if(ob1.m_sign != ob2.m_sign || ob1.m_digit.size() != ob2.m_digit.size())
        return false;
    for(unsigned int i = 0; i < ob1.m_digit.size(); i++)
        if(ob1.m_digit[i] != ob2.m_digit[i])
            return false;
    return true;
}

bool operator==(const BigInteger& ob, int a)
{
    int b = a;
    unsigned int counter = 0;
    while(b != 0)
    {
        b = b/10;
        counter++;
    }
    if(counter != ob.m_digit.size())
        return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if(ob.m_digit[i]-'0' !=  a%10)
            return false;
        a = a/10;
    }
    return true;
}

bool operator==(int a, const BigInteger& ob)
{
    int b = a;
    unsigned int counter = 0;
    while(b != 0)
    {
        b = b/10;
        counter++;
    }
    if(counter != ob.m_digit.size())
        return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if(ob.m_digit[i]-'0' !=  a%10)
            return false;
        a = a/10;
    }
    return true;
}

bool operator!=(const BigInteger& ob1, const BigInteger& ob2)
{
    if(ob1 == ob2)
        return false;
    return true;
}

bool operator!=(const BigInteger& ob, int a)
{
    if(ob == a)
        return false;
    return true;
}

bool operator!=(int a, const BigInteger& ob)
{
    if(a == ob)
        return false;
    return true;
}

bool operator<(const BigInteger& ob1, const BigInteger& ob2)
{
    if(ob1.m_digit.size() < ob2.m_digit.size() || (ob1.m_sign == '-' && ob2.m_sign == '+'))
        return true;
    if(ob1.m_sign == '+' && ob2.m_sign == '-')
        return false;
    for(unsigned int i = ob1.m_digit.size()-1; i >= 0; i--)
        if(ob1.m_digit[i] >= ob2.m_digit[i])
            return false;
    return true;
}

bool operator<(const BigInteger& ob, int a)
{
    int b = a;
    unsigned int counter = 0;
    while(b != 0)
    {
        b = b/10;
        counter++;
    }
    if(counter < ob.m_digit.size())
        return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if(ob.m_digit[i]-'0' >=  a%10)
            return false;
        a = a/10;
    }
    return true;
}

bool operator<(int a, const BigInteger& ob)
{
    int b = a;
    unsigned int counter = 0;
    while(b != 0)
    {
        b = b/10;
        counter++;
    }
    if(counter >= ob.m_digit.size())
        return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if(ob.m_digit[i]-'0' <=  a%10)
            return false;
        a = a/10;
    }
    return true;
}

bool operator>(const BigInteger& ob1, const BigInteger& ob2)
{
    if(ob1.m_digit.size() > ob2.m_digit.size() || (ob1.m_sign == '+' && ob2.m_sign == '-'))
        return true;
    if(ob1.m_sign == '-' && ob2.m_sign == '+')
        return false;
    for(unsigned int i = ob1.m_digit.size()-1; i >= 0; i--)
        if(ob1.m_digit[i] <= ob2.m_digit[i])
            return false;
    return true;
}

bool operator>(const BigInteger& ob, int a)
{
    int b = a;
    unsigned int counter = 0;
    while(b != 0)
    {
        b = b/10;
        counter++;
    }
    if(counter >= ob.m_digit.size())
        return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if(ob.m_digit[i]-'0' <=  a%10)
            return false;
        a = a/10;
    }
    return true;
}

bool operator>(int a, const BigInteger& ob)
{
    int b = a;
    unsigned int counter = 0;
    while(b != 0)
    {
        b = b/10;
        counter++;
    }
    if(counter <= ob.m_digit.size())
        return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if(ob.m_digit[i]-'0' >=  a%10)
            return false;
        a = a/10;
    }
    return true;
}

bool operator<=(const BigInteger& ob1, const BigInteger& ob2)
{
    if(ob1 < ob2 || ob1 == ob2)
        return true;
    return false;
}

bool operator<=(const BigInteger& ob, int a)
{
    if(ob < a || ob == a)
        return true;
    return false;
}

bool operator<=(int a, const BigInteger& ob)
{
    if(ob < a || ob == a)
        return true;
    return false;
}

bool operator>=(const BigInteger& ob1, const BigInteger& ob2)
{
    if(ob1 > ob2 || ob1 == ob2)
        return true;
    return false;
}

bool operator>=(const BigInteger& ob, int a)
{
    if(ob > a || ob == a)
        return true;
    return false;
}

bool operator>=(int a, const BigInteger& ob)
{
    if(a > ob || a == ob)
        return true;
    return false;
}

BigInteger min(const BigInteger& a, const BigInteger& b)
{
    if(a.m_digit.size() < b.m_digit.size())
        return a;
    if(b.m_digit.size() < a.m_digit.size())
        return b;
    for(unsigned int i = a.m_digit.size() - 1; i >= 0; i--)
        if(a.m_digit[i] < b.m_digit[i])
            return a;
    return b;
}

std::istream& operator>>(std::istream& stream, BigInteger& ob)
{
    ob.m_digit.clear();
    std::cout << "\nCitire cifra cu cifra pana la aparitia caracterului 'x'.\n";
    std::cout << "Introduceti semnul numarului (+ sau -): ";
    stream >> ob.m_sign;
    try
    {
        if(strchr("+-", ob.m_sign)==NULL)
            throw std::runtime_error("Nu ati introdus un semn valid.");
    }
    catch(std::runtime_error& e)
    {
        std::cout<<e.what();
        exit(0);
    }
    std::cout << "Introduceti cifrele. Prima cifra introdusa va fi cea a unitatilor:\n";
    char a;
    stream >> a;
    while(a != 'x' && a!= 'X')
    {
        try
        {
            if(strchr("0123456789xX", a)==NULL)
                throw std::runtime_error("Nu ati introdus o cifra valida.");
        }
        catch(std::runtime_error& e)
        {
            std::cout<<e.what();
            exit(0);
        }
        ob.m_digit.push_back(a);
        stream >> a;
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, BigInteger& ob)
{
    if(ob.m_digit.size() == 1 && ob.m_digit[0] == '0')
    {
        stream << "Numarul este: 0, in baza "<<(int)ob.m_base <<"\n";
        return stream;
    }
    stream << "Numarul este: " << ob.m_sign;
    std::vector<unsigned char>::reverse_iterator i = ob.m_digit.rbegin();
    if(*i != '0')
        stream << *i;
    for(i = ob.m_digit.rbegin()+1; i != ob.m_digit.rend(); ++i)
        stream << *i;
    stream << ", in baza " << (int)ob.m_base << ".\n";
    return stream;
}
