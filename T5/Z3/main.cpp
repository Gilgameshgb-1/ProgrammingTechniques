/*
    TP 2018/2019: Tutorijal 5, Zadatak 3

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
#include <vector>
#include <algorithm>
#include <cmath>

void unos(int &a){
	int temp;
	std::cin>>temp;
	a=temp;
}

bool brojcifri(int a,int b){
	int d = 1+log(abs(a));
	int k = 1+log(abs(b));
	return d<k;
}

bool HocemoTrocifren(int a){
	if(abs(a)>=100 && abs(a)<=999) return true;
	return false;
}

bool DaLiJePotpun(int a){
	if(int(sqrt(a))==sqrt(a)) return true;
	return false;
}

void ispis(int a){
	std::cout<<" "<<a;
}

bool cifra(int a){
	return true;
}

int main ()
{
	int brojelem;
	int v[1000];
	int prepis[1000];
	std::cout<<"Unesite broj elemenata (max. 1000): ";
	std::cin>>brojelem;
	std::cout<<"Unesite elemente: ";
	std::for_each(v,v+brojelem,unos);
	std::cout<<"Najveci element niza je "<< *(std::max_element(v,v+brojelem));
	int temp = *(std::min_element(v,v+brojelem));
	std::cout<<"\nNajmanji element niza se pojavljuje "<<std::count(v,v+brojelem,temp)<<" puta u nizu";
	std::cout<<"\nU nizu ima "<<std::count_if(v,v+brojelem,DaLiJePotpun)<<" brojeva koji su potpuni kvadrati";
	std::cout<<"\nPrvi element sa najmanjim brojem cifara je "<<*(std::min_element(v,v+brojelem,brojcifri));
	std::remove_copy_if(v,v+brojelem,prepis,HocemoTrocifren);
	int z = std::count_if(v,v+brojelem,HocemoTrocifren);
	std::cout<<"\nElementi koji nisu trocifreni su:"/*<<)*/;
	std::for_each(prepis,prepis+brojelem-z,ispis);
	
	return 0;
}
