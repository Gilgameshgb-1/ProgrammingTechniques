//TP 2018/2019: Zadaća 4, Zadatak 3
#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <algorithm>
#include <exception>

bool IspravnostDatumaNovo(int d,int m,int g){
    int broj_dana[12]{31,28,31,30,31,30,31,31,30,31,30,31};
    if(g%4 == 0 && g%100 != 0 || g%400 == 0) broj_dana[1]++;
    if(g<1 || d<1 || m<1 || m>12 || d>broj_dana[m-1]) return false;
    return true;
}

class Datum{
    int d,m,g;
public:
    Datum(int dan,int mjesec,int godina){if(IspravnostDatumaNovo(dan,mjesec,godina)==false) throw std::domain_error("Neispravan datum");d=dan;m=mjesec;g=godina;};
    void Postavi(int dan,int mjesec,int godina){if(IspravnostDatumaNovo(dan,mjesec,godina)==false) throw std::domain_error("Neispravan datum");d=dan;m=mjesec;g=godina;};
    std::tuple<int,int,int> Ocitaj() const{return std::make_tuple(d,m,g);};
    void Ispisi() const{std::cout<<d<<"/"<<m<<"/"<<g;};
    friend class Pregled;
    friend class Pregledi;
};

bool IspravnostVremena(int s,int m){
    if(s<0 || s>23 || m>59 || m<0) return false;
    return true;
}

class Vrijeme{
    int h,m;
public:
    Vrijeme(int sati,int minute){if(IspravnostVremena(sati,minute)==false) throw std::domain_error("Neispravno vrijeme");h=sati;m=minute;};
    void Postavi(int sati,int minute){if(IspravnostVremena(sati,minute)==false) throw std::domain_error("Neispravno vrijeme");h=sati;m=minute;};
    std::pair<int,int> Ocitaj() const{return std::make_pair(h,m);};
    void Ispisi() const{std::cout<<std::setfill('0')<<std::right<<std::setw(2)<<h<<":"<<std::setw(2)<<m<<std::setfill(' ');/*<<std::cout.fill(' ')*/;};
    friend class Pregled;
    friend class Pregledi;
};

class Pregled{
    std::string ime_i_prezime;
    Datum dat_pregleda;
    Vrijeme vr_pregleda;
public:
    Pregled(const std::string &ime_pacijenta,const Datum &datum_pregleda,const Vrijeme &vrijeme_pregleda);
    Pregled(const std::string &ime_pacijenta,int dan_pregleda,int mjesec_pregleda,int godina_pregleda,int sati_pregleda,int minute_pregleda);
    void PromijeniPacijenta(const std::string &ime_pacijenta){ime_i_prezime = ime_pacijenta;};
    void PromijeniDatum(const Datum &novi_datum){dat_pregleda.Postavi(novi_datum.d,novi_datum.m,novi_datum.g);};
    void PromijeniVrijeme(const Vrijeme &novo_vrijeme){vr_pregleda.Postavi(novo_vrijeme.h,novo_vrijeme.m);};
    void PomjeriDanUnaprijed();
    void PomjeriDanUnazad();
    std::string DajImePacijenta() const{return ime_i_prezime;};
    Datum DajDatumPregleda() const{return dat_pregleda;};
    Vrijeme DajVrijemePregleda() const{return vr_pregleda;};
    static bool DolaziPrije(const Pregled &p1,const Pregled &p2);
    void Ispisi() const{std::cout<<std::setw(30)<<std::left<<ime_i_prezime;dat_pregleda.Ispisi();std::cout<<" ";vr_pregleda.Ispisi();std::cout<<std::endl/*<<std::cout.fill(' ')*/;};
    friend class Pregledi;
    friend class Datum;
};

Pregled::Pregled(const std::string &ime_pacijenta,const Datum &datum_pregleda,const Vrijeme &vrijeme_pregleda):
dat_pregleda(datum_pregleda),vr_pregleda(vrijeme_pregleda)
{
    ime_i_prezime=ime_pacijenta;
}

Pregled::Pregled(const std::string &ime_pacijenta,int dan_pregleda,int mjesec_pregleda,int godina_pregleda,int sati_pregleda,int minute_pregleda):
    dat_pregleda(dan_pregleda,mjesec_pregleda,godina_pregleda),vr_pregleda(sati_pregleda,minute_pregleda)
{
    ime_i_prezime = ime_pacijenta;
}

void Pregled::PomjeriDanUnaprijed(){
    Datum x = this->DajDatumPregleda();
    int broj_dana[12]{31,28,31,30,31,30,31,31,30,31,30,31};
    if(x.g%4 == 0 && x.g%100 != 0 || x.g%400 == 0) broj_dana[1]++;
    dat_pregleda.d++;
    if(dat_pregleda.d>broj_dana[dat_pregleda.m-1]){
        dat_pregleda.d = 1;
        dat_pregleda.m++;
        if(dat_pregleda.m==13) {
            dat_pregleda.m = 1;
            dat_pregleda.g++;
        }
    }
}

void Pregled::PomjeriDanUnazad(){
    Datum x = this->DajDatumPregleda();
    int broj_dana[12]{31,28,31,30,31,30,31,31,30,31,30,31};
    if(x.g%4 == 0 && x.g%100 != 0 || x.g%400 == 0) broj_dana[1]++;
    dat_pregleda.d--;
    if(dat_pregleda.d<=0){
        dat_pregleda.m--;
        if(dat_pregleda.m!=0){
            dat_pregleda.d = broj_dana[dat_pregleda.m-1];
        }
        if(dat_pregleda.m==0){
            dat_pregleda.d=31;
            dat_pregleda.m=12;
            dat_pregleda.g--;
        }
    }
}

bool Pregled::DolaziPrije(const Pregled &p1,const Pregled &p2){
    if(p1.dat_pregleda.g < p2.dat_pregleda.g) return true;
    else if(p1.dat_pregleda.m < p2.dat_pregleda.m && p1.dat_pregleda.g == p2.dat_pregleda.g) return true;
    else if(p1.dat_pregleda.d < p2.dat_pregleda.d && p1.dat_pregleda.g == p2.dat_pregleda.g && p1.dat_pregleda.m == p2.dat_pregleda.m) return true;
    else if(p1.dat_pregleda.d == p2.dat_pregleda.d && p1.dat_pregleda.g == p2.dat_pregleda.g && p1.dat_pregleda.m == p2.dat_pregleda.m){
        if(p1.vr_pregleda.h < p2.vr_pregleda.h) return true;
        else if(p1.vr_pregleda.h == p2.vr_pregleda.h && p2.vr_pregleda.m < p2.vr_pregleda.m) return true;
    }
    return false;
}

class Pregledi{
    const int kapacitet;
    int trenutni_broj_zakazanih = 0;
    Pregled **zakazani_pregledi;
public:
    explicit Pregledi(int max_broj_pregleda):kapacitet(max_broj_pregleda), zakazani_pregledi(new Pregled*[max_broj_pregleda]{}){};
    Pregledi(std::initializer_list<Pregled> spisak_pregleda): kapacitet(spisak_pregleda.size()), zakazani_pregledi(new Pregled*[spisak_pregleda.size()]{}){
        for(auto it = spisak_pregleda.begin(); it!=spisak_pregleda.end(); it++){
            zakazani_pregledi[trenutni_broj_zakazanih] = new Pregled(*it);
            trenutni_broj_zakazanih++;
        }
    };
    ~Pregledi(){for(int i = 0; i<trenutni_broj_zakazanih; i++) delete zakazani_pregledi[i];delete[] zakazani_pregledi;};
    Pregledi(const Pregledi &pregledi): kapacitet(pregledi.kapacitet){
        zakazani_pregledi = new Pregled*[pregledi.kapacitet];
        trenutni_broj_zakazanih = pregledi.trenutni_broj_zakazanih;
        for(int i = 0; i<pregledi.trenutni_broj_zakazanih; i++){
            zakazani_pregledi[i] = new Pregled(*pregledi.zakazani_pregledi[i]);
        }
    };
    Pregledi(Pregledi &&pregledi): kapacitet(pregledi.kapacitet),trenutni_broj_zakazanih(pregledi.trenutni_broj_zakazanih),zakazani_pregledi(pregledi.zakazani_pregledi){
        pregledi.zakazani_pregledi = nullptr;
    };
    Pregledi &operator = (const Pregledi &pregledi){
        if(&pregledi != this){
        trenutni_broj_zakazanih = pregledi.trenutni_broj_zakazanih;
        if(pregledi.trenutni_broj_zakazanih > trenutni_broj_zakazanih){
            for(int i = trenutni_broj_zakazanih; i<pregledi.trenutni_broj_zakazanih;i++){
                zakazani_pregledi[i] = new Pregled(*pregledi.zakazani_pregledi[i]);
            }
        }else{
            for(int i = pregledi.trenutni_broj_zakazanih;i<trenutni_broj_zakazanih;i++){
                delete zakazani_pregledi[i];zakazani_pregledi[i]=nullptr;
            }
        }
        for(int i = 0;i<trenutni_broj_zakazanih;i++){
            *zakazani_pregledi[i] = *pregledi.zakazani_pregledi[i];
        }
        }
        return *this;
    };
    Pregledi &operator = (Pregledi &&pregledi){
        for(int i = 0;i<trenutni_broj_zakazanih;i++) delete zakazani_pregledi[i];delete[] zakazani_pregledi;
        trenutni_broj_zakazanih = pregledi.trenutni_broj_zakazanih;zakazani_pregledi = pregledi.zakazani_pregledi;pregledi.zakazani_pregledi=nullptr;
        return *this;
    }
    void RegistrirajPregled(const std::string &ime_pacijenta, const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda);
    void RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda, int mjesec_pregleda, int godina_pregleda, int sati_pregleda, int minute_pregleda);
    void RegistrirajPregled(Pregled *pregled);
    int DajBrojPregleda() const{return trenutni_broj_zakazanih;};
    int DajBrojPregledaNaDatum(const Datum &datum) const;
    Pregled &DajNajRanijiPregled();
    Pregled DajNajranijiPregled() const;
    void IsprazniKolekciju();
    void ObrisiNajranijiPregled();
    void ObrisiPregledePacijenta(const std::string &ime_pacijenta);
    void IspisiPregledeNaDatum(const Datum &datum) const;
    void IspisiSvePreglede() const;
};

void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta, const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda){
    if(trenutni_broj_zakazanih+1>kapacitet) throw std::range_error("Dostignut maksimalni broj pregleda");
    zakazani_pregledi[trenutni_broj_zakazanih] = new Pregled(ime_pacijenta, datum_pregleda, vrijeme_pregleda);
    trenutni_broj_zakazanih++;
}

void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda, int mjesec_pregleda, int godina_pregleda, int sati_pregleda, int minute_pregleda){
    if(trenutni_broj_zakazanih+1>kapacitet) throw std::range_error("Dostignut maksimalni broj pregleda");
    zakazani_pregledi[trenutni_broj_zakazanih] = new Pregled(ime_pacijenta, dan_pregleda, mjesec_pregleda, godina_pregleda, sati_pregleda, minute_pregleda);
}

void Pregledi::RegistrirajPregled(Pregled *pregled){
    if(trenutni_broj_zakazanih+1>kapacitet) throw std::range_error("Dostignut maksimalni broj pregleda");
    zakazani_pregledi[trenutni_broj_zakazanih] = pregled;
    trenutni_broj_zakazanih++;
}

int Pregledi::DajBrojPregledaNaDatum(const Datum &datum) const{
    std::count_if(zakazani_pregledi,zakazani_pregledi+trenutni_broj_zakazanih,[datum](const Pregled *neki)->bool{
        if(neki->dat_pregleda.d == datum.d && neki->dat_pregleda.m == datum.m && neki->dat_pregleda.g == datum.g) return true;
        return false;
    });
}

void Pregledi::IsprazniKolekciju(){
/*    if(trenutni_broj_zakazanih == 0) throw std::range_error("Prazna kolekcija");*/
    for(int i = 0;i<trenutni_broj_zakazanih;i++){
        delete zakazani_pregledi[i];
        zakazani_pregledi[i]=nullptr;
    }
}

Pregled& Pregledi::DajNajRanijiPregled(){
    if(trenutni_broj_zakazanih == 0) throw std::domain_error("Nema registriranih pregleda");
    auto x = std::min_element(zakazani_pregledi,zakazani_pregledi+trenutni_broj_zakazanih,[](const Pregled *p1,const Pregled *p2)->bool{
        if(p1->dat_pregleda.g < p2->dat_pregleda.g) return true;
        else if(p1->dat_pregleda.m < p2->dat_pregleda.m && p1->dat_pregleda.g == p2->dat_pregleda.g) return true;
        else if(p1->dat_pregleda.d < p2->dat_pregleda.d && p1->dat_pregleda.g == p2->dat_pregleda.g && p1->dat_pregleda.m == p2->dat_pregleda.m) return true;
        else if(p1->dat_pregleda.d == p2->dat_pregleda.d && p1->dat_pregleda.g == p2->dat_pregleda.g && p1->dat_pregleda.m == p2->dat_pregleda.m){
        if(p1->vr_pregleda.h < p2->vr_pregleda.h) return true;
        else if(p1->vr_pregleda.h == p2->vr_pregleda.h && p2->vr_pregleda.m < p2->vr_pregleda.m) return true;
        }
        return false;
    });
    return **x;
}

Pregled Pregledi::DajNajranijiPregled() const{
    if(trenutni_broj_zakazanih == 0) throw std::domain_error("Nema registriranih pregleda");
    auto x = std::min_element(zakazani_pregledi,zakazani_pregledi+trenutni_broj_zakazanih,[](const Pregled *p1,const Pregled *p2)->bool{
        if(p1->dat_pregleda.g < p2->dat_pregleda.g) return true;
        else if(p1->dat_pregleda.m < p2->dat_pregleda.m && p1->dat_pregleda.g == p2->dat_pregleda.g) return true;
        else if(p1->dat_pregleda.d < p2->dat_pregleda.d && p1->dat_pregleda.g == p2->dat_pregleda.g && p1->dat_pregleda.m == p2->dat_pregleda.m) return true;
        else if(p1->dat_pregleda.d == p2->dat_pregleda.d && p1->dat_pregleda.g == p2->dat_pregleda.g && p1->dat_pregleda.m == p2->dat_pregleda.m){
        if(p1->vr_pregleda.h < p2->vr_pregleda.h) return true;
        else if(p1->vr_pregleda.h == p2->vr_pregleda.h && p2->vr_pregleda.m < p2->vr_pregleda.m) return true;
        }
        return false;
    });
    return **x;
}

void Pregledi::ObrisiNajranijiPregled(){
    if(trenutni_broj_zakazanih == 0) throw std::range_error("Prazna kolekcija");
    auto x = DajNajRanijiPregled();
    std::string ime = x.DajImePacijenta();
    Datum d1 = x.DajDatumPregleda();
    Vrijeme v1 = x.DajVrijemePregleda();
    for(int i = 0;i<trenutni_broj_zakazanih;i++){
        Datum d2 = zakazani_pregledi[i]->DajDatumPregleda();
        Vrijeme v2 = zakazani_pregledi[i]->DajVrijemePregleda();
        if(zakazani_pregledi[i]->DajImePacijenta() == ime &&  d2.d == d1.d &&  d2.m == d1.m && d2.g == d1.g && v1.h == v2.h && v1.m == v2.m){
            delete zakazani_pregledi[i];
            for(int j = i;j<trenutni_broj_zakazanih-1;j++){
                zakazani_pregledi[j]=zakazani_pregledi[j+1];
            }
        }
    }
    trenutni_broj_zakazanih--;
}

void Pregledi::ObrisiPregledePacijenta(const std::string &ime_pacijenta){
    if(trenutni_broj_zakazanih == 0) throw std::range_error("Prazna kolekcija");
    for(int i = 0;i<trenutni_broj_zakazanih;i++){
        Datum d2 = zakazani_pregledi[i]->DajDatumPregleda();
        Vrijeme v2 = zakazani_pregledi[i]->DajVrijemePregleda();
        if(zakazani_pregledi[i]->DajImePacijenta() == ime_pacijenta){
            delete zakazani_pregledi[i];
            for(int j = i;j<trenutni_broj_zakazanih-1;j++){
                zakazani_pregledi[j]=zakazani_pregledi[j+1];
            }
            trenutni_broj_zakazanih--;
        }
    }
}
void Pregledi::IspisiPregledeNaDatum(const Datum &datum) const{
    Pregled** ispis;
    ispis = zakazani_pregledi;
    std::sort(ispis,ispis+trenutni_broj_zakazanih,[](const Pregled *p1,const Pregled *p2)->bool{
        if(p1->dat_pregleda.g < p2->dat_pregleda.g) return true;
        else if(p1->dat_pregleda.m < p2->dat_pregleda.m && p1->dat_pregleda.g == p2->dat_pregleda.g) return true;
        else if(p1->dat_pregleda.d < p2->dat_pregleda.d && p1->dat_pregleda.g == p2->dat_pregleda.g && p1->dat_pregleda.m == p2->dat_pregleda.m) return true;
        else if(p1->dat_pregleda.d == p2->dat_pregleda.d && p1->dat_pregleda.g == p2->dat_pregleda.g && p1->dat_pregleda.m == p2->dat_pregleda.m){
        if(p1->vr_pregleda.h < p2->vr_pregleda.h) return true;
        else if(p1->vr_pregleda.h == p2->vr_pregleda.h && p2->vr_pregleda.m < p2->vr_pregleda.m) return true;
        }
        return false;
    });
    for(int i = 0;i<trenutni_broj_zakazanih;i++){
        auto x = ispis[i]->DajDatumPregleda();
        if(datum.d ==x.d  && datum.m ==x.m && datum.g==x.g){
            ispis[i]->Ispisi();
        }
    }   
}

void Pregledi::IspisiSvePreglede() const{
    Pregled** ispis;
    ispis = zakazani_pregledi;
    std::sort(ispis,ispis+trenutni_broj_zakazanih,[](const Pregled *p1,const Pregled *p2)->bool{
        if(p1->dat_pregleda.g < p2->dat_pregleda.g) return true;
        else if(p1->dat_pregleda.m < p2->dat_pregleda.m && p1->dat_pregleda.g == p2->dat_pregleda.g) return true;
        else if(p1->dat_pregleda.d < p2->dat_pregleda.d && p1->dat_pregleda.g == p2->dat_pregleda.g && p1->dat_pregleda.m == p2->dat_pregleda.m) return true;
        else if(p1->dat_pregleda.d == p2->dat_pregleda.d && p1->dat_pregleda.g == p2->dat_pregleda.g && p1->dat_pregleda.m == p2->dat_pregleda.m){
        if(p1->vr_pregleda.h < p2->vr_pregleda.h) return true;
        else if(p1->vr_pregleda.h == p2->vr_pregleda.h && p2->vr_pregleda.m < p2->vr_pregleda.m) return true;
        }
        return false;
    });
    for(int i = 0;i<trenutni_broj_zakazanih;i++){
        ispis[i]->Ispisi();
    }   
}

int main ()
{
    int max;
    std::cout<<"Unesite maksimalan broj pregleda: ";
    std::cin>>max;
    int i = 0;
    Pregledi baza(max);
    while(i<max){
        std::cin.ignore(1000,'\n');
        std::cout<<"Unesite ime novog pacijenta ili 'kraj' za zavrsetak unosa: ";
        std::string temp;
        std::getline(std::cin,temp);
        if(temp=="kraj") break;
        int d,m,g;
        std::cout<<"Unesite dan mjesec i godinu pregleda: ";
        std::cin>>d>>m>>g;
        int sat,min;
        std::cout<<"Unesite sate i minute pregleda: ";
        std::cin>>sat>>min;
        Datum date(d,m,g);
        Vrijeme v(sat,min);
        try{
            baza.RegistrirajPregled(temp,date,v);
        }catch(std::domain_error e){
            std::cout<<e.what();
            i--;
        }catch(std::range_error e){
            std::cout<<e.what();
            i--;
        }
        i++;
    }
    std::cout<<"Trenutno su registrovani sljedeci pregledi\n";
    baza.IspisiSvePreglede();
    while(1){
        std::cout<<"\n";
        std::cout<<"\nOdaberite jednu od sljedecih opcija";
        std::cout<<"\n1 - Broj pregleda na datum\n2 - Najraniji pregled\n3 - Obrisi pregled pacijenta\n4 - Obrisi najraniji pregled"<<
        "\n5 - Ispisi sve pregleda na datum\n6 - Ispisi sve preglede\n7 - Kraj programa";
        int opcija;
        std::cin>>opcija;
        if(opcija==1){
            std::cout<<"\nUnesite dan mjesec i godinu :";
            std::cin.ignore(100,'\n');
            int d,m,g;
            std::cin>>d>>m>>g;
            Datum date(d,m,g);
            std::cout<<" Broj pregleda na datum "<<d<<" "<<m<<" "<<g<<" je: "<<baza.DajBrojPregledaNaDatum(date);
        }
        if(opcija==2){
            Pregled neki = baza.DajNajRanijiPregled();
            std::cout<<"\nNajraniji pregled je:\n";
            neki.Ispisi();
        }
        if(opcija==3){
            std::cout<<"\nUnesite ime pacijenta: ";
            std::string temp;
            std::cin.ignore(100,'\n');
            std::getline(std::cin,temp);
            int y = baza.DajBrojPregleda();
            baza.ObrisiPregledePacijenta(temp);
            int x = baza.DajBrojPregleda();
            std::cout<<"Uspjesno obrisano "<<y-x<<" pregleda";
        }
        if(opcija==4){
            baza.ObrisiNajranijiPregled();
            std::cout<<"\nNajraniji pregled uspjesno obrisan";
        }
        if(opcija==5){
            std::cout<<"\nUnesite dan mjesec i godinu : ";
            int d,m,g;
            std::cin>>d>>m>>g;
            Datum date(d,m,g);
            std::cout<<"Pregledi na datum "<<d<<" "<<m<<" "<<g<<" su:\n";
            baza.IspisiPregledeNaDatum(date);
        }
        if(opcija==6){
            std::cout<<"\n";
            baza.IspisiSvePreglede();
        }
        if(opcija==7){
            break;
        }
    }
	return 0;
}