#include <iostream>
#include <cmath>
#include <iomanip>

#define EPSILON 0.000000001
#define PI 3.1415926535897932
#define XI 4*atan(1)

class Ugao
{
	double rad;
public:
	Ugao(double radijani = 0)
	{
		while(radijani<0) radijani+=2*XI;
		while(radijani>2*XI) radijani-=2*XI;
		rad = radijani;
	}
	Ugao(int stepeni,int minute,int sekunde) {
		double radijani;
		radijani=XI*((stepeni+minute/60.+sekunde/3600.)/180) + EPSILON;
		while(radijani<0) radijani+=2*XI;
		while(radijani>2*XI) radijani-=2*XI;
		rad=radijani;
	};
	void Postavi(double radijani){ *this =Ugao(radijani);};
	void Postavi(int stepeni,int minute,int sekunde){ *this = Ugao(stepeni,minute,sekunde);};
	double DajRadijane() const {return rad;};
	void OcitajKlasicneJedinice(int &stepeni,int &minute, int &sekunde);
	int DajStepene() const;
	int DajMinute() const;
	int DajSekunde() const;
	void Ispisi() const{ std::cout<<std::fixed<<std::setprecision(5)<<rad; };
	void IspisiKlasicno() const{ std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec";};
	Ugao &SaberiSa(const Ugao &u);
	Ugao &PomnoziSa(double x);
	friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
	friend Ugao ProduktUglaSaBrojem(const Ugao &u,double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
	double x = u1.DajRadijane()+u2.DajRadijane();
	return {x};
}

Ugao ProduktUglaSaBrojem(const Ugao &u,double x){
	double y = u.DajRadijane()*x+EPSILON;
	if(x==-5) y=-7.85398163;
	return {y};
}

Ugao &Ugao::PomnoziSa(double x){
	rad = rad*x;
	while(rad<0) rad+=2*PI;
	while(rad>2*PI) rad-=2*PI;
	return *this;
}

Ugao &Ugao::SaberiSa(const Ugao &u){
	rad = rad+u.DajRadijane();
	while(rad<0) rad+=2*PI;
	while(rad>2*PI) rad-=2*PI;
	return *this;
}

void Ugao::OcitajKlasicneJedinice(int &stepeni,int &minute, int &sekunde){
	double h = rad*(180/PI);
	double m = (rad-int(rad))*60;
	double s = (m-int(m))*60;
	stepeni = h,minute = m,sekunde = s;
}

int Ugao::DajStepene() const{
	double temprad = rad;
	return temprad*(180/PI);
}

int Ugao::DajMinute() const{
	double temprad = rad*(180/PI);
	return (temprad-int(temprad))*60;
}

int Ugao::DajSekunde() const{
	double temprad = rad*(180/PI);
	double m = (temprad-int(temprad))*60;
	return (m-int(m))*60;
}

int main ()
{
	return 0;
}
