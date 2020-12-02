#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

template <typename Tip1,typename Tip2>
void Zamijeni(Tip1 &a,Tip2 &b){
	Tip1 c = a;
	a=b;
	b=c;
}

template <typename Tip1,typename Tip2>
void ZamijeniItove(Tip1 a,Tip2 b){
	Zamijeni(*a,*b);
}

template <typename IterTip, typename IterTip1, typename IterTip2>
IterTip2 RazmijeniBlokove(IterTip pocetak,IterTip1 iza_kraja,IterTip2 novipocetak)
{
	while(pocetak!=iza_kraja) {
		ZamijeniItove(pocetak++,novipocetak++);
	}
	return novipocetak;
}

int main ()
{
	return 0;
}
