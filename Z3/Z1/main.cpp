#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <cmath>

double tezinskikoeficijent(std::vector<std::pair<double,double>> v,int i,int d,int n)
{
    double suma = 0;
    for(int k=std::max(1,i-d); k<=std::min(i,n-d); k++) {
        double produkt = 1;
        for(int j = k; j<=(k+d); j++) {
            if(j-1!=i-1) {
                produkt*=(1/(v[i-1].first-v[j-1].first));
            }
        }
        suma+=(pow(-1,k-1)*produkt);
    }
    std::cout<<suma<<"\n";
    return suma;
}

std::function<double(double)> BaricentricnaInterpolacija(std::vector<std::pair<double,double>> v,int d)
{
    if(d<0 || d>=v.size()) throw std::domain_error("Nedozvoljen red");
    for(int i = 0; i<v.size(); i++) {
        double temp = v[i].first;
        for(int j=(i+1); j<v.size(); j++) {
            if(temp==v[j].first) throw std::domain_error("Neispravni cvorovi");
        }
    }
    return [v,d](double x) {
        int n = v.size();
        double brojnik = 0;
        for(int i = 0; i<n; i++) if(v[i].first==x) return v[i].second;
        for(int i = 1; i<=n; i++) {
            double wi=tezinskikoeficijent(v,i,d,n);
            brojnik+=((wi/(x-v[i-1].first))*v[i-1].second);
        }
        double nazivnik = 0;
        for(int i = 1; i<=n; i++) {
            double wi=tezinskikoeficijent(v,i,d,n);
            nazivnik+=(wi/(x-v[i-1].first));
        }
        double povratna = 0;
        povratna = brojnik/nazivnik;
        return povratna;
    };
}

std::function<double(double)> BaricentricnaInterpolacija(std::function<double(double)> f,double xmin,double xmax,double deltax,int d)
{
    if(xmin>xmax || deltax<=0) throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double,double>> v;
    int n = xmax/deltax-xmin/deltax;
    for(int i = 0; i<=n; i++) {
        double y = f(xmin+i*deltax);
        v.push_back(std::make_pair((xmin+i*deltax),y));
    }
    return BaricentricnaInterpolacija(v,d);
}

int main ()
{
     std::vector<std::pair<double,double>> v;
     int izbor;
     std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
     std::cin>>izbor;
     try {
         if(izbor==1) {
             int brojcvorova=0;
             std::cout<<"Unesite broj cvorova: ";
             std::cin>>brojcvorova;
             std::cout<<"Unesite cvorove kao parove x y: ";
             for(int i = 0; i<brojcvorova; i++) {
                 int x,y;
                 std::cin>>x>>y;
                 v.push_back(std::make_pair(x,y));
             }
             int redinterpolacije;
             std::cout<<"Unesite red interpolacije: ";
             std::cin>>redinterpolacije;
             auto f = BaricentricnaInterpolacija(v,redinterpolacije);
             double argument;
             char q='"';
             while(1) {
                 std::cout<<"Unesite argument (ili "<<q<<"kraj"<<q<<" za kraj): ";
                 std::cin>>argument;
                 if(!std::cin) break;
                 std::cout<<"f"<<"("<<argument<<") = "<<f(argument);
                 std::cout<<"\n";
             }
         }
         if(izbor==2) {
             double xmin,xmax,korak;
             int redinterpolacije;
             std::cout<<"Unesite krajeve intervala i korak: ";
             std::cin>>xmin>>xmax>>korak;
             std::cin.ignore(100,'\n');
             std::cout<<"Unesite red interpolacije: ";
             std::cin>>redinterpolacije;
             auto fun = BaricentricnaInterpolacija([](double x) {
                 return x * x + std::sin(x);
             },xmin,xmax,korak,redinterpolacije);
             char q='"';
             double argument;
             while(1) {
                 std::cout<<"Unesite argument (ili "<<q<<"kraj"<<q<<" za kraj): ";
                 std::cin>>argument;
                 if(!std::cin) break;
                 std::cout<<"f"<<"("<<argument<<") = "<<argument * argument + std::sin(argument);
                 std::cout<<" fapprox"<<"("<<argument<<") = "<<fun(argument);
                 std::cout<<"\n";
             }
         }
     } catch(std::domain_error e) {
         std::cout<<e.what();
     }
    return 0;
}
