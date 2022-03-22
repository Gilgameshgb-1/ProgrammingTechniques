/*
    TP 2018/2019: Tutorijal 5, Zadatak 7

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
#include <vector>
#include <string>

template <typename IterTip>
auto SumaBloka(IterTip pocetak,IterTip iza_kraja) -> decltype(*pocetak+*pocetak)
{
	try {
		if(pocetak==iza_kraja) throw std::range_error("Blok je prazan");
	} catch(std::range_error e) {
		throw std::range_error("Blok je prazan");
		return 0;
	}
	auto suma = *pocetak;
	pocetak++;
	while(pocetak!=iza_kraja) suma+=*pocetak++;
	return suma;
}

int main ()
{
	return 0;
}
