#include <iostream>
#include"BigInteger.hpp"
#include"BigInteger.cpp"

int main()
{
    BigInteger ob1("+80", 10), ob2(-200), ob3("-123456789"), ob4(123456789);
	BigInteger ob5 = ob1 + ob2;
	std::cout << "ob1 + ob2 --> " << ob5;
	ob5 = ob1 - ob2;
	std::cout << "ob1 - ob2 --> " << ob5;
	ob5 = ob1 * ob2;
	std::cout << "ob1 * ob2 --> " << ob5;
	ob5 = ob1 / 4 ;
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
