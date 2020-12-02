#include <iostream>
#include <tuple>
#include <cmath>
#include <vector>
#include <algorithm>
#include <memory>

typedef std::pair<double,double> Tacka;

class Trougao
{
    Tacka t1,t2,t3;
public:
    Trougao(const Tacka &t1,const Tacka &t2,const Tacka &t3);
    void Postavi(const Tacka &t1,const Tacka &t2,const Tacka &t3);
    void Postavi(int indeks, const Tacka &t);
    static int Orijentacija(const Tacka &t1,const Tacka &t2,const Tacka &t3);
    Tacka DajTjeme(int indeks) const;
    double DajStranicu(int indeks) const;
    double DajUgao(int indeks) const;
    Tacka DajCentar() const;
    double DajObim() const;
    double DajPovrsinu() const;
    bool DaLiJePozitivnoOrijentiran() const;
    bool DaLiJeUnutra(const Tacka &t) const;
    void Ispisi() const;
    void Transliraj(double delta_x,double delta_y);
    void Centriraj(const Tacka &t);
    void Rotiraj(const Tacka &t,double ugao);
    void Skaliraj(const Tacka &t,double faktor);
    void Rotiraj(double ugao);
    void Skaliraj(double faktor);
    friend bool DaLiSuIdenticni(const Trougao &t1,const Trougao &t2);
    friend  bool DaLiSuPodudarni(const Trougao &t1,const Trougao &t2);
    friend bool DaLiSuSlicni(const Trougao &t1,const Trougao &t2);
};


double Izraz(const Tacka &t1,const Tacka &t2,const Tacka &t3){
    double izraz=0;
    izraz = t1.first*(t2.second-t3.second)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second);
    return izraz;
}

Trougao::Trougao(const Tacka &t1,const Tacka &t2,const Tacka &t3){
    if(Izraz(t1,t2,t3)==0) throw std::domain_error("Nekorektne pozicije tjemena");
    Trougao::t1=t1;Trougao::t2=t2;Trougao::t3=t3;//potrebno postaviti izuzetak
}

void Trougao::Postavi(const Tacka &t1,const Tacka &t2,const Tacka &t3){
    if(Izraz(t1,t2,t3)==0) throw std::domain_error("Nekorektne pozicije tjemena");
    Trougao::t1=t1;Trougao::t2=t2;Trougao::t3=t3;//potrebno postaviti izuzetak
}

void Trougao::Postavi(int indeks,const Tacka &t){
    if(indeks>3 || indeks<1) throw std::range_error("Nekorektan indeks");
    if(indeks == 1) t1=t;
    if(indeks == 2) t2=t;
    if(indeks == 3) t3=t;
}

int Trougao::Orijentacija(const Tacka &t1,const Tacka &t2,const Tacka &t3){
    double izraz = Izraz(t1,t2,t3);
    if(izraz == 0) return 0;
    if(izraz < 0) return -1;
    if(izraz > 0) return 1;
}

Tacka Trougao::DajTjeme(int indeks) const{
    if(indeks>3 || indeks<1) throw std::range_error("Nekorektan indeks");
    if(indeks == 1) return t1;
    if(indeks == 2) return t2;
    if(indeks == 3) return t3;
}

double Razdaljina(const Tacka &t1,const Tacka &t2){
    double duzina = 0;
    duzina = sqrt(pow((t2.first-t1.first),2)+pow((t2.second-t1.second),2));
    return duzina;
}

double Trougao::DajStranicu(int indeks) const{
    if(indeks>3 || indeks<1) throw std::range_error("Nekorektan indeks");
    if(indeks == 1) return Razdaljina(t2,t3);
    if(indeks == 2) return Razdaljina(t1,t3);
    if(indeks == 3) return Razdaljina(t1,t2);
}

double Kosinusna(const Tacka &t1,const Tacka &t2,const Tacka &t3){
    double a = Razdaljina(t2,t3);
    double b = Razdaljina(t1,t3);
    double c = Razdaljina(t1,t2);
    double ugao = acos((pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c));
    return ugao;
}

double Trougao::DajUgao(int indeks) const{
    if(indeks>3 || indeks<1) throw std::range_error("Nekorektan indeks");
    if(indeks == 1) return Kosinusna(t1,t2,t3);
    if(indeks == 2) return Kosinusna(t2,t1,t3);
    if(indeks == 3) return Kosinusna(t3,t2,t1);
}

Tacka Trougao::DajCentar() const{
    return std::make_pair((t1.first+t2.first+t3.first)/3,(t1.second+t2.second+t3.second)/3);
}

double Trougao::DajObim() const{
    return Razdaljina(t1,t2)+Razdaljina(t2,t3)+Razdaljina(t3,t1);
}

double Trougao::DajPovrsinu() const{
    return 0.5*abs(Izraz(t1,t2,t3));
}

bool Trougao::DaLiJePozitivnoOrijentiran() const{
    if(Izraz(t1,t2,t3)>0) return true;
    return false;
}

double Izraz1(Tacka p1,Tacka p2,Tacka p3){
    return (p1.first*(p2.second-p3.second)+p2.first*(p3.second-p1.second)+p3.first*(p1.second-p2.second))/2;
}

bool Trougao::DaLiJeUnutra(const Tacka &t) const{
    double A = 0.5*abs(Izraz(t1,t2,t3));
    double A1 = 0.5*abs(Izraz(t,t1,t2));
    double A2 = 0.5*abs(Izraz(t,t2,t3));
    double A3 = 0.5*abs(Izraz(t,t1,t3));
    if((A1+A2+A3)==A) return true;
    return false;
}

void Trougao::Ispisi() const{
    std::cout<<"(("<<t1.first<<","<<t1.second<<"),"<<"("<<t2.first<<","<<t2.second<<"),"<<"("<<t3.first<<","<<t3.second<<"))";
}

void Trougao::Transliraj(double delta_x,double delta_y){
    t1.first+=delta_x;
    t1.second+=delta_y;
    t2.first+=delta_x;
    t2.second+=delta_y;
    t3.first+=delta_x;
    t3.second+=delta_y;
}

void Trougao::Centriraj(const Tacka &t){
    auto c = DajCentar();
    double delta_x=t.first-c.first;
    double delta_y=t.second-c.second;
    Transliraj(delta_x,delta_y);
}

Tacka RotacionaTacka(Tacka t1,Tacka t2,double ugao){
    return std::make_pair(t1.first+(t2.first-t1.first)*cos(ugao)-(t2.second-t1.second)*sin(ugao),t1.second+(t2.first-t1.first)*sin(ugao)+(t2.second-t1.second)*cos(ugao));
}

void Trougao::Rotiraj(const Tacka &t,double ugao){
    t1=RotacionaTacka(t,t1,ugao);
    t2=RotacionaTacka(t,t2,ugao);
    t3=RotacionaTacka(t,t3,ugao);
}

Tacka Skaliranje(Tacka tc,Tacka t,double faktor){
    return std::make_pair(tc.first+faktor*(t.first-tc.first),tc.second+faktor*(t.second-tc.second));
}

void Trougao::Skaliraj(const Tacka &t,double faktor){
    if(faktor == 0) throw std::domain_error("Nekorektan faktor skaliranja");
    t1 = Skaliranje(t,t1,faktor);
    t2 = Skaliranje(t,t2,faktor);
    t3 = Skaliranje(t,t3,faktor);
}

void Trougao::Rotiraj(double ugao){
    auto t = DajCentar();
    t1=RotacionaTacka(t,t1,ugao);
    t2=RotacionaTacka(t,t2,ugao);
    t3=RotacionaTacka(t,t3,ugao);
}

void Trougao::Skaliraj(double faktor){
    if(faktor == 0) throw std::domain_error("Nekorektan faktor skaliranja");
    auto t = DajCentar();
    t1 = Skaliranje(t,t1,faktor);
    t2 = Skaliranje(t,t2,faktor);
    t3 = Skaliranje(t,t3,faktor);
}

bool DaLiSuIdenticni(const Trougao &t1,const Trougao &t2){
    std::vector<std::pair<double,double>> v1 = {{t1.t1.first,t1.t1.second},{t1.t2.first,t1.t2.second},{t1.t3.first,t1.t3.second}};
    std::vector<std::pair<double,double>> v2 = {{t2.t1.first,t2.t1.second},{t2.t2.first,t2.t2.second},{t2.t3.first,t2.t3.second}};
    int c=0;
    for(int i = 0;i<3; i++){
        for(int j = 0;j<3; j++){
            if(v1[i].first == v2[j].first && v1[i].second == v2[j].second)c++;
        }
    }
    if(c==3) return true;
    return false;
}

bool DaLiSuPodudarni(const Trougao &t1,const Trougao &t2){
    std::vector<Tacka> VT1;
    std::vector<Tacka> VT2;
    for(int i = 1;i<=3;i++){
        VT1.push_back(t1.DajTjeme(i));
    }
    for(int i = 1;i<=3;i++){
        VT2.push_back(t2.DajTjeme(i));
    }
    double temp1 = Razdaljina(VT1[0],VT1[1]);
    double temp2 = Razdaljina(VT2[0],VT2[0]);
    std::sort(VT1.begin(),VT1.end(),[temp1](Tacka t1,Tacka t2){return temp1>Razdaljina(t1,t2);});
    std::sort(VT2.begin(),VT2.end(),[temp2](Tacka t1,Tacka t2){return temp2>Razdaljina(t1,t2);});
    double k1 = Izraz(VT1[0],VT1[1],VT1[2]);
    double k2 = Izraz(VT2[0],VT2[1],VT2[2]);
    if(k1==k2) return true;
    return false;
}

bool DaLiSuSlicni(const Trougao &t1,const Trougao &t2){
    std::vector<double> VR1;
    std::vector<double> VR2;
    for(int i = 1;i<=3;i++){
        VR1.push_back(t1.DajStranicu(i));
    }
    for(int i = 1;i<=3;i++){
        VR2.push_back(t2.DajStranicu(i));
    }
    std::sort(VR1.begin(),VR1.end());
    std::sort(VR2.begin(),VR2.end());
    double temp = VR1[0]/VR2[0];
    for(int i = 0;i<3;i++){
        if((VR1[i]/VR2[i]) != temp) return false;
    }
    return true;
}



int main ()
{
    int broj;
    std::cout<<"Koliko zelite kreirati trouglova: ";
    std::cin>>broj;
    std::vector<std::shared_ptr<Trougao>> v(broj);
    for(int i = 0;i<broj;i++){
        double x1,x2,x3,y1,y2,y3;
        std::cout<<"Unesite podatke za "<<i+1<<". trougao (x1 y1 x2 y2 x3 y3): ";
        std::cin>>x1>>y1>>x2>>y2>>x3>>y3;
        Tacka p1,p2,p3;
        p1=std::make_pair(x1,y1);
        p2=std::make_pair(x2,y2);
        p3=std::make_pair(x3,y3);
        try{
            Trougao t(p1,p2,p3);
            v[i]=(std::make_shared<Trougao>(t));
        }catch(std::domain_error e){
            std::cout<<e.what()<<", ponovite unos!\n";
            i--;
        }
    }
    double ugao,dx,dy,faktor;
    std::cout<<"Unesite vektor translacije (dx dy): ";
    std::cin>>dx>>dy;
    std::cout<<"Unesite ugao rotacije: ";
    std::cin>>ugao;
    std::cout<<"Unesite faktor skaliranja: ";
    std::cin>>faktor;
    std::transform(v.begin(),v.end(),v.begin(),[dx,dy,ugao,faktor](std::shared_ptr<Trougao> t){
        t->Transliraj(dx,dy);
        t->Rotiraj(ugao);
        t->Skaliraj(t->DajTjeme(1),faktor);
        return t;
    });
    std::sort(v.begin(),v.end(),[](std::shared_ptr<Trougao> t1,std::shared_ptr<Trougao> t2)->bool{
        if(t1->DajPovrsinu()<t2->DajPovrsinu()) return true;
        return false;
    });
    std::cout<<"Trouglovi nakon obavljenih transformacija:\n";
    for(int i = 0;i<broj;i++){
        Tacka p1,p2,p3;
        p1 = v[i]->DajTjeme(1);
        p2 = v[i]->DajTjeme(2);
        p3 = v[i]->DajTjeme(3);
        std::cout<<"\n(("<<p1.first<<","<<p1.second<<"),("<<p2.first<<","<<p2.second<<"),("<<p3.first<<","<<p3.second<<"))";
    }
    auto it = std::min_element(v.begin(),v.end(),[](std::shared_ptr<Trougao> t1,std::shared_ptr<Trougao> t2)->bool{
        if(t1->DajObim()<t2->DajObim()) return true;
        return false;
    });
    std::cout<<"\nTrougao sa najmanjim obimom: ";
    (*it)->Ispisi();
    int c = 0;
    for(int i = 0;i<broj;i++){
        for(int j = i+1;j<broj;j++){
            if(DaLiSuIdenticni(*v[i],*v[j])==true){
            c++;
            }
        }
    }
    if(c!=0){
    std::cout<<"\nParovi identicnih trouglova: \n";
    for(int i = 0;i<broj;i++){
        for(int j = i+1;j<broj;j++){
            if(DaLiSuIdenticni(*v[i],*v[j])==true){
            v[i]->Ispisi();
            std::cout<<" i ";
            v[j]->Ispisi();
            c++;
            std::cout<<"\n";
            }
        }
    }
    }
    if(c==0) std::cout<<"\nNema identicnih trouglova!";
    c=0;
        for(int i = 0;i<broj;i++){
        for(int j = i+1;j<broj;j++){
            if(DaLiSuPodudarni(*v[i],*v[j])==true){
            c++;
            }
        }
    }
    if(c!=0){
    std::cout<<"Parovi podudarnih trouglova: \n";
    for(int i = 0;i<broj;i++){
        for(int j = i+1;j<broj;j++){
            if(DaLiSuPodudarni(*v[i],*v[j])==true){
            v[i]->Ispisi();
            std::cout<<" i ";
            v[j]->Ispisi();
            std::cout<<"\n";
            c++;
            }
        }
    }
    }
    if(c==0) std::cout<<"\nNema podudarnih trouglova!";
    c=0;
    for(int i = 0;i<broj;i++){
        for(int j = i+1;j<broj;j++){
            if(DaLiSuSlicni(*v[i],*v[j])==true){
            c++;
            }
        }
    }
    if(c!=0){
    std::cout<<"Parovi slicnih trouglova: \n";
    for(int i = 0;i<broj;i++){
        for(int j = i+1;j<broj;j++){
            if(DaLiSuSlicni(*v[i],*v[j])==true){
            v[i]->Ispisi();
            std::cout<<" i ";
            v[j]->Ispisi();
            std::cout<<"\n";
            c++;
            }
        }
    }
    }
    if(c==0) std::cout<<"\nNema slicnih trouglova!";
/*    p2=*it->DajTjeme(2);
    p3=*it->DajTjeme(3);
    <<"(("<<p1.first<<","<<p1.second<<"),("<<p2.first<<","<<p2.second<<"),("<<p3.first<<","<<p3.second<<"))";*/
    return 0;
}
