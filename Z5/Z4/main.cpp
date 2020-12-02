#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

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

class PolimorfniSpremnik{
    Spremnik* spr;
    void Test() const{
        if(!spr) throw std::logic_error("Nespecificiran spremnik");
    }
public:
    PolimorfniSpremnik() : spr(nullptr){}
    ~PolimorfniSpremnik(){delete spr;}
    PolimorfniSpremnik(const Spremnik &s) : spr(s.DajKopiju()){}
    PolimorfniSpremnik(const PolimorfniSpremnik &s){
        if(!s.spr) spr=nullptr;
        else spr = s.spr->DajKopiju();
    }
    PolimorfniSpremnik(PolimorfniSpremnik &&s){
        spr=s.spr; s.spr=nullptr;
    }
    PolimorfniSpremnik &operator = (const PolimorfniSpremnik &s){
        Spremnik *p_novi = nullptr;
        if(s.spr != nullptr) p_novi = s.spr->DajKopiju();
        delete spr;
        spr = p_novi;
        return *this;
    }
    PolimorfniSpremnik &operator = (PolimorfniSpremnik &&s){
        std::swap(spr,s.spr);
        return *this;
    }
    double DajTezinu() const{Test(); return spr->DajTezinu();};
    double DajUkupnuTezinu() const {Test(); return spr->DajUkupnuTezinu();};
    void Ispisi() const {Test(); spr->Ispisi();};
};

int main(){
    return 0;
}