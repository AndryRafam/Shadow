#include <iostream>
#include <exception>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/gcm.h>
#include <cryptopp/sha.h>
#include <cryptopp/hkdf.h>
#include <cryptopp/aes.h>

#include "../Core/ASERP.h"

#include <cstdio>
#define Red "\x1B[31m"
#define Reset "\x1B[0m"

using namespace CryptoPP;

ASERP::ASERP(void){ }

std::string ASERP::aserp(std::string text, std::string password1, std::string salt1, std::string password2, std::string salt2, std::string choice)
{
	std::string inter, ciphertext, recovered;
	
	try
	{
		SecByteBlock key1(AES::MAX_KEYLENGTH);
		SecByteBlock key2(AES::MAX_KEYLENGTH);
		SecByteBlock iv1(AES::BLOCKSIZE);
		SecByteBlock iv2(AES::BLOCKSIZE);
		HKDF<SHA256> hkdf;
		hkdf.DeriveKey(key1, key1.size(), (const byte*)password1.data(), password1.size(), (const byte*)salt1.data(), salt1.size(), NULL, 0); 
		hkdf.DeriveKey(key2, key2.size(), (const byte*)password2.data(), password2.size(), (const byte*)salt2.data(), salt2.size(), NULL, 0);
		hkdf.DeriveKey(iv1, iv1.size(), (const byte*)password1.data(), password1.size(), (const byte*)salt1.data(), salt1.size(), NULL, 0);
		hkdf.DeriveKey(iv2, iv2.size(), (const byte*)password2.data(), password2.size(), (const byte*)salt2.data(), salt2.size(), NULL, 0);
		GCM<AES>::Encryption enc1;
		GCM<AES>::Encryption enc2;
		GCM<AES>::Decryption dec1;
		GCM<AES>::Decryption dec2;
		if(choice == "e")
		{	
			enc1.SetKeyWithIV(key1, key1.size(), iv1, iv1.size());
			enc2.SetKeyWithIV(key2, key2.size(), iv2, iv2.size());
			StringSource(text, true, new AuthenticatedEncryptionFilter(enc1, new StringSink(inter)));
			StringSource(inter, true, new AuthenticatedEncryptionFilter(enc2, new StringSink(ciphertext)));
		}
		else
		{
			dec1.SetKeyWithIV(key1, key1.size(), iv1, iv1.size());
			dec2.SetKeyWithIV(key2, key2.size(), iv2, iv2.size());
			StringSource(text, true, new AuthenticatedDecryptionFilter(dec2, new StringSink(inter), AuthenticatedDecryptionFilter::THROW_EXCEPTION));
			StringSource(inter, true, new AuthenticatedDecryptionFilter(dec1, new StringSink(recovered), AuthenticatedDecryptionFilter::THROW_EXCEPTION));
		}
	}
	catch(Exception& ex)
	{
		std::cout << "\n";
		std::cerr << Red << "ERROR: " << ex.what() << Reset << "\n\n";
		exit(0);
	}
	if(choice == "e")
	{
		return ciphertext;
		
	}
	else
	{
		return recovered;
	}
}

ASERP::~ASERP(void){ }
