#include <iostream>
#include <list>
#include <algorithm>

template <typename NekiTip>
void SortirajListu(std::list<NekiTip> &ls)
{
	for(auto it1 = ls.begin(); it1!=ls.end(); it1++) {
		for(auto it2 = it1; it2!=ls.end(); it2 ++) {
			if(*it2<*it1) {
				auto zamjena = *it2;
				*it2 = *it1;
				*it1=zamjena;
			}
		}
	}
}

int main ()
{
	int broj;
	std::cout<<"Koliko ima elemenata: ";
	std::cin>>broj;
	std::cout<<"Unesite elemente: ";
	std::list<int> ls;
	for(int i = 0;i<broj;i++){
		int temp;
		std::cin>>temp;
		ls.push_back(temp);
	}
	std::cout<<"Sortirana lista: ";
	SortirajListu(ls);
	for(auto x : ls) std::cout<<x<<" ";
	return 0;
}
