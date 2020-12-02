#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include <string>

#define PI 4*atan(1)

class Lik{
public:
    virtual ~Lik(){};
    virtual double  DajObim() const {};
    virtual double  DajPovrsinu() const {};
    virtual void IspisiSpecificnosti() const {};
    virtual void Ispisi(){IspisiSpecificnosti();};
};

class Krug : public Lik{
    double r;
public:
    Krug(double poluprecnik){if(poluprecnik<=0) throw std::domain_error("Neispravni parametri");r=poluprecnik;};
    double DajObim() const override{return 2*PI*r;}
    double DajPovrsinu() const override{return r*r*PI;}
    void IspisiSpecificnosti() const override{std::cout<<"Krug poluprecnika "<<r<<"\nObim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<"\n";}
    void Ispisi() override{IspisiSpecificnosti();}
};

class Pravougaonik: public Lik{
    double a,b;
public:
    Pravougaonik(double x,double y){if(x<=0 || y<=0) throw std::domain_error("Neispravni parametri");a=x;b=y;};
    double DajObim() const override{return 2*a+2*b;}
    double DajPovrsinu() const override{return a*b;}
    void IspisiSpecificnosti() const override{std::cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<"\nObim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<"\n";}
    void Ispisi() override{IspisiSpecificnosti();}
};

class Trougao: public Lik{
    double a,b,c;
public:
    Trougao(double x,double y,double z){if(x<=0 || y<=0 || z<=0 || x+y<=z || x+z<=y || z+y<=x) throw std::domain_error("Neispravni parametri");a=x;b=y;c=z;};
    double DajObim() const override{return a+b+c;}
    double DajPovrsinu() const override{
        double s = (a+b+c)/2;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }
     void IspisiSpecificnosti() const override{std::cout<<"Trougao sa stranicama duzine "<<a<<", "<<b<<" i "<<c<<"\nObim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<"\n";}
    void Ispisi() override{IspisiSpecificnosti();}
};

int main ()
{
    int broj;
    std::vector<std::shared_ptr<Lik>> v;
    std::cout<<"Koliko zelite likova";
    std::cin>>broj;
    for(int i = 0;i<broj;i++){
        std::string temp;
        std::getline(std::cin,temp);
        if(temp[0]=='P'){
            try{
/*                double a = temp[1];
                double b = temp[3];*/
                v.push_back(std::make_shared<Pravougaonik>(a,b));
            }catch(std::domain_error e){
                std::cout<<e.what();
                i--;
            }
        }
        if(temp[0]=='K'){
            try{
//                double a = temp[1];
                v.push_back(std::make_shared<Krug>(a));
            }catch(std::domain_error e){
                std::cout<<e.what();
                i--;
            }
        }
        if(temp[0]=='T'){
            try{
/*                double a = temp[1];
                double b = temp[3];
                double c= temp[5];*/
                v.push_back(std::make_shared<Trougao>(a,b,c));
            }catch(std::domain_error e){
                std::cout<<e.what();
                i--;
            }
        }
    }
    for(int i = 0;i<broj;i++){
        v[i]->Ispisi();
    }
}
