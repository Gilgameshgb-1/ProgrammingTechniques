/* TP, 2018/2019
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

void RastavaBroja(int n,int &a,int &b)
{
    std::vector<int> v;
    std::vector<int> stepeni;
    std::vector<int> baza;
    std::vector<int> visak;
    bool biggay=false;
    int temp = n;
    try {
        if(n<=0) throw std::domain_error("Broj koji se rastavlja mora biti prirodan");
        while(n%2==0) {
            v.push_back(2);
            n/=2;
        }
        for(int i = 3; i<=sqrt(n); i+=2) {
            while(n%i==0) {
                v.push_back(i);
                n/=i;
            }
            if(n==0) break;
        }
        if(n>2) {
            v.push_back(n);
            biggay=true;
        }
        for(int i =0; i<sqrt(temp); i++) {
            if(count(v.begin(),v.end(),i)>1) {
                int c = count(v.begin(),v.end(),i);
                if(c%2==0) {
                    stepeni.push_back(c);
                    baza.push_back(i);
                } else {
                    stepeni.push_back(c-1);
                    baza.push_back(i);
                    visak.push_back(i);
                }
            } else if(count(v.begin(),v.end(),i)==1) {
                visak.push_back(i);
            }
        }
        if(biggay==true && n>sqrt(temp)) visak.push_back(n);
        int q = 1;
        int p = 1;
        for(int i =0; i<stepeni.size(); i++) {
            q*=pow(baza.at(i),stepeni.at(i));
        }
        q=sqrt(q);
        for(int i =0 ; i<visak.size(); i++) {
            p*=visak.at(i);
        }
        a=p;
        b=q;
    } catch(std::domain_error e) {
        throw std::domain_error ("Broj koji se rastavlja mora biti prirodan");
    }
}

int main ()
{
    int a,b,broj;
    std::cout<<"Unesite prirodan broj\n";
    try {
        std::cin>>broj;
        RastavaBroja(broj,a,b);
        std::cout<<a<<" "<<b;
    } catch(std::domain_error e) {
        std::cout<<"Izuzetak: "<<e.what()<<"!";
    }
    return 0;
}
