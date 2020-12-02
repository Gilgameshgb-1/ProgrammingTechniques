#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <string>

int NakoBrojanje(std::string s)
{
    int brojac=0;
    for(int i = 0; i<s.size(); i++) {
        if((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || (s[i]>='0' && s[i]<='9')) {
            brojac++;
        }
    }
    return brojac;
}
std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> v,int k)
{
    if(k>v.size() || k<=0) throw std::logic_error("Razvrstavanje nemoguce");
    int prvihpar = v.size()%k;
    int drugihpar = v.size()/k;
    int brclprvih = v.size()/k+1;
    int brcldrugih = v.size()/k;
    std::list<std::string> kopija;
    for(int i = 0; i<v.size(); i++) {
        kopija.push_back(v[i]);
    }
    std::vector<std::set<std::string>> povratni(k);
    int brojacp = 0;
    auto it = kopija.begin();
    auto predkraj = kopija.end()--;
    int i = 0;
    //prvi timovi
    while(i!=prvihpar) {
        povratni[i].insert(*it);
        std::string temp = *it;
        it = kopija.erase(it);
        auto predkraj = kopija.end()--;// ovaj ovdje iterator se uvijek vraca jedno mjesto unazad od kraja
        brojacp++;
        for(int i = 0; i<NakoBrojanje(temp)-1; i++) {
            if(it==predkraj) it = kopija.begin();
            it++;
            if(it==predkraj) it = kopija.begin();
        }
        if(brojacp==brclprvih) {
            brojacp=0;
            i++;
        }
    }
    int c = 0;
    int h = i;
    //drugi timovi
    while(c<(k-h)) {
        povratni[i].insert(*it);
        std::string temp = *it;
        it = kopija.erase(it);
        auto predkraj = kopija.end()--;
        brojacp++;//nako brojanje broji broj slova
        for(int i = 0; i<NakoBrojanje(temp)-1; i++) {
            if(it==predkraj) it = kopija.begin();//kad dodje pred kraj ide na pocetak
            it++;
            if(it==predkraj) it = kopija.begin();
        }
        if(brojacp==brcldrugih) {
            brojacp=0;
            i++;
            c++;
        }
    }
    return povratni;
}

int main ()
{
    std::cout<<"Unesite broj djece: ";
    int brojdjece;
    std::cin>>brojdjece;
    std::cout<<"Unesite imena djece: ";
    std::cin.ignore(10000,'\n');
    std::vector<std::string> v;
    for(int i=0; i<brojdjece; i++) {
        std::string temp;
        std::getline(std::cin,temp);
        v.push_back(temp);
    }
    int brojtimova;
    std::cout<<"\nUnesite broj timova: ";
    std::cin>>brojtimova;
    try {
        std::vector<std::set<std::string>> z = Razvrstavanje(v,brojtimova);
        for(int i=0 ; i<brojtimova; i++) {
            std::cout<<"Tim "<<i+1<<": ";
            for(auto it = z[i].begin(); it!=z[i].end(); it++) {
                if(it!=(--z[i].end())) std::cout<<*it<<", ";
                else std::cout<<*it;
            }
            std::cout<<'\n';
        }
    } catch(std::logic_error e){
        std::cout<<"Izuzetak: "<<e.what();
    }
        return 0;
}
