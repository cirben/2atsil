#include "block128.h"

using namespace std;

Block128::Block128(const vector<bitset<8>>& data){
	for(vector<bitset<8>>::const_iterator it = data.begin(); it < data.begin()+16; it++){
		int x = it - data.begin();
		block[x/4][x%4] = *it;
	}
}
