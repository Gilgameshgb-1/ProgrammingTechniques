#include <iostream>
#include <cstring>
#include <iomanip>

class Tim
{
	char ime_tima[20];
	mutable int broj_odigranih = 0;
	mutable int broj_pobjeda = 0;
	mutable int broj_nerijesenih = 0;
	mutable int broj_poraza = 0;
	mutable int broj_datih = 0;
	mutable int broj_primljenih = 0;
	mutable int broj_poena = 0;
public:
	Tim (const char ime[]);
	void ObradiUtakmicu(int broj_datih,int broj_primljenih);
	const char* DajImeTima() const{return ime_tima;};
	int DajBrojPoena() const{return broj_poena;};
	int DajGolRazliku() const{return broj_datih-broj_primljenih;};
	void IspisiPodatke() const;
};

Tim::Tim(const char ime[]){
	if(std::strlen(ime)>19) throw std::range_error("Predugacko ime tima");
	std::strcpy(ime_tima,ime);
}

void Tim::ObradiUtakmicu(int broj_datih,int broj_primljenih){
	if(broj_datih<0 || broj_primljenih<0) throw std::range_error("Neispravan broj golova");
	Tim::broj_odigranih++;
	if(broj_datih>broj_primljenih){
		Tim::broj_pobjeda++;
		Tim::broj_poena+=3;
	}else if(broj_datih<broj_primljenih){
		Tim::broj_poraza++;
	}else{
		Tim::broj_nerijesenih++;
		Tim::broj_poena+=1;
	}
	Tim::broj_datih+=broj_datih;
	Tim::broj_primljenih+=broj_primljenih;
}

void Tim::IspisiPodatke() const{
	std::cout<<std::setw(20)<<std::left<<DajImeTima()<<std::setw(4)<<std::right<<std::setw(4)<<broj_odigranih
	<<std::setw(4)<<broj_pobjeda<<std::setw(4)<<broj_nerijesenih<<std::setw(4)<<broj_poraza<<std::setw(4)<<
	broj_datih<<std::setw(4)<<broj_primljenih<<std::setw(4)<<broj_poena<<std::endl;
}

int main ()
{
	return 0;
}
