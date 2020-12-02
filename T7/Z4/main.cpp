#include <iostream>
#include <new>
#include <string>
#include <algorithm>
#include <memory>

int main ()
{
	int broj;
	try {
		std::cout<<"Koliko zelite recenica: ";
		std::cin>>broj;
		std::cin.ignore(10000,'\n');
		std::cout<<"Unesite recenice: ";
		typedef std::shared_ptr<std::string> shared;
		std::unique_ptr<shared[]> p(new shared[broj]);
		for(int i = 0; i<broj; i++) {
			p[i]=std::make_shared<std::string>();
			std::getline(std::cin,*p[i].get());
		}
		std::sort(p.get(),p.get()+broj,[](shared s1,shared s2){if(*s1<*s2) return true; return false;});
		std::cout<<"\nSortirane recenice:"<<std::endl;
		for(int i = 0; i<broj; i++) std::cout<<*p[i]<<std::endl;
	} catch(std::bad_alloc) {
		std::cout<<"\nProblemi s memorijom!";
	}
	return 0;
}
