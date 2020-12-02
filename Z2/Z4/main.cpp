/* TP, 2018/2019
*/
#include <iostream>
#include <new>

long long int** StirlingoviBrojeviV1(long long int n)
{
    if(n<0) throw std::domain_error("Parametar ne smije biti negativan");
    if(n>=23) throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    long long int** a=nullptr;
    try {
        long long int** a=new long long int*[n+1];
        a[0]=new long long int[n+1];
        for(int i = 1; i<n+1; i++) {
            a[i]=new long long int[i+1];
        }
        for(int i = 0; i<n+1; i++) {
            for(int j =0; j<=i; j++) {
                if(j==0 && i==0) a[i][j]=1;
                else if(j==1 && i!=0) a[i][j]=1;
                else if(j==0 && i!=0) a[i][j]=0;
                else if(j==i) a[i][j]=1;
                else if(i!=0 && j!=0)a[i][j]=a[i-1][j-1]+j*a[i-1][j];
            }
        }
        return a;
    } catch(std::domain_error e) {
        throw std::domain_error("Parametar ne smije biti negativan");
    } catch(std::bad_alloc) {
        for(int i = 0; i<n+1; i++) {
            delete[] a[i];
        }
        delete[] a;
        throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
}

long long int** StirlingoviBrojeviV2(long long int n)
{
    if(n<0) throw std::domain_error("Parametar ne smije biti negativan");
    if(n>=23) throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    long long int** a=nullptr;
    try {
        long long int** a=new long long int*[n+1];
        a[0]=new long long int[((n+1)*(n+1))];
        for(int i = 1; i<n+1; i++) {
            a[i]=a[i-1]+(i+1);
        }
        for(int i = 0; i<n+1; i++) {
            for(int j = 0; j<n+1; j++) {
                if(j==0 && i==0) a[i][j]=1;
                else if(j==1 && i!=0) a[i][j]=1;
                else if(j==0 && i!=0) a[i][j]=0;
                else if(j==i) a[i][j]=1;
                else if(i!=0 && j!=0)a[i][j]=a[i-1][j-1]+j*a[i-1][j];
            }
        }
        return a;
    } catch(std::domain_error e) {
        throw std::domain_error("Parametar ne smije biti negativan");
    } catch(std::bad_alloc) {
        delete[] a;
        throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
}
int main ()
{
    try {
        int n;
        std::cin>>n;
        long long int** p = StirlingoviBrojeviV2(n);
        for (int i(0); i<=n; i++) {
            for (int j(0); j<=i; j++)
                std::cout << p[i][j] << " ";
            std::cout << std::endl;
        }
        delete[] p[0];
        delete[] p;
        long long int** p1 = StirlingoviBrojeviV1(n);
        for (int i(0); i<=n; i++) {
            for (int j(0); j<=i; j++)
                std::cout << p1[i][j] << " ";
            std::cout << std::endl;
        }
        for(int i = 0; i<n+1; i++) {
            delete[] p1[i];
        }
        delete[] p1;
    } catch(std::domain_error e) {
        std::cout<<e.what();
    } catch(std::range_error e) {
        std::cout<<"Range error: "<<e.what();
    }
    return 0;
}
