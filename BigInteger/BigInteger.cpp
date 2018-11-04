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
    if(digits[0] == '-') m_sign = '-';
    else if(digits[0] == '+')  m_sign = '+';
    else throw std::runtime_error
        ("Prima pozitie a string-ului trebuie sa fie reprezentata de semn (+ sau -).");

    for(int i = digits.length()-1; i >= 1; i--)
    {
        if(strchr("0123456789", digits[i])==NULL)
            throw std::runtime_error("String-ul nu reprezinta un numar");
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
    if(number == 0) m_digit.push_back('0');

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

BigInteger& BigInteger::operator+=(const BigInteger& ob)
{
    if(m_base != ob.m_base)
        throw std::runtime_error("Numerele sunt in baze diferite. Nu se pot face operatii.");
    if(ob == 0) return *this;

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

BigInteger& BigInteger::operator+=(int a)
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

BigInteger& BigInteger::operator-=(const BigInteger& ob)
{
    *this += (-ob);
    return *this;
}

BigInteger& BigInteger::operator-=(int a)
{
    *this += (-a);
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& ob)
{
    if(ob == 0 || *this == 0)
    {
        m_digit.clear();
        m_digit.push_back('0');
        return *this;
    }

    if(m_sign == ob.m_sign) m_sign = '+';
    else m_sign = '-';

    int size1 = m_digit.size();
    int size2 = ob.m_digit.size();
    std::vector<int> result(size1 + size2, 0);
    int i_n1 = 0;
    int i_n2 = 0;

    for (int i = 0; i < size2; i++)
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
    int i = result.size()-1;
    while(result.at(i) == 0)
    {
        result.pop_back();
        i--;
    }

    m_digit.clear();
    for(unsigned int i = 0; i < result.size(); i++)
        m_digit.push_back(result[i] +'0');

    return *this;
}

BigInteger& BigInteger::operator*=(int a)
{
    if(a == 0 || *this == 0)
    {
        m_digit.clear();
        m_digit.push_back('0');
        return *this;
    }

    BigInteger temp;
    temp.m_digit.clear();
    if( a >= 0 )
        temp.m_sign = '+';
    else temp.m_sign = '-';
    if(a < 0 ) a = std::abs(a);
    while(a != 0)
    {
        temp.m_digit.push_back((a % 10) + '0');
        a = a / 10;
    }
    *this *= temp;
    return *this;
}

BigInteger& BigInteger::operator/=(int a)
{
    if(a == 0)
        throw std::runtime_error("Impartire la 0.");

    if( *this < a )
    {
        m_digit.clear();
        m_digit.push_back('0');
        return *this;
    }

    char a_sign = '+';
    if( a < 0) a_sign = '-';
    if(m_sign == a_sign) m_sign = '+';
    else m_sign = '-';
    int divisor = std::abs(a);


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

BigInteger& BigInteger::operator/=(const BigInteger& ob)
{
    if(ob == 0)
        throw std::runtime_error("Impartire la 0.");
    if(*this < ob)
    {
        std::cout<<"mai mic";
        m_digit.clear();
        m_digit.push_back('0');
        return *this;
    }
    if(m_sign == ob.m_sign) m_sign = '+';
    else m_sign = '-';
    BigInteger result, temp;
    result.m_digit.clear();
    result.m_sign = m_sign;
    temp.m_digit.clear();
    int idx = m_digit.size()-1;

    temp.m_digit.push_back(m_digit[idx]);
    while(temp < ob)
    {
        idx--;
        temp.m_digit.push_back(m_digit[idx]);
    }
    int quotient, i;
    BigInteger rest;
    rest.m_digit.clear();
    while(idx >= 0)
    {
        idx--;
        for( i = 0; i <= 9; i++)
        {
            BigInteger x = ob*i;
            if(x == temp)
            {
                quotient = i;
                break;
            }
            if(x > temp)
            {
                quotient = i-1;
                break;
            }
        }
        std::cout<<"quotient is "<<quotient<<'\n';
        result.m_digit.push_back(quotient + '0');
        rest = temp - (ob * quotient);
        rest *= 10;
        if(idx >= 0)
            temp = rest + (m_digit.at(idx)-'0');
    }
    std::reverse(result.m_digit.begin(), result.m_digit.end());
    *this = result;
    return *this;
}

BigInteger& BigInteger::operator%=(int a)
{
    if(a == 0)
        throw std::runtime_error("Impartire la 0.");
    if(a < 0) a = std::abs(a);
    int result = 0;
    for(auto i = m_digit.rbegin(); i != m_digit.rend(); ++i)
        result = (result * 10 + (*i-'0')) % a;
    m_digit.clear();
    if(result == 0)
    {
        m_digit.push_back('0');
        return *this;
    }
    while(result != 0)
    {
        m_digit.push_back(result%10+'0');
        result /= 10;
    }
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

    if(ok == 0)
        throw std::runtime_error("Impartire la 0.");

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

BigInteger operator/(const BigInteger& ob1, const BigInteger& ob2)
{
    BigInteger temp(ob1);
    temp /= ob2;
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

BigInteger operator%(const BigInteger& ob, int a)
{
    BigInteger temp(ob);
    temp %= a;
    return temp;
}

bool operator==(const BigInteger& ob1, const BigInteger& ob2)
{
    if((ob1.m_sign != ob2.m_sign) || (ob1.m_digit.size() != ob2.m_digit.size()))
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
    if(a == 0) counter = 1;
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
    if(a == 0) counter = 1;
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

bool operator!= (const BigInteger& ob1, const BigInteger& ob2)
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
    if((ob1.m_sign == '-' && ob2.m_sign == '+') || (ob1.m_digit.size() < ob2.m_digit.size()))
        return true;
    if((ob1.m_sign == '+' && ob2.m_sign == '-') || (ob1.m_digit.size() > ob2.m_digit.size()))
        return false;
    if(ob1 == ob2) return false;
    for( int i = ob1.m_digit.size()-1; i >= 0; i--)
    {
        if(ob1.m_digit[i] > ob2.m_digit[i])
            return false;
        if(ob1.m_digit[i] < ob2.m_digit[i])
            return true;
    }
    return true;
}

bool operator< (const BigInteger& ob, int a)
{
    if(ob == a) return false;
    int b = a;
    unsigned int counter = 0;
    while(b != 0)
    {
        b = b/10;
        counter++;
    }
    if(a == 0) counter = 1;
    if(ob.m_digit.size() > counter)
        return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if((ob.m_digit[i]-'0') >  a%10)
            return false;
        else if ((ob.m_digit[i]-'0') <  a%10)
            return true;
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
    if(a == 0) counter = 1;
    if(counter > ob.m_digit.size())
        return false;
    if(ob == a) return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if(ob.m_digit[i]-'0' <  a%10)
            return false;
        if(ob.m_digit[i]-'0' >  a%10)
            return true;
        a = a/10;
    }
    return true;
}

bool operator> (const BigInteger& ob1, const BigInteger& ob2)
{
    if((ob1.m_sign == '+' && ob2.m_sign == '-') || (ob1.m_digit.size() > ob2.m_digit.size()))
        return true;
    if((ob1.m_sign == '-' && ob2.m_sign == '+') || (ob1.m_digit.size() < ob2.m_digit.size()))
        return false;
    if(ob1 == ob2) return false;
    for(int i = ob1.m_digit.size()-1; i >= 0; i--)
    {
        if(ob1.m_digit[i] < ob2.m_digit[i])
            return false;
        if(ob1.m_digit[i] > ob2.m_digit[i])
            return true;
    }
    return true;
}

bool operator> (const BigInteger& ob, int a)
{
    int b = a;
    unsigned int counter = 0;
    while(b != 0)
    {
        b = b/10;
        counter++;
    }
    if(a == 0) counter = 1;
    if(counter > ob.m_digit.size())
        return false;
    if(ob == a) return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if(ob.m_digit[i]-'0' <  a%10)
            return false;
        else if(ob.m_digit[i]-'0' >  a%10)
            return true;
        a = a/10;
    }
    return true;
}

bool operator> (int a, const BigInteger& ob)
{
    int b = a;
    unsigned int counter = 0;
    if(a == 0) counter = 1;
    while(b != 0)
    {
        b = b/10;
        counter++;
    }
    if(counter < ob.m_digit.size())
        return false;
    if(b == a) return false;
    for(unsigned int i = 0; i < counter; i++)
    {
        if(ob.m_digit[i]-'0' >  a%10)
            return false;
        else if(ob.m_digit[i]-'0' <  a%10)
            return true;
        a = a/10;
    }
    return true;
}

bool operator<= (const BigInteger& ob1, const BigInteger& ob2)
{
    if(ob1 < ob2 || ob1 == ob2)
        return true;
    return false;
}

bool operator<= (const BigInteger& ob, int a)
{
    if(ob < a || ob == a)
        return true;
    return false;
}

bool operator<=(int a, const BigInteger& ob)
{
    if(a < ob || a == ob)
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
    if(strchr("+-", ob.m_sign)==NULL)
        throw std::runtime_error("Nu ati introdus un semn valid.");

    std::cout << "Introduceti cifrele. Prima cifra introdusa va fi cea a unitatilor:\n";
    char a;
    stream >> a;
    while(a != 'x' && a!= 'X')
    {
        if(strchr("0123456789xX", a)==NULL)
            throw std::runtime_error("Nu ati introdus o cifra valida.");
        ob.m_digit.push_back(a);
        stream >> a;
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, BigInteger& ob)
{
    if(ob.m_digit.size()==1 && ob.m_digit[0] == '0') //de modificat
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
