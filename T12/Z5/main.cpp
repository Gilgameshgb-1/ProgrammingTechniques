#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

int main ()
{
	std::cout<<"Koliko zelite elemenata: ";
	int broj;
	std::cin>>broj;
	std::vector<double> v(broj);
	std::cout<<"Unesite elemente: ";
	for(int i = 0;i<broj;i++){
		double temp;
		std::cin>>temp;
		v[i]=temp;
	}
	std::cout<<"Transformirani elementi: ";
	std::transform(v.begin(),v.end(),v.begin(),std::bind(std::divides<double>(),1,std::placeholders::_1));
	for(int i = 0;i<broj;i++){
		std::cout<<v[i]<<" ";
	}
	return 0;
}