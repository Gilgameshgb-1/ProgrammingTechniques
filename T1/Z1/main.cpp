//TP 2016/2017: Tutorijal 1, Zadatak 1
#include <iostream>
#include <cmath>
int main ()
{
    int a,b,c;
    int d;
    std::cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    std::cin>>a>>b>>c;
    std::cout<<"Unesite sirinu plocice u centimetrima: ";
    std::cin>>d;
    int povrsina_bazena(0);
    povrsina_bazena=a*b+2*(a*c)+2*(b*c);
    int povrsina_plocice(0);
    povrsina_plocice=d*d;
    if((povrsina_bazena*10000)%povrsina_plocice==0 && (a*b*10000)%povrsina_plocice==0 && (b*c*10000)%povrsina_plocice==0 && (a*c*10000)%povrsina_plocice==0 && a*100%d==0 && b*100%d==0 && c*100%d==0) {
        std::cout<<"\nZa poplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<"\npotrebno je "<<(povrsina_bazena*10000)/povrsina_plocice<<" plocica.";
    } else {
        std::cout<<"\nPoplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<"\nnije izvodljivo bez lomljenja plocica!";
    }
    return 0;
}
