#include <iostream>
#include <cmath>
#include <iomanip>
#define PI 4*atan(1)


class Krug
{
    double poluprecnik;
    public:
    explicit Krug(double x)
    {
        if(x<=0) throw std::domain_error("Neispravan poluprecnik");
        poluprecnik = x;
    }
    void Postavi(double x)
    {
        if(x<=0) throw std::domain_error("Neispravan poluprecnik");
        poluprecnik = x;
    }
    double DajPoluprecnik() const {return poluprecnik;}
    double DajObim() const {return 2*poluprecnik*PI;}
    double DajPovrsinu() const {return poluprecnik*poluprecnik*PI;}
    void Skaliraj(double x)
    {
        if(x<=0) throw std::domain_error("Neispravan faktor skaliranja");
        poluprecnik = poluprecnik*x;
    }
    void Ispisi() const{std::cout<<std::fixed<<std::setprecision(5)<<"R="<<poluprecnik<<" O="<<DajObim()<<" P="<<DajPovrsinu();}
};

class Valjak
{
    Krug baza;
    double visina;
    public:
    explicit Valjak(double r,double h) :
    baza(r)
    {
        if(h<0) throw std::domain_error("Neispravna visina");
        visina=h;
    }
    void Postavi(double r,double h)
    {
        if(r<=0) throw std::domain_error("Neispravan poluprecnik");
        if(h<0) throw std::domain_error("Neispravna visina");
        this->baza.Postavi(r);
        visina = h;
    }
    Krug DajBazu(){return this->baza;}
    double DajPoluprecnikBaze() const {return baza.DajPoluprecnik();}
    double DajVisinu() const {return visina;}
    double DajPovrsinu() const {return 2*baza.DajPoluprecnik()*PI*(baza.DajPoluprecnik()+visina);}
    double DajZapreminu() const {return baza.DajPoluprecnik()*baza.DajPoluprecnik()*PI*visina;}
    void Skaliraj(double x)
    {
        if(x<=0) throw std::domain_error("Neispravan faktor skaliranja");
        baza.Skaliraj(x);
        visina=visina+x;
    }
    void Ispisi() const{std::cout<<std::fixed<<std::setprecision(5)<<"R="<<baza.DajPoluprecnik()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();}
};


int main ()
{
    
    return 0;
}
