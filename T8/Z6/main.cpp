#include <iostream>

template <typename TipElemenata>
struct Cvor {
    TipElemenata element;
    Cvor<TipElemenata> *veza;
};

template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni)
{
    Cvor<TipElemenata>* pocetak=nullptr,*prethodni;
    while(1) {
        TipElemenata podatak;
        std::cin>>podatak;
        if(podatak==zavrsni) break;
        Cvor<TipElemenata>* novi = new Cvor<TipElemenata> {podatak,nullptr};
        if(!pocetak) pocetak = novi;
        else prethodni->veza = novi;
        prethodni=novi;
    }
    return pocetak;
}

template <typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak)
{
    int c = 0;
    for(auto p=pocetak; p!=nullptr; p=p->veza) {
        c++;
    }
    return c;
}

template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak)
{
    TipElemenata suma = 0;
    for(auto p=pocetak; p!=nullptr; p=p->veza) {
        suma+=p->element;
    }
    return suma;
}

template <typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag)
{
    int c = 0;
    for(auto p=pocetak; p!=nullptr; p=p->veza) {
        if(p->element>prag) {
            c++;
        }
    }
    return c;
}

template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak)
{
    Cvor<TipElemenata>* iduci;
    while(pocetak!=nullptr) {
        iduci = pocetak->veza;
        delete pocetak;
        pocetak = iduci;
    }
}

int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    auto a = KreirajPovezanuListu(0.0);
    double aritm = SumaElemenata(a)/BrojElemenata(a);
    std::cout<<"U slijedu ima "<<BrojVecihOd(a,aritm)<<" brojeva vecih od njihove aritmeticke sredine";
    UnistiListu(a);
    return 0;
}
