//TP 2017/2018: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>

bool TestPerioda(std::vector<double> v,int p)
{
    if(p>=v.size()) return false;
    int z = 0;
    if(p==0) return false;
    for(int i=p; i<v.size(); i++) {
        if(v[z]!=v[i]) {
            return false;
        }
        z++;
    }
    return true;
}

int OdrediOsnovniPeriod(std::vector<double> v)
{
    for(int i  =1; i<v.size(); i++) {
        if(TestPerioda(v,i)==true) {
            return i;
        }
    }
    return 0;
}

int main ()
{
    std::vector<double> niz;
    int i =0;
    double broj;
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    while(1) {
        std::cin>>broj;
        if(broj==0) {
            break;
        } else {
            niz.push_back(broj);
            i++;
        }
    }
    if(OdrediOsnovniPeriod(niz)) {
        std::cout<<"Slijed je periodican sa osnovnim periodom "<<OdrediOsnovniPeriod(niz)<<".";

    } else {
        std::cout<<"Slijed nije periodican!";
    }
    return 0;
}
