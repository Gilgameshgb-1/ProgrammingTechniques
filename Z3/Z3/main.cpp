#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>

template <typename TipElemenata>
    struct Matrica{
        int br_redova, br_kolona;
        TipElemenata **elementi = nullptr;
    };
    
template <typename TipElemenata>
    void UnistiMatricu(Matrica<TipElemenata> &mat){
        if(!mat.elementi) return;
        for(int i =0;i<mat.br_redova;i++) delete[] mat.elementi[i];
        delete[] mat.elementi;
        mat.elementi = nullptr;
    }
    
template <typename TipElemenata>
    Matrica<TipElemenata> StvoriMatricu(int br_redova,int br_kolona){
        Matrica<TipElemenata> mat;
        mat.br_redova = br_redova;
        mat.br_kolona = br_kolona;
        mat.elementi = new TipElemenata*[br_redova]{};
        try{
            for(int i = 0;i<br_redova;i++){
                mat.elementi[i]= new TipElemenata[br_kolona];
            }
        }catch(...){
            UnistiMatricu(mat);
            throw;
        }
        return mat;
    }
    
template <typename TipElemenata>
    void UnesiMatricu(char ime_matrice, Matrica<TipElemenata> &mat){
        for(int i =0;i<mat.br_redova;i++){
            for(int j = 0;j<mat.br_kolona;j++){
                std::cout<<ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
                std::cin>>mat.elementi[i][j];
            }
        }
    }

template <typename TipElemenata>
    void IspisiMatricu(/*const */Matrica<TipElemenata> &mat,int sirina_ispisa,int preciznost = 6,bool treba_brisati = false){
        for(int i = 0;i<mat.br_redova;i++){
            for(int j = 0;j<mat.br_kolona;j++){
                std::cout<<std::setw(sirina_ispisa)<<std::setprecision(preciznost)<<mat.elementi[i][j];
            }
            std::cout<<"\n";
        }
        if(treba_brisati == true) UnistiMatricu(mat);
    }
    template <typename TipElemenata>
    void ZbirMatrica(Matrica<TipElemenata> &m1,Matrica<TipElemenata> &m2){
        if(m1.br_redova!=m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
        for(int i = 0;i<m1.br_redova;i++){
            for(int j = 0;j<m1.br_kolona;j++){
                m1.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
            }
        }
    }

template <typename TipElemenata>
    Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1,const Matrica<TipElemenata> &m2){
        if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
        auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova,m2.br_kolona);
        for(int i =0;i<m1.br_redova;i++){
            for(int j = 0;j<m2.br_kolona;j++){
                m3.elementi[i][j]=0;
                for(int k= 0;k<m1.br_kolona;k++){
                    m3.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
                }
            }
        }
        return m3;
    }

template <typename TipElemenata>
    Matrica<TipElemenata> MatricniPolinom(const Matrica<TipElemenata> &m1,std::vector<double> v){
        if(m1.br_redova!=m1.br_redova) throw std::domain_error("Matrica mora biti kvadratna");
        auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova,m1.br_kolona);
        Matrica<TipElemenata> m4;
        for(int i = 0;i<m3.br_redova;i++){
            for(int j = 0;j<m3.br_kolona;j++){
                if(i==j) m3.elementi[i][j]=1;
                else m3.elementi[i][j]=0;
            }
        }//OK
        auto RezultantnaMatrica = StvoriMatricu<TipElemenata>(m1.br_redova,m1.br_kolona);
        for(int i = 0;i<m3.br_redova;i++){
            for(int j = 0;j<m3.br_kolona;j++){
                RezultantnaMatrica.elementi[i][j]=0;
            }
        }//izaziva mem greske ovo dole
        for(int i = 0;i<v.size();i++){
            if(i==0){
            for(int j = 0;j<m3.br_redova;j++){
                for(int k =0;k<m3.br_redova;k++){
                    m3.elementi[j][k]=v[i]*m3.elementi[j][k];
                }
            }
                ZbirMatrica(RezultantnaMatrica,m3);
                for(int i = 0;i<m3.br_redova;i++){
                    for(int j = 0;j<m3.br_kolona;j++){
                        m3.elementi[i][j]=m1.elementi[i][j];
                    }
                }
            }else if(v[i]!=0){
                for(int j = 0;j<m3.br_redova;j++){
                    for(int k = 0;k<m3.br_kolona;k++){
                        m3.elementi[j][k]=v[i]*m3.elementi[j][k];
                    }
                }
                ZbirMatrica(RezultantnaMatrica,m3);
                if(v[i]!=0){
                    for(int j = 0;j<m3.br_redova;j++){
                        for(int k = 0;k<m3.br_kolona;k++){
                            m3.elementi[j][k]=m3.elementi[j][k]/v[i];
                        }
                    }
                }
                m4=ProduktMatrica(m3,m1);
                for(int i = 0;i<m1.br_redova;i++){
                    for(int j =0;j<m1.br_redova;j++){
                        m3.elementi[i][j]=m4.elementi[i][j];
                    }
                }
                UnistiMatricu(m4);
            }else if(v[i]==0){
                 m4=ProduktMatrica(m3,m1);
                for(int i = 0;i<m1.br_redova;i++){
                    for(int j =0;j<m1.br_redova;j++){
                        m3.elementi[i][j]=m4.elementi[i][j];
                    }
                }
                UnistiMatricu(m4);
            }
        }
        UnistiMatricu(m3);
        return RezultantnaMatrica;
    }

int main ()
{
    std::vector<double> v;
    Matrica<double> a;
    Matrica<double> c;
    std::cout<<"Unesite dimenziju kvadratne matrice: ";
    int temp;
    std::cin>>temp;
    std::cout<<"Unesite elemente matrice A: \n";
    a=StvoriMatricu<double>(temp,temp);
    UnesiMatricu('A',a);
    std::cout<<"Unesite red polinoma: ";
    int red;
    std::cin>>red;
    std::cout<<"Unesite koeficijente polinoma: ";
    for(int i = 0;i<=red;i++){
        int g;
        std::cin>>g;
        v.push_back(g);
    } 
    try{
    c=MatricniPolinom<double>(a,v);
    IspisiMatricu(c,10);
    UnistiMatricu(a);
    UnistiMatricu(c);
    }catch(std::domain_error e){
        std::cout<<e.what();
        UnistiMatricu(a);
        UnistiMatricu(c);
    }
    return 0;
}