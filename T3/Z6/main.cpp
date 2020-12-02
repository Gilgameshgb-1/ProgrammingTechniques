//TP 2017/2018: Tutorijal 3, Zadatak 6
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>

typedef std::vector<std::vector<int>> Matrica;

Matrica KreirajMatricu(int broj_redova, int broj_kolona)
{
    return Matrica(broj_redova, std::vector<int>(broj_kolona));
}

int NajvecaSirina(Matrica m)
{
    if(m.size()==0) {
        return 0;
    }
    int broj = m[0][0];
    int brojtemp = 0;
    int brojac1=0,brojac=0;
    if(broj<0) brojac++;
    broj=abs(broj);
    while(broj>0) {
        broj/=10;
        brojac++;
    }

    for(int i = 0; i<m.size(); i++) {
        for(int j = 0; j<m[i].size(); j++) {
            brojtemp=m[i][j];
            if(brojtemp<0) brojac1++;
            if(brojtemp==std::numeric_limits<int>::min()) return 11;
            brojtemp=abs(brojtemp);
                while(brojtemp>0) {
                    brojtemp/=10;
                    brojac1++;
                }
            if(brojac1>brojac) {
                brojac=brojac1;
            }
            brojac1=0;
        }
    }


    return brojac;
}

Matrica KroneckerovProizvod(std::vector<int> v1,std::vector<int> v2)
{

    Matrica m=KreirajMatricu(v1.size(),v2.size());
    for(int i = 0; i<v1.size(); i++) {
        for(int j = 0; j<v2.size(); j++) {
            m[i][j]=v1[i]*v2[j];
        }
    }
    return m;
}

int main ()
{

    Matrica m;
    std::vector<int> v1;
    std::vector<int> v2;
    int broj1,broj2;
    int input;
    int i;

        std::cout<<"Unesite broj elemenata prvog vektora: ";
        std::cin>>broj1;
        std::cout<<"Unesite elemente prvog vektora: ";
        for(i=0; i<broj1; i++) {
            std::cin>>input;
            v1.push_back(input);
        }
        std::cout<<"Unesite broj elemenata drugog vektora: ";
        std::cin>>broj2;
        std::cout<<"Unesite elemente drugog vektora:";
        for(i=0; i<broj2; i++) {
            std::cin>>input;
            v2.push_back(input);
        }
        m=KroneckerovProizvod(v1,v2);
        int najveci = NajvecaSirina(m);
        std::cout<<"\n";
        for(int i = 0; i<broj1; i++) {
            for(int j = 0; j<broj2; j++) {
                std::cout<<std::setw(najveci+1)<<m[i][j];
            }
            std::cout<<"\n";
        }
    return 0;
}
