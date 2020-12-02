//TP 2018/2019: Tutorijal 4, Zadatak 2
#include <iostream>
#include <string>

void IzvrniString(std::string &s)
{
    int duzina = s.size();
    int z;
    for(int i = duzina-1; i>=0;  i--) {
        s.push_back(s.at(i));
    }
    int duzina1 = s.size();
    z=duzina;
    int i;
    for(i = 0; i<duzina; i++ ) {
        s.at(i)=s.at(z);
        z++;
    }s.resize(duzina);
}

int main ()
{
    std::string s;
    std::cout<<"Unesi string: ";
    std::getline(std::cin,s);
    IzvrniString(s);
    std::cout<<"Izvrnuti string je: "<<s;
    return 0;
}
