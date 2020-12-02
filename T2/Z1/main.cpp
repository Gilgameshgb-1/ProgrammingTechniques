//TP 2017/2018: Tutorijal 2, Zadatak 1
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

bool DaLiJeProst(int n)
{
    if(n==2) {
        return true;
    }
    if(n<=0 || n==1) {
        return false;
    }
    for(int i =2; i<sqrt(n)+1; i++) {
        if(n%i==0) {
            return false;
        }
    }
    return true;
}


std::vector<int> ProstiBrojeviUOpsegu(int a,int b)
{
    std::vector<int> niz;
    if(a>0) {
        for(unsigned int i = a; i<=b; i++) {
            if(DaLiJeProst(i)==true && i!=1  && i>0) {
                niz.push_back(i);
            }
        }
    } else {
        for(int i = a; i<=b; i++) {
            if(DaLiJeProst(i)==true && i!=1  && i>0) {
                niz.push_back(i);
            }
        }
    }
    return niz;
}

int main ()
{
    int broj1,broj2;
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>broj1;
    std::cin>>broj2;

    std::vector<int> niz = ProstiBrojeviUOpsegu(broj1,broj2);
    if(niz.size()!=0) {
        std::cout<<"Prosti brojevi u rasponu od "<<broj1<<" do "<<broj2<<" su: ";
        for(int i = 0; i<niz.size(); i++) {
            if(i!=(niz.size()-1)) {
                std::cout<<niz[i]<<", ";
            } else {
                std::cout<<niz[i];
            }
        }
        std::cout<<"\n";
    } else {
        std::cout<<"Nema prostih brojeva u rasponu od "<<broj1<<" do "<<broj2<<"!";
    }
    return 0;
}
