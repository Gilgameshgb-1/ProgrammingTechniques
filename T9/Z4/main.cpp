#include <iostream>
#include <new>
#include <stdexcept>
#include <iomanip>

class Sat
{
	int sati,minute,sekunde;
public:
	static bool DaLiJeIspravno(int h,int m,int s){
		if(h>23 || h<0) return false;
		if(m>59 || m<0) return false;
		if(s>59 || s<0) return false;
		return true;
	}
	void Postavi(int h,int m,int s){
		if(DaLiJeIspravno(h,m,s)==false) throw std::domain_error("Neispravno vrijeme");
		Sat::sati=h; Sat::minute=m; Sat::sekunde=s;
	} 
	void PostaviNormalizirano(int h,int m,int s);
	void Ispisi() const;
	Sat &Sljedeci();
	Sat &Prethodni();
	Sat &PomjeriZa(int x);
	int DajSate() const {return Sat::sati;}
	int DajMinute() const {return Sat::minute;}
	int DajSekunde() const {return Sat::sekunde;}
	friend int BrojSekundiIzmedju(const Sat &s1, const Sat &s2){
		int a=s1.DajSate()*3600+s1.DajMinute()*60+s1.DajSekunde();
		int b=s2.DajSate()*3600+s2.DajMinute()*60+s2.DajSekunde();
		return a-b; 
	}
	static int Razmak(const Sat &s1, const Sat &s2){
		int a=s1.DajSate()*3600+s1.DajMinute()*60+s1.DajSekunde();
		int b=s2.DajSate()*3600+s2.DajMinute()*60+s2.DajSekunde();
		return a-b;
	}
};

Sat &Sat::PomjeriZa(int x){
	if(x<0){
		while(x!=0){
			Prethodni();
			x++;
		}
	}else if(x>0){
		while(x!=0){
			Sljedeci();
			x--;
		}
	}
}

Sat &Sat::Prethodni(){
	Sat::sekunde--;
	if(Sat::sekunde<0){
		Sat::sekunde=59;
		Sat::minute--;
	}if(Sat::minute<0){
		Sat::minute=59;
		Sat::sati--;
	}if(Sat::sati<0){
		Sat::sati=23;
	}
	return *this;
}

Sat &Sat::Sljedeci(){
	Sat::sekunde++;
	if(Sat::sekunde>=60){
		Sat::sekunde=0;
		Sat::minute++;
	}if(Sat::minute>=60){
		Sat::minute=0;
		Sat::sati++;
	}if(Sat::sati>=24){
		Sat::sati=0;
	}
	return *this;
}

void Sat::PostaviNormalizirano(int h,int m,int s){
	bool kontrola = false;
	if(s>=60){
		m=m+s/60;
		s=s-(s/60)*60; 
	}else if(s<0){
		while(s<0){
			s+=60;
			m--;
			kontrola=true;
		}
	}
	if(m>=60){
		h=h+m/60;
		m=m-(m/60)*60;
	}
	else if(m<0){
		while(m<0){
			m+=60;
			h--;
			kontrola=true;
		}
	}
	if(h>=24){
		h=h-24*(h/24);
	}
	else if(h<0){
		while(h<0){
			h=h+24;
			kontrola=true;
		}
	}
	if(kontrola==true){
		Sat::sekunde=s%60;
		Sat::minute=(m+s/60)%60;
		Sat::sati=(h+m/60+s/3600)%24;
		return;
	}
	Sat::sati=h;
	Sat::minute=m;
	Sat::sekunde=s;
}

void Sat::Ispisi() const
{
    std::cout<<std::setw(2)<<std::setfill('0')<<Sat::sati<<":"<<std::setw(2)<<Sat::minute<<":"<<std::setw(2)<<Sat::sekunde;
}

int main ()
{
	return 0;
}
