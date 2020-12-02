//TP 2017/2018: Tutorijal 3, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

typedef std::vector<int> Vektor;

Vektor IzdvojiElemente(Vektor v,bool c)
{
    Vektor PovratP;
    Vektor PovratN;
    Vektor ocuvanje = v;

    if(c==true) {
        int SumaP=0;
        for(int x : v) {
            int i = 0;
            ocuvanje[i]=abs(x);
            while(ocuvanje[i]>0) {
                int temp = ocuvanje[i]%10;
                SumaP+=temp;
                ocuvanje[i]/=10;
            }
            if(SumaP%2==0) {
                PovratP.push_back(x);
            }
            SumaP=0;
            i++;
        }
        return PovratP;
    } else {
        int SumaN=0;
        for(int x : v) {
            int i = 0;
            if(x==std::numeric_limits<int>::min()){
                PovratN.push_back(x);
            }
            ocuvanje[i]=abs(x);
            while(ocuvanje[i]>0) {
                int temp = ocuvanje[i]%10;
                SumaN+=temp;
                ocuvanje[i]/=10;
            }
            if(SumaN%2!=0) {
                PovratN.push_back(x);
            }
            SumaN=0;
            i++;
        }
        return PovratN;
    }
}

int main ()
{
    int n;
    Vektor a;

        std::cout<<"Koliko zelite unijeti elemenata: ";
        std::cin>>n;
        if(n<=0){
            std::cout<<"Broj elemenata mora biti veci od 0!";
            return 1;
        }
        std::cout<<"Unesite elemente: ";
        for(int i = 0; i<n; i++) {
            int broj;
            std::cin>>broj;
            a.push_back(broj);
        }
        Vektor b;
        Vektor c;
        b=IzdvojiElemente(a,true);
        c=IzdvojiElemente(a,false);

        for(int x : b){
            std::cout<<x<<" ";
        }
        std::cout<<"\n";
        for(int x: c){
            std::cout<<x<<" ";
        }

    return 0;
}
