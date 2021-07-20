#include<iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <random>
#include <ctime>
#include <iomanip> 
#include <numeric>
using namespace std;

class pazzle_8{
	private:
	int n = 3;
	vector<int> pazzle;
	map<char,bool> Movable {{'w',false},{'a',false},{'s',false},{'d',false}};
	int turn = 0;
	public:
	pazzle_8(int _n){
		n = _n;
		pazzle = vector<int>(n*n,0);
		*pazzle.begin() = 0;
		iota(pazzle.begin()+1, pazzle.end(), 1);
		for(auto it = pazzle.begin(); it != pazzle.end(); ++it){
			cout << *it << endl;
		}
	}

	void show(){
		//cout << "show" << endl;
		auto begin = pazzle.begin();
		cout << "pazzle turn : " << turn << endl;
		auto end = pazzle.end();
		auto it = pazzle.begin();
		it++;
		it != end;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				
				if(*(begin + (n*i+j)) == 0){
					cout << "  □ ";
				}else{
					cout << setfill(' ') << setw(3) << *(begin + (n*i+j)) << " ";
				}
			}
			cout << endl;
		}
	}

	bool move(char dir){
		//cout << "move" << endl;
		auto result = find(pazzle.begin(), pazzle.end(), 0);
		if(dir == 'w'){
			*result = *(result-n);
			*(result-n) = 0;
		} else if(dir == 'a'){
			*result = *(result-1);
			*(result-1) = 0;
		} else if(dir == 's'){
			*result = *(result+n);
			*(result+n) = 0;
		} else if(dir == 'd'){
			*result = *(result+1);
			*(result+1) = 0;
		}
		turn++;
		return true;
	}

	bool renewMovableList(){
		//cout << "renewMovableList" << endl;
		auto result = find(pazzle.begin(), pazzle.end(), 0);
		Movable['w'] = false;
		Movable['a'] = false;
		Movable['s'] = false;
		Movable['d'] = false;
		if(result == pazzle.end()){
			return false;
		}
		if((result - n) >= pazzle.begin()){
			Movable['w'] = true;
		}
		if((distance(pazzle.begin(), result) % n) != 0){
			Movable['a'] = true;
		}
		if(result + n < pazzle.end()){
			Movable['s'] = true;
		}
		if((distance(pazzle.begin(), result) % n) != n-1){
			Movable['d'] = true;
		}
		return true;
	}

	char getMoveDir(void){
		//cout << "getMoveDir" << endl;
		renewMovableList();
		char input = 'q';
		do{
			cin >> input;
		}while(!((input == 'w' || input == 'a' || input == 's' || input == 'd') && Movable[input]));
		return input;
	}

	bool isFinish(){
		int counter = 1;
		for(auto it = pazzle.begin(),end = pazzle.end()-1; it != end; ++it){
			if(counter != *it){
				return false;
			}
			counter++;
		}
		return true;
	}

	void shaffle(void){
		//cout << "shaffle" << endl;
		mt19937_64 engine(time(0));
		shuffle(pazzle.begin(), pazzle.end(), engine);
	}
};

int main(){
	pazzle_8 pazzle = pazzle_8(4);
	pazzle.shaffle();
	while(!pazzle.isFinish()){
		pazzle.show();
		pazzle.renewMovableList();
		cout << "'w↑ a← s↓ d→' : ";
		pazzle.move(pazzle.getMoveDir());
	}
	pazzle.show();
	cout << "finish" << endl;
	cin.get();
	return 0;
}