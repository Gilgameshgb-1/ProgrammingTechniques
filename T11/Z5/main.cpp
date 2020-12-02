#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <memory>

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

class Liga
{
	std::vector<std::shared_ptr<Tim>> timovi;
public:
	explicit Liga(){};
	explicit Liga(std::initializer_list<Tim> lista_timova){
		for(auto it = lista_timova.begin();it!=lista_timova.end();it++){
			std::shared_ptr<Tim> a(new Tim(*it)); 
			timovi.push_back(std::move(a));
		}
	};
	~Liga() = default;/*{for(int i = 0;i<timovi.size();i++) delete timovi[i];delete[] timovi;};*/
	Liga(const Liga &l){
		timovi.clear();
		for(int i = 0;i<l.timovi.size();i++){
			std::shared_ptr<Tim> a(new Tim(*l.timovi[i]));
			timovi.push_back(a);
		}
	};
	Liga(Liga &&l){
		timovi=std::move(l.timovi);
	};
	Liga &operator = (const Liga &l){
		timovi=std::move(l.timovi);
		return *this;
	};
	Liga &operator = (Liga &&l){
		timovi=std::move(l.timovi);
		return *this;
	};
	void DodajNoviTim(const char ime_tima[]);
	void RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2);
	void IspisiTabelu();
};

void Liga::IspisiTabelu(){
	std::sort(timovi.begin(),timovi.end(),[] (std::shared_ptr<Tim> t1,std::shared_ptr<Tim> t2)->bool{
	if(t1->DajBrojPoena()!=t2->DajBrojPoena()) return t1->DajBrojPoena()>t2->DajBrojPoena();
	else if(t1->DajGolRazliku()!=t2->DajGolRazliku()) return t1->DajGolRazliku()>t2->DajGolRazliku();
	int i = strcmp(t1->DajImeTima(),t2->DajImeTima());
	if(i<0 || i==0) return true;
	return false;
	});
	for(int i = 0;i<timovi.size();i++){
		timovi[i]->IspisiPodatke();
	}
}

void Liga::RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2){
	if(rezultat_1<0 || rezultat_2<0) throw std::range_error("Neispravan broj golova");
	int c = 0;
	for(int i = 0;i<timovi.size();i++){
		if(strcmp(tim1,timovi[i]->DajImeTima())==0) c++;
		if(strcmp(tim2,timovi[i]->DajImeTima())==0) c++;
	} if(c!=2) throw std::logic_error("Tim nije nadjen");
	for(int i = 0;i<timovi.size();i++){
		if(strcmp(tim1,timovi[i]->DajImeTima())==0){
			timovi[i]->ObradiUtakmicu(rezultat_1,rezultat_2);
		}
		if(strcmp(tim2,timovi[i]->DajImeTima())==0){
			timovi[i]->ObradiUtakmicu(rezultat_2,rezultat_1);
		}
	}
}
void Liga::DodajNoviTim(const char ime_tima[]){
	std::shared_ptr<Tim> a(new Tim(ime_tima));
	timovi.push_back(a);
}

int main ()
{
	return 0;
}
