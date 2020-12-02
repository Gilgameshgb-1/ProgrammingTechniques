//TP 2017/2018: Tutorijal 3, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <deque>

typedef std::deque<int> Dek;

Dek IzdvojiElemente(Dek v,bool c)
{
    Dek PovratP;
    Dek PovratN;
    Dek ocuvanje = v;

    if(c==true) {
        int SumaP=0;
        for(int x : v) {
            int i = 0;
            if(x==std::numeric_limits<int>::min()) {
                ocuvanje[i]=1;
            } else {
                ocuvanje[i]=abs(x);
            }
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
            if(x==std::numeric_limits<int>::min()) {
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
    Dek a;

    std::cout<<"Koliko zelite unijeti elemenata: ";
    std::cin>>n;
    if(n<=0) {
        std::cout<<"Broj elemenata mora biti veci od 0!";
        return 1;
    }
    std::cout<<"Unesite elemente: ";
    for(int i = 0; i<n; i++) {
        int broj;
        std::cin>>broj;
        a.push_back(broj);
    }
    Dek b;
    Dek c;
    b=IzdvojiElemente(a,true);
    c=IzdvojiElemente(a,false);

    for(int i = 0 ; i<b.size(); i++) {
        if(i!=b.size()-1) {
            std::cout<<b[i]<<",";
        } else {
            std::cout<<b[i];
        }
    }
    std::cout<<"\n";
    for(int i = 0; i<c.size(); i++) {
        if(i!=c.size()-1) {
            std::cout<<c[i]<<",";
        } else {
            std::cout<<c[i];
        }
    }

    return 0;
}
