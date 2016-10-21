#ifndef FLOAD_H
#define FLOAD_H

#include <vector>
#include <bitset>
#include <string>

namespace fload{
	std::vector<std::bitset<8>> loadMsg(std::string);
	std::vector<std::bitset<8>> get128(const std::vector<std::bitset<8>>&, int = 0);
	std::vector<std::bitset<8>> getNum(const std::vector<std::bitset<8>>&,int, int = 0);
	void printData(const std::vector<std::bitset<8>>&);
	std::vector<std::bitset<8>> base16toBin(std::string&);
	std::vector<std::bitset<8>> base256toBin(std::string&);
	
	void load_key(unsigned char*, int, std::string);
	void load_iv(unsigned char*, int, std::string);
}

#endif
