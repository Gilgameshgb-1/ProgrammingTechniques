#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <memory>

struct Dijete {
    std::string ime;
    std::shared_ptr<Dijete> sljedeci;
};

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
    std::shared_ptr<Dijete>pocetak=nullptr;
    std::shared_ptr<Dijete> prethodni;
    for(int i = 0; i<v.size(); i++) {
        std::shared_ptr<Dijete> novi = std::make_shared<Dijete>(Dijete{v[i],nullptr});
        if(!pocetak) pocetak = novi;
        else prethodni->sljedeci = novi;
        prethodni = novi;
        novi = nullptr;
    }
    prethodni->sljedeci=pocetak;
    std::vector<std::set<std::string>> povratni(k);
    int brojacp = 0;
    int i = 0;
    std::shared_ptr<Dijete>constp = pocetak;
    std::shared_ptr<Dijete>p = pocetak;
    std::shared_ptr<Dijete>tempp = pocetak;
    int q = 0;
    while(i!=prvihpar) {
        q++;
        povratni[i].insert(p->ime);
        std::string temp = p->ime;
        tempp = p->sljedeci;
        p=tempp;
        std::shared_ptr<Dijete> TempY = p;
        for(int x = 0; x<v.size()-q-1; x++) {
            TempY = TempY->sljedeci;
            if(x==(v.size()-q-2)) {
                std::shared_ptr<Dijete> tempX = p;
                TempY->sljedeci = p;
            }
        }
        brojacp++;
        for(int j = 0; j<NakoBrojanje(temp)-1; j++) {
            p=p->sljedeci;
        }
        if(brojacp==brclprvih) {
            brojacp=0;
            i++;
        }
    }
    int c = 0;
    int h = i;
    pocetak = p;
    while(c<(k-h)) {
        q++;
        povratni[i].insert(p->ime);
        std::string temp = p->ime;
        if(v.size()-q!=0) {
            tempp = p->sljedeci;
            p=tempp;
            std::shared_ptr<Dijete> TempY = p;
            for(int x = 0; x<v.size()-q-1; x++) {
                TempY = TempY->sljedeci;
                if(x==(v.size()-q-2)) {
                    std::shared_ptr<Dijete> tempX = p;
                    TempY->sljedeci = p;
                }
            }
            brojacp++;
            if(v.size()-q!=1) {
                for(int j = 0; j<NakoBrojanje(temp)-1; j++) {
                    p=p->sljedeci;
                }
            }
            if(brojacp==brcldrugih) {
                brojacp=0;
                i++;
                c++;
            }
        } else {
            c++;
        }
    }
    p->sljedeci = nullptr;
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
    } catch(std::logic_error e) {
        std::cout<<"Izuzetak: "<<e.what();
    }
    return 0;
}
