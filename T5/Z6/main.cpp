/*
    TP 2018/2019: Tutorijal 5, Zadatak 6

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

void unos(int &a)
{
	int temp;
	std::cin>>temp;
	a=temp;
}

int sumacifri(int n)
{
	if(n==0) return 0;
	return(abs(n%10)+sumacifri(n/10));
}

bool UporedbaCifri(int a,int b)
{
	if(sumacifri(a)<sumacifri(b)) return true;
	if(sumacifri(a)==sumacifri(b) && a<b) return true;
	return false;
}

void ispis(int a)
{
	std::cout<<" "<<a;
}

int main ()
{
	int brojelem;
	std::vector<int> v;
	std::cout<<"Unesite broj elemenata: ";
	std::cin>>brojelem;
	std::cout<<"Unesite elemente: ";
	v.resize(brojelem);
	std::for_each(std::begin(v),std::end(v),unos);
	sort(std::begin(v),std::end(v),UporedbaCifri);
	std::cout<<"Niz sortiran po sumi cifara glasi:";
	std::for_each(std::begin(v),std::end(v),ispis);
	std::cout<<"\nUnesite broj koji trazite: ";
	int pretraga;
	std::cin>>pretraga;
	auto broj = std::lower_bound(v.begin(),v.end(),pretraga,UporedbaCifri);
	if(binary_search(std::begin(v),std::end(v),pretraga,UporedbaCifri)==false) {
		std::cout<<"Trazeni broj ne nalazi se u nizu!";
		return 0;
	} else {
		std::cout<<"Trazeni broj nalazi se na poziciji "<<broj-std::begin(v);
	}
	return 0;
}
