#include <iostream>
#include"BigInteger.hpp"
#include"BigInteger.cpp"

int main()
{
    BigInteger ob1(124), ob2(12), ob3, ob4("-123456789");
    std::cout<<"ob1 --> "<<ob1;
    std::cout<<"ob2 --> "<<ob2;
    try
    {
        ob1 /= ob2;
        std::cout<<"ob1 /= ob2 --> "<<ob1;
    }
    catch(std::runtime_error& e)
    {
        std::cout<<e.what();
        exit(0);
    }

    try
    {
        ob2 %= 5;
        std::cout<<"ob2 %= 5 --> "<<ob2;
    }
    catch(std::runtime_error& e)
    {
        std::cout<<e.what();
        exit(0);
    }

    std::cout<<"ob1 --> "<<ob1;
    std::cout<<"ob2 --> "<<ob2;
    BigInteger ob5 = ob1 + ob2;
    std::cout << "ob1 + ob2 --> " << ob5;
    ob5 = ob1 - ob2;
    std::cout << "ob1 - ob2 --> " << ob5;
    ob5 = ob1 * ob2;
    std::cout << "ob1 * ob2 --> " << ob5;
    ob5 = ob1 / 4;
    std::cout << "ob1/4 --> " << ob5;
    ob5 = ob1 ^ 2;
    std::cout << "ob1^2 --> " << ob5;
    ob1 += 1;
    std::cout << "ob1+=1 --> " << ob1;
    ob1 += (-1);
    std::cout << "ob1+=(-1) --> " << ob1;
    ob1 -= (-20);
    std::cout << "ob1-=(-20) --> " << ob1;
    std::cout<<'\n';
    std::cout<<"ob1 --> "<<ob1;
    std::cout<<"ob2 --> "<<ob2;
    std::cout<<"ob3 --> "<<ob3;
    std::cout<<"ob4 --> "<<ob4;
    std::cout<<"ob5 --> "<<ob5;
    return 0;
}
