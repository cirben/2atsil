#include "Decryptor.h"
#include<iostream>
#include<math.h>
#include "data.h"
#include "fload.h"
#include "Decryptor.h"
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/base64.h"


using namespace CryptoPP;
using namespace std;

Decryptor::Decryptor(){}

void Decryptor::setSIC(string su,string iv,string ci){
	sufix = su;
	ivector = iv;
	cipher = ci;
}

void Decryptor::init(){
	plen =  64 - sufix.length();	
	keyc = pow(16,plen);
	fload::load_iv(iv, sizeof(iv),ivector);
	threads = 8;
	dead = 0;
	stop = false;
	Base64Decoder decoder;
	decoder.Attach( new StringSink(cipherDecoded));
	decoder.Put((byte*)cipher.data(), cipher.size());
	decoder.MessageEnd();
}

void Decryptor::compute(){
	for(int i = 0; i < threads; i++){
		workers.push_back(new thread(&Decryptor::tfunc, this, i, keyc/8));
	}
	for(thread *t : workers){
		t->join();
	}

}

void Decryptor::tfunc(int number, long portion){
	bool cont = true;
	int counter =0;
	while(cont){
		long min, max;
		min = portion * number;
		max = portion * (number+1);
		string tab = "0123456789abcdef";
		string key;
		long tmp;
		byte aes_key[32];
		CBC_Mode<AES>::Decryption dec;
		bool ok;
		string alph = "\n aąbcćdeęfghijklłmnoópqrsśtuvwxyzżźAĄBCĆDEĘFGHIJKLŁMNOÓPQRSTUVWXYZŻŹ0123456789,.";
		for(long i = min; i < max; i++){
			tmp = i;
			string prefix = "";
			
			for(int j = 0; j < plen; j++){
				prefix = tab[tmp%16] + prefix;
				tmp /= 16;
			}
			key =  prefix + sufix; 
//			cout << "thread "<< number << " checking " << key << endl;
			fload::load_key(aes_key, sizeof(aes_key), key);
			
			dec.SetKeyWithIV(aes_key, sizeof(aes_key), iv);
			string recovered;
			StringSink* sink = new StringSink(recovered);
			StreamTransformationFilter *aes_dec = new StreamTransformationFilter(dec, sink);
			
			try{
				StringSource source(cipherDecoded, true, aes_dec);
			}catch(CryptoPP::InvalidCiphertext a){continue;}
			ok = true;
			for(char a : recovered){
				bool found = false;
				for(char b : alph){
					if(a == b){
						found = true;
						break;
					}
				}
				if(!found){
					ok = false;
					break;
				}
			}
			if(ok){
				mutex.lock();
				stop=true;
				award=recovered;
				cout << "FOUND IT~!" << endl;
				mutex.unlock();
			}
			counter ++;
			if(counter >= 128){
				counter = 0;
				mutex.lock();
				if(stop){
					if(dead+1==threads){
						cout << award << endl;
					}
					dead++;
					cout << "Thread " << number << "dies, dead: " << dead << endl;
					mutex.unlock();
					return;
				}
				mutex.unlock();
				cout << "thread "<< number << " checking " << prefix << endl;
			}
		}

		mutex.lock();
		if(dead+1==threads){
			cout << award << endl;
		}
		dead++;
		cout << "thread " << number << " dies , dead: " << dead << endl;
		mutex.unlock();
		return;
	}
}

