/*
    TP 2018/2019: Tutorijal 5, Zadatak 5

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
#include <cmath>
#include <iomanip>

double F(double x)
{
	return x*x*x;
}

double G(double x)
{
	return 1/x;
}

double TrapeznoPravilo(double fun(double),double a,double b,int n)
{
	double fa=fun(a);
	double fb=fun(b);
	double rezultat(0);
	double suma(0);

	for(int k = 1; k < n; k++) {
		suma+=fun(a+(((b-a)/n))*k);
	}
	rezultat=((b-a)/n)*(0.5*fa+0.5*fb+suma);
	return rezultat;
}

int main ()
{
	int broj;
	const double PI(4 * std::atan(1));

	std::cout<<"Unesite broj podintervala: ";
	std::cin>>broj;
	std::cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:";
	std::cout<<"\n- Za funkciju sin x na intervalu (0,pi): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo(std::sin,0,PI,broj);
	std::cout<<"\n- Za funkciju x^3 na intervalu (0,10): "<<std::fixed<<std::setprecision(2)<<TrapeznoPravilo(F,0,10,broj);
	std::cout<<"\n- Za funkciju 1/x na intervalu (1,2): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo(G,1,2,broj);

	return 0;
}
