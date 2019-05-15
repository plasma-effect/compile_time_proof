#include"compile_time_proof/axiom.hpp"
#include<iostream>
#include<iomanip>

void Main()
{

}

int main()
{
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(15);
	try
	{
		Main();
	}
	catch (std::exception & exp)
	{
		std::cerr << exp.what() << std::endl;
	}
}