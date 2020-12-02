#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename TipEl,template <typename...> class Kontejner = std::vector>
    class Tok{
        Kontejner<TipEl> kolekcija;
    public:
        template <typename TipEl2, template<typename...> class Kontejner2>
            friend class Tok;//Stavara prijateljstvo izmedju razlictih tokova
        template <typename IterTip>
            Tok(IterTip pocetak,const IterTip iza_kraja){
                auto it1 = std::begin(kolekcija);
                for(auto it = pocetak; it!=iza_kraja; it++){
                    /*ontejner<TipEl>::iterator*/
                    kolekcija.insert(it1,*it);
                }
            };
        template <typename IterabilniKontejner>
            Tok(const IterabilniKontejner &kontejner){
                for(auto it = std::begin(kontejner);it!=std::end(kontejner);it++){
                    auto it1 = std::end(kolekcija);
                    kolekcija.insert(it1,*it);
                }
            };
        Tok(std::initializer_list<TipEl> lista):kolekcija(lista){};
        static Tok<TipEl,Kontejner> Opseg(TipEl poc,TipEl kraj,TipEl korak = 1){
            TipEl temp = poc;
            Kontejner<TipEl> nesto;
            for(temp ; temp!=kraj; temp+korak){
                nesto.insert(nesto.end(),temp);
            }
            return nesto;
        };
        unsigned int Velicina() const{
            return std::end(kolekcija)-std::begin(kolekcija);
        };
        bool Prazan() const{
            if(std::begin(kolekcija)==std::end(kolekcija)) return true;
            return false;
        };
        Tok<TipEl,Kontejner> Limitiraj(unsigned int n) const{
            Kontejner<TipEl> nesto;
            auto it = std::begin(nesto);
            auto it1 = std::begin(kolekcija);
            for(int i = 0;i<n;i++){
                nesto.insert(it,*it1);
                it++;
                it1++;
            }
        };
        Tok<TipEl,Kontejner> Preskoci(unsigned int n) const{
            Kontejner<TipEl> nesto(kolekcija);
            for(auto i = std::begin(kolekcija)+n;i!=std::end(kolekcija);i++){
                nesto.insert(++i,*i);
            }
        };
        Tok<TipEl,Kontejner> Obrnut() const{
            Kontejner<TipEl> nesto;
            for(auto i = std::end(kolekcija)-1; i >=std::begin(kolekcija); i--){
                auto it = std::end(nesto);
                nesto.insert(it,*i);
            }
            return nesto;
        };
        Tok<TipEl,Kontejner> Akcija(std::function<void(void)> akcija) const{
            Kontejner<TipEl> nesto = kolekcija;
            akcija();
            return nesto;
        };
        void ZaSvaki(std::function<void(TipEl)> akcija) const{
            for(auto it = std::begin(kolekcija);it!=std::end(kolekcija);it++){
                akcija(*it);
            }
        };
        Tok<TipEl,Kontejner> Filtriraj(std::function<bool(TipEl)> predikat) const{
            Kontejner<TipEl> nesto;
            for(auto it = std::begin(kolekcija);it!=std::end(kolekcija);it++){
                if(prekidat(*it)==true) nesto.insert(*it);
            }
        };
        TipEl PronadjiPrvi() const{
            if(Prazan()==true) throw std::logic_error("Tok je prazan");
            return *std::begin(kolekcija);
        };
        TipEl PronadjiPosljednji() const{
            if(Prazan()==true) throw std::logic_error("Tok je prazan");
            return *(std::end(kolekcija)-1);
        };
        bool ZadovoljavaBaremJedan(std::function<bool(TipEl)> kriterij) const{
            for(auto it = std::begin(kolekcija); it!=std::end(kolekcija); it++){
                if(kriterij(*it)==true) return true;
            }
            return false;
        };
        bool ZadovoljavaNijedan(std::function<bool(TipEl)> kriterij) const{
            for(auto it = std::begin(kolekcija); it!=std::end(kolekcija); it++){
                if(kriterij(*it)==true) return false;
            }
            return true;
        };
        bool ZadovoljavuSvi(std::function<bool(TipEl)> kriterij) const{
            for(auto it = std::begin(kolekcija); it!=std::end(kolekcija); it++){
                if(kriterij(*it)==false) return false;
            }
            return true;
        };
        TipEl Akumuliraj(TipEl inicijalna,std::function<TipEl(TipEl, TipEl)> akumulator) const{
            if(Prazan()==true) return inicijalna;
            if(Prazan()==true) throw std::logic_error("Tok je prazan");
            TipEl suma(0);
            auto poc = std::begin(kolekcija);
            auto kraj = std::end(kolekcija);
            while(poc!=kraj){
                inicijalna = akumulator(inicijalna,*poc);
                std::cout<<inicijalna<<"\n";
                ++poc;
            }
            return inicijalna;
        };
        TipEl Akumuliraj(std::function<TipEl(TipEl, TipEl)> akumulator) const{
            if(Prazan()==true) throw std::logic_error("Tok je prazan");
            TipEl suma(0);
            auto poc = std::begin(kolekcija);
            auto kraj = std::end(kolekcija);
            TipEl returnirajuca = *poc;
            poc++;
            while(poc!=kraj){
                returnirajuca = akumulator(returnirajuca,*poc);
                ++poc;
            }
            return returnirajuca;
        };
        Tok<TipEl, Kontejner> Sortirano(std::function<bool(TipEl, TipEl)> komparator
        = [](TipEl x, TipEl y) { return x < y; }) const{
            Kontejner<TipEl> temp = kolekcija;
            std::sort(std::begin(temp),std::end(temp),komparator);
            return temp;
        };
        Tok<TipEl, Kontejner> Unikatno(std::function<bool(TipEl, TipEl)> komparator
        = [](TipEl x, TipEl y) { return x == y; }) const{
            Kontejner<TipEl> temp = kolekcija;
            std::copy_if(std::begin(temp),std::end(temp),komparator);
            std::unique(std::begin(temp),std::end(temp));
            return temp;
        };
        Tok<TipEl, Kontejner> Proviri(std::function<void(TipEl)> akcija) const{
            Kontejner<TipEl> temp = kolekcija;
            temp.ZaSvaki(akcija());
            return *this;
        };
        TipEl Minimalan(std::function<bool(TipEl, TipEl)> komparator
        = [](TipEl x, TipEl y) { return x < y; }) const{
            if(std::begin(kolekcija)==std::end(kolekcija)) throw std::logic_error("Tok je prazan");
            return *std::min(std::begin(kolekcija),std::end(kolekcija));
        };
        TipEl Maksimalan(std::function<bool(TipEl, TipEl)> komparator
        = [](TipEl x, TipEl y) { return x > y; }) const{
            if(std::begin(kolekcija)==std::end(kolekcija)) throw std::logic_error("Tok je prazan");
            return *std::max(std::begin(kolekcija),std::end(kolekcija));
        };
        template <typename Kont2>
            Kont2 Sakupi(std::function<void(Kont2 &, TipEl)> kombinator) const{
                Kontejner<TipEl> temp;
                for(auto it = std::begin(kolekcija);it!=std::end(kolekcija);it++)
                kombinator(&temp,*it);
                return temp;
            };
        template <typename TipEl2>
            Tok<TipEl2, Kontejner> Mapiraj(std::function<TipEl2(TipEl)> maper) const{
                
            };
        template <typename TipEl2>
            Tok<TipEl2, Kontejner> MapirajPoravnato(
         std::function<Tok<TipEl2, Kontejner>(TipEl)> maper) const{
             
         };
};

int main ()
{
    return 0;
}