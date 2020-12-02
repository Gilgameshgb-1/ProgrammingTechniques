/* TP, 2018/2019
*/
#include <iostream>
#include <string>
#include <algorithm>

std::string smanji(std::string str)
{
    for(int i = 0; i<str.length(); i++) {
        if(str[i]>='A' && str[i]<='Z') str[i]+=32;
    }
    return str;
}

bool KriterijSortiranja(std::string p1,std::string p2)
{
    if(p1.size()<p2.size()) return true;
    if(p1.size()==p2.size()) {
        std::string temp1 = p1;
        std::string temp2 = p2;
        temp1=smanji(temp1);
        temp2=smanji(temp2);
        if(temp1<temp2) return true;
        else return false;
    }
    return false;
}

void SortirajPoDuzini(std::string* p1,int n)
{
    std::sort(p1,(p1+n),KriterijSortiranja);
}

bool PretraziBinarno(std::string* p1,int n,std::string pretraga)
{
    std::string* temp = new std::string[n];
    std::copy(p1,p1+n,temp);
    if(std::binary_search(temp,temp+n,pretraga)) {
        delete[] temp;
        return true;
    }
    delete[] temp;
    return false;
}

int main ()
{
    std::cout<<"Unesite broj rijeci: ";
    int broj;
    std::cin>>broj;
    std::cout<<"Unesite rijeci: ";
    std::string* poc = new std::string[broj];
    for(int i =0; i<broj; i++) {
        std::string temp;
        std::cin>>temp;
        *(poc+i)=temp;
    }
    SortirajPoDuzini(poc,broj);
    std::cout<<"Sortirane rijeci:";
    for(int i =0; i<broj; i++) {
        std::cout<<" "<<*(poc+i);
    }
    std::cout<<"\nUnesite rijec za pretragu: ";
    std::string temp;
    std::cin>>temp;
    if(PretraziBinarno(poc,broj,temp)   ==true) std::cout<<"Rijec "<<"'"<<temp<<"' "<<"se nalazi u nizu.";
    else std::cout<<"Rijec "<<"'"<<temp<<"' "<<"se ne nalazi u nizu.";
    delete[] poc;
}
    return 0;
}
