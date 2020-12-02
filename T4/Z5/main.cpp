//TP 2018/2019: Tutorijal 4, Zadatak 5
#include <iostream>
#include <vector>
#include <string>

template <typename Nekitip>
bool Duplikat(Nekitip varijabla,std:: vector<Nekitip> v)
{
    for(int i=0; i<v.size(); i++) {
        if(varijabla==v.at(i)) return true;
    }
    return false;
}

template <typename Nekitip>
std::vector<Nekitip> Presjek(std::vector<Nekitip> v1,std::vector<Nekitip> v2)
{
    std::vector<Nekitip> v3;
    for(int i = 0; i<v1.size(); i++) {
        for(int j = 0; j<v2.size(); j++) {
            if(v1.at(i)==v2.at(j) && Duplikat(v1.at(i),v3)==false) {
                v3.push_back(v1.at(i));
            }
        }
    }
    return v3;
}

int main ()
{
           std::vector<double> v1;
            std::vector<double> v2;
            std::cout<<"Test za realne brojeve...";
            std::cout<<"\nUnesite broj elemenata prvog vektora: ";
            int broj1;
            std::cin>>broj1;
            std::cout<<"Unesite elemente prvog vektora: ";
            for(int i = 0; i<broj1; i++) {
                int temp;
                std::cin>>temp;
                v1.push_back(temp);
            }
            std::cout<<"Unesite broj elemenata drugog vektora: ";
            int broj2;
            std::cin>>broj2;
            std::cout<<"Unesite elemente drugog vektora: ";
            for(int i = 0; i<broj2; i++) {
                int temp;
                std::cin>>temp;
                v2.push_back(temp);
            }
            std::vector<double> v3;
            v3=Presjek(v1,v2);
            std::cout<<"Zajednicki elementi su:";
            for(int i = 0 ; i<v3.size(); i++){
                std::cout<<" "<<v3.at(i);
            }
            std::cin.clear();
            std::cin.ignore(10000,'\n');
    std::vector<std::string> v4;
    std::vector<std::string> v5;
    std::cout<<"\nTest za stringove...";
    std::cout<<"\nUnesite broj elemenata prvog vektora: ";
    int broj3;
    std::cin>>broj3;
    std::cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    for(int i = 0; i<broj3+1; i++) {
        std::string temp;
        std::getline(std::cin,temp);
        v4.push_back(temp);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    int broj4;
    std::cin>>broj4;
    std::cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    for(int i = 0; i<broj4+1; i++) {
        std::string temp;
        std::getline(std::cin,temp);
        v5.push_back(temp);
    }
    std::vector<std::string> v6;
    v6=Presjek(v4,v5);
    std::cout<<"Zajednicki elementi su:";
    for(int i = 0 ; i<v6.size(); i++) {
        std::cout<<'\n';
        std::cout<<v6.at(i);
    }
    return 0;
}
