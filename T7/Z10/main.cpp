#include <iostream>
#include <functional>

std::function<int(int)> IteriranaFunkcija(std::function<int(int)> funk,int n)
{
    return [funk,n](int x) {
        for(int i = 0; i<n; i++) {
            x=funk(x);
        }
        return x;
    };
}

int main ()
{

    return 0;
}
