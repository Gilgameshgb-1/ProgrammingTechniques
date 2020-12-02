#include <iostream>
#include <string>
#include <vector>

enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};

Dani &operator++(Dani &d){
	return d = Dani((int(d)+1)%7);
}


Dani operator++(Dani &d,int){
	Dani pomocni = d; ++d; return pomocni;
}

std::ostream &operator<<(std::ostream &tok,const Dani d){
	std::vector<std::string> v{"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};
	return tok<<v[d];
}

int main ()
{
	return 0;
}