#include<iostream>
#include<math.h>
#include "data.h"
#include "Decryptor.h"
#include "fload.h"
#include "Decryptor.h"
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/base64.h"


using namespace CryptoPP;
using namespace std;

int main(int argc, char* argv[]){	
	int t;
	try{
		string a = string(argv[1]);
		t= std::stoi(a);
	}catch(std::logic_error){
		t=0;
	}
	Decryptor b;
	if(argc == 2)
		b.setSIC(data::sufix[t], data::iv[t], data::cipher[t]);
	else
		b.setSIC("e2dbf33bb28325f4ec937632e3b0ae3d15333b33692d3967532d6473552","fdf881c75a1a52a21c13b4e752b10d39", "6ONvZI7q7NAUW7wJHkKPu3Zp3OjRM5mpfloPi57755XaDUCb3bf22Xxkdkm6U+vVps9cob0EUm6ekbxJj+Aq+laOYy71CiM5c02Ekdh+Nh+NUzN2LkK+VelSV2bXhegkfApUjKv/rTRLJtNN1sbSjA==");
	b.init();
	b.compute();
}

