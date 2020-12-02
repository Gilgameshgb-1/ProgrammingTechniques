//TP 2018/2019: Tutorijal 4, Zadatak 3
#include <iostream>
#include <string>
#include <vector>

bool LeksikografskiPoredak(std::string s1,std::string s2)
{
    for(int i = 0; i<s1.size(); i++) {
        s1.at(i)=char(std::toupper(s1.at(i)));
    }
    for(int i = 0; i<s2.size(); i++) {
        s2.at(i)=char(std::toupper(s2.at(i)));
    }
    if(s1>s2) return true;
    if(s1<s2) return false;
    return false;
}

void IzdvojiKrajnjeRijeci(std::vector<std::string> v,std::string &str1,std::string &str2)
{
    if(v.size()!=0) {
        std::string tempprva=v.at(0);
        std::string tempzadnja=v.at(0);
        for(int i = 1; i<v.size(); i++) {
            if(LeksikografskiPoredak(v.at(i),tempzadnja)==true) tempzadnja=v.at(i);
            if(LeksikografskiPoredak(v.at(i),tempprva)==false) tempprva=v.at(i);
        }
        str1=tempprva;
        str2=tempzadnja;
    }
}

void ZadrziDuplikate(std::vector<std::string> &v)
{
    std::string tempstring="";
    if(v.size()!=0) {
        std::vector<std::string> v1;
        int brojac = 0;
        for(int i = 0; i<v.size()-1; i++) {
            for(int j = (i+1); j<v.size(); j++) {
                if(v.at(i)==v.at(j) && v.at(i)!=tempstring) {
                    v1.push_back(v.at(i));
                    brojac++;
                    tempstring=v.at(i);
                }
            }
        }
        v.resize(brojac);
        for(int i = 0; i<v.size(); i++) {
            v.at(i)=(v1.at(i));
        }
    }
}

int main ()
{
        int broj;
        std::string s1;
        std::string s2;
        std::string tempstring;
        std::vector<std::string> v;

        std::cout<<"Koliko zelite unijeti rijeci: ";
        std::cin>>broj;
        std::cout<<"Unesite rijeci: ";
        for(int i = 0; i<broj; i++){
            std::cin>>tempstring;
            v.push_back(tempstring);
        }

        IzdvojiKrajnjeRijeci(v,s1,s2);
        ZadrziDuplikate(v);
        std::cout<<"\nPrva rijec po abecednom poretku je: "<<s1;
        std::cout<<"\nPosljednja rijec po abecednom poretku je: "<<s2;
        std::cout<<"\nRijeci koje se ponavljaju su: ";
        for(int i = 0;i <v.size();i++){
            std::cout<<v.at(i)<<" ";
        }
    return 0;
}
