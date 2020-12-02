#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

class GradjaninBiH
{   
 //   GradjaninBiH::Pol spol;//Kako ovo radi unutar klase, kako se deklarise ?
    int spol;
    std::string imeipr;
    long long int jedmatbroj;
    int dan;
    int mjesec;
    int godina;
    int regija;
    GradjaninBiH* prethodni;
    static GradjaninBiH* posljednji;
public:
    enum Pol{Musko,Zensko};
    GradjaninBiH(std::string ime_i_prezime, long long int jmbg);
    GradjaninBiH(const GradjaninBiH &neko) = delete;
    GradjaninBiH(GradjaninBiH &&neko) = delete;
    GradjaninBiH &operator = (const GradjaninBiH &neko) = delete;
    GradjaninBiH &operator = (GradjaninBiH &&neko) = delete;
    ~GradjaninBiH(){
        if(this == posljednji){
            posljednji = prethodni;
        }else{
            GradjaninBiH* nesto = posljednji;
            while(nesto->prethodni !=nullptr && nesto->prethodni!=this){
                nesto = nesto->prethodni;
            }
            nesto->prethodni = this->prethodni;
        }
    };
    GradjaninBiH(std::string ime_i_prezime, int dan_rodjenja,int mjesec_rodjenja,
    int godina_rodjenja,int sifra_regije, Pol pol);
    std::string DajImeIPrezime() const {return imeipr;};
    long long int DajJMBG() const{return jedmatbroj;};
    int DajDanRodjenja() const{return dan;};
    int DajMjesecRodjenja() const{return mjesec;};
    int DajGodinuRodjenja() const{return godina;};
    int DajSifruRegije() const{return regija;};
    Pol DajPol() const{if(spol>=0 && spol<=499)return Musko;else return Zensko;};
    //potrebno zabraniti kopiranje = delete;
    void PromijeniImeIPrezime(std::string novo_ime){imeipr=novo_ime;};
};

GradjaninBiH* GradjaninBiH::posljednji = nullptr;

bool IspravnostDatuma(int d,int m,int g){
    if(g>=0 && g<=17) g = g+2000; 
    else if(g>=917 && g<=999) g = g+1000;
    else return false;
    int broj_dana[12]{31,28,31,30,31,30,31,31,30,31,30,31};
    if(g%4 == 0 && g%100 != 0 || g%400 == 0) broj_dana[1]++;
    if(g<1 || d<1 || m<1 || m>12 || d>broj_dana[m-1]) return false;
    return true;
}

bool IspravnostDatumaNovo(int d,int m,int g){
    int broj_dana[12]{31,28,31,30,31,30,31,31,30,31,30,31};
    if(g%4 == 0 && g%100 != 0 || g%400 == 0) broj_dana[1]++;
    if(g<1 || d<1 || m<1 || m>12 || d>broj_dana[m-1]) return false;
    return true;
}

GradjaninBiH::GradjaninBiH(std::string ime_i_prezime,long long int jmbg){//konstruktor samo sa JMBG
        imeipr=ime_i_prezime;
        long long int Sacuvanje = jmbg;
        int brojevi[13]{};
        for(int i = 12; i>=0; i--){
                brojevi[i] = jmbg % 10;
                jmbg/=10;
        }
        int c12 = brojevi[0]*10+brojevi[1];//dan
        int c34 = brojevi[2]*10+brojevi[3];//mjesec
        int c567 = brojevi[4]*100+brojevi[5]*10+brojevi[6];//godina
        if(IspravnostDatuma(c12,c34,c567)==false) throw std::logic_error("\nJMBG nije validan");
        int c89 = brojevi[7]*10+brojevi[8];//sifra regije
        int c101112 = brojevi[9]*100+brojevi[10]*10+brojevi[11];//sifra za spol
        int c13 = 0;//kontrola
        int temp = 0;
        for(int i = 0;i<6;i++){
            temp+=((7-i)*(brojevi[i]+brojevi[i+6]));
        }
        c13 = 11 - temp%11;
        if(c13 == 11) c13=0;
        if(Sacuvanje%10 != c13) throw std::logic_error("\nJMBG nije validan");
        if(c13 == 10) throw std::logic_error("\nJMBG nije validan");
        //ne smijemo imati duplikate ljudi, tj ne smijemo imati jednak JMBG
        if(posljednji == nullptr){
            jedmatbroj = Sacuvanje;
            dan = c12;
            mjesec = c34;
            if(c567>=0 && c567<=17) c567 = c567+2000; 
            else if(c567>=917 && c567<=999) c567 = c567+1000;
            godina = c567;
            regija = c89;
            spol = c101112;
            imeipr = ime_i_prezime;
            posljednji = this;
            prethodni = nullptr;
        }else{
            GradjaninBiH* temp = posljednji;
            bool ctrl = false;
/*            while(temp!=nullptr){ //prolazimo kroz nasu "listu", temp->jedmatbroj je ustvari nas trenacni objekat
                if(Sacuvanje==temp->jedmatbroj){
                    ctrl = true;
                }
                temp = temp->prethodni;//ovo je ekvivalentno i--, temp->prethodni je ustvari prethodni objekat u odnosu na trenutacni
            }*/
           // if(ctrl==true){throw std::logic_error("Vec postoji gradjanin sa istim JMBG");}
            /*else*/{
                jedmatbroj = Sacuvanje;
                dan = c12;
                mjesec = c34;
                if(c567>=0 && c567<=17) c567 = c567+2000; //konverzija u normalnu godinu
                else if(c567>=917 && c567<=999) c567 = c567+1000;
                godina = c567;
                regija = c89;
                spol = c101112;
                imeipr = ime_i_prezime;
                this->prethodni = &(*posljednji);
                posljednji = this;
            }
        }
    }


GradjaninBiH::GradjaninBiH(std::string ime_i_prezime, int dan_rodjenja,int mjesec_rodjenja,
int godina_rodjenja,int sifra_regije, Pol pol){//veeeliki kontstruktor
        if(IspravnostDatumaNovo(dan_rodjenja,mjesec_rodjenja,godina_rodjenja)==false || 
        sifra_regije<0 || sifra_regije>99){
          throw std::logic_error("Neispravni podaci");
        } 
        int brojevi[13]{};
        if(dan_rodjenja<10){
            brojevi[0] = 0;
            brojevi[1] = dan_rodjenja;
        }else{
            brojevi[0] = dan_rodjenja/10;
            brojevi[1] = dan_rodjenja%10;
        }
        if(mjesec_rodjenja < 10){
            brojevi[2] = 0;
            brojevi[3] = mjesec_rodjenja;
        }else{
            brojevi[2] = mjesec_rodjenja/10;
            brojevi[3] = mjesec_rodjenja%10;
        }
        brojevi[6] = godina_rodjenja%10;
        godina_rodjenja = godina_rodjenja/10;
        brojevi[5] = godina_rodjenja%10;
        godina_rodjenja = godina_rodjenja/10;
        brojevi[4] = godina_rodjenja%10;
        brojevi[7] = sifra_regije/10;
        brojevi[8] = sifra_regije%10;
        if(pol==Zensko){
        brojevi[9] = 5;
        }else{
            brojevi[9]=0;
        }
        brojevi[10] = 0;
        brojevi[11] = 0;
        
        int temp = 0;
        for(int i = 0;i<6;i++){
            temp+=((7-i)*(brojevi[i]+brojevi[i+6]));
        }
        brojevi[12] = 11-temp%11;
        if(brojevi[12] == 11) brojevi[12] = 0;
        if(brojevi[12] == 10) throw std::logic_error("JMBG nije validan");
        long long int povrat = 0;
        for(int i = 0;i<=12;i++){
            povrat+=(brojevi[i]*pow(10,12-i));
        }
        if(posljednji == nullptr){
            jedmatbroj = povrat;
            dan = dan_rodjenja;
            mjesec = mjesec_rodjenja;
            godina = godina_rodjenja;
            regija = sifra_regije;
            int c101112 = brojevi[9]*100+brojevi[10]*10+brojevi[11];
            spol = c101112;
            imeipr = ime_i_prezime;
            posljednji = this;
            prethodni = nullptr;
        }else{
            GradjaninBiH* temp = posljednji;
            bool ctrl = false;
            while(temp!=nullptr){//prolazimo kroz nasu "listu", temp->jedmatbroj je ustvari nas trenacni objekat
                if(povrat==temp->jedmatbroj){
                    ctrl = true;
                }
                temp = temp->prethodni;//ovo je ekvivalentno i--, temp->prethodni je ustvari prethodni objekat u odnosu na trenutacni
            }
            //if(ctrl==true){throw std::logic_error("Vec postoji gradjanin sa istim JMBG");}
            /*else*/{
                jedmatbroj = povrat;
                dan = dan_rodjenja;
                mjesec = mjesec_rodjenja;
                int c101112 = brojevi[9]*100+brojevi[10]*10+brojevi[11];
                godina = godina_rodjenja;
                regija = sifra_regije;
                spol = c101112;
                imeipr = ime_i_prezime;
                this->prethodni = &(*posljednji);
                posljednji = this;
            }
        }
        //potrebno kreirati JMBG 
}

int main ()
{
   /*std::cout<<"Koliko gradjana zelite unijeti po JMBG? ";
    int n;
    std::cin>>n;
   // GradjaninBiH niz[n];
    for(int i = 0;i<n;i++){
        std::cin.ignore(100,'\n');
        std::string temp;
        std::cout<<"\nUnesite ime i prezime (u istom redu): ";
        std::getline(std::cin,temp);
        std::cout<<"\nUnesite JMBG: ";
        long long int jmbg;
        std::cin>>jmbg;
        try{
        GradjaninBiH x(temp,jmbg);
        std::cout<<"\nUnijeli ste gradjanina "<<x.DajImeIPrezime()<<" rodjenog "<<x.DajDanRodjenja()<<"."<<
        x.DajMjesecRodjenja()<<"."<<x.DajGodinuRodjenja()<<" u regiji "<<x.DajSifruRegije()<<", ";
        if(x.DajPol()==GradjaninBiH::Pol::Musko){
            std::cout<<"musko.";
        }
        else{
            std::cout<<"zensko.";
        }
        }catch(std::logic_error e){
            std::cout<<e.what();
            i--;
        }
    }
    std::cout<<"\nKoliko gradjana zelite unijeti po datumu rodjenja, regiji i polu? ";
    std::cin>>n;
    for(int i = 0;i<n;i++){
        std::cin.ignore(100,'\n');
        std::cout<<"\nUnesite ime i prezime (u istom redu): ";
        std::string temp;
        std::getline(std::cin,temp);
        std::cout<<"\nUnesite datum rodjenja (format dd/mm/gggg): ";
        std::string datum;
        std::getline(std::cin,datum);
        int d = stoi(datum.substr(0,2));
        int m = stoi(datum.substr(3,5));
        int g = stoi(datum.substr(6,10));
        std::cout<<"\nUnesite sifru regije: ";
        int sifra;
        std::cin>>sifra;
        std::cout<<"\nUnesite M za musko, Z za zensko: ";
        char c;
        std::cin>>c;
        try{
        if(c=='M'){
            GradjaninBiH x(temp,d,m,g,sifra,GradjaninBiH::Pol::Musko);
           std::cout<<"\nUnijeli ste gradjanina "<<x.DajImeIPrezime()<<" JMBG: "<<x.DajJMBG()<<".";
        }else if(c=='Z'){
            GradjaninBiH x(temp,d,m,g,sifra,GradjaninBiH::Pol::Zensko);
            std::cout<<"\nUnijeli ste gradjanina "<<x.DajImeIPrezime()<<" JMBG: "<<x.DajJMBG()<<".";
        }
        }catch(std::logic_error e){
            std::cout<<"\n"<<e.what();
            i--;
        }
    }*/
    std::string ime = "Muhamed Gusic";
    GradjaninBiH g(ime, 8,7,1996, 91, GradjaninBiH::Pol::Musko);
    std::cout << g.DajJMBG() <<std::endl;
    return 0;
}
