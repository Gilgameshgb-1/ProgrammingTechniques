/*
    TP 2018/2019: Tutorijal 5, Zadatak 1

	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.

	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.

			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>

int main ()
{
	char niz[1000];
	char* p = niz;
	int i = 0;
	std::cout<<"Unesite recenicu: ";
	char znak;
	while(std::cin.peek()!='\n' && i < 999) {
		znak = std::cin.get();
		*p=znak;
		p++;
		i++;
	}
	*p='\0';
	p = niz;
	char* p1=niz;
	if(*p==' ') {
		while(*p==' ')p++;
	}
	while(*p!=' ' && *p!='\0') p++;
	while(*p==' ') p++;
	p--;
	if(*p==' ') {
		p++;
		while(*p!='\0') {
			*p1=*p;
			p1++;
			p++;
		}
	} else if(*p=='\0') *p1=*p;
	else if(*p!='\0') {
		p++;
		*p1=*p;
	}
	*p1='\0';
	p1=niz;
	std::cout<<"Recenica bez prve rijeci glasi: ";
	while(*p1!='\0') std::cout<<*p1++;
	std::cout<<'\n';
	return 0;
}
