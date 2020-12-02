#include <iostream>
#include <new>
#include <string>
#include <cstring>

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
		for(int i = 0; i<broj-1; i++) {
			for(int j = 0; j<broj-1; j++) {
				if(std::strcmp(recenice[j],recenice[j+1])>0) {
					char* pomocni = recenice[j];
					recenice[j]=recenice[j+1];
					recenice[j+1]=pomocni;
				}
			}
		}
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
