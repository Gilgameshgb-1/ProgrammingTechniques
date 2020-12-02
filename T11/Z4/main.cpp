#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>

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
	const int max_br_timova;
	int broj_timova = 0;
	Tim **timovi;
public:
	explicit Liga(int velicina_lige): max_br_timova(velicina_lige),timovi(new Tim*[velicina_lige]){};
	explicit Liga(std::initializer_list<Tim> lista_timova): max_br_timova(lista_timova.size()),timovi(new Tim*[lista_timova.size()]){
		for(auto it = lista_timova.begin();it!=lista_timova.end();it++){
			timovi[broj_timova] = new Tim(*it);
			broj_timova++;
		}
	};
	~Liga(){for(int i = 0;i<broj_timova;i++) delete timovi[i];delete[] timovi;};
	Liga(const Liga &l) : max_br_timova(l.max_br_timova){
		broj_timova = l.broj_timova;
		timovi = new Tim*[l.max_br_timova];
		for(int i = 0;i<l.broj_timova;i++){
			timovi[i] = new Tim(*l.timovi[i]);
		}
	};
	Liga(Liga &&l): max_br_timova(l.max_br_timova), broj_timova(l.broj_timova), timovi(l.timovi){
		l.timovi=nullptr;
	};
	Liga &operator = (const Liga &l){
		if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
		if(l.max_br_timova > broj_timova){
			for(int i = broj_timova;i<l.broj_timova;i++){
				timovi[i] = new Tim(*l.timovi[i]);
			}
		}else{
			for(int i = l.broj_timova;i<broj_timova;i++){
				delete timovi[i];timovi[i]=nullptr;
			}
		}
		broj_timova = l.broj_timova;
		for(int i = 0;i<broj_timova;i++) *timovi[i]=*l.timovi[i];
		return *this;
	};
	Liga &operator = (Liga &&l){
		if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
		for(int i = 0;i<max_br_timova;i++) delete timovi[i];delete[] timovi;
		broj_timova = l.broj_timova; timovi = l.timovi; l.timovi = nullptr;
		return *this;
	};
	void DodajNoviTim(const char ime_tima[]);
	void RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2);
	void IspisiTabelu();
};

void Liga::IspisiTabelu(){
	std::sort(timovi,timovi+broj_timova,[] (Tim *t1,Tim *t2)->bool{
	if(t1->DajBrojPoena()!=t2->DajBrojPoena()) return t1->DajBrojPoena()>t2->DajBrojPoena();
	else if(t1->DajGolRazliku()!=t2->DajGolRazliku()) return t1->DajGolRazliku()>t2->DajGolRazliku();
	int i = strcmp(t1->DajImeTima(),t2->DajImeTima());
	if(i<0 || i==0) return true;
	return false;
	});
	for(int i = 0;i<broj_timova;i++){
		timovi[i]->IspisiPodatke();
	}
}

void Liga::RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2){
	if(rezultat_1<0 || rezultat_2<0) throw std::range_error("Neispravan broj golova");
	int c = 0;
	for(int i = 0;i<broj_timova;i++){
		if(strcmp(tim1,timovi[i]->DajImeTima())==0) c++;
		if(strcmp(tim2,timovi[i]->DajImeTima())==0) c++;
	} if(c!=2) throw std::logic_error("Tim nije nadjen");
	for(int i = 0;i<broj_timova;i++){
		if(strcmp(tim1,timovi[i]->DajImeTima())==0){
			timovi[i]->ObradiUtakmicu(rezultat_1,rezultat_2);
		}
		if(strcmp(tim2,timovi[i]->DajImeTima())==0){
			timovi[i]->ObradiUtakmicu(rezultat_2,rezultat_1);
		}
	}
}
void Liga::DodajNoviTim(const char ime_tima[]){
	if(broj_timova+1>max_br_timova) throw std::range_error("Liga popunjena");
	timovi[broj_timova] = new Tim(ime_tima);
	broj_timova++;
}

int main ()
{
	
// AT7: Testiranje da li se operator dodjele ponasa konzistentno i da li je ispravno implementirano duboko kopiranje
 
Liga l1{"NK Zeljeznicar", "HSK Zrinjski", "FK Sarajevo", "FK Sloboda", "FK Krupa", "FK Radnik Bijeljina"};
l1.RegistrirajUtakmicu("NK Zeljeznicar", "HSK Zrinjski",2,0);

Liga l2 = l1;

std::cout << "Orginalna Liga za Prvaka: " << std::endl;
l1.IspisiTabelu();
std::cout << std::endl << "Kopija Lige za Prvaka: " << std::endl;
l2.IspisiTabelu();

l2.RegistrirajUtakmicu("FK Krupa", "FK Sloboda",1,1);

std::cout << std::endl << "Nakon izmjene kopije: " << std::endl << std::endl;

std::cout << "Orginalna Liga za Prvaka: " << std::endl;
l1.IspisiTabelu();  
std::cout << std::endl << "Kopija Lige za Prvaka: " << std::endl;
l2.IspisiTabelu();
	
	return 0;
}
