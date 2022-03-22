#include <iostream>
#include <vector>
#include <complex>

typedef std::vector<std::vector<int>> Matrica;
typedef std::complex<double> Kompleksni;

int BrojRedova(Matrica m)
{
	return m.size();
}

int BrojKolona(Matrica m)
{
	return m.at(0).size();
}

Matrica KreirajMatricu(int broj_redova, int broj_kolona)
{
	return Matrica(broj_redova,std::vector<int>(broj_kolona));
}

bool ObicnaProvjera(Matrica a,int i, int j)
{
	int tempmax = a.at(i).at(j);
	if(a.at(i-1).at(j) <= tempmax && a.at(i-1).at(j+1)<=tempmax && a.at(i).at(j+1)<=tempmax &&	a.at(i+1).at(j+1)<=tempmax && a.at(i+1).at(j)<=tempmax && a.at(i+1).at(j-1)<=tempmax && a.at(i).at(j-1)<=tempmax &&a.at(i-1).at(j-1)<=tempmax) {
		return true;
	}
	return false;
}

bool GoreLijevoProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(a.at(i).at(j+1)<=tempmax && a.at(i+1).at(j+1)<=tempmax && a.at(i+1).at(j)<=tempmax) return true;
	return false;
}

bool GoreDesnoProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(a.at(i).at(j-1)<=tempmax && a.at(i+1).at(j)<=tempmax && a.at(i+1).at(j-1)<=tempmax) return true;
	return false;
}

bool DoleLijevoProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(a.at(i-1).at(j+1)<=tempmax && a.at(i).at(j+1)<=tempmax && a.at(i-1).at(j)<=tempmax) return true;
	return false;
}

bool DoleDesnoProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(a.at(i-1).at(j-1)<=tempmax && a.at(i-1).at(j)<=tempmax && a.at(i).at(j-1)<=tempmax) return true;
	return false;
}

bool GornjiRedProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(a.at(i).at(j+1)<=tempmax && a.at(i+1).at(j+1)<=tempmax && a.at(i+1).at(j)<=tempmax && a.at(i+1).at(j-1)<=tempmax && a.at(i).at(j-1)<=tempmax) return true;
	return false;
}

bool DonjiRedProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(a.at(i-1).at(j)<=tempmax && a.at(i-1).at(j+1)<=tempmax && a.at(i).at(j+1)<=tempmax && a.at(i).at(j-1)<=tempmax && a.at(i-1).at(j-1)<=tempmax) return true;
	return false;
}

bool LijeviRedProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(a.at(i-1).at(j)<=tempmax && a.at(i-1).at(j+1)<=tempmax && a.at(i).at(j+1)<=tempmax && a.at(i+1).at(j+1)<=tempmax && a.at(i-1).at(j)<=tempmax) return true;
	return false;
}

bool DesniRedProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(a.at(i-1).at(j)<=tempmax && a.at(i+1).at(j)<=tempmax && a.at(i+1).at(j-1)<=tempmax && a.at(i).at(j-1)<=tempmax && a.at(i-1).at(j-1)<=tempmax) return true;
	return false;
}

bool JedanRedProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(j!=BrojKolona(a)-1) {
		if(a.at(i).at(j+1)<=tempmax && a.at(i).at(j-1)<=tempmax) return true;
	} else {
		if(a.at(i).at(j)<=tempmax && a.at(i).at(j-1)<=tempmax) return true;
	}
	return false;
}

bool JednaKolonaProvjera(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	if(i!=BrojRedova(a)-1) {
		if(a.at(i+1).at(j)<=tempmax && a.at(i-1).at(j)<=tempmax) return true;
	} else {
		if(a.at(i-1).at(j)<=tempmax) return true;
	}
	return false;
}

Kompleksni SamoJednaKolona(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;
	if(a.at(i+1).at(j)>tempmax) {
		tempmax=a.at(i+1).at(j);
		vracanjei=(i+1);
		vracanjej=j;
	}
	if(i!=0 && a.at(i-1).at(j)>tempmax) {
		tempmax=a.at(i-1).at(j);
		vracanjei=(i-1);
		vracanjej=j;
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;
}

Kompleksni SamoJedanRed(Matrica a,int i, int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;
	if(a.at(i).at(j+1)>tempmax) {
		tempmax=a.at(i).at(j+1);
		vracanjei=i;
		vracanjej=(j+1);
	}
	if(a.at(i).at(j-1)>tempmax) {
		tempmax=a.at(i).at(j-1);
		vracanjei=i;
		vracanjej=(j-1);
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;
}

Kompleksni GornjiRed(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;
	if(a.at(i).at(j+1)>tempmax) {
		tempmax=a.at(i).at(j+1);
		vracanjei=(i);
		vracanjej=(j+1);
	}
	if(a.at(i+1).at(j+1)>tempmax) {
		tempmax=a.at(i+1).at(j+1);
		vracanjei=(i+1);
		vracanjej=(j+1);
	}
	if(a.at(i+1).at(j)>tempmax) {
		tempmax=a.at(i+1).at(j);
		vracanjei=(i+1);
		vracanjej=j;
	}
	if(a.at(i+1).at(j-1)>tempmax) {
		tempmax=a.at(i+1).at(j-1);
		vracanjei=(i+1);
		vracanjej=(j-1);
	}
	if(a.at(i).at(j-1)>tempmax) {
		tempmax=a.at(i).at(j-1);
		vracanjei=(i);
		vracanjej=(j-1);
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;
}

Kompleksni DonjiRed(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;
	if(a.at(i-1).at(j)>tempmax) {
		tempmax=a.at(i-1).at(j);
		vracanjei=(i-1);
		vracanjej=j;
	}
	if(a.at(i-1).at(j+1)>tempmax) {
		tempmax=a.at(i-1).at(j+1);
		vracanjei=(i-1);
		vracanjej=(j+1);
	}
	if(a.at(i).at(j+1)>tempmax) {
		tempmax=a.at(i).at(j+1);
		vracanjei=(i);
		vracanjej=(j+1);
	}
	if(a.at(i).at(j-1)>tempmax) {
		tempmax=a.at(i).at(j-1);
		vracanjei=(i);
		vracanjej=(j-1);
	}
	if(a.at(i-1).at(j-1)>tempmax) {
		tempmax=a.at(i-1).at(j-1);
		vracanjei=(i-1);
		vracanjej=(j-1);
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;
}

Kompleksni LijeviRed(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;
	if(a.at(i-1).at(j)>tempmax) {
		tempmax=a.at(i-1).at(j);
		vracanjei=(i-1);
		vracanjej=j;
	}
	if(a.at(i-1).at(j+1)>tempmax) {
		tempmax=a.at(i-1).at(j+1);
		vracanjei=(i-1);
		vracanjej=(j+1);
	}
	if(a.at(i).at(j+1)>tempmax) {
		tempmax=a.at(i).at(j+1);
		vracanjei=(i);
		vracanjej=(j+1);
	}
	if(a.at(i+1).at(j+1)>tempmax) {
		tempmax=a.at(i+1).at(j+1);
		vracanjei=(i+1);
		vracanjej=(j+1);
	}
	if(a.at(i+1).at(j)>tempmax) {
		tempmax=a.at(i+1).at(j);
		vracanjei=(i+1);
		vracanjej=j;
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;
}

Kompleksni DesniRed(Matrica a,int i,int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;
	if(a.at(i-1).at(j)>tempmax) {
		tempmax=a.at(i-1).at(j);
		vracanjei=(i-1);
		vracanjej=j;
	}
	if(a.at(i+1).at(j)>tempmax) {
		tempmax=a.at(i+1).at(j);
		vracanjei=(i+1);
		vracanjej=j;
	}
	if(a.at(i+1).at(j-1)>tempmax) {
		tempmax=a.at(i+1).at(j-1);
		vracanjei=(i+1);
		vracanjej=(j-1);
	}
	if(a.at(i).at(j-1)>tempmax) {
		tempmax=a.at(i).at(j-1);
		vracanjei=(i);
		vracanjej=(j-1);
	}
	if(a.at(i-1).at(j-1)>tempmax) {
		tempmax=a.at(i-1).at(j-1);
		vracanjei=(i-1);
		vracanjej=(j-1);
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;
}

Kompleksni GornjiLijevi(Matrica a,int i, int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;

	if(a.at(i).at(j+1)>tempmax) {
		tempmax=a.at(i).at(j+1);
		vracanjej=(j+1);
		vracanjei=i;
	}

	if(a.at(i+1).at(j+1)>tempmax) {
		tempmax=a.at(i+1).at(j+1);
		vracanjei=(i+1);
		vracanjej=(j+1);
	}

	if(a.at(i+1).at(j)>tempmax) {
		tempmax=a.at(i+1).at(j);
		vracanjei=(i+1);
		vracanjej=j;
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;
}

Kompleksni GornjiDesni(Matrica a,int i, int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;

	if(a.at(i+1).at(j)>tempmax) {
		tempmax=a.at(i+1).at(j);
		vracanjei=(i+1);
		vracanjej=j;
	}
	if(a.at(i+1).at(j-1)>tempmax) {
		tempmax=a.at(i+1).at(j-1);
		vracanjei=(i+1);
		vracanjej=(j-1);
	}

	if(a.at(i).at(j-1)>tempmax) {
		tempmax=a.at(i).at(j-1);
		vracanjej=(j-1);
		vracanjei=i;
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;
}

Kompleksni DonjiLijevi(Matrica a,int i, int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;

	if(a.at(i-1).at(j)>tempmax) {
		tempmax=a.at(i-1).at(j);
		vracanjej=j;
		vracanjei=(i-1);
	}

	if(a.at(i-1).at(j+1)>tempmax) {
		tempmax=a.at(i-1).at(j+1);
		vracanjei=(i-1);
		vracanjej=(j+1);
	}

	if(a.at(i).at(j+1)>tempmax) {
		tempmax=a.at(i).at(j+1);
		vracanjei=i;
		vracanjej=(j+1);
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;

}

Kompleksni DonjiDesni(Matrica a,int i, int j)
{
	int tempmax=a.at(i).at(j);
	int vracanjei=i,vracanjej=j;

	if(a.at(i-1).at(j)>tempmax) {
		tempmax=a.at(i-1).at(j);
		vracanjej=j;
		vracanjei=(i-1);
	}

	if(a.at(i).at(j-1)>tempmax) {
		tempmax=a.at(i).at(j-1);
		vracanjei=i;
		vracanjej=(j-1);
	}

	if(a.at(i-1).at(j-1)>tempmax) {
		tempmax=a.at(i-1).at(j-1);
		vracanjei=(i-1);
		vracanjej=(j-1);
	}

	Kompleksni z(vracanjei,vracanjej);
	return z;

}

Kompleksni ObicniSlucaj(Matrica a,int i, int j)
{
	int tempmax = a.at(i).at(j);
	int vracanjei=i,vracanjej=j;

	if(a.at(i-1).at(j)>tempmax) {
		tempmax=a.at(i-1).at(j);
		vracanjei=(i-1);
		vracanjej=j;
	}
	if(a.at(i-1).at(j+1)>tempmax) {
		tempmax=a.at(i-1).at(j+1);
		vracanjei=(i-1);
		vracanjej=(j+1);
	}
	if(a.at(i).at(j+1)>tempmax) {
		tempmax=a.at(i).at(j+1);
		vracanjei=(i);
		vracanjej=(j+1);
	}
	if(a.at(i+1).at(j+1)>tempmax) {
		tempmax=a.at(i+1).at(j+1);
		vracanjei=(i+1);
		vracanjej=(j+1);
	}
	if(a.at(i+1).at(j)>tempmax) {
		tempmax=a.at(i+1).at(j);
		vracanjei=(i+1);
		vracanjej=j;
	}
	if(a.at(i+1).at(j-1)>tempmax) {
		tempmax=a.at(i+1).at(j-1);
		vracanjei=(i+1);
		vracanjej=(j-1);
	}
	if(a.at(i).at(j-1)>tempmax) {
		tempmax=a.at(i).at(j-1);
		vracanjei=(i);
		vracanjej=(j-1);
	}
	if(a.at(i-1).at(j-1)>tempmax) {
		tempmax=a.at(i-1).at(j-1);
		vracanjei=(i-1);
		vracanjej=(j-1);
	}
	Kompleksni z(vracanjei,vracanjej);
	return z;
}

std::complex<double> VrhMatrice(Matrica m, int pocred, int pockolona)
{
	bool devil_trigger = false;
	bool grbava = false;
	bool jedanred = false;
	bool jednakolona= false;
	if(BrojRedova(m)==1) jedanred=true;
	if(BrojRedova(m)!=0) {
		if(BrojKolona(m)==1) jednakolona=true;
	}
	Kompleksni z(0,0);
	Kompleksni suicide;
	if(jedanred==true && jednakolona==true) {
		return z;
	}
	int i=pocred,j=pockolona;
	for(int x = 0; x<BrojRedova(m); x++ ) {
		if(m.at(x).size()!=m.at(0).size()) {
			grbava = true;
			break;
		}
	}
	try {
		if(grbava==true || m.size()==0 || m.at(0).size()==0) throw std::domain_error("Nekorektna matrica");
		if(pocred>BrojRedova(m) || pocred<0 || pockolona<0 || pockolona>BrojKolona(m)) throw std::range_error("Nekorektna pocetna pozicija");
	} catch(std::range_error e) {
		throw std::range_error ("Nekorektna pocetna pozicija");
		return suicide;
	} catch(std::domain_error e) {
		throw std::domain_error ("Nekorektna matrica");
		return suicide;
	}
	while(devil_trigger==false) {
		if(i==0 && j==0 && jednakolona==false) {
			z=GornjiLijevi(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i==0 && j==BrojKolona(m)-1 && jednakolona==false) {
			z=GornjiDesni(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i==BrojRedova(m)-1 && j==0 && jednakolona==false) {
			z=DonjiLijevi(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i==BrojRedova(m)-1 && j==BrojKolona(m)-1) {
			z=DonjiDesni(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i==0 && j!=0 && j!=BrojKolona(m)-1 && jedanred==false) {
			z=GornjiRed(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i==BrojRedova(m)-1 && j!=0 && j!=BrojKolona(m)-1 && jedanred==false) {
			z=DonjiRed(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i==0 && jedanred==true && j<BrojKolona(m)) {
			z=SamoJedanRed(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(j==0 && jednakolona==true && i<BrojRedova(m)) {
			z=SamoJednaKolona(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i!=0 && i!=BrojRedova(m)-1 && j==0 && jednakolona==false) {
			z=LijeviRed(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i!=0 && i!=BrojRedova(m)-1 && j==BrojKolona(m)-1 && jednakolona==false) {
			z=DesniRed(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i!=0 && i!=BrojRedova(m)-1 && j!=0 && j!=BrojKolona(m)-1) {
			z=ObicniSlucaj(m,i,j);
			i=z.real();
			j=z.imag();
		}
		if(i==0 && j==0) devil_trigger=GoreLijevoProvjera(m,i,j);
		if(i==0 && j==BrojKolona(m)-1 && jedanred==false) devil_trigger=GoreDesnoProvjera(m,i,j);
		if(i==BrojRedova(m)-1 && j==BrojKolona(m)-1 && jedanred==false && jednakolona==false) devil_trigger=DoleDesnoProvjera(m,i,j);
		if(i==BrojRedova(m)-1 && j==0 && jedanred==false && jednakolona==false) devil_trigger=DoleLijevoProvjera(m,i,j);
		if(i==0 && j!=0 && j!=BrojKolona(m)-1 && jedanred==false) devil_trigger=GornjiRedProvjera(m,i,j);
		if(i==BrojRedova(m)-1 && j!=0 && j!=BrojKolona(m)-1 && jedanred==false) devil_trigger=DonjiRedProvjera(m,i,j);
		if(i==0 && jedanred==true) devil_trigger=JedanRedProvjera(m,i,j);
		if(j==0 && jednakolona==true) devil_trigger=JednaKolonaProvjera(m,i,j);
		if(i!=0 && i!=BrojRedova(m)-1 && j==0 && jednakolona==false) devil_trigger=LijeviRedProvjera(m,i,j);
		if(i!=0 && i!=BrojRedova(m)-1 && j==BrojKolona(m)-1 && jednakolona==false) devil_trigger=DesniRedProvjera(m,i,j);
		if(i!=0 && i!=BrojRedova(m)-1 && j!=0 && j!=BrojKolona(m)-1) {
			devil_trigger=ObicnaProvjera(m,i,j);
		}
	}
	Kompleksni f(i,j);
	return f;
}

int main ()
{
	int red,kol;
	Kompleksni z;
	std::cout<<"Unesite broj redova i kolona matrice:\n";
	std::cin>>red>>kol;
	std::cout<<"Unesite elemente matrice:\n";

	Matrica m = KreirajMatricu(red,kol);

	for(int i = 0; i < red; i++ ) {
		for(int j = 0; j < kol; j++) {
			int temp;
			std::cin>>temp;
			m.at(i).at(j)=temp;
		}
	}

	std::cout<<"Unesite poziciju odakle zapocinje pretraga:\n";

	int brojr,brojk;

	std::cin>>brojr>>brojk;
	try {
		z=VrhMatrice(m,brojr,brojk);
	} catch(std::range_error ohno) {
		std::cout<<"Greska: "<<ohno.what();
		return 0;
	} catch(std::domain_error ohno) {
		std::cout<<"Greska: "<<ohno.what();
		return 0;
	}
	std::cout<<"Nadjen je vrh matrice na poziciji "<<z.real()<<" "<<z.imag()<<"\n";
	std::cout<<"Njegova vrijednost je "<<m.at(z.real()).at(z.imag());

	return 0;
}
