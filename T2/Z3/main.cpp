//TP 2017/2018: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>

int main ()
{

    int broj;
    std::cout<<"Unesite broj elemenata: \n";
    std::cin>>broj;

    double real(0),imag(0);
    std::complex<double> paralela(0,0);

    std::complex<double> red(0,0);
    for(int i=0; i<broj; i++) {
        std::complex<double> z1;
        std::cout<<"Z_"<<i+1<<" = ";
        std::cin>>z1;
        paralela+=(1./z1);
    }
    red=1./paralela;

    std::cout<<"\nParalelna veza ovih elemenata ima impedansu Z_ = "<<red<<".";

    return 0;
}
