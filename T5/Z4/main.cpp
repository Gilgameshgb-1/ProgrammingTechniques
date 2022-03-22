/*
    TP 2018/2019: Tutorijal 5, Zadatak 4

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
#include <deque>
#include <algorithm>
#include <cmath>

int main ()
{
	int brojelem;
	std::deque<int> v;
	std::deque<int> prepis;
	std::cout<<"Unesite broj elemenata: ";
	std::cin>>brojelem;
	std::cout<<"Unesite elemente: ";
	v.resize(brojelem);
	std::for_each(std::begin(v),std::end(v),[] (int &a){int temp; std::cin>>temp; a=temp;});
	std::cout<<"Najveci element deka je "<< *(std::max_element(std::begin(v),std::end(v)));
	int temp = *(std::min_element(std::begin(v),std::end(v)));
	std::cout<<"\nNajmanji element deka se pojavljuje "<< std::count(std::begin(v),std::end(v),temp)<<" puta u deku";
	std::cout<<"\nU deku ima "<< std::count_if(std::begin(v),std::end(v),[](int a){return int(sqrt(a))==sqrt(a);})<<" brojeva koji su potpuni kvadrati";
	std::cout<<"\nPrvi element sa najmanjim brojem cifara je "<<*std::min_element(std::begin(v),std::end(v),[] (int a,int b){return (1+int(log10(abs(a))))<(1+int(log10(abs(b))));});
	std::cout<<"\nElementi koji nisu trocifreni su:";
	int broj = std::count_if(std::begin(v),std::end(v),[] (int a){return (abs(a)>=100 && abs(a)<=999);});
	prepis.resize(brojelem-broj);
	std::remove_copy_if(std::begin(v),std::end(v),std::begin(prepis),[] (int a){return (abs(a)>=100 && abs(a)<=999);});
	std::for_each(std::begin(prepis),std::end(prepis),[] (int a){std::cout<<" "<<a;});
	return 0;
}
