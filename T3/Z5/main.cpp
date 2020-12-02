//TP 2017/2018: Tutorijal 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <limits>
#include <deque>

typedef std::deque<int> Dek;

Dek IzdvojiElemente(Dek v,bool c)
{
    int suma(0);
    int z(0);
    Dek dek;
    if(c==true) {

        for(int i = v.size()-1; i>=0; i--) {
            if(v.at(i)==std::numeric_limits<int>::min()){
                z=1;
            }else{
            z=abs(v.at(i));
            }
            while(z>0) {
                suma+=z%10;
                z/=10;
            }
            if(suma%2==0){
            dek.push_front(v.at(i));
            }
            suma=0;
        }
    } else {

        for(int i = v.size()-1; i>=0; i--) {
            if(v.at(i)==std::numeric_limits<int>::min()){
                dek.push_front(v.at(i));
            }
            z=abs(v.at(i));
            while(z>0) {
                suma+=z%10;
                z/=10;
            }
            
            if(suma%2!=0){
                dek.push_front(v.at(i));
            }
            suma=0;
        }
    }

    return dek;
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
    std::cout<<"\n";
    return 0;
}
