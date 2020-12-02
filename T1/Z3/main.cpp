//TP 2016/2017: Tutorijal 1, Zadatak 3
#include <iostream>
#include <iomanip>
#include <cmath>

int main ()
{

    int a,b;

    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>a>>b;

    if(b<a || a>9999 || b>9999 || a<0 || b<0) {
        std::cout<<"Neispravno";
        return 1;
    }

    std::cout<<"\n+---------+----------+----------+-----------+\n";
    std::cout<<"| Brojevi | Kvadrati | Korijeni | Logaritmi |\n";
    std::cout<<"+---------+----------+----------+-----------+\n";

    for(int i=a; i<=b; i++) {
        std::cout<<"| ";
        std::cout<<std::setw(7)<<std::left<<i;
        std::cout<<" |"<<std::setw(9)<<std::right<<i*i;
        std::cout<<" |"<<std::setw(9)<<std::fixed<<std::setprecision(3)<<std::sqrt(i);
        std::cout<<" |"<<std::setw(10)<<std::fixed<<std::setprecision(5)<<std::log(i)<<" |";
        std::cout<<"\n";
    }

    std::cout<<"+---------+----------+----------+-----------+\n";

    return 0;
}
