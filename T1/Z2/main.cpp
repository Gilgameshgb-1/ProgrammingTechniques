#include <iostream>
#include <cmath>

int main()
{

    double a,b,c;

    std::cout<<"Unesite tri broja: ";
    std::cin>>a>>b>>c;

    if(a<0 || b<0 || c<0) {
        std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
        return 1;
    }
    if(a+b<=c || a+c<=b || b+c<=a) {
        std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
        return 1;
    }

    double Obim(0);
    double Povrsina(0);
    double Heron(0);

    Heron=(a+b+c)/2;

    Obim=a+b+c;
    Povrsina=sqrt(Heron*(Heron-a)*(Heron-b)*(Heron-c));

    std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "
             <<Obim<<".";

    std::cout<<"\n"<<"Njegova povrsina iznosi "<<Povrsina<<".";

    double pi=4*atan(1);
    double alfa(0);
    double beta(0);
    double gama(0);

    alfa=acos((pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c));
    beta=acos((pow(c,2)+pow(a,2)-pow(b,2))/(2*c*a));
    gama=acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));

    if(alfa<=gama && alfa<=beta) {
        alfa=alfa*(180/pi);
        int alfastepen=int(alfa);
        double ostatak=(alfa-alfastepen)*60;
        int alfaminute=int(ostatak);
        double zadnjiostatak = (ostatak-alfaminute)*60;
        int alfasekunde=int(zadnjiostatak);
        std::cout<<"\n"<<"Njegov najmanji ugao ima "<<alfastepen<<" stepeni, "<<
                 alfaminute<<" minuta"<<" i "<<alfasekunde<<" sekundi.";
    } else if(beta<=alfa && beta<=gama) {
        beta=beta*(180/pi);
        int betastepen=int(beta);
        double ostatak=(beta-betastepen)*60;
        int betaminute=int(ostatak);
        double zadnjiostatak = (ostatak-betaminute)*60;
        int betasekunde=int(zadnjiostatak);
        std::cout<<"\n"<<"Njegov najmanji ugao ima "<<betastepen<<" stepeni, "<<
                 betaminute<<" minuta"<<" i "<<betasekunde<<" sekundi.";
    } else if(gama<=alfa && gama<=beta) {
        gama=gama*(180/pi);
        int gamastepen=int(gama);
        double ostatak=(gama-gamastepen)*60;
        int gamaminute=int(ostatak);
        double zadnjiostatak = (ostatak-gamaminute)*60;
        int gamasekunde=int(zadnjiostatak);
        std::cout<<"\n"<<"Njegov najmanji ugao ima "<<gamastepen<<" stepeni, "<<
                 gamaminute<<" minuta"<<" i "<<gamasekunde<<" sekundi.";
    }else if(gama==beta && gama==alfa && alfa==beta){
         gama=gama*(180/pi);
        int gamastepen=int(gama);
        double ostatak=(gama-gamastepen)*60;
        int gamaminute=int(ostatak);
        double zadnjiostatak = (ostatak-gamaminute)*60;
        int gamasekunde=int(zadnjiostatak);
        std::cout<<"\n"<<"Njegov najmanji ugao ima "<<gamastepen<<" stepeni, "<<
                 gamaminute<<" minuta"<<" i "<<gamasekunde<<" sekundi.";
    }

    return 0;
}
