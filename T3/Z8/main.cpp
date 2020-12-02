//TP 2017/2018: Tutorijal 3, Zadatak 8
#include <iostream>
#include <string>

std::string IzdvojiRijec(std::string s,int n)
{
    int brojac=0;
    int z = 0;
    std::string izvod;
    for(int i = 0; i<=s.length(); i++) {
        if(s[i]==' ' && s[i+1]!=' ' && s[i+1]!='\0') {
            brojac++;
        }
    }
    if(s[0]!=' ') {
        brojac=1;
    }
    if(s[0]=='\0'){
        brojac=0;
    }
    if(n<0 || n>brojac) throw std::range_error("IZUZETAK: Pogresan redni broj rijeci!");
    brojac=0;
    if(s[0]!=' ') {
        brojac=1;
    }
    for(int i = 0; i<=s.length(); i++) {
        if(s[i]==' ' && s[i+1]!=' ') {
            brojac++;
            i++;
        }
        if(brojac==n) {
            while(s[i]!=' ' && i<s.length()) {
                izvod+=s[i];
                i++;
                z++;
            }
            izvod[z]='\0';
            return izvod;
        }
    }

    return izvod;
}

int main ()
{
    int broj;
    std::string s;
    std::string rijesenje;
    std::cout<<"Unesite redni broj rijeci: ";
    try {
        std::cin>>broj;
        std::cin.ignore(1000,'\n');
        std::cout<<"Unesite recenicu: ";
        std::getline(std::cin,s);
        rijesenje=IzdvojiRijec(s,broj);
    } catch(std::range_error izuzetak) {
        std::cout<<izuzetak.what();
        return 0;
    }
    std::cout<<"Rijec na poziciji "<<broj<<" je "<<rijesenje;

    return 0;
}
