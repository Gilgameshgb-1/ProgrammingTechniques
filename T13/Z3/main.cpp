#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class ApstraktniStudent{
	std::string ime;
	std::string prezime;
	int indeks;
	int brojPolozenih = 0;
	double prosjecnaOcjena = 5;
public: 
	virtual ~ApstraktniStudent(){};
    ApstraktniStudent(std::string ime,std::string prezime,int bri): ime(ime),prezime(prezime),indeks(bri){};
	std::string DajIme() const {return ime;};
	std::string DajPrezime() const{return prezime;};
	int DajBrojIndeksa() const{return indeks;};
	int DajBrojPolozenih() const{return brojPolozenih;};
	double DajProsjek() const{return prosjecnaOcjena;};
	void RegistrirajIspit(int ispit){
		if(ispit>10 || ispit<5) throw std::domain_error("\nNeispravna ocjena");
	if(ispit!=5){
				brojPolozenih++;
		if(brojPolozenih==1){
			prosjecnaOcjena = ispit;
		}else{
			prosjecnaOcjena = (prosjecnaOcjena*(brojPolozenih-1) + ispit)/brojPolozenih;
		}
	}
};
	void PonistiOcjene(){
		brojPolozenih = 0;
		prosjecnaOcjena = 5;
	};
	virtual void IspisiPodatke() const = 0;
	virtual ApstraktniStudent *DajKopiju() const = 0;
};

class StudentBachelor : public ApstraktniStudent{
public:
	StudentBachelor(std::string ime,std::string prezime,int indeks):ApstraktniStudent(ime,prezime,indeks){};
	void IspisiPodatke() const override{
		std::cout<<"Student bachelor studija "<<this->DajIme()<<" "<<this->DajPrezime()<<", sa brojem indeksa "<<this->DajBrojIndeksa()<<",\nima prosjek "<<this->DajProsjek()<<".\n";	
	};
	ApstraktniStudent *DajKopiju() const override{return new StudentBachelor(*this);}
};

class StudentMaster: public ApstraktniStudent{
	int datum;
public:
	StudentMaster(std::string ime,std::string prezime,int indeks,int godina):ApstraktniStudent(ime,prezime,indeks),datum(godina){}
	void IspisiPodatke() const override{
		std::cout<<"Student master studija "<<this->DajIme()<<" "<<this->DajPrezime()<<", sa brojem indeksa "<<this->DajBrojIndeksa()<<",\nzavrsio bachelor studij godine "<<datum<<",ima prosjek "<<this->DajProsjek()<<".\n";
	}
	ApstraktniStudent *DajKopiju() const override{return new StudentMaster(*this);}
};

class Fakultet {
	std::vector<ApstraktniStudent*> v;
public:
	Fakultet():v(0){}; 
	~Fakultet(){
		for(int i = 0;i<v.size();i++){
			delete v[i];
		}v.resize(0);	
	};
	Fakultet(const Fakultet &k){
		try{
			for(int i = 0;i<k.v.size();i++) v.push_back(k.v[i]->DajKopiju());
		}catch(...){
			for(int i = 0;i<v.size();i++) delete v[i];
		}
	}
	Fakultet(const Fakultet &&k){
		for(int i = 0;i<k.v.size();i++){
			v.push_back(k.v[i]->DajKopiju());
		}
		for(int i = 0;i<k.v.size();i++){
			delete k.v[i];
		}
	}
	Fakultet &operator = (const Fakultet &k){
		std::vector<ApstraktniStudent*> Novo;
		for(int i = 0;i<k.v.size();i++){
			Novo.push_back(k.v[i]->DajKopiju());
		}
		for(int i = 0;i<k.v.size();i++){
			delete k.v[i];
		}
		for(int i = 0;i<v.size();i++){
			delete v[i];
		}
		for(int i = 0;i<Novo.size();i++){
			v.push_back(Novo[i]);
		}
		return *this;
	}
	Fakultet &operator = (Fakultet &&k){
		std::swap(v,k.v);
		return *this;
	}
	void UpisiStudenta(std::string ime,std::string prezime,int bri){
		if(std::count_if(v.begin(),v.end(),[bri](ApstraktniStudent* x){
			if(x->DajBrojIndeksa()==bri) return true;
			return false;
		})) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
		v.push_back(new StudentBachelor(ime,prezime,bri));
	}
	void UpisiStudenta(std::string ime,std::string prezime,int bri,int godina){
		if(std::count_if(v.begin(),v.end(),[bri](ApstraktniStudent* x){
			if(x->DajBrojIndeksa()==bri) return true;
			return false;
		})) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
		v.push_back(new StudentMaster(ime,prezime,bri,godina));
	}
	void ObrisiStudenta(int bri){
		if(std::count_if(v.begin(),v.end(),[bri](ApstraktniStudent* x){
			if(x->DajBrojIndeksa()==bri) return true;
			return false;
		})==0) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		auto it = std::find_if(v.begin(),v.end(),[bri](ApstraktniStudent* x){
			if (x->DajBrojIndeksa()==bri) return true;
			return false;
		});
		delete *it;
		v.erase(it);
	}
	ApstraktniStudent &operator[](int bri){
		if(std::count_if(v.begin(),v.end(),[bri](ApstraktniStudent* x){
			if(x->DajBrojIndeksa()==bri) return true;
			return false;
		})==0) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		return **std::find_if(v.begin(),v.end(),[bri](ApstraktniStudent* x){
			if (x->DajBrojIndeksa()==bri) return true;
			return false;
		});
	}
	ApstraktniStudent &operator[](int bri) const{
		if(std::count_if(v.begin(),v.end(),[bri](ApstraktniStudent* x){
			if(x->DajBrojIndeksa()==bri) return true;
			return false;
		})==0) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		return **std::find_if(v.begin(),v.end(),[bri](ApstraktniStudent* x){
			if (x->DajBrojIndeksa()==bri) return true;
			return false;
		});
	}
	void IspisiSveStudente() const{
		Fakultet x(*this);
		std::sort(x.v.begin(),x.v.end(),[](ApstraktniStudent *p1,ApstraktniStudent *p2){
			if(p1->DajProsjek()>p2->DajProsjek()) return true;
			if(p1->DajProsjek()>p2->DajProsjek()) return false;
			if(p1->DajProsjek()==p2->DajProsjek()){
				if(p1->DajBrojIndeksa()<p2->DajBrojIndeksa()) return true;
				return false;
			}
		});
		for(auto z: x.v) z->IspisiPodatke();
	}
};
int main ()
{
 
return 0;
}