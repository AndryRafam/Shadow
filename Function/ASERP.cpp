#include <iostream>
#include <exception>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/gcm.h>
#include <cryptopp/sha.h>
#include <cryptopp/hkdf.h>
#include <cryptopp/aes.h>
#include <cryptopp/serpent.h>

#include "../Core/ASERP.h"

using namespace CryptoPP;

ASERP::ASERP(void){ }

std::string ASERP::aserp(std::string text, std::string password, std::string choice)
{
	std::string inter, ciphertext, recovered;

	try
	{
		byte key1[AES::MAX_KEYLENGTH];
		byte key2[Serpent::MAX_KEYLENGTH];
		byte iv1[AES::BLOCKSIZE];
		byte iv2[Serpent::BLOCKSIZE];
		HKDF<SHA256> hkdf;
		hkdf.DeriveKey(key1, sizeof(key1), (const byte*)password.data(), password.size(), NULL, 0, NULL, 0); 
		hkdf.DeriveKey(key2, sizeof(key2), (const byte*)password.data(), password.size(), NULL, 0, NULL, 0);
		hkdf.DeriveKey(iv1, sizeof(iv1), (const byte*)password.data(), password.size(), NULL, 0, NULL, 0);
		hkdf.DeriveKey(iv2, sizeof(iv2), (const byte*)password.data(), password.size(), NULL, 0, NULL, 0);
		GCM<AES>::Encryption enc1;
		GCM<Serpent>::Encryption enc2;
		GCM<AES>::Decryption dec1;
		GCM<Serpent>::Decryption dec2;
		if(choice == "e")
		{	
			enc1.SetKeyWithIV(key1, sizeof(key1), iv1, sizeof(iv1));
			enc2.SetKeyWithIV(key2, sizeof(key2), iv2, sizeof(iv2));
			StringSource(text, true, new AuthenticatedEncryptionFilter(enc2, new StringSink(inter)));
			StringSource(inter, true, new AuthenticatedEncryptionFilter(enc1, new StringSink(ciphertext)));
		}
		else
		{
			dec1.SetKeyWithIV(key1, sizeof(key1), iv1, sizeof(iv1));
			dec2.SetKeyWithIV(key2, sizeof(key2), iv2, sizeof(iv2));
			StringSource(text, true, new AuthenticatedDecryptionFilter(dec1, new StringSink(inter), AuthenticatedDecryptionFilter::THROW_EXCEPTION));
			StringSource(inter, true, new AuthenticatedDecryptionFilter(dec2, new StringSink(recovered), AuthenticatedDecryptionFilter::THROW_EXCEPTION));
		}
	}
	catch(Exception& ex)
	{
		std::cerr << "ERROR: " << ex.what() << std::endl;
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