#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#include<thread>
#include<iostream>
#include<vector>
#include<math.h>
#include<mutex>
#include "data.h"
#include "fload.h"
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/base64.h"

class Decryptor{
	public:
	Decryptor();
	void setSIC(std::string,std::string,std::string);
	void init();
	void compute();

	private:
	byte iv[16];
	std::string sufix;
	std::string ivector;
	std::string cipher;
	std::string cipherDecoded;
	std::vector<std::thread*> workers;
	void tfunc(int, long);
	std::mutex mutex;

	int plen;
	long keyc;
	int threads;

	bool stop;
	int dead;
	std::string award;
};

#endif
