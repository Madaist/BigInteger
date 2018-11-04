#include <iostream>
#include"BigInteger.hpp"
#include"BigInteger.cpp"

int main()
{
    BigInteger ob1(80), ob2(4), ob3("-123456789"), ob4(123456789);
    ob1 /= ob2;
    std::cout<<ob1;
    /*BigInteger ob5 = ob1 + ob2;
	std::cout << "ob1 + ob2 --> " << ob5;
	ob5 = ob1 - ob2;
	std::cout << "ob1 - ob2 --> " << ob5;
	ob5 = ob1 * ob2;
	std::cout << "ob1 * ob2 --> " << ob5;
	ob5 = ob1 / 10 ;
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
	std::cout<<"ob5 --> "<<ob5; */
    return 0;
}
