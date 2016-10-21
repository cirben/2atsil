#include "converter.h"

using namespace std;

std::string converter::hexToBin(char num){
	string ret;
	switch(num){
		case '0': ret = "0000"; break;
		case '1': ret = "0001"; break;
		case '2': ret = "0010"; break;
		case '3': ret = "0011"; break;
		case '4': ret = "0100"; break;
		case '5': ret = "0101"; break;
		case '6': ret = "0110"; break;
		case '7': ret = "0111"; break;
		case '8': ret = "1000"; break;
		case '9': ret = "1001"; break;
		case 'a':
		case 'A': ret = "1010"; break;
		case 'b':
		case 'B': ret = "1011"; break;
		case 'c':
		case 'C': ret = "1100"; break;
		case 'd':
		case 'D': ret = "1101"; break;
		case 'e':
		case 'E': ret = "1110"; break;
		case 'f':
		case 'F': ret = "1111"; break;
	}
	return ret;
}
