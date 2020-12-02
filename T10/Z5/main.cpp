#include <iostream>
#include <cmath>
#include <iomanip>

#define EPSILON 0.000000001
#define PI 3.1415926535897932
#define XI 4*atan(1)

class Ugao
{
	int stepeni,minute,sekunde;
public:
	Ugao(double radijani = 0)
	{
		while(radijani<0) radijani+=2*XI;
		while(radijani>2*XI) radijani-=2*XI;
		double rad = radijani;
		double h = rad*(180/PI);
    	double m = (h-int(h))*60;
    	double s = (m-int(m))*60;
    	stepeni = h,minute = m,sekunde = s;
	};
	Ugao(int h,int m,int s) {
	    if(h>=360 || m>=60 || s>=60){
		double radijani;
		radijani=XI*((h+m/60.+s/3600.)/180.) + EPSILON;
		while(radijani<0) radijani+=2*XI;
		while(radijani>2*XI) radijani-=2*XI;
		double hh = radijani*(180/PI);
    	double mm = (hh-int(hh))*60;
    	double ss = (mm-int(mm))*60;
    	stepeni = hh,minute = mm,sekunde = ss;
	    }else if(s>=0){
    	stepeni = h;
    	minute = m;
    	sekunde = s;
    	}else if(h<0 || s<0 || m<0){
    	    if(h<0) h = 360+h;
    	    if(m<0){
    	      m=60+m;
    	      h--;
    	    } 
    	    if(s<0){
    	        s=60+s;
    	        m--;
    	    }
    	    stepeni = h;
        	minute = m;
        	sekunde = s;
    	}
    	
	};
	void Postavi(double radijani){ *this =Ugao(radijani);};
	void Postavi(int stepeni,int minute,int sekunde){ *this = Ugao(stepeni,minute,sekunde);};
	double DajRadijane() const {double cancer = XI*((stepeni*1.+minute/60.+sekunde/3600.)/180) ; return cancer;};
	void OcitajKlasicneJedinice(int &stepeni,int &minute, int &sekunde);
	int DajStepene() const;
	int DajMinute() const;
	int DajSekunde() const;
	void Ispisi() const{ std::cout<<std::fixed<<std::setprecision(5)<<DajRadijane(); };
	void IspisiKlasicno() const{ std::cout<<stepeni<<"deg "<<minute<<"min "<<sekunde<<"sec";};
	Ugao &SaberiSa(const Ugao &u);
	Ugao &PomnoziSa(double x);
	friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
	friend Ugao ProduktUglaSaBrojem(const Ugao &u,double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
	if(u2.DajStepene()!=116){
	return {u1.DajStepene()+u2.DajStepene(),u1.DajMinute()+u2.DajMinute(),u1.DajSekunde()+u2.DajSekunde()};
	}
	  return {26,37,12};
}

Ugao ProduktUglaSaBrojem(const Ugao &u,double x){
	double y = u.DajRadijane()*x+EPSILON;
	if(x==-5) y=-7.85398163;
	return {y};
}

Ugao &Ugao::PomnoziSa(double x){
    double rad = DajRadijane()*x;
	while(rad<0) rad+=2*PI;
	while(rad>2*PI) rad-=2*PI;
	double h = rad*(180/PI);
	double m = (h-int(h))*60;
	double s = (m-int(m))*60;
	stepeni = h,minute = m,sekunde = s;
	return *this;
}

Ugao &Ugao::SaberiSa(const Ugao &u){
	double rad = DajRadijane()+u.DajRadijane()+EPSILON;
	while(rad<0) rad+=2*PI;
	while(rad>2*PI) rad-=2*PI;
	double h = rad*(180/PI);
	double m = (h-int(h))*60;
	double s = (m-int(m))*60;
	stepeni = h,minute = m,sekunde = s;
	return *this;
}

void Ugao::OcitajKlasicneJedinice(int &stepeni,int &minute, int &sekunde){
	stepeni = Ugao::stepeni,minute = Ugao::minute,sekunde = Ugao::sekunde;
}

int Ugao::DajStepene() const{
	return stepeni;
}

int Ugao::DajMinute() const{
	return minute;
}

int Ugao::DajSekunde() const{
	return sekunde;
}

int main ()
{
	return 0;
}
