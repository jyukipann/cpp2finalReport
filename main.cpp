#include<iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class pazzle_8{
	private:
	vector<int> pazzle = {1,2,3,4,5,6,7,8,0};
	map<char,bool> Movable {{'w',false},{'a',false},{'s',false},{'d',false}};
	public:
	pazzle_8(){
		//cout << "pazzle" << endl;
	}
	void show(){
		cout << "pazzle" << endl;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(pazzle[3*i+j] == 0){
					cout << "  ";
				}else{
					cout << pazzle[3*i+j] << " ";
				}
			}
			cout << endl;
		}
	}
	bool move(char dir){
	}
	bool renewMovableList(){
		auto result = std::find(pazzle.begin(), pazzle.end(), 0);
		Movable['w'] = false;
		Movable['a'] = false;
		Movable['s'] = false;
		Movable['d'] = false;
		if(result == pazzle.end()){
			return false;
		}
		if(result - 3 >= 0){
			Movable['w'] = true;
		}
		if(result % 3 != 0){
			Movable['a'] = true;
		}
		if(result + 3 < 9){
			Movable['s'] = true;
		}
		if(result % 3 != 2){
			Movable['d'] = true;
		}
		return true;
	}
};

int main(){
	pazzle_8 pazzle = pazzle_8();
	pazzle.show();
	cout << "end" << endl;
	cin.get();
	return 0;
}