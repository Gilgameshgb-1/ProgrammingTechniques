#include <iostream>
#include <algorithm>
#include <iterator>

std::string IzvrniBezRazmaka(std::string str)
{
	std::string temp;
	std::remove_copy(str.rbegin(),str.rend(),std::back_inserter(temp),' ');
	return temp;
}

int main ()
{
	return 0;
}
