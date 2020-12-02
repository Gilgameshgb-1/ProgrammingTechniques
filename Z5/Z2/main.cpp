    #include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iterator>

class Berza{
    std::vector<double> v;
    double maximalna;
    double minimalna;
public:
    Berza(double min,double max){
        if(min<0 || max<0) throw std::range_error("Ilegalne granicne cijene");
        maximalna = max;
        minimalna = min;
    };
    explicit Berza(double max){
        if(max<0) throw std::range_error("Ilegalne granicne cijene");
        maximalna = max;
        minimalna = 0;
    };
    void RegistrirajCijenu(double x){
        if(x>maximalna || x<minimalna) throw std::range_error("Ilegalna cijena");
        v.push_back(x);
    }
    int DajBrojRegistriranihCijena() const{
        return v.size();
    }
    void BrisiSve(){
        v.clear();
    }
    double DajMinimalnuCijenu(){
        if(v.size()==0) throw std::range_error("Nema registriranih cijena");
        return *std::min_element(v.begin(),v.end());
    };
    double DajMaksimalnuCijenu(){
        if(v.size()==0) throw std::range_error("Nema registriranih cijena");
        return *std::max_element(v.begin(),v.end());
    };
    bool operator !(){
        if(v.size()==0) return true;
        else return false;
    }
    int DajBrojCijenaVecihOd(double x){
        return std::count_if(v.begin(),v.end(),std::bind(std::greater<double>(),std::placeholders::_1,x));
    }
    void Ispisi() const{
        std::vector<double> kopija = v;
        std::sort(kopija.begin(),kopija.end(),std::greater<double>());
        std::transform(kopija.begin(),kopija.end(),kopija.begin(),std::bind(std::divides<double>(),std::placeholders::_1,100));
        std::copy(kopija.begin(),kopija.end(),std::ostream_iterator<double>(std::cout<<std::setprecision(2)<<std::fixed,"\n"));
    }
    double operator [](int indeks) const{
        if(indeks <= 0 || (indeks-1) > v.size()) throw std::range_error("Neispravan indeks");
        return v[indeks - 1];
    }
    Berza &operator ++(){
        if(std::count_if(v.begin(),v.end(),std::bind(std::greater<double>(),std::placeholders::_1,maximalna-100))>0) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        std::transform(v.begin(),v.end(),v.begin(),std::bind(std::plus<double>(),std::placeholders::_1,100.0));
        return *this;
    }
    Berza operator ++(int){
        if(std::count_if(v.begin(),v.end(),std::bind(std::greater<double>(),std::placeholders::_1,maximalna-100))>0) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        Berza pomocna(minimalna,maximalna);
        pomocna.v = v;
        std::transform(v.begin(),v.end(),v.begin(),std::bind(std::plus<double>(),std::placeholders::_1,100.0));
        return pomocna;
    }
    Berza &operator --(){
        if(std::count_if(v.begin(),v.end(),std::bind(std::less<double>(),std::placeholders::_1,100))>0) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        if(std::count_if(v.begin(),v.end(),std::bind(std::less<double>(),std::placeholders::_1,minimalna-100))>0) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        std::transform(v.begin(),v.end(),v.begin(),std::bind(std::minus<double>(),std::placeholders::_1,100.0));
        return *this;
    }
    Berza operator --(int){
        if(std::count_if(v.begin(),v.end(),std::bind(std::less<double>(),std::placeholders::_1,100))>0) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        if(std::count_if(v.begin(),v.end(),std::bind(std::less<double>(),std::placeholders::_1,minimalna-100))>0) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        Berza pomocna(minimalna,maximalna);
        pomocna.v = v;
        std::transform(v.begin(),v.end(),v.begin(),std::bind(std::minus<double>(),std::placeholders::_1,100.0));
        return pomocna;
    }
    Berza operator -(){
        double vrijednost = maximalna + minimalna;
        Berza kopija(minimalna,maximalna);
        kopija.v = v;
        std::transform(kopija.v.begin(),kopija.v.end(),kopija.v.begin(),std::bind(std::plus<double>(),std::placeholders::_1,vrijednost));
        std::transform(kopija.v.begin(),kopija.v.end(),v.begin(),kopija.v.begin(),std::minus<double>());
        return kopija;
    }
    bool operator ==(Berza &b){
        if(v.size() != b.v.size()) return false;
        //if(std::equal(v.begin,v.end(),b.v.begin())) return true;
        if(v==b.v) return true;
        return false;
    }
    bool operator !=(Berza &b){
        if(v.size() == b.v.size()) return false;
        //if(std::equal(v.begin(),v.end(),b.v.begin())) return false;
        if(!(v==b.v)) return true;
        return false;
    }
    friend Berza operator +(Berza &b,double y){
        Berza x(b.minimalna,b.maximalna);
        x.v = b.v;
        std::transform(x.v.begin(),x.v.end(),x.v.begin(),std::bind(std::plus<double>(),std::placeholders::_1,y));
        if(std::count_if(x.v.begin(),x.v.end(),std::bind(std::less<double>(),std::placeholders::_1,0.0))>0){
            throw std::domain_error("Nesaglasni operandi");
        }
        return x;
    }
    friend Berza operator +(double y,Berza &b){
        return b+y;
    }
    friend Berza operator -(double y,Berza &b){
        Berza x(b.minimalna,b.maximalna);
        x.v = b.v;
        std::transform(x.v.begin(),x.v.end(),x.v.begin(),std::bind(std::minus<double>(),std::placeholders::_1,y));
        if(std::count_if(x.v.begin(),x.v.end(),std::bind(std::less<double>(),std::placeholders::_1,0.0))>0){
            throw std::domain_error("Nesaglasni operandi");
        }
        return x;
    }
    friend Berza operator -(Berza &b,double y){
        return y-b;
    }
    Berza operator +(Berza &b) = delete;
    Berza operator -(Berza &b){
        Berza x(minimalna,maximalna);
        x.v = v;
        std::transform(x.v.begin(),x.v.end(),b.v.begin(),x.v.begin(),(std::minus<double>()));
        if(std::count_if(x.v.begin(),x.v.end(),std::bind(std::less<double>(),std::placeholders::_1,0.0))>0){
            throw std::domain_error("Nesaglasni operandi");
        }
        return x;
    }
    Berza &operator +=(double y){
        std::transform(v.begin(),v.end(),v.begin(),std::bind(std::plus<double>(),std::placeholders::_1,y));
        if(std::count_if(v.begin(),v.end(),std::bind(std::less<double>(),std::placeholders::_1,0.0))>0){
            throw std::domain_error("Nesaglasni operandi");
        }
        return *this;
    }
    Berza &operator -=(double y){
        std::transform(v.begin(),v.end(),v.begin(),std::bind(std::minus<double>(),std::placeholders::_1,y));
        if(std::count_if(v.begin(),v.end(),std::bind(std::less<double>(),std::placeholders::_1,0.0))>0){
            throw std::domain_error("Nesaglasni operandi");
        }
        return *this;
    }
};

int main ()
{
        Berza b1 = Berza(1000,4000);

    b1.RegistrirajCijenu(3000);
    b1.RegistrirajCijenu(1500);
    b1.RegistrirajCijenu(2000);
    std::cout << "Broj registrovanih cijena: " << b1.DajBrojRegistriranihCijena() << std::endl;
   
    b1.Ispisi();
    b1.BrisiSve();
    std::cout << "Broj registrovanih cijena: " << b1.DajBrojRegistriranihCijena();
	return 0;
}