#include <iostream>
#include <map>
#include <string>
bool DaLiJeSlovo(char c)
{
    if((c>='a' && c<='z') || (c>='A' && c<='Z')) return true;
    return false;
}

bool Provjera(std::string s,std::map<std::string,std::string> mapa)
{
    auto it = mapa.find(s);
    if(it == mapa.end()) return false;
    else return true;
}

std::string ZamijeniPremaRjecniku(std::string s,std::map<std::string,std::string> rijecnik)
{
    std::string vracamo;
    for(int i = 0; i <s.size(); i++) {
        std::string temp="";
        if(DaLiJeSlovo(s[i])) {
            while(s[i]!=' ' && i!=(s.size())) {
                temp+=s[i];
                i++;
            }
            if(Provjera(temp,rijecnik)) {
                auto it = rijecnik.find(temp);
                vracamo += it->second;
                vracamo.push_back(s[i]);
            } else {
                vracamo+=temp;
                if(i!=s.size()){
                vracamo.push_back(s[i]);
                }
            }
        } else {
            vracamo.push_back(s[i]);
        }
    }
    return vracamo;
}

int main ()
{
    return 0;
}
