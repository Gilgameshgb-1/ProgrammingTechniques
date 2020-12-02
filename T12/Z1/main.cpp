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
	Sat(int h,int m,int s){
		bool kontrola=true;
	if(DaLiJeIspravno(h,m,s)==false)bool kontrola = false;
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
	Sat(){Sat::sati=0;Sat::minute=0;Sat::sekunde=0;}
	void Postavi(int h,int m,int s){
		if(DaLiJeIspravno(h,m,s)==false) throw std::domain_error("Neispravno vrijeme");
		Sat::sati=h; Sat::minute=m; Sat::sekunde=s;
	} 
	std::ostream &operator<<(std::ostream &tok);
	friend Sat &operator--(Sat &t);
	friend Sat operator--(Sat &t,int);
	friend Sat &operator++(Sat &t);
	friend Sat operator ++(Sat &t,int);
	int DajSate() const {return Sat::sati;}
	int DajMinute() const {return Sat::minute;}
	int DajSekunde() const {return Sat::sekunde;}
	friend Sat &operator+=(Sat &s1,int x){
	if(x>0){
		while(x!=0){
			s1++;
			x--;
		}
	}
	return s1;
	}
	friend Sat &operator-=(Sat &s1,int x){
	if(x>0){
		while(x!=0){
			s1--;
			x--;
		}
	}
		return s1;
	}
	friend Sat operator+(const Sat &s1,int x){
		Sat s2=s1;
		while(x!=0){
			s2++;
			x--;
		}
		return s2;
	}
	friend Sat operator-(const Sat &s1,int x){
		Sat s2=s1;
		while(x!=0){
			s2--;
			x--;
		}
		return s2;
	}
	friend int operator-(const Sat &s1,const Sat &s2){
		int a=s1.sati*3600+s1.minute*60+s1.sekunde;
		int b=s2.sati*3600+s2.minute*60+s2.sekunde;
		return a-b; 
	}
};
std::ostream &operator<<(std::ostream &tok,const Sat &t)
{
    return tok<<std::setw(2)<<std::setfill('0')<<t.DajSate()<<":"<<std::setw(2)<<t.DajMinute()<<":"<<std::setw(2)<<t.DajSekunde();
}

Sat &operator++(Sat &t){
	t.sekunde++;
	if(t.sekunde>=60){
		t.sekunde=0;
		t.minute++;
	}if(t.minute>=60){
		t.minute=0;
		t.sati++;
	}if(t.sati>=24){
		t.sati=0;
	}
	return t;
}

Sat operator ++(Sat &t,int){
	Sat v = t;
	++t;
	return v;
}

Sat &operator--(Sat &t){
			t.sekunde--;
		if(t.sekunde<0){
			t.sekunde=59;
			t.minute--;
		}if(t.minute<0){
			t.minute=59;
			t.sati--;
		}if(t.sati<0){
			t.sati=23;
		}
	return t;
}

Sat operator--(Sat &t,int){
		Sat v = t;
		--t;
	return v;
}

int main ()
{
  //AT 4 testiranje operatora +, - i +=
  Sat s1(11, 4, 39);
  std::cout << s1 << std::endl;
  Sat s2(25, 150, 1000);
  std::cout << s2 << std::endl;
  std::cout << s1 - s2 << std::endl;
  std::cout << s1 + 100 << std::endl;
  std::cout << s1 << std::endl;        
  std::cout << s1 - 100 << std::endl;
  std::cout << s1 << std::endl;
  s2 = s1 += 100; 
  std::cout << s2 << std::endl;
	return 0;
}
