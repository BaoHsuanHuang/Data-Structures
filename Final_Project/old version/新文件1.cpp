#include <set>
#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;


int main(void)
{
    set<int> a,b,c;   //c�]�i�H�w�q��vector
    a.insert(1);
    a.insert(6);
    a.insert(6);
    b.insert(2);
    b.insert(6);
    b.insert(9);


    //�̫�@�Ӥ޼ƭY�ϥ�c.begin()�|���ͽsĶ���~assignment of read-only localtion.


    set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
    for(set<int>::iterator it=c.begin();it!=c.end();it++)
        cout<<*it<<" ";
        
    cout << endl;
	a.insert(1);
	for(set<int>::iterator it=a.begin();it!=a.end();it++)
        cout<<*it<<" ";

    return 0;
}
