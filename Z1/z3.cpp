/* TP, 2018/2019, Zadaća 1, Zadatak 3

	NAPOMENA: ulaz/izlaz za zadatke je specificiran
	javnim autotestovima. Zalbe za ne analiziranje testova
	se ne uvazavaju!

	NAPOMENA: nece svi (javni) testovi sa zamgera biti
	dostupni na c9.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

typedef std::vector<std::vector<int>> Matrica;

Matrica KreirajMatricu(int broj_redova, int broj_kolona)
{
	return Matrica(broj_redova,std::vector<int>(broj_kolona));
}

int BrojRedova(Matrica A)
{
	return A.size();
}

int BrojKolona(Matrica A)
{
	return A.at(0).size();
}

bool IspravnostMatrice(Matrica A)
{
	int broj = A.at(0).size();
	for(int i = 0; i < A.size() ; i++) {
		if(broj!=A.at(i).size()) return false;
	}
	return true;
}

Matrica KroneckerovProizvod(Matrica A,Matrica B)
{
	if(BrojRedova(A)==0 || BrojRedova(B)==0){
		Matrica m(0);
		return m;
	}
	Matrica C;
	std::vector<int> v;
	try {
		if(IspravnostMatrice(A)==false && IspravnostMatrice(B)==false) throw std::domain_error("Parametri nemaju formu matrice");
		if(IspravnostMatrice(A)==false) throw std::domain_error("Prvi parametar nema formu matrice");
		if(IspravnostMatrice(B)==false) throw std::domain_error("Drugi parametar nema formu matrice");
	} catch(std::domain_error izuzetak) {
		std::cout<<izuzetak.what()<<"\n";
		Matrica n(0);
		return n;
	}
	C=KreirajMatricu(BrojRedova(A)*BrojRedova(B),BrojKolona(A)*BrojKolona(B));
	for(int ared = 0; ared < BrojRedova(A); ared++) {
		for(int bred = 0; bred < BrojRedova(B); bred++) {
			for(int akolona = 0; akolona < BrojKolona(A); akolona++) {
				for(int bkolona = 0; bkolona < BrojKolona(B); bkolona++) {
					v.push_back(A.at(ared).at(akolona)*B.at(bred).at(bkolona));
				}
			}
		}
	}
	int z = 0;
	for(int i = 0 ; i < BrojRedova(C) ; i++ ) {
		for(int j = 0 ; j < BrojKolona(C) ; j++ ) {
			C.at(i).at(j)=v.at(z);
			z++;
		}
	}
	return C;
}

int NajvecaSirina(Matrica m)
{
	int broj = m.at(0).at(0);
	int brojtemp = 0;
	int brojac1=0,brojac=0;
	if(broj<0) brojac++;
	broj=abs(broj);
	while(broj>0) {
		broj/=10;
		brojac++;
	}
	for(int i = 0; i<BrojRedova(m); i++) {
		for(int j = 0; j<BrojKolona(m); j++) {
			brojtemp=m.at(i).at(j);
			if(brojtemp<0) brojac1++;
			if(brojtemp==std::numeric_limits<int>::min()) return 1;
			brojtemp=abs(brojtemp);
			while(brojtemp>0) {
				brojtemp/=10;
				brojac1++;
			}
			if(brojac1>brojac) {
				brojac=brojac1;
			}
			brojac1=0;
		}
	}
	return brojac;
}

int main ()
{
	Matrica A;
	Matrica B;
		int broj_redova,broj_kolona;

		std::cout<<"Unesite dimenzije prve matrice:";
		std::cin>>broj_redova>>broj_kolona;
		A=KreirajMatricu(broj_redova,broj_kolona);
		std::cin.ignore(10000,'\n');
		std::cout<<"\nUnesite elemente prve matrice:";
		for(int i = 0 ; i < broj_redova ; i++ ) {
			for(int j = 0 ; j < broj_kolona ; j++ ) {
				int broj;
				std::cin>>broj;
				A.at(i).at(j)=broj;
			}
		}
		std::cout<<"\nUnesite dimenzije druge matrice:";
		std::cin>>broj_redova>>broj_kolona;
		B=KreirajMatricu(broj_redova,broj_kolona);
		std::cin.ignore(10000,'\n');
		std::cout<<"\nUnesite elemente druge matrice:";
		for(int i = 0 ; i < broj_redova ; i++ ) {
			for(int j = 0 ; j < broj_kolona ; j++ ) {
				int broj;
				std::cin>>broj;
				B.at(i).at(j)=broj;
			}
		}
		Matrica Ispis = KroneckerovProizvod(A,B);
		int sirina = NajvecaSirina(Ispis);
		std::cout<<"\nNjihov Kroneckerov proizvod glasi:";
		std::cout<<"\n";
		for(int i = 0 ; i< BrojRedova(Ispis); i++ ) {
			for(int j = 0; j< BrojKolona(Ispis); j++ ) {
				std::cout<<std::setw(sirina+1)<<Ispis.at(i).at(j);
			}
			std::cout<<"\n";
		}
	return 0;
}
