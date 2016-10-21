#include<iostream>
#include<string>
#include<vector>
#include<fstream>

#include "fload.h"
#include "converter.h"

using namespace std;

void fload::load_key(unsigned char* out, int size, string key){
	vector<bitset<8>> binkey = fload::base16toBin(key);
	binkey = fload::getNum(binkey, 256);
	for(int i = 0; i < size; i++){
		*(out+i) = static_cast<unsigned char>(binkey[i].to_ulong());
	}
	return;
}

void fload::load_iv(unsigned char* out, int size, string key){
	vector<bitset<8>> biniv = fload::base16toBin(key);
	biniv = fload::getNum(biniv, 256);
	for(int i = 0; i < size; i++){
		*(out+i) = static_cast<unsigned char>(biniv[i].to_ulong());
	}
	return;
}


vector<bitset<8>> fload::base16toBin(string& number){
	vector<bitset<8>> binary;
	bitset<8> a(string("00000000"));
	string oct[2];
	int index = 0;
	for(char c : number){
		oct[index] = converter::hexToBin(c);
		index++;
		if(index == 2){
			index = 0;
			string byte = oct[0] + oct[1];
			for(int i = 0 ; i < 8 ; i++){
				if(byte[i] == '1')
					a[7-i] = 1;
				else
					a[7-i] = 0;
			}
			binary.push_back(a);
		}
	}
	if(index == 1){
		string byte = oct[0] + "0000";
		for(int i = 0 ; i < 8 ; i++)
			if(byte[i] == '1')
				a[7-i] = 1;
			else
				a[7-i] = 0;
		binary.push_back(a);
	}
	return binary;
}

vector<bitset<8>> fload::base256toBin(string& number){
	vector<bitset<8>> binary;
	bitset<8> a(string("00000000"));
	string oct;
	for(char c : number){
		oct = converter::hexToBin(c);
		string byte = "0000"  + oct;
		for(int i = 0 ; i < 8 ; i++){
			if(byte[i] == '1')
				a[7-i] = 1;
			else
				a[7-i] = 0;
		}
		binary.push_back(a);
	}
	return binary;
}

vector<bitset<8>> fload::loadMsg(string path){
	vector<bitset<8>> fullMsg;
	string msg;
	string line;
	ifstream file(path);
	if(file.is_open()){
		while(getline(file,line)){
			msg += line;
		}
	}
	int index = 0;
	bitset<8> a(string("00000000"));
	for(char c : msg){
		if(c == '1' || c == '0'){
			if(c == '1')
				a[7-index++] = 1;
			else 
				a[7-index++] = 0;
			if(index == 8){
				index=0;
				fullMsg.push_back(a);
				a ^= a;
			}
		}
	}
	return fullMsg;
}

vector<bitset<8>> fload::get128(const vector<bitset<8>> &msg, int firstI){
	vector<bitset<8>> set;
	int copied = 0;
	for(vector<bitset<8>>::const_iterator it = msg.begin() + firstI; it < msg.end(); it++){
		set.push_back(*it);
		copied++;
		if(copied == 16)
			break;
	}
	while(copied != 16){
		bitset<8> zero(string("00000000"));
		set.push_back(zero);
		copied++;
	}
	return set;
}


vector<bitset<8>> fload::getNum(const vector<bitset<8>> &msg,int num, int firstI){
	vector<bitset<8>> set;
	num = num / 8;
	int copied = 0;
	for(vector<bitset<8>>::const_iterator it = msg.begin() + firstI; it < msg.end(); it++){
		set.push_back(*it);
		copied++;
		if(copied == num)
			break;
	}
	while(copied != num){
		bitset<8> zero(string("00000000"));
		set.push_back(zero);
		copied++;
	}
	return set;
}

void fload::printData(const vector<bitset<8>> &msg){
	for(bitset<8> b : msg){
		cout << b << " ";
	}
	cout << "\n\n";
	return;
}
