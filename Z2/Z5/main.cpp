/* TP, 2018/2019
*/
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

template <typename Tip1,typename Tip2>
bool ZaSve(Tip1 p1,Tip1 p2,Tip2 fun)
{
    if(p1!=p2) {
        if(fun(*p1)==false) return false;
        p1++;
        ZaSve(p1,p2,fun);
    } else return true;
}

template <typename Tip1,typename Tip2>
bool MakarJedan(Tip1 p1,Tip1 p2,Tip2 fun)
{
    if(p1!=p2) {
        if(fun(*p1)==true) return true;
        p1++;
        MakarJedan(p1,p2,fun);
    } else return false;
}

template <typename Tip1,typename Tip2,typename Tip3>
Tip3 Akumuliraj(Tip1 p1,Tip1 p2,Tip2 fun,Tip3 &a)
{
    if(p1!=p2) {
        a=fun(*p1,a);
        p1++;
        Akumuliraj(p1,p2,fun,a);
    }
    return a;
}

int main ()
{
    std::cout<<"Unesite string: ";
    std::string str;
    std::getline(std::cin,str);
    if(ZaSve(str.begin(),str.end(),[](char x){return ((x>='0' && x<='9') || (x>='A' && x<='Z') || (x>='a' && x<='z'));})) std::cout<<"Uneseni string sadrzi samo slova i cifre";
    else std::cout<<"Uneseni string sadrzi i druge znakove osim slova i cifara";
    std::cout<<"\nUnesite niz od 10 brojeva: ";
    int niz[10];
    std::for_each(niz,niz+10,[](int &a){std::cin>>a; return a;});
    if(MakarJedan(niz,niz+10,[](int a){int temp = a; if(temp == 0) return false;int suma=0;while(temp!=0){suma+=temp%10;temp/=10;} if(a%suma==0) return true; else return false;})==true) std::cout<<"U nizu ima brojeva djeljivih sa sumom svojih cifara";
    else std::cout<<"U nizu nema brojeva djeljivih sa sumom svojih cifara";
    std::cout<<"\nUnesite dek od 10 elemenata: ";
    std::deque<int> v;
    v.resize(10);
    std::for_each(v.begin(),v.end(),[](int &a){std::cin>>a; return a;});
    int suma = 0;
    std::cout<<"\nSuma deka: "<<Akumuliraj(v.begin(),v.end(),[](int a,int b){return a+b;},suma);
    int produkt = 1;
    std::cout<<"\nProdukt deka: "<<Akumuliraj(v.begin(),v.end(),[](int a,int b){return a*b;},produkt);
    int max = v.at(0);
    std::cout<<"\nNajveci elemenat deka: "<<Akumuliraj(v.begin(),v.end(),[](int a,int b){if(a>b) return a; else return b;},max);
    int min = v.at(0);
    std::cout<<"\nNajmanji elemenat deka: "<<Akumuliraj(v.begin(),v.end(),[](int a,int b){if(a<b) return a; else return b;},min);
    return 0;
}
