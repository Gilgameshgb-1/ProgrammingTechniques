#include <iostream>
#include <fstream>
#include <functional>
#include <cstring>
#include <algorithm>
#include <vector>

template <typename TipElemenata>
class DatotecniKontejner
{
    std::fstream tok;
public:
    DatotecniKontejner(const std::string &ime_datoteke){
        tok.open(ime_datoteke,std::ios::binary|std::ios::out);
        tok.close();
        tok.open(ime_datoteke,std::ios::in|std::ios::out|std::ios::binary);
        if(!tok) throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke");
    };
    void DodajNoviElement(const TipElemenata &element){
        TipElemenata kopija = element;
        tok.clear();
        tok.seekp(0, std::ios::end);
        tok.write(reinterpret_cast<char*> (&kopija),sizeof kopija);
        tok.flush();
    };
    int DajBrojElemenata(){
        int brojac = 0;
        TipElemenata var(0);
        tok.clear();
        tok.seekg(0,std::ios::beg);
        while(tok.read(reinterpret_cast<char*>(&var),sizeof var)){
            brojac++;
        }
        tok.flush();
        return brojac;
    };
    TipElemenata DajElement(int pozicija){
        if(pozicija<0 || pozicija >= DajBrojElemenata()) throw std::range_error("Neispravna pozicija");
        tok.clear();
        int x = pozicija*(sizeof(TipElemenata));
        tok.seekg(x,std::ios::beg);
        TipElemenata var = 0;
        tok.read(reinterpret_cast<char*>(&var),sizeof var);
        return var;
    };
    void IzmijeniElement(int pozicija, const TipElemenata &element){
        if(pozicija<0 || pozicija >= DajBrojElemenata()) throw std::range_error("Neispravna pozicija");
        tok.clear();
        tok.seekp(0,std::ios::beg);
        tok.seekp(pozicija*sizeof(TipElemenata),std::ios::beg);
        TipElemenata kopija = element;
        tok.write(reinterpret_cast<char*>(&kopija),sizeof kopija);
        tok.flush();
    };
    void Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)>kriterij = std::less<TipElemenata>()){
        tok.clear();
        for(int i = 0;i<DajBrojElemenata();i++){
            for(int j = i;j<DajBrojElemenata();j++){
                if(kriterij(DajElement(j),DajElement(i))){
                    TipElemenata temp = DajElement(j);
                    IzmijeniElement(j,DajElement(i));
                    IzmijeniElement(i,temp);
                }
            }
        }
    };
};



int main ()
{
    
    return 0;
}
