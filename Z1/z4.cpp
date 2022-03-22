/* TP, 2018/2019, Zadaća 1, Zadatak 4

	NAPOMENA: ulaz/izlaz za zadatke je specificiran
	javnim autotestovima. Zalbe za ne analiziranje testova
	se ne uvazavaju!

	NAPOMENA: nece svi (javni) testovi sa zamgera biti
	dostupni na c9.
*/
#include <iostream>
#include <vector>
#include <string>

typedef std::vector<std::string> StringVektor;

bool Simetricnost(std::string s)
{
	if(s.size()==1) return false;
	for(int i = 0; i<s.size(); i++) {
		s.at(i)=char(std::toupper(s.at(i)));
	}
	for(int i = 0; i<s.size()/2; i++ ) {
		if(s.at(i)!=s.at(s.size()-1-i)) return false;
	}
	return true;
}

bool TempPrazan(std::string s)
{
	int i = 0;
	for(i=0; i<s.size(); i++) {
		if(s.at(i)!=' ') return false;
	}
	return true;
}

StringVektor NadjiSimetricneRijeci(std::string s)
{
	StringVektor Vracanje;
	std::string temp = "";
	for(int i = 0; i <s.size(); i++) {
		if(s.at(i)==' ' || (s.at(i)>=0 && s.at(i)<65) || (s.at(i)>122 && s.at(i)<=127)) {
			if(Simetricnost(temp)==true && TempPrazan(temp)==false) Vracanje.push_back(temp);
			temp="";
		} else {
			temp=temp+s.at(i);
		}
	}
	if(Simetricnost(temp)==true && TempPrazan(temp)==false) Vracanje.push_back(temp);
	return Vracanje;
}

int main ()
{
		std::string unos;

		std::cout<<"Unesite recenicu:";
		std::getline(std::cin,unos);

		StringVektor v = NadjiSimetricneRijeci(unos);
		if(v.size()!=0) {
			std::cout<<"\nSimetricne rijeci unutar recenice su:";
			for(int i = 0; i<v.size(); i++) {
				std::cout<<"\n"<<v.at(i);
			}
		} else {
			std::cout<<"\nRecenica ne sadrzi simetricne rijeci!";
		}
	return 0;
}
