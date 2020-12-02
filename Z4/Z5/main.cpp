//TP 2018/2019: Zadaća 4, Zadatak 5
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <utility>

class Student
{
    int BrojIndeksa;
    std::string GodinaStudija,ImeiPrezime,Adresa,BrojTelefona;
public:
    Student(int brIndeksa,std::string godSt,std::string ime_i_prezime,std::string adresa,std::string brTel);
    int DajIndeks() const{return BrojIndeksa;};
    std::string DajGodinuStudija() const{return GodinaStudija;};
    std::string DajImePrezime() const{return ImeiPrezime;};
    std::string DajAdresu() const{return Adresa;};
    std::string DajTelefon() const{return BrojTelefona;};
    void Ispisi(){
        std::cout<<"\nBroj indeksa: "<<DajIndeks();
        std::cout<<"\nGodina studija: "<<DajGodinuStudija();
        std::cout<<"\nIme i prezime: "<<DajImePrezime();
        std::cout<<"\nAdresa: "<<DajAdresu();
        std::cout<<"\nTelefon: "<<DajTelefon();
    };
};

Student::Student(int brIndeksa,std::string godSt,std::string ime_i_prezime,std::string adresa,std::string brTel){
    if(((int)log10(brIndeksa)+1)!=5) throw std::domain_error("Neispravni parametri");
    BrojIndeksa = brIndeksa;
    std::vector<std::string> v{"1","2","3","1/B","2/B","3/B","1/M","2/M","1/D","2/D","3/D"};
    bool Kontrola = false;
    for(int i = 0;i<=10;i++){
        if(v[i].compare(godSt)==0){
            Kontrola=true;
        } 
    }
    
    if(Kontrola==false) throw std::domain_error("Neispravni parametri");    
    
    if(godSt == "1") GodinaStudija = "1/B";
    else if(godSt == "2") GodinaStudija = "2/B";
    else if(godSt == "3") GodinaStudija = "3/B";
    else GodinaStudija = godSt;
    
    unique_copy(ime_i_prezime.begin(),ime_i_prezime.end(),std::back_insert_iterator<std::string>(ImeiPrezime),[](char a,char b){return isspace(a) && isspace(b);});
    if(ImeiPrezime[0]==' '){
        for(int i = 0;i<ImeiPrezime.size()-1;i++){
            ImeiPrezime[i]=ImeiPrezime[i+1];
        }
        ImeiPrezime.resize(ImeiPrezime.size()-1);
    }
    int c = 0;
    for(int i = ImeiPrezime.size()-1;i>=0;i--){
        if(ImeiPrezime[i]==' ')  c++;
        if(ImeiPrezime[i]!=' ') break;
    }
    ImeiPrezime.resize(ImeiPrezime.size()-c);
    unique_copy(adresa.begin(),adresa.end(),std::back_insert_iterator<std::string>(Adresa),[](char a,char b){return isspace(a) && isspace(b);});
    if(Adresa[0]==' '){
        for(int i = 0;i<Adresa.size()-1;i++){
            Adresa[i]=Adresa[i+1];
        }
        Adresa.resize(Adresa.size()-1);
    }
    c = 0;
    for(int i = Adresa.size()-1;i>=0;i--){
        if(Adresa[i]==' ')  c++;
        if(Adresa[i]!=' ') break;
    }
    Adresa.resize(Adresa.size()-c);
    int c1=0;
    int c2=0;
    for(int i = 0;i<brTel.size();i++){
        if(brTel[i]=='/') c1++;
        if(brTel[i]=='-') c2++;
        if(brTel[i]!='/' && brTel[i]!='-' && (brTel[i]<'0' || brTel[i]>'9')) c1 = 0;
    }
    if(c1!=1 || c2!=1) throw std::domain_error("Neispravni parametri");
    BrojTelefona = brTel;
}

class Laptop{
    int ev_broj;
    std::string naziv;
    std::string karakteristike;
    Student* kod_koga_je = nullptr;
public:
    Laptop(int Broj,std::string Ime,std::string Karakt);
    int DajEvidencijskiBroj() const{return ev_broj;};
    std::string DajNaziv() const{return naziv;};
    std::string DajKarakteristike() const{return karakteristike;};
    void Zaduzi(Student &s){
        if(kod_koga_je != nullptr) throw std::domain_error("Laptop vec zaduzen");
        kod_koga_je = &s;
    };
    void Razduzi(){
        if(kod_koga_je!=nullptr){
        kod_koga_je = nullptr;
        }
    };
    bool DaLiJeZaduzen(){
        if(kod_koga_je==nullptr) return false;
        return true;
    };
    Student DajKodKogaJe(){
        if(kod_koga_je == nullptr) throw std::domain_error("Laptop nije zaduzen");
        return *kod_koga_je;
    };
    Student* DajPokKodKogaJe(){
        return kod_koga_je;
    };
    void Ispisi(){
        std::cout<<"\nEvidencijski broj: "<<DajEvidencijskiBroj();
        std::cout<<"\nNaziv: "<<DajNaziv();
        std::cout<<"\nKarakteristike: "<<DajKarakteristike();
    };
};

Laptop::Laptop(int Broj,std::string Ime,std::string Karakt){
    if(Broj < 0) throw std::domain_error("Neispravni parametri");
    ev_broj = Broj;
    naziv = Ime;
    karakteristike = Karakt;
}

class Administracija{
    std::map<int,Student*> mapastudenata;
    std::map<int,Laptop*> mapalaptopa;
public:
    Administracija(){};
    ~Administracija(){
        for(auto it = mapastudenata.begin();it!=mapastudenata.end();it++){
            delete it->second;
        }
        for(auto it = mapalaptopa.begin();it!=mapalaptopa.end();it++){
            delete it->second;
        }
    };
    void RegistrirajNovogStudenta(int brIndeksa,std::string godSt,std::string ime_i_prezime,std::string adresa,std::string brTel){
        if(mapastudenata.count(brIndeksa)!=0) throw std::domain_error("Student s tim indeksom vec postoji");
        mapastudenata.insert(std::make_pair(brIndeksa,new Student(brIndeksa,godSt,ime_i_prezime,adresa,brTel)));
    };
    void RegistrirajNoviLaptop(int Broj,std::string Ime,std::string Karakt){
        if(mapalaptopa.count(Broj)!=0) throw std::domain_error("Laptop s tim evidencijskim brojem vec postoji");
        mapalaptopa.insert(std::make_pair(Broj,new Laptop(Broj,Ime,Karakt)));
    };
    Student NadjiStudenta(int indeks){
        if(mapastudenata.count(indeks) == 0) throw std::domain_error("Student nije nadjen");
        auto it = mapastudenata.find(indeks);
        return *(it->second);
    };
    Student &NadjiStudenta(int indeks) const{
        if(mapastudenata.count(indeks) == 0) throw std::domain_error("Student nije nadjen");
        auto it = mapastudenata.find(indeks);
        return *(it->second);
    };
    Laptop NadjiLaptop(int Broj){
        if(mapalaptopa.count(Broj) == 0) throw std::domain_error("Laptop nije nadjen");
        auto it = mapalaptopa.find(Broj);
        return *(it->second);//ista prica
    }
    Laptop &NadjiLaptop(int Broj) const{
        if(mapalaptopa.count(Broj) == 0) throw std::domain_error("Laptop nije nadjen");
        auto it = mapalaptopa.find(Broj);
        return *(it->second);
    }
    void IzlistajStudente(){
        for(auto it = mapastudenata.begin(); it!=mapastudenata.end() ; it++){
            it->second->Ispisi();
            std::cout<<"\n";
        }
    };
    void IzlistajLaptope(){
        for(auto it = mapalaptopa.begin(); it!=mapalaptopa.end(); it++){
            it->second->Ispisi();
            if(it->second->DaLiJeZaduzen()==true){
                std::cout<<"\nZaduzio(la): "<<it->second->DajKodKogaJe().DajImePrezime()<<" ("<<it->second->DajKodKogaJe().DajIndeks()<<")";
            }
            std::cout<<"\n";
        }
    };
    void ZaduziLaptop(int indeks,int Broj){
        if(mapastudenata.count(indeks) == 0) throw std::domain_error("Student nije nadjen");
        if(mapalaptopa.count(Broj) == 0) throw std::domain_error("Laptop nije nadjen");
        auto it = mapalaptopa.find(Broj);
        auto st = mapastudenata.find(indeks);
        if(it->second->DaLiJeZaduzen() == true) throw std::domain_error("Laptop vec zaduzen");
        for(auto x = mapalaptopa.begin();x!=mapalaptopa.end();x++){
            if(x->second->DajPokKodKogaJe()!=nullptr){
                if(x->second->DajPokKodKogaJe()->DajIndeks() == indeks) throw std::domain_error("Student je vec zaduzio laptop");
            }
        }
        it->second->Zaduzi(*(st->second));
    };
    int NadjiSlobodniLaptop(){
        for(auto it = mapalaptopa.begin(); it!=mapalaptopa.end(); it++){
            if(it->second->DaLiJeZaduzen() == false) return it->second->DajEvidencijskiBroj();
        }
        throw std::domain_error("Nema slobodnih laptopa");
    };
    void RazduziLaptop(int Broj){
        auto it = mapalaptopa.find(Broj);
        if(it == mapalaptopa.end()) throw std::domain_error("Laptop nije nadjen");
        if(it->second->DaLiJeZaduzen() == false) throw std::domain_error("Laptop nije zaduzen");
        it->second->Razduzi();
    };
    void PrikaziZaduzenja(){
        int c = 0;
        for(auto it = mapalaptopa.begin(); it!=mapalaptopa.end(); it++){
                if(it->second->DaLiJeZaduzen() == true){
                c++;
                std::cout<<"Student "<<it->second->DajKodKogaJe().DajImePrezime()<<" ("<<it->second->DajKodKogaJe().DajIndeks()<<")"
                <<" zaduzio/la laptop broj "<<it->first<<std::endl;
            }
        }
        if(c==0)std::cout<<"Nema zaduzenja";
    };
};

int main ()
{  
    return 0;
}
