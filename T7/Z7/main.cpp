#include <iostream>
#include <set>
#include <algorithm>

template <typename NekiTip>
std::set<NekiTip> Unija(std::set<NekiTip> s1,std::set<NekiTip> s2)
{
	std::set<NekiTip> s3{};
	for(auto it = s1.begin(); it!=s1.end(); it++) s3.insert(*it);
	for(auto it = s2.begin(); it!=s2.end(); it++) s3.insert(*it);
	return s3;
}

template <typename NekiTip>
std::set<NekiTip> Presjek(std::set<NekiTip> s1,std::set<NekiTip> s2)
{
	std::set<NekiTip> s3{};
	for(auto it1 = s1.begin(); it1!=s1.end(); it1++) {
		for(auto it2 = s2.begin(); it2!=s2.end(); it2++) {
			if(*it1==*it2) s3.insert(*it1);
		}
	}
	return s3;
}

int main ()
{
	return 0;
}
