#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>

class Spremnik{
protected:
    double SopstvenaTezina;
    std::string Naziv;
public:
    virtual ~Spremnik(){};
    Spremnik(double x,std::string y):SopstvenaTezina(x),Naziv(y){}
    virtual double DajTezinu() const{ return SopstvenaTezina;};
    virtual double DajUkupnuTezinu() const = 0;
    virtual void Ispisi() const = 0;
    virtual Spremnik *DajKopiju() const = 0;
};

class Sanduk: public Spremnik{
    std::vector<double> v;
public:
    Sanduk(double m,std::string ime,std::vector<double> x):Spremnik(m,ime){v = x;}
    double DajUkupnuTezinu() const override{double suma = 0; for(int i = 0;i<v.size();i++)suma+=v[i];suma+=DajTezinu();return suma;}
    void Ispisi() const override{
        std::cout<<"Vrsta spremnika: Sanduk\nSadrzaj: "<<this->Naziv<<"\nTezine predmeta: ";
        for(int i = 0;i<v.size();i++) std::cout<<v[i]<<" ";
        std::cout<<"(kg)\n"<<"Vlastita tezina: "<<DajTezinu()<<" (kg)\n";
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)\n";
    }
    Spremnik *DajKopiju() const override {return new Sanduk(*this);}
};

class Vreca: public Spremnik{
    double TezinaMaterije;
public:
    Vreca(double m,std::string ime,double mP):Spremnik(m,ime),TezinaMaterije(mP){}
    double DajUkupnuTezinu() const override{return (TezinaMaterije + DajTezinu());};
    void Ispisi() const override{
        std::cout<<"Vrsta spremnika: Vreca\nSadrzaj: "<<this->Naziv<<"\nVlastita tezina: "<<DajTezinu()<<" (kg)\n";
        std::cout<<"Tezina pohranjene materije: "<<TezinaMaterije<<" (kg)\n";
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)\n";
    };
    Spremnik *DajKopiju() const override{return new Vreca(*this);}
};

class Bure: public Spremnik{
  double specificnaTezina;
  double Zapremina;
public:
    Bure(double mT,std::string ime,double mSpec,double V):Spremnik(mT,ime),specificnaTezina(mSpec),Zapremina(V){}
    double DajUkupnuTezinu() const override{return ((Zapremina/1000*specificnaTezina) + DajTezinu());}
    void Ispisi() const override{
        std::cout<<"Vrsta spremnika: Bure\nSadrzaj: "<<this->Naziv<<"\nVlastita tezina: "<<DajTezinu()<<" (kg)\n";
        std::cout<<"Specificna tezina tecnosti: "<<specificnaTezina<<" (kg/m^3)\n";
        std::cout<<"Zapremina tecnosti: "<<Zapremina<<" (l)\n"<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)\n";
    }
    Spremnik *DajKopiju() const override{return new Bure(*this);}
};

class Skladiste{
    std::vector<std::shared_ptr<Spremnik>> v;
public:
    //~Skladiste(){v.resize(v.size()-1);}
    Skladiste():v(0){};
    std::shared_ptr<Spremnik> DodajSanduk(double m,std::string ime,std::vector<double> x){
        v.push_back(std::make_shared<Sanduk>(Sanduk(m,ime,x)));
        return v[v.size()-1];
    }
    std::shared_ptr<Spremnik> DodajVrecu(double m,std::string ime,double mP){
        v.push_back(std::make_shared<Vreca>(Vreca(m,ime,mP)));
        return v[v.size()-1];
    }
    std::shared_ptr<Spremnik> DodajBure(double mT,std::string ime,double mSpec,double V){
        v.push_back(std::make_shared<Bure>(Bure(mT,ime,mSpec,V)));
        return v[v.size()-1];
    }
    Spremnik* DodajSpremnik(Spremnik* s,bool vlastnistvo){
        if(vlastnistvo == true){
            v.emplace_back(s);
            //Spremnik* z= v[v.size()-1].get();
            return v[v.size()-1].get();
        }
        v.emplace_back((s->DajKopiju()));
        //Spremnik* z= v[v.size()-1].get();
       return v[v.size()-1].get();
    }
    void BrisiSpremnik(Spremnik* s){
        for(int i = 0;i<v.size();i++){
            if(v[i].get()==s) {
                //delete v[i];
                for(int j = i;j<v.size()-1;j++){
                    v[j]=v[j+1];
                }
                if(i==v.size()-1){
                    v.resize(v.size()-1);
                }
                break;
            }
        }
    }
    Spremnik &DajNajlaksi() {
        if(v.size()==0) throw std::range_error("Skladiste je prazno");
        auto x = std::min_element(v.begin(),v.end(),[](std::shared_ptr<Spremnik> s1,std::shared_ptr<Spremnik> s2)->bool{
            if(s1->DajTezinu() > s2->DajTezinu()) return false;
            return true;
        });
            return **x;
    };
    Spremnik &DajNajtezi(){
        if(v.size()==0) throw std::range_error("Skladiste je prazno");
        auto x = std::min_element(v.begin(),v.end(),[](std::shared_ptr<Spremnik> s1,std::shared_ptr<Spremnik> s2)->bool{
            if(s1->DajTezinu() > s2->DajTezinu()) return true;
            return false;
        });
        return **x;
    };
    int BrojPreteskih(double tezinahehe) const{ 
        return std::count_if(v.begin(),v.end(),[tezinahehe](std::shared_ptr<Spremnik> s1)->bool{
            if(s1->DajUkupnuTezinu() > tezinahehe ) return true;
            return false;
        });
    }
    void IzlistajSkladiste() const{
        std::vector<std::shared_ptr<Spremnik>> temp;
        temp = v;
       std::sort(temp.begin(),temp.end(),[](std::shared_ptr<Spremnik> s1,std::shared_ptr<Spremnik> s2){
           if(s1->DajUkupnuTezinu() > s2->DajUkupnuTezinu()) return true;
           return false;
        });
        for(int i = 0;i<temp.size();i++){
            temp[i]->Ispisi();
        }
    }
    void UcitajIzDatoteke(const std::string &ime_datoteke){
        std::fstream tok(ime_datoteke);
        if(!tok)  throw std::logic_error("Trazena datoteka ne postoji");
        for(int i = 0; i <v.size();i++){
            BrisiSpremnik(v[i].get());
        }
        while(tok){
            std::string s;
            std::getline(tok,s,'\n');
            if(tok.peek() == EOF) tok.clear();
            std::string x = s.substr(0,1);
            std::string ime = s.substr(2,s.size()-1);
            if(x=="S"){
                double st;
                std::vector<double> tezine;
                double t;
                bool kontrola = false;
                int br;
                while(tok.peek() !='\n' && tok.peek() != EOF){
                    if(kontrola == false){
                        tok>>st;
                        kontrola = true; 
                    }
                    tok>>br;
/*                    std::cout<<"!!!!"<<br;*/
                    for(int i = 0;i<br;i++){
                        if(tok.fail()) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                        tok>>t;
                        if(tok.fail()) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                        tezine.push_back(t);
                    }
                }
                if(tok.peek()==EOF){tok.clear();}
                tok.get();
                DodajSanduk(st,ime,tezine);
            }else if(x=="V"){
                double mt;
                double mP;
                tok>>mt>>mP;
                if(tok.peek()==EOF){tok.clear();}
                tok.get();
                DodajVrecu(mt,ime,mP);
            }else if(x=="B"){
                double st;
                double tt;
                double gt;
                tok>>st>>tt>>gt;
                if(tok.peek()==EOF){tok.clear();}
                tok.get();
                DodajBure(st,ime,tt,gt);
            }
        }
//        throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }
};



int main (){
Skladiste s;
    try{
        s.UcitajIzDatoteke("ROBA.TXT");
        s.IzlistajSkladiste();
    }catch(std::logic_error e){
        std::cout<<e.what();
    }
}