/* TP, 2018/2019, Zadaća 1, Zadatak 1

	NAPOMENA: ulaz/izlaz za zadatke je specificiran
	javnim autotestovima. Zalbe za ne analiziranje testova
	se ne uvazavaju!

	NAPOMENA: nece svi (javni) testovi sa zamgera biti
	dostupni na c9.
*/
#include <iostream>
#include <vector>
#include <cmath>

typedef std::vector<int> Vektor;

int ObrniCifre(int broj)
{

	int ObrnutBroj(0);

	while(broj>0) {
		ObrnutBroj=broj%10+10*ObrnutBroj;
		broj/=10;
	}

	return ObrnutBroj;
}

bool DaLiJePalindrom(int broj)
{

	Vektor privremeno;

	while(broj>0) {
		privremeno.push_back(broj%10);
		broj/=10;
	}
	for(int i = 0 ; i<privremeno.size()/2; i++) {
		if(privremeno.at(i) != privremeno.at(privremeno.size()-i-1)) return false;
	}
	return true;
}

Vektor PalindromskaOtpornost(Vektor v)
{

	Vektor Otpornosti;
	int suma(0);
	int brojac(0);

	for(int i=0;i<v.size(); i++) {
		suma=abs(v.at(i));
		while(DaLiJePalindrom(suma)==false) {
			suma+=ObrniCifre(suma);
			brojac++;
		}
		Otpornosti.push_back(brojac);
		brojac=0;
	}
	return Otpornosti;
}

int main ()
{
	int n;
	Vektor a;
	std::cout<<"Koliko zelite unijeti elemenata: ";
	std::cin>>n;
	std::cout<<"Unesite elemente: ";
	for(int i = 0; i<n; i++) {
		int broj;
		std::cin>>broj;
		a.push_back(broj);
	}
	Vektor c = PalindromskaOtpornost(a);
	for(int i=0;i< c.size(); i++) {
		std::cout<<"Palindromska otpornost broja "<<a.at(i)<<" iznosi "<<c.at(i)<<"\n";
	}

	return 0;
}
