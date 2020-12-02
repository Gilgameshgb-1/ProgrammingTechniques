/* TP, 2018/2019
*/
#include <iostream>

bool aktivnost = true;

enum class Smjer {Nalijevo, Nadesno};
enum class Pravci {Sjever, Istok, Jug, Zapad};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};

void AktivirajRobota();//aktivira

void DeaktivirajRobota();//deaktivira

void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu);//okrece robota
// na_koju_stranu = [nalijevo,nadesno]
void Idi(int &x,int &y, Pravci orijentacija,int korak);//pomjera za broj koraka u smjeru odredjenom orijentacijom
//x,y trenutna pozicija
void IspisiPoziciju(int x,int y, Pravci Orijentacija);

void PrijaviGresku(KodoviGresaka kod_greske);

void IzvrsiKomandu(Komande komanda,int parametar,int &x,int &y,Pravci &orijentacija);

bool UnosKomande(Komande &komanda,int &parametar, KodoviGresaka &kod_greske)
{
    
}

int main ()
{
    while(1) {
        char z;
        while(std::cin.peek()!='\n') {
            z=std::cin.get();
            UnosKomande(z,)
        }
  //      UnosKomande(z);
   //     std::cout<<"Robot je trenutno"<<aktivnost<<", nalazi se na poziciji("<<0<<","<<0<<") i gleda na"<<sjever<<".";
    }
    return 0;
}
