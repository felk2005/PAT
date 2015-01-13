#include <iostream>
#include <vector>
#include "MaxSequenceSum.h"

using namespace std;


int main(int argc, const char * argv[])
{
    int a[] = {-2,11,-4,13,-5,-2};
    vector<int> seq = vector<int>(a, a+6);
// 	int n,k=0;
// 	cout<<"Please input 'n':";
// 	cin>>n;

//     seq.reserve(n);
// 	cout<<"Please input the numbers:";//输入n*n个数
// 	for(int i=0;i<n;i++)
// 	{
// 		cin>>k;
// 		seq.push_back(k);
// 	}
// 	for(int i=0;i<n;i++)//为了便于对照，把整个数组输出一次
// 	{
// 		cout << seq[i] << " ";
// 	}
    cout << MaxSequenceSum::Solution(seq);
	cout<<endl;
    return 0;
}