#include <iostream>
#include <iomanip>

struct Vrijeme {
    int sati;
    int minute;
    int sekunde;
};

void TestirajVrijeme(const Vrijeme &t)
{
    if(t.sekunde>=60 || t.sekunde<0) throw std::domain_error("Neispravno vrijeme");
    if(t.minute>=60 || t.minute<0) throw std::domain_error("Neispravno vrijeme");
    if(t.sati>=24 || t.sati<0) throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme(const Vrijeme &t)
{
    TestirajVrijeme(t);
    std::cout<<std::setw(2)<<std::setfill('0')<<t.sati<<":"<<std::setw(2)<<t.minute<<":"<<std::setw(2)<<t.sekunde;
}

Vrijeme SaberiVrijeme(const Vrijeme &t1, const Vrijeme &t2)
{
    TestirajVrijeme(t1);
    TestirajVrijeme(t2);
    int temp(0);
    Vrijeme t3;
    t3.sekunde = t1.sekunde+t2.sekunde;
    if(t3.sekunde>=60) {
        temp = t3.sekunde/60;
        t3.sekunde = t3.sekunde%60;
    }
    t3.minute = t1.minute+t2.minute+temp;
    temp = 0;
    if(t3.minute>=60) {
        temp = t3.minute/60;
        t3.minute = t3.minute%60;
    }
    t3.sati = t1.sati+t2.sati+temp;
    if(t3.sati==24) t3.sati=0;
    if(t3.sati>24) t3.sati=23;
    return t3;
}

int main ()
{
    struct Vrijeme t1,t2,t3;
    try {
        std::cout<<"Unesite prvo vrijeme (h m s): ";
        std::cin>>t1.sati>>t1.minute>>t1.sekunde;
        TestirajVrijeme(t1);
        std::cout<<"Unesite drugo vrijeme (h m s): ";
        std::cin>>t2.sati>>t2.minute>>t2.sekunde;
        TestirajVrijeme(t2);
        std::cout<<"Prvo vrijeme: ";
        IspisiVrijeme(t1);
        std::cout<<"\nDrugo vrijeme: ";
        IspisiVrijeme(t2);
        t3 = SaberiVrijeme(t1,t2);
        std::cout<<"\nZbir vremena: ";
        IspisiVrijeme(t3);
    } catch(std::domain_error e) {
        std::cout<<e.what();
    }
    return 0;
}
