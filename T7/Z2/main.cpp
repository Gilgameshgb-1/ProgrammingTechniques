#include <iostream>
#include <new>
#include <string>
#include <cstring>
#include <algorithm>

int main ()
{
	char** recenice=nullptr;
	int broj;
	try {
		std::cout<<"Koliko zelite recenica: ";
		std::cin>>broj;
		std::cin.ignore(10000,'\n');
		std::cout<<"Unesite recenice: ";
		char** recenice= new char*[broj];
		for(int i = 0; i<broj; i++) {
			char radni_prostor[1000];
			std::cin.getline(radni_prostor,sizeof radni_prostor);
			recenice[i]=new char[std::strlen(radni_prostor)+1];
			std::strcpy(recenice[i],radni_prostor);
		}
		std::sort(recenice,recenice+broj,[](char* s1,char *s2){if(std::strcmp(s1,s2)<0) return true;return false;});
		std::cout<<"\nSortirane recenice:"<<std::endl;
		for(int i = 0; i<broj; i++) std::cout<<recenice[i]<<std::endl;
		for(int i = 0; i<broj; i++) delete[] recenice[i];
		delete[] recenice;
	} catch(std::bad_alloc) {
		std::cout<<"\nProblemi s memorijom!";
		delete[] recenice;
	}
	return 0;
}
