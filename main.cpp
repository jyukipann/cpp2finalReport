//T319059 Tanimoto Juki
#include<iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <random>
#include <ctime>
#include <iomanip> 
#include <numeric>
#include <fstream>
using namespace std;

class pazzle_8{
	private:
	int n = 3;
	vector<int> pazzle;
	map<char,bool> Movable {{'w',false},{'a',false},{'s',false},{'d',false}};
	int turn = 0;
	int blank = 0;
	public:
	pazzle_8(int _n){
		n = _n;
		blank = n*n;
		pazzle = vector<int>(n*n,0);
		iota(pazzle.begin(), pazzle.end(), 1);
		shaffle();
	}

	bool isSolvable(){
		vector<int> payyle(pazzle.size());
		copy(pazzle.begin(), pazzle.end(), payyle.begin());
		int now = 1;
		int swapcount = 0;
		int tmp = 0;
		for(int i = 0; i < pazzle.size(); i++){
			if(now <= pazzle.size()){
				auto result = find(pazzle.begin()+now-1, pazzle.end(), now);
				//cout << *result << endl;
				if(pazzle.begin()+now-1 != result){
					swapcount+=1;
					tmp = *result;
					*result = *(pazzle.begin()+now-1);
					*(pazzle.begin()+now-1) = tmp;
				}
				now+=1;
			}
			//cout << "a";
		}
		//show();
		//cout << "swap : " << swapcount << endl;
		copy(payyle.begin(), payyle.end(), pazzle.begin());
		auto result = find(pazzle.begin(), pazzle.end(), blank);
		int i = (distance(pazzle.begin(), result)/n );
		//cout << i << endl;
		int j = (distance(pazzle.begin(), result)%n);
		//cout << j << endl;
		//cout << "dist : " << 6-(i+j) << endl;
		if((i+j)%2 == swapcount%2){
			return true;
		}else{
			return false;
		}
	}

	void refinePazzle(){
		auto result = find(pazzle.begin(), pazzle.end(), blank);
		if(pazzle.begin() == result){
			int tmp = *(result+1);
			*(result+1) = *(result+2);
			*(result+2) = tmp;
		}else if(pazzle.end()-1 == result){
			int tmp = *(result-1);
			*(result-1) = *(result-2);
			*(result-2) = tmp;
		}else{
			int tmp = *(result-1);
			*(result-1) = *(result+1);
			*(result+1) = tmp;
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
				
				if(*(begin + (n*i+j)) == blank){
					cout << "  @ ";
				}else{
					cout << setfill(' ') << setw(3) << *(begin + (n*i+j)) << " ";
				}
			}
			cout << endl;
		}
	}

	bool move(char dir){
		//cout << "move" << endl;
		auto result = find(pazzle.begin(), pazzle.end(), blank);
		if(dir == 'w'){
			*result = *(result-n);
			*(result-n) = blank;
		} else if(dir == 'a'){
			*result = *(result-1);
			*(result-1) = blank;
		} else if(dir == 's'){
			*result = *(result+n);
			*(result+n) = blank;
		} else if(dir == 'd'){
			*result = *(result+1);
			*(result+1) = blank;
		}
		turn++;
		return true;
	}

	bool renewMovableList(){
		//cout << "renewMovableList" << endl;
		auto result = find(pazzle.begin(), pazzle.end(), blank);
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

	//load pazzle
	// n pazzle(n*n) turn
	void loadData(){
		
	}

	//save current pazzle
	// n pazzle(n*n) turn
	void saveData(){
		ofstream save_file;
		save_file.open("save_data.txt");
		save_file << n << endl;
		//save_file << pazzle << endl;
		save_file << turn << endl;
	}

	char getMoveDir(void){
		//cout << "getMoveDir" << endl;
		renewMovableList();
		char input = 'q';
		do{
			cin >> input;
			if(input == 's'){
				saveData();
			}else if(input == 'l'){
				loadData();
			}
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
		if(!isSolvable()){
			refinePazzle();
		}
	}
};

int main(){
	int n = 0;
	cout << "n = ";
	cin >> n;
	if(n < 3){
		n = 3;
	}
	pazzle_8 pazzle = pazzle_8(n);
/* 	if(pazzle.isSolvable()){
		cout << "solvable" << endl;
	}else{
		cout << "cant solve" << endl;
	} */
	while(!pazzle.isFinish()){
		pazzle.show();
		pazzle.renewMovableList();
		cout << "w(up) a(right) s(dwon) d(left) r(save) l(load): ";
		pazzle.move(pazzle.getMoveDir());
	}
	pazzle.show();
	cout << "finish" << endl;
	return 0;
}