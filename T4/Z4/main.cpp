//TP 2018/2019: Tutorijal 4, Zadatak 4
#include <iostream>
#include <string>
#include <cmath>

template <typename NekiTip>
NekiTip UnosBroja(std::string a,std::string b,NekiTip &c)
{
    int belaj=1;
    bool isdouble=false;
    std::string str;
    while(1) {
        std::cout<<'\n';
        std::cout<<a;
        std::cin>>str;
        int i = 0;
        while(i<str.size()) {
            if(str.at(i)<'0' || str.at(i)>'9') {
                if(str.at(i)=='.' || str.at(i)=='-') {
                    belaj=0;
                } else {
                    belaj=1;
                    break;
                }
            }
            if(str.at(i)=='.') {
                isdouble=true;
            }
            belaj=0;
            i++;
        }
        if(belaj==0) {
            if(isdouble==false) {
                c=stoi(str);
            }
            if(isdouble==true) {
                c=stod(str);
            }
            break;
        }
        if(belaj==1) {
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cout<<'\n'<<b;
        }
    }
    return c;
}


int main ()
{
    double baza;
    double eksponent;
    double rezultat;
    UnosBroja("Unesite bazu: ", "Neispravan unos, pokusajte ponovo...", baza);
    std::cout<<'\n';
    while(1){
    UnosBroja("Unesite cjelobrojni eksponent: ", "Neispravan unos, pokusajte ponovo...", eksponent);
        if(eksponent==int(eksponent)) break;
        else{
            std::cout<<"\nNeispravan unos, pokusajte ponovo...";
        }
    }
    double temp = baza;
    int i = 0;
    if(eksponent>0){
        rezultat=baza;
        while(i<eksponent-1){
        rezultat*=baza;
        i++;
        }
    }else{
        while(i<abs(eksponent)-1){
        baza*=baza;
        i++;
        }
        rezultat=1/baza;
    }
    std::cout<<'\n';
    std::cout<<'\n'<<temp<<" na "<<eksponent<<" iznosi "<<rezultat;
    return 0;
}
