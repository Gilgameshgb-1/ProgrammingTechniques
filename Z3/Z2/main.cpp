#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <tuple>
#include <set>

void IspisiIndeksPojmova(std::map<std::string,std::set<int>> mapa)
{
    for(auto it = mapa.begin(); it != mapa.end(); it++) {
        if(it->first!="") {
            std::cout << it->first <<": ";
            for(auto it2=it->second.begin(); it2!=it->second.end(); it2++) {
                if(it2!=--it->second.end()) {
                    std::cout<<*it2<<",";
                } else {
                    std::cout<<*it2;
                }
            }
            std::cout<<"\n";
        }
    }
}

std::set<int> PretraziIndeksPojmova(std::string s,std::map<std::string,std::set<int>> mapa)
{
    if(!mapa.count(s)) throw(std::logic_error("Unesena rijec nije nadjena!"));
    else {
        std::set<int> v;
        auto it = mapa.find(s);
        for(auto it2 = it->second.begin(); it2!=it->second.end(); it2++) {
            v.insert(*it2);
        }
        return v;
    }
}

bool Provjera(char c)
{
    if((c>='a' && c<='z') || (c>='0' && c<='9') || (c>='A' && c<='Z')) return true;
    else return false;
}

std::map<std::string,std::set<int>> KreirajIndeksPojmova(std::string s)
{
    std::map<std::string,std::set<int>> mapa;
    std::vector<std::string> v;
    std::string temp;
    for(int i = 0; i<s.size(); i++) {
        if(Provjera(s[i])==true) temp+=s[i];
        if((Provjera(s[i])==false || i==s.size()-1) && (std::count(v.begin(),v.end(),temp)<1)) {
            v.push_back(temp);
            temp="";
        } else if(Provjera(s[i])==false && (std::count(v.begin(),v.end(),temp)>=1)) {
            temp="";
        }
    }
    temp="";
    int indeks=0;
    for(int i = 0; i<v.size(); i++) {
        std::set<int> v1;
        for(int j = 0; j<s.size(); j++) {
            if(Provjera(s[j])==true && temp=="") {
                temp+=s[j];
                indeks = j;
            } else if(Provjera(s[j])==true) {
                temp+=s[j];
            }
            if(Provjera(s[j])==false || j==s.size()-1) {
                if(temp==v[i]) {
                    v1.insert(indeks);
                    temp="";
                    indeks=0;
                } else {
                    temp="";
                    indeks=0;
                }
            }
        }
        std::transform(v[i].begin(),v[i].end(),v[i].begin(),::tolower);
        if(v[i]!="") {
            mapa.insert({v[i],v1});
        }
    }
    return mapa;
}

int main ()
{
    std::string str;
    std::cout<<"Unesite tekst: ";
    std::getline(std::cin,str);
    std::map<std::string,std::set<int>> mapa= KreirajIndeksPojmova(str);
    IspisiIndeksPojmova(mapa);
    while(1) {
        std::cout<<"\nUnesite rijec: ";
        std::string temp;
        std::cin>>temp;
        if(temp==".") return 0;
        try {
            std::transform(temp.begin(),temp.end(),temp.begin(),::tolower);
            std::set<int> tempvec = PretraziIndeksPojmova(temp,mapa);
            for(auto x : tempvec) std::cout<<x<<" ";
        } catch(std::logic_error e) {
            std::cout<<e.what();
        }
    }
/*    std::map<std::string, std::set<int>> m = KreirajIndeksPojmova("abc aBc  cde g  aBC Abc ABC AbC CDE ");
    for (const auto &i : m)
    {
        for (const auto &j : i.second)
            std::cout << j << " ";
        std::cout << " <--- " << i.first << std::endl;
    }*/
    return 0;
}
