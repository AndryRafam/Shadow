#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <sys/types.h>
#include <unistd.h>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/gcm.h>
#include <cryptopp/sha.h>
#include <cryptopp/hkdf.h>
#include <cryptopp/aes.h>

#include "../Core/Shadow.h"

using namespace CryptoPP;

Shadow::Shadow(void){ }

std::string Shadow::Aes256(std::string input,std::string pass1,std::string salt1,std::string pass2,std::string salt2,std::string mode){
	std::string inter, final, recovered;
	try{
		SecByteBlock key1(AES::MAX_KEYLENGTH);
		SecByteBlock iv1(AES::BLOCKSIZE);
		SecByteBlock key2(AES::MAX_KEYLENGTH);
		SecByteBlock iv2(AES::BLOCKSIZE);
		HKDF<SHA256> hkdf;
		hkdf.DeriveKey(key1,key1.size(),(const byte*)pass1.data(),pass1.size(),(const byte*)salt1.data(),salt1.size(),NULL,0);
		hkdf.DeriveKey(iv1,iv1.size(),(const byte*)pass1.data(),pass1.size(),(const byte*)salt1.data(),salt1.size(),NULL,0);
		hkdf.DeriveKey(key2,key2.size(),(const byte*)pass2.data(),pass2.size(),(const byte*)salt2.data(),salt2.size(),NULL,0);
		hkdf.DeriveKey(iv2,iv2.size(),(const byte*)pass2.data(),pass2.size(),(const byte*)salt2.data(),salt2.size(),NULL,0);
		GCM<AES>::Encryption enc1;
		GCM<AES>::Decryption dec1;
		GCM<AES>::Encryption enc2;
		GCM<AES>::Decryption dec2;
		if(mode=="encrypt"){
			enc1.SetKeyWithIV(key1,key1.size(),iv1,iv1.size());
			enc2.SetKeyWithIV(key2,key2.size(),iv2,iv2.size());
			StringSource(input,true,new AuthenticatedEncryptionFilter(enc1,new StringSink(inter)));
			StringSource(inter,true,new AuthenticatedEncryptionFilter(enc2,new StringSink(final)));
		}
		else{
			dec1.SetKeyWithIV(key1,key1.size(),iv1,iv1.size());
			dec2.SetKeyWithIV(key2,key2.size(),iv2,iv2.size());
			StringSource(input,true,new AuthenticatedDecryptionFilter(dec2,new StringSink(inter),AuthenticatedDecryptionFilter::THROW_EXCEPTION));
			StringSource(inter,true,new AuthenticatedDecryptionFilter(dec1,new StringSink(recovered),AuthenticatedDecryptionFilter::THROW_EXCEPTION));
		}
	}
	catch(Exception& ex){
		std::cout << "\n";
		std::cout << ex.what() << "\n\n";
		exit(0);
	}
	if(mode=="encrypt")
		return final;
	else
		return recovered;
}

inline bool Shadow::checkDigit(std::string str){
	return (std::any_of(str.begin(),str.end(), ::isdigit) ? true:false);
}

inline bool Shadow::checkLower(std::string str){
	return (std::any_of(str.begin(),str.end(), ::islower) ? true:false);
}

inline bool Shadow::checkUpper(std::string str){
	return (std::any_of(str.begin(),str.end(), ::isupper) ? true:false);
}

inline bool Shadow::checkSpecChar(std::string str){
	bool flag = false;
	for(auto i = 0; str[i]; i++){
		if((str[i]>=32 and str[i]<=47)||(str[i]>=58 and str[i]<=64)||(str[i]>=91 and str[i]<=96)||(str[i]>=123 and str[i]<=126)){
			flag = true;
			break;
		}
	}
	return flag;
}

inline bool Shadow::checkPassword(std::string str){
	return((checkDigit(str) && checkLower(str) && checkUpper(str) && checkSpecChar(str) && str.length()>=16) ? true:false);
}

inline void Shadow::about(){
	std::ifstream infile;
	std::string line;
	infile.open("About.txt");
	while(std::getline(infile,line)){
		std::cout << "\e[1m" << line << "\e[0m" << std::endl;
	}
	infile.close();
	std::cout << "\n";
	return;
}

inline void Shadow::usage(){
	std::ifstream infile;
	std::string line;
	infile.open("Usage.txt");
	while(std::getline(infile,line)){
		std::cout << "\e[1m" << line << "\e[0m" << std::endl;
	}
	infile.close();
	std::cout << "\n";
	return;	
}

inline void Shadow::pass_rules(){
	std::ifstream infile;
	std::string line;
	infile.open("PassRules.txt");
	while(std::getline(infile,line)){
		std::cout << "\e[1m" << line << "\e[0m" << std::endl;
	}
	infile.close();
	std::cout << "\n";
	return;
}

inline void Shadow::license(){
	std::ifstream infile;
	std::string line;
	infile.open("LICENSE");
	while(std::getline(infile,line)){
		std::cout << "\e[1m" << line << "\e[0m" << std::endl;
	}
	infile.close();
	std::cout << "\n";
	return;
}

inline int Shadow::sum(std::string str){
	int c = 0;
	for(auto x = 0; str[x]; x++){
		c+=int(str[x]);
	}
	return c;
}

void Shadow::file(std::string mode, std::string path){
	std::string sink = "";
	std::string pass1,pass2;
	std::vector<std::string> salt;
	int s1,s2;
	char car;
	if(mode=="encrypt"){
		condition1: 
			pass1 = getpass("> 1st Password: ");
			if(!checkPassword(pass1)){
					std::cout << "FAIL: 1st Password not enough complex. Try again." << "\n";
					goto condition1;
			}
		condition2:
			pass2 = getpass("> 2nd Password: ");
			if(pass2==pass1 or !checkPassword(pass2)){
				std::cout << "FAIL: 2nd Password not enough complex or same as the 1st password. Try again." << "\n";
				goto condition2;
			}
		std::string line;
		std::ifstream Ifile;
		Ifile.open("Salt.txt");
		while(getline(Ifile,line)){
				salt.emplace_back(line);
		}
		Ifile.close();
		int s = salt.size();
		s1 = sum(pass1)%s;
		s2 = sum(pass2)%s;
		std::ifstream infile;
		infile.open(path);
		while(infile.get(car)){
			sink+=car;	
		}
		infile.close();
		std::ofstream ofile;
		ofile.open(path,std::ofstream::out | std::ofstream::trunc);
		ofile << Aes256(sink,pass1,salt[s1],pass2,salt[s2],mode);
		ofile.close();
		std::cout << "> Encrypted" << "\n";
	}
	else if(mode=="decrypt"){
		pass1 = getpass("> 1st Password: ");
		pass2 = getpass("> 2nd Password: ");
		std::string line;
		std::ifstream Ifile;
		Ifile.open("Salt.txt");
		while(getline(Ifile,line)){
			salt.emplace_back(line);
		}
		Ifile.close();
		int s = salt.size();
		s1 = sum(pass1)%s;
		s2 = sum(pass2)%s;
		std::ifstream infile;
		infile.open(path);
		while(infile.get(car)){
			sink+=car;
		}
		infile.close();
		std::ofstream ofile;
		ofile.open(path,std::ofstream::out | std::ofstream::trunc);
		ofile << Aes256(sink,pass1,salt[s1],pass2,salt[s2],mode);
		ofile.close();
		std::cout << "> Decrypted" << "\n";
	}
	return;
}

void Shadow::folder(std::string mode, std::string path){
	std::string pass1,pass2;
	std::vector<std::string> salt,data;
	int s1,s2;
	char car;
	if(mode=="encrypt"){
		condition1: 
			pass1 = getpass("> 1st Password: ");
			if(!checkPassword(pass1)){
					std::cout << "FAIL: 1st Password not enough complex. Try again." << "\n";
					goto condition1;
			}
		condition2:
			pass2 = getpass("> 2nd Password: ");
			if(pass2==pass1 or !checkPassword(pass2)){
				std::cout << "FAIL: 2nd Password not enough complex or same as the 1st password. Try again." << "\n";
				goto condition2;
			}
		std::string line;
		std::ifstream Ifile;
		Ifile.open("Salt.txt");
		while(getline(Ifile,line)){
				salt.emplace_back(line);
		}
		Ifile.close();
		int s = salt.size();
		s1 = sum(pass1)%s;
		s2 = sum(pass2)%s;
		for(const auto & entry : std::filesystem::recursive_directory_iterator(path)){
			if(std::filesystem::is_regular_file(entry.path())){
					data.emplace_back(entry.path());
			}
		}
		#pragma omp parallel for
		for(auto &file : data){
			std::string sink = "";
			std::ifstream infile;
			infile.open(file);
			while(infile.get(car)){
					sink+=car;	
			}
			infile.close();
			std::ofstream ofile;
			ofile.open(file,std::ofstream::out | std::ofstream::trunc);
			ofile << Aes256(sink,pass1,salt[s1],pass2,salt[s2],mode);
			ofile.close();
		}
		std::cout << "> Encrypted" << "\n";		
	}
	else if(mode=="decrypt"){
		pass1 = getpass("> 1st Password: ");
		pass2 = getpass("> 2nd Password: ");
		std::string line;
		std::ifstream Ifile;
		Ifile.open("Salt.txt");
		while(getline(Ifile,line)){
			salt.emplace_back(line);
		}
		Ifile.close();
		int s = salt.size();
		s1 = sum(pass1)%s;
		s2 = sum(pass2)%s;
		for(const auto & entry : std::filesystem::recursive_directory_iterator(path)){
			if(std::filesystem::is_regular_file(entry.path())){
					data.emplace_back(entry.path());
			}
		}
		#pragma omp parallel for
		for(auto &file : data){
			std::string sink = "";
			std::ifstream infile;
			infile.open(file);
			while(infile.get(car)){
				sink+=car;
			}
			infile.close();
			std::ofstream ofile;
			ofile.open(file, std::ofstream::out | std::ofstream::trunc);
			ofile << Aes256(sink,pass1,salt[s1],pass2,salt[s2],mode);
			ofile.close();
		}
		std::cout << "> Decrypted" << "\n";
	}
	return;
}

void Shadow::encrypt(std::string mode){
	system("clear");
	about();
	std::cout << "\n" << "\e[1m" << "Encryption Mode" << "\e[0m" << "\n\n";
	if(mode=="encrypt"){
		label:
			std::cout << "> ";
			std::string input;
			std::cin >> input; std::cin.ignore();
		if(std::filesystem::is_regular_file(input)){
			file(mode,input);
		}
		else if(std::filesystem::is_directory(input)){
			folder(mode,input);
		}
		else if(input=="usage"){
			usage();
			goto label;
		}
		else if(input=="password"){
			pass_rules();
			goto label;
		}
		else if(input=="show_license"){
			license();
			goto label;
		}
		else if(input=="clear"){
			system("clear");
			about();
			std::cout << "\n" << "\e[1m" << "Encryption Mode" << "\e[0m" << "\n\n";
			goto label;
		}
		else{
			std::cout << "FAIL: Command not recongnized." << "\n";
			goto label;
		}
	}
	return;
}

void Shadow::decrypt(std::string mode){
	system("clear");
	about();
	std::cout << "\n" << "\e[1m" << "Decryption Mode" << "\e[0m" << "\n\n";
	if(mode=="decrypt"){
		label:
			std::cout << "> ";
			std::string input;
			std::cin >> input; std::cin.ignore();
		if(std::filesystem::is_regular_file(input)){
			file(mode,input);
		}
		else if(std::filesystem::is_directory(input)){
			folder(mode,input);
		}
		else if(input=="usage"){
			usage();
			goto label;
		}
		else if(input=="password"){
			pass_rules();
			goto label;
		}
		else if(input=="show_license"){
			license();
			goto label;
		}
		else if(input=="clear"){
			system("clear");
			about();
			std::cout << "\n" << "\e[1m" << "Decryption Mode" << "\e[0m" << "\n\n";
			goto label;
		}
		else{
			std::cout << "FAIL: Command not recongnized." << "\n";
			goto label;
		}
	}
	return;
}

Shadow::~Shadow(void){ }
