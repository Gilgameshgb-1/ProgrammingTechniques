#include <iostream>
#include <new>
#include <string>
#include <algorithm>

int main ()
{
	
	std::string** recenice=nullptr;
	int broj;
	try {
		std::cout<<"Koliko zelite recenica: ";
		std::cin>>broj;
		std::cin.ignore(10000,'\n');
		std::cout<<"Unesite recenice: ";
		std::string** recenice = new std::string*[broj];
		for(int i = 0; i<broj; i++) {
			recenice[i] = new std::string;
			std::getline(std::cin,*recenice[i],'\n');
		}
		std::sort(recenice,recenice+broj,[](std::string* s1,std::string* s2){if(*s1<*s2) return true;return false;});
		std::cout<<"\nSortirane recenice:"<<std::endl;
		for(int i = 0; i<broj; i++) std::cout<<*recenice[i]<<std::endl;
		for(int i = 0; i<broj; i++) delete recenice[i];
		delete[] recenice;
	} catch(std::bad_alloc) {
		std::cout<<"\nProblemi s memorijom!";
		delete[] recenice;
	}
	return 0;
}
