#include <iostream>

class StedniRacun
{
	double pocvrijednost;
	static int b1;
	static int b2;
public:
	StedniRacun(double x = 0) {if(x<0) throw std::logic_error("Nedozvoljeno pocetno stanje"); pocvrijednost = x;b1++;}
	StedniRacun(const StedniRacun &x){pocvrijednost = x.pocvrijednost;b1++;}
	~StedniRacun(){b2++;}
	void Ulozi(double y){if(y+pocvrijednost<0) throw std::logic_error("Transakcija odbijena"); pocvrijednost += y;};
	void Podigni(double y){if(y>pocvrijednost) throw std::logic_error("Transakcija odbijena"); pocvrijednost = pocvrijednost-y;};
	void ObracunajKamatu(double z){if(z<0) throw std::logic_error("Nedozvoljena kamatna stopa"); pocvrijednost = pocvrijednost + pocvrijednost*(z/100);}
	double DajStanje() const {return pocvrijednost;}
	static int DajBrojKreiranih(){return b1;};
	static int DajBrojAktivnih(){return b1-b2;};
};

int StedniRacun::b1=0;
int StedniRacun::b2=0;

int main ()
{

	return 0;
}
