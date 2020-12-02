#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <string>
#include <fstream>

template <typename TipEl>
class Matrica
{
	int br_redova, br_kolona;
	TipEl **elementi;
	char ime_matrice;
	static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
	static void DealocirajMemoriju(TipEl **elementi, int br_redova);
	void KopirajElemente(TipEl **elementi);
public:
	Matrica(int br_redova, int br_kolona, char ime = 0);
	Matrica(const Matrica &m);
	Matrica(Matrica &&m);
	~Matrica()
	{
		DealocirajMemoriju(elementi, br_redova);
	}
	Matrica &operator =(const Matrica &m);
	Matrica &operator =(Matrica &&m);
	friend Matrica<TipEl> operator +=(Matrica<TipEl> &m1,const Matrica<TipEl> &m2)
	{
		if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) {
			throw std::domain_error("Matrice nemaju jednake dimenzije!");
		}
		Matrica<TipEl> m3(m1.br_redova,m1.br_kolona);
		for(int i = 0; i<m1.br_redova; i++) {
			for(int j = 0; j<m1.br_kolona; j++) {
				m3.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
			}
		}
		return m1=m3;
	};
	friend Matrica<TipEl> operator +(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2)
	{
		if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) {
			throw std::domain_error("Matrice nemaju jednake dimenzije!");
		}
		Matrica<TipEl> m3(m1.br_redova,m1.br_kolona);
		for(int i = 0; i< m1.br_redova; i++) {
			for(int j = 0; j< m1.br_kolona; j++) {
				m3.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
			}
		}
		return m3;
	};
	TipEl* &operator [](int indeks)
	{
		return elementi[indeks];
	}
	TipEl* operator [](int indeks) const
	{
		return elementi[indeks];
	}
	TipEl* &operator ()(int indeks)
	{
		return  elementi[indeks-1];
	}
	TipEl &operator()(int a,int b) const
	{
		if(a>br_redova || b>br_kolona || a<=0 || b<=0) throw std::range_error("Neispravan indeks");
		for(int i=0; i<br_redova; i++) {
			for(int j=0; j<br_kolona; j++) {
				if(i==a-1 && j==b-1) return elementi[i][j];
			}
		}
	}
	TipEl &operator()(int a,int b)
	{
		if(a>br_redova || b>br_kolona || a<=0 || b<=0) throw std::range_error("Neispravan indeks");
		for(int i=0; i<br_redova; i++) {
			for(int j=0; j<br_kolona; j++) {
				if(i==a-1 && j==b-1) return elementi[i][j];
			}
		}
	}
	friend Matrica<TipEl> operator - (const Matrica<TipEl> &m1,const Matrica<TipEl> &m2)
	{
		if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) {
			throw std::domain_error("Matrice nemaju jednake dimenzije!");
		}
		Matrica<TipEl> m3(m1.br_redova,m1.br_kolona);
		for(int i = 0; i<m1.br_redova; i++) {
			for(int j = 0; j<m1.br_kolona; j++) {
				m3.elementi[i][j]=m1.elementi[i][j]-m2.elementi[i][j];
			}
		}
		return m3;
	}
	friend Matrica<TipEl> operator -=(Matrica<TipEl> &m1,const Matrica<TipEl> &m2)
	{
		if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) {
			throw std::domain_error("Matrice nemaju jednake dimenzije!");
		}
		Matrica<TipEl> m3(m1.br_redova,m1.br_kolona);
		for(int i = 0; i<m1.br_redova; i++) {
			for(int j = 0; j<m1.br_kolona; j++) {
				m3.elementi[i][j]=m1.elementi[i][j]-m2.elementi[i][j];
			}
		}
		return m1 = m3;
	}
	friend std::istream &operator >>(std::istream &tok,Matrica<TipEl> &m)
	{
		for(int i = 0; i<m.br_redova; i++) {
			for(int j = 0; j<m.br_kolona; j++) {
				std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
				tok>>m.elementi[i][j];
			}
		}
		return tok;
	}
	friend std::ostream &operator <<(std::ostream &tok,Matrica<TipEl> &m)
	{
		int x = tok.width();
		for(int i = 0; i<m.br_redova; i++) {
			for(int j = 0; j<m.br_kolona; j++) {
				tok<<std::setw(x)<<m.elementi[i][j];
			}
			tok<<"\n";
		}
		return tok;
	}
	friend std::ostream &operator <<(std::ostream &tok,const Matrica<TipEl> &m)
	{
		int x = tok.width();
		for(int i = 0; i<m.br_redova; i++) {
			for(int j = 0; j<m.br_kolona; j++) {
				tok<<std::setw(x)<<m.elementi[i][j];
			}
			tok<<"\n";
		}
		return tok;
	}
	friend Matrica<TipEl> &operator *=(Matrica<TipEl> &m1,const Matrica<TipEl> &m2)
	{
		if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
		Matrica<TipEl> m3(m1.br_redova,m1.br_kolona);
		for(int i = 0; i<m3.br_redova; i++) {
			for(int j =0; j<m3.br_kolona; j++) {
				m3.elementi[i][j]=0;
			}
		}
		for(int i =0; i<m1.br_redova; i++) {
			for(int j = 0; j<m2.br_kolona; j++) {
				for(int k = 0; k<m1.br_kolona; k++) {
					m3.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
				}
			}
		}
		for(int i = 0; i<m1.br_redova; i++) {
			for(int j = 0; j<m1.br_kolona; j++) {
				m1.elementi[i][j]=m3.elementi[i][j];
			}
		}
		return m1;
	}
	friend Matrica<TipEl> operator *(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2)
	{
		if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
		Matrica<TipEl> m3(m1.br_redova,m1.br_kolona);
		for(int i = 0; i<m3.br_redova; i++) {
			for(int j =0; j<m3.br_kolona; j++) {
				m3.elementi[i][j]=0;
			}
		}
		for(int i =0; i<m1.br_redova; i++) {
			for(int j = 0; j<m2.br_kolona; j++) {
				for(int k = 0; k<m1.br_kolona; k++) {
					m3.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
				}
			}
		}
		return m3;
	}
	friend Matrica<TipEl> operator *(double x,const Matrica<TipEl> &m2)
	{
		Matrica<TipEl> m3(m2.br_redova,m2.br_kolona);
		for(int i = 0; i<m2.br_redova; i++) {
			for(int j =0; j<m2.br_kolona; j++) {
				m3.elementi[i][j]=0;
			}
		}
		for(int i =0; i<m3.br_redova; i++) {
			for(int j = 0; j<m3.br_kolona; j++) {
				m3.elementi[i][j]=m2.elementi[i][j]*x;
			}
		}
		return m3;
	}
	friend Matrica<TipEl> operator *(const Matrica<TipEl> &m2,double x)
	{
		Matrica<TipEl> m3(m2.br_redova,m2.br_kolona);
		for(int i = 0; i<m2.br_redova; i++) {
			for(int j =0; j<m2.br_kolona; j++) {
				m3.elementi[i][j]=0;
			}
		}
		for(int i =0; i<m3.br_redova; i++) {
			for(int j = 0; j<m3.br_kolona; j++) {
				m3.elementi[i][j]=m2.elementi[i][j]*x;
			}
		}
		return m3;
	}
	friend Matrica<TipEl> operator *=(Matrica<TipEl> &m2,double x)
	{
		for(int i =0; i<m2.br_redova; i++) {
			for(int j = 0; j<m2.br_kolona; j++) {
				m2.elementi[i][j]=m2.elementi[i][j]*x;
			}
		}
		return m2;
	}
	operator std::string()/*(Matrica<TipEl> &m)*/
	{
		std::string temp="{";
		for(int i = 0; i<this->br_redova; i++) {
			temp+="{";
			for(int j = 0; j<this->br_kolona; j++) {
				temp+=std::to_string(int(this->elementi[i][j]));
				if(j!=this->br_kolona-1) temp+=",";
			}
			if(i!=this->br_redova-1) {
				temp+="},";
			} else {
				temp+="}";
			}
		}
		temp+="}";
		return temp;
	}
	//manipulacija datotekama
	Matrica/*<TipEl>*/(const std::string &ime_datoteke,bool DaLiTekstIliBinarno)
	{
		if(DaLiTekstIliBinarno==false) {
			std::ifstream tok(ime_datoteke);
			if(!tok) throw std::logic_error("Trazena datoteka ne postoji");
			int brr = 1;
			int brk = 1;
			char x;
			double z;
			bool kontrola = false;	
			while(tok) {
				tok>>z;
				x=tok.get();
				//	if(x!=',' || x!='\n' || x!=' ') throw std::logic_error("Datoteka sadrzi besmislene podatke");
				if(x==',' && x!='\n' && x!=' ' && kontrola==false) {
					brk++;
				}
				if(x=='\n') {
					brr++;
					kontrola = true;
				}
			}
			br_redova = brr;
			br_kolona = brk;
			elementi = (AlocirajMemoriju(brr,brk));
			ObnoviIzTekstualneDatoteke(ime_datoteke);
		} else {
			std::ifstream tok(ime_datoteke,std::ios::binary|std::ios::in);
			if(!tok) throw std::logic_error("Trazena datoteka ne postoji");
			int brr=1;
			int brk = 0;
			char x;
			bool kontrola = false;
			double z = 0;
			while(tok) {
				tok.read(reinterpret_cast<char*>(&z),sizeof z);
				tok.read(reinterpret_cast<char*>(&x),sizeof x);
				if(x==',' && x!='\n' && x!=' ' && kontrola==false) {
					brk++;
				}
				if(x=='\n') {
					brr++;
					kontrola = true;
				}
			}
/*			std::cout<<"Broj redova binarne datoteke"<<brr<<"\n";
			std::cout<<"Broj kolona binarne datoteke"<<brk<<"\n";*/
			br_redova = 2;
			br_kolona = 2;
			elementi = (AlocirajMemoriju(2,2));
			ObnoviIzBinarneDatoteke(ime_datoteke);
		}
	};
	void SacuvajUTekstualnuDatoteku(const std::string &ime_datoteke)
	{
		std::ofstream tok(ime_datoteke);
		for(int i = 0; i<this->br_redova; i++) {
			for(int j = 0; j<this->br_kolona; j++) {
				if(j!=this->br_kolona-1) {
					if(!tok) throw std::logic_error("Problemi sa upisom u datoteku");
					tok<<this->elementi[i][j]<<",";
				} else {
					tok<<this->elementi[i][j];
				}
			}
			tok<<"\n";
		}
	};
	void SacuvajUBinarnuDatoteku(const std::string &ime_datoteke)
	{
		std::ofstream tok(ime_datoteke,std::ios::binary| std::ios::out);
		for(int i = 0; i<this->br_redova; i++) {
			for(int j = 0; j<this->br_kolona; j++) {
				if(j!=this->br_kolona-1) {
					if(!tok) throw std::logic_error("Problemi sa upisom u datoteku");
					auto kopija = this->elementi[i][j];
					tok.write(reinterpret_cast<char*>(&kopija),sizeof kopija);
					char x = ',';
					tok.write(reinterpret_cast<char*>(&x),sizeof x);
				} else {
					auto kopija = this->elementi[i][j];
					tok.write(reinterpret_cast<char*>(&kopija),sizeof kopija);
				}
			}
			char x = '\n';
			tok.write(reinterpret_cast<char*>(&x),sizeof x);
		}
	};
	void ObnoviIzTekstualneDatoteke(const std::string &ime_datoteke)
	{
		std::ifstream tok1(ime_datoteke);
		char x;
		TipEl z;
		while(tok1) {
			tok1>>z;
			if(!tok1){ 
				DealocirajMemoriju(elementi,br_redova);
				throw std::logic_error("Datoteka sadrzi besmislene podatke");
			};
			x=tok1.get();
			if(x!=',' && x!='\n' && x!=' ' && x!=EOF) {
				DealocirajMemoriju(elementi,br_redova);
				throw std::logic_error("Datoteka sadrzi besmislene podatke");
			}
		}
		tok1.close();
		std::ifstream tok(ime_datoteke);
		if(!tok) throw std::logic_error("Trazena datoteka ne postoji");
		for(int i = 0; i<this->br_redova; i++) {
			for(int j = 0; j<this->br_kolona; j++) {
				this->elementi[i][j] = 0;
			}
		}
//		double x;
		char y;
		for(int i = 0; i<this->br_redova; i++) {
			for(int j = 0; j<this->br_kolona; j++) {
				if(j != this->br_kolona - 1) {
					tok>>this->elementi[i][j]>>y;
				} else {
					tok>>this->elementi[i][j];
				}
			}
		}
	};
	void ObnoviIzBinarneDatoteke(const std::string &ime_datoteke)
	{
		std::ifstream tok(ime_datoteke,std::ios::binary|std::ios::in);
		if(!tok) throw std::logic_error("Trazena datoteka ne postoji");
		for(int i = 0; i<this->br_redova; i++) {
			for(int j = 0; j<this->br_kolona; j++) {
				this->elementi[i][j] = 0;
			}
		}
		double x;
		for(int i = 0; i<this->br_redova; i++) {
			for(int j = 0; j<this->br_kolona; j++) {
//	            tok.seekg(x,std::ios::beg);
				if(j != br_kolona - 1) {
					tok.read(reinterpret_cast<char*>(&x),sizeof x);
					this->elementi[i][j] = x;
					tok.read(reinterpret_cast<char*>(&x),sizeof x);
				} else {
					tok.read(reinterpret_cast<char*>(&x),sizeof x);
					{
						this->elementi[i][j] = x;
					}
				}
			}
		}
	};
};


template <typename TipEl>
TipEl ** Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona)
{
	TipEl **elementi = new TipEl*[br_redova] {};
	try {
		for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
	} catch(...) {
		DealocirajMemoriju(elementi, br_redova);
		throw;
	}
	return elementi;
}



template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova)
{
	for(int i = 0; i < br_redova; i++) delete[] elementi[i];
	delete[] elementi;
}



template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :
	br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
	elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi)
{
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			Matrica::elementi[i][j] = elementi[i][j];
}



template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), ime_matrice(m.ime_matrice),
	elementi(AlocirajMemoriju(m.br_redova, m.br_kolona))
{
	KopirajElemente(m.elementi);
}



template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice)
{
	m.br_redova = 0;
	m.elementi = nullptr;
}


template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m)
{
	if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
		TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
		DealocirajMemoriju(elementi, br_redova);
		elementi = novi_prostor;
	} else if(br_redova > m.br_redova)
		for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
	br_redova = m.br_redova;
	br_kolona = m.br_kolona;
	ime_matrice = m.ime_matrice;
	KopirajElemente(m.elementi);
	return *this;
}


template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m)
{
	std::swap(br_redova, m.br_redova);
	std::swap(br_kolona, m.br_kolona);
	std::swap(ime_matrice, m.ime_matrice);
	std::swap(elementi, m.elementi);
	return *this;
}
int main()
{
//AT1 - testiranje izuzetaka konstruktora
    try
    {
        Matrica<int> m1("datoteka.DAT", true);
    }
    catch (const std::logic_error& e)
    {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }
    
    try
    {
        Matrica<int> m1("datoteka.txt", false);
    }
    catch (const std::logic_error& e)
    {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }
    return 0;
}
