#include <iostream>
#include <string>

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
		std::cout<<"Student master studija "<<this->DajIme()<<" "<<this->DajPrezime()<<", sa brojem indeksa "<<this->DajBrojIndeksa()<<",\nzavrsio bachelor studij godine "<<datum<<",ima prosjek "<<this->DajProsjek()<<".";
	}
	ApstraktniStudent *DajKopiju() const override{return new StudentMaster(*this);}
};

int main ()
{
return 0;
}