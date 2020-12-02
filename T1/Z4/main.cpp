//TP 2016/2017: Tutorijal 1, Zadatak 4
#include <iostream>
#include <cmath>
int main ()
{
    
    float n;
    int suma(0);
    int kontrola(0);
    
    while(1){
        std::cout<<"\nUnesite prirodan broj ili 0 za kraj: ";
        std::cin>>n;
        if(n==0 && std::cin){
            std::cout<<"Dovidjenja!";
            return 1;
        }
        if(!std::cin || n<0 || n!=int(n)){
            std::cout<<"Niste unijeli prirodan broj!";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            kontrola=0;
        }
        int temp = int(n);
        if(n>0 && n==int(n)){
            kontrola=1;
        }
        for(int i =1;i<temp;i++){
            if(temp%i==0){
                suma+=i;
            }
        }
        if(suma>temp && kontrola==1 && std::cin){
            std::cout<<"Broj "<<temp<<" je obilan!";
        }else if(suma<temp && kontrola==1 && std::cin){
            std::cout<<"Broj "<<temp<<" je manjkav!";
        }else if(suma==temp && kontrola==1 && std::cin){
            std::cout<<"Broj "<<temp<<" je savrsen!";
        }
        kontrola=0;
        suma=0;
    }
    
	return 0;
}