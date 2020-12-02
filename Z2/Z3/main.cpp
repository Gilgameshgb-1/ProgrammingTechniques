/* TP, 2018/2019
*/
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

template <typename Tip1,typename Tip2,typename Tip3>
Tip3 SimetricnaRazlikaBlokova(Tip1 p1,Tip1 p2,Tip2 p3,Tip2 p4,Tip3 p5)
{
    int duzina1=0;
    Tip1 pok2= p1;
    while(pok2!=p2) {
        duzina1++;
        pok2++;
    }
    Tip2 pok1=p3;
    int duzina2 = 0;
    while(pok1!=p4) {
        duzina2++;
        pok1++;
    }
    bool kontrola = false;
    Tip3 pok = p5;
    for(int i = 0; i<duzina1; i++) {
        kontrola = false;
        for(int j = 0; j<duzina2; j++) {
            if(*(p1+i)==*(p3+j)) {
                kontrola=true;
                break;
            }
        }
        if(kontrola == false  && std::count(pok,p5,*(p1+i))==0) {
            *p5++=*(p1+i);
        }
    }
    for(int i = 0; i<duzina2; i++) {
        kontrola = false;
        for(int j = 0; j<duzina1; j++) {
            if(*(p3+i)==*(p1+j)) {
                kontrola=true;
                break;
            }
        }
        if(kontrola == false  && std::count(pok,p5,*(p3+i))==0) {
            *p5++=*(p3+i);
        }
    }
    return p5;
}

int main ()
{
    int niz[100];
    std::deque<int> dek;
    int broj;
    std::cout<<"Unesite broj elemenata niza";
    std::cin>>broj;
    std::cout<<"\nUnesite elemente niza";
    for(int i = 0; i<broj; i++) {
        int temp;
        std::cin>>temp;
        niz[i]=temp;
    }
    int broj1;
    std::cout<<"\nUnesite broj elemenata deka";
    std::cin>>broj1;
    std::cout<<"\nUnesite elemente deka";
    for(int i = 0; i<broj1; i++) {
        int temp;
        std::cin>>temp;
        dek.push_back(temp);
    }
    std::vector<int> v;
    v.resize(broj*2);
    std::vector<int>::iterator poc = v.begin();
    std::vector<int>::iterator p=(SimetricnaRazlikaBlokova(niz,niz+broj,dek.begin(),dek.end(),v.begin()));
    v.resize(p-v.begin());
    if(v.size()!=0) {
        std::cout<<"\nSimetricna razlika blokova je:";
        for(p = v.begin(); p!=v.end(); p++) {
            std::cout<<" "<<*p;
        }
    } else std::cout<<"\nBlokovi nemaju simetricnu razliku";
    return 0;
}
