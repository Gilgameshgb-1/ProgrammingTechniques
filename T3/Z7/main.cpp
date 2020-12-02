//TP 2017/2018: Tutorijal 3, Zadatak 7
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

typedef std::vector<std::vector<int>> Matrica;

int NajvecaSirina(Matrica m)
{
    if(m.size()==0) {
        return 0;
    }
    int broj = m[0][0];
    int brojtemp = 0;
    int brojac1=0,brojac=0;
    if(broj<0) brojac++;
    broj=abs(broj);
    while(broj>0) {
        broj/=10;
        brojac++;
    }

    for(int i = 0; i<m.size(); i++) {
        for(int j = 0; j<m[i].size(); j++) {
            brojtemp=m[i][j];
            if(brojtemp<0) brojac1++;
            if(brojtemp==std::numeric_limits<int>::min()) return 1;
            brojtemp=abs(brojtemp);
            while(brojtemp>0) {
                brojtemp/=10;
                brojac1++;
            }
            if(brojac1>brojac) {
                brojac=brojac1;
            }
            brojac1=0;
        }
    }


    return brojac;
}

Matrica PascalovTrougao(int n)
{
    try {
        if(n<0) throw std::domain_error("Broj redova ne smije biti negativan");
    } catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what()<<"\n";
        Matrica n(0);
        return n;
    }
    Matrica m(n);
    if(n==0) return m;

    for(int i = 0; i<n; i++) m[i].resize(i+1);
    int i =0;
    int j =0;
    int broj = 1;
    m[0][0]=1;
    while(i<n) {
        for(int z=0; z<=i; z++) {
            if(i==0 || j==0 || z==i) {
                m[i][j]=1;
            } else {
                m[i][j]=m[i-1][j]+m[i-1][j-1];
            }
            j++;
        }
        i++;
        j=0;
    }
    return m;
}

int main ()
{
    int n;
    std::cout<<"Unesite broj redova: ";
    std::cin>>n;
    Matrica m = PascalovTrougao(n);
    std::cout<<"\n";
    for(int i = 0; i<m.size(); i++) {
        for(int j = 0; j<m[i].size(); j++) {
            std::cout<<std::setw(NajvecaSirina(m)+1)<<m[i][j];
        }
        std::cout<<"\n";
    }

    return 0;
}
