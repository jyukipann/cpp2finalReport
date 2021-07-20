#include<iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <random>
#include <numeric>
#include <iomanip> 
#include <ctime>
using namespace std;

int main(){
	//char input = 'q';
	//cin >> input;
/* 	if((input == 'w' || input == 'a' || input == 's' || input == 'd')){
		cout << 'a' << endl;
	} */
	//cout << setfill('0') << setw(3) << (int)38 << " ";
	vector<int> pazzle(4*4);
	pazzle[0] = 0;
	iota(pazzle.begin()+1, pazzle.end(), 1);
	mt19937_64 engine(time(0));
	shuffle(pazzle.begin(), pazzle.end(), engine);
	for(auto it = pazzle.begin(),end = pazzle.end(); it != end; ++it){
		cout << *it << endl;
	}
	return 0;
}