//TP 2017/2018: Tutorijal 2, Zadatak 5
#include <iostream>
#include <complex>

int main ()
{
    int broj;
    std::cout<<"Unesi broj elemenata: ";
    std::cin>>broj;

    double pi=4*atan(1);

    double prividni_otpor,fazni_pomak;
    std::complex<double> paralela(0,0);

    std::complex<double> red(0,0);

    for(int i = 0; i<broj; i++) {
        std::cout<<"\nZ"<<i+1<<" = ";
        std::cin>>prividni_otpor;
        std::cout<<"fi"<<i+1<<" = ";
        std::cin>>fazni_pomak;
        std::complex<double> z1;
        fazni_pomak=(fazni_pomak*pi)/180;
        z1=std::polar(prividni_otpor,fazni_pomak);
        paralela+=(1./z1);
    }
    red=1./paralela;
    if(red.imag()!=0) {
        std::cout<<"\nParalelna veza ovih elemenata ima Z = "<<abs(red)<<" i "<<"fi = "<<atan(red.imag()/red.real())*(180/pi)<<".";
    } else {
        std::cout<<"\nParalelna veza ovih elemenata ima Z = "<<abs(red)<<" i "<<"fi = "<<".";
    }
    return 0;
}
