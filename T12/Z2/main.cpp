#include <iostream>
#include <set>
#include <algorithm>
#include <tuple>

template <typename NekiTip>
std::set<NekiTip> operator+(const std::set<NekiTip> &s1,const std::set<NekiTip> &s2)
{
	std::set<NekiTip> s3{};
	for(auto it = s1.begin(); it!=s1.end(); it++) s3.insert(*it);
	for(auto it = s2.begin(); it!=s2.end(); it++) s3.insert(*it);
	return s3;
}

template <typename NekiTip>
std::set<NekiTip> operator*(const std::set<NekiTip> &s1,const std::set<NekiTip> &s2)
{
	std::set<NekiTip> s3{};
	for(auto it1 = s1.begin(); it1!=s1.end(); it1++) {
		for(auto it2 = s2.begin(); it2!=s2.end(); it2++) {
			if(*it1==*it2) s3.insert(*it1);
		}
	}
	return s3;
}

template <typename NekiTip>
std::ostream &operator<<(std::ostream &tok,const std::set<NekiTip> s){
    tok<<"{";
    for(auto it = s.begin(); it != s.end(); it++){
        if(it != --s.end() ){
            tok<<*it<<",";
        }else if(it == --s.end() ) {
            tok<<*it;
        }
    }
    tok<<"}";
    return tok;
}

template <typename NekiTip>
std::set<NekiTip> &operator+=(std::set<NekiTip> &s1,const std::set<NekiTip> &s2){
	for(auto it = s2.begin(); it!=s2.end(); it++) s1.insert(*it);
	return s1;
} 


template <typename NekiTip>
std::set<NekiTip> &operator*=(std::set<NekiTip> &s1,const std::set<NekiTip> &s2){
	std::set<NekiTip> s3{};
	for(auto it1 = s1.begin(); it1!=s1.end(); it1++) {
		for(auto it2 = s2.begin(); it2!=s2.end(); it2++) {
			if(*it1==*it2) s3.insert(*it1);
		}
	}
	s1.clear(); 
	s1=s3;
    return s1;
} 

template <typename NekiTip1,typename NekiTip2>
std::set<std::pair<NekiTip1,NekiTip2>> operator%(const std::set<NekiTip1> &s1,const std::set<NekiTip2> &s2){
    std::set<std::pair<NekiTip1,NekiTip2>> p;
    for(auto it1 = s1.begin(); it1!=s1.end(); it1++){
        for(auto it2 = s2.begin(); it2!=s2.end(); it2++){
            p.insert(std::make_pair(*it1,*it2));
        }
    }
    return p;
}

template<typename NekiTip1,typename NekiTip2>
std::ostream &operator<<(std::ostream &tok,const std::set<std::pair<NekiTip1,NekiTip2>> p){
    tok<<"{";
    for(auto it = p.begin(); it != p.end(); it++){
        if(it != --p.end()){
            tok<<"("<<it->first<<","<<it->second<<"),";
        }else{
            tok<<"("<<it->first<<","<<it->second<<")";
        }
    }
    tok<<"}";
}

int main()
{
//AT4 testiranje Dekartovog proizvoda
std::set<char> s3{'A', 'B'};
std::set<int> s4{1, 2, 3};
std::cout << s3 % s4 << std::endl;

    return 0;
}