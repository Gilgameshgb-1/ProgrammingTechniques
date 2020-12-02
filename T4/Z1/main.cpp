//TP 2018/2019: Tutorijal 4, Zadatak 1
#include <iostream>
#include <cmath>

int Cifre(long long int n,int &c_min,int &c_max)
{
    long long int temp=n;
    int tempmax;
    int tempmin;
    int brojac=1;
    int temptemp=abs(temp%10);
    tempmax=abs(temptemp);
    tempmin=abs(temptemp);
    temp/=10;

    while(temp!=0) {
        temptemp=abs(temp%10);
        if(temptemp>tempmax) tempmax=temptemp;
        if(temptemp<tempmin) tempmin=temptemp;
        temp/=10;
        brojac++;
    }
    c_min=tempmin;
    c_max=tempmax;
    return brojac;
}

int main ()
{
    int a,b,e;
    long long int n;
    std::cout<<"Unesite broj: ";
    std::cin>>n;
    e=Cifre(n,a,b);
    std::cout<<"Broj "<<n<<" ima "<<e<<" cifara, najveca je "<<b<<" a najmanja "<<a<<".";
    return 0;
}
