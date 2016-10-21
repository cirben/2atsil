#ifndef BLOCK128_H
#define BLOCK128_H

#include<bitset>
#include<vector>

struct Block128{
	std::bitset<8> block[4][4];
	Block128(const std::vector<std::bitset<8>>&);
};

#endif
