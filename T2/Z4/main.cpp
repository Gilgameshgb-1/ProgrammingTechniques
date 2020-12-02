//TP 2017/2018: Tutorijal 2, Zadatak 4
#include <iostream>
#include <complex>

int main ()
{
    int broj;

    std::cout<<"Unesite broj elemenata: ";
    std::cin>>broj;

    double real(0),imag(0);
    std::complex<double> paralela(0,0);

    std::complex<double> red(0,0);
    for(int i =0; i<broj; i++) {
        std::cout<<"\nR"<<i+1<<" = ";
        std::cin>>real;
        std::cout<<"X"<<i+1<<" = ";
        std::cin>>imag;
        std::complex<double> z1(real,imag);
        paralela+=(1./z1);
    }
    red=1./paralela;

    std::cout<<"\nParalelna veza ovih elemenata ima R = "<<red.real()<<" i "<<"X = "
             <<red.imag()<<".";

    return 0;
}
