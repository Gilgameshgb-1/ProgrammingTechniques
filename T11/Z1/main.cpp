#include <iostream>

class NeobicnaKlasa
{
	int x;
public:
	explicit NeobicnaKlasa(int y){std::cout<<"\nDirektna inicijalizacija";}
	NeobicnaKlasa(double y){std::cout<<"\nKopirajuca inicijalizacija";}
};



int main ()
{
	return 0;
}
