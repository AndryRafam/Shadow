#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <unistd.h>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include <sys/types.h>
#include <cryptopp/filters.h>

#include "../Core/SHADOW.h"
#include "../Core/Colors.h"
#include "../Core/ASERP.h"

using namespace CryptoPP;

SHADOW::SHADOW(void){ }

inline bool SHADOW::checkDigit(std::string str)
{
	return (std::any_of(str.begin(),str.end(), ::isdigit) ? true:false);
}

inline bool SHADOW::checkLower(std::string str)
{
	return (std::any_of(str.begin(),str.end(), ::islower) ? true:false);
}

inline bool SHADOW::checkUpper(std::string str)
{
	return (std::any_of(str.begin(),str.end(), ::isupper) ? true:false);
}

inline bool SHADOW::checkSpecChar(std::string str)
{
	bool flag = false;
	for(auto i = 0; str[i]; i++)
	{
		if((str[i]>=32 and str[i]<=47)||(str[i]>=58 and str[i]<=64)||(str[i]>=91 and str[i]<=96)||(str[i]>=123 and str[i]<=126))
		{
			flag = true;
			break;
		}
	}
	return flag;
}

inline bool SHADOW::checkPassword(std::string str)
{
	return((checkDigit(str) && checkLower(str) && checkUpper(str) && checkSpecChar(str) && str.length()>=16) ? true:false);
}

inline void SHADOW::about()
{
	std::ifstream infile;
	std::string line;
	infile.open("About.txt");

	while(std::getline(infile,line))
	{
		std::cout << line << std::endl;
	}
	infile.close();
	return;
}

inline void SHADOW::passRules()
{
	std::ifstream infile;
	std::string line;
	infile.open("PassRules.txt");

	while(std::getline(infile,line))
	{
		std::cout << line << std::endl;
	}
	infile.close();
	return;
}

inline int SHADOW::sum(std::string str)
{
	int c = 0;
	for(auto x = 0; str[x]; x++)
	{
		c+=int(str[x]);
	}
	return c;
}

void SHADOW::file()
{

	ASERP crypt;
	about();
	std::cout << "\n";

	std::string filename;
	std::string clr_msg = "";
	std::string choice;
	std::string pass1, pass2;
	std::vector<std::string> salt;
	int s1,s2;
	char car;

	validChoice:
		std::cout << "(ENCRYPT OR DECRYPT A FILE ? (e or d)) > ";
		std::cin >> choice;
		std::cin.ignore();

		system("clear");
		about();

		if(choice == "e")
		{
			label:
				std::cout << "\n";
				std::cout << "(FILE TO ENCRYPT (Input: /Absolute/path/to/file.extension)) > ";
				std::getline(std::cin,filename);

			if(!std::filesystem::is_regular_file(filename))
			{
				system("clear");
				about();
				std::cout << Red << "FILE DOESN'T EXIST. PLEASE TRY AGAIN." << Reset << "\n";
				goto label; 
			}
			condition1: 
				std::cout << "\n";
				pass1 = getpass("(ENTER 1ST PASSWORD) > ");
				if(!checkPassword(pass1))
				{
					system("clear");
					about();
					std::cout << Red << "SORRY, 1ST PASSWORD NOT ENOUGH COMPLEX. TRY AGAIN. (REMEMBER THE PASSWORD RULES)" << Reset << "\n";
					goto condition1;
				}
			std::cout << "\n";
			condition2:
				pass2 = getpass("(ENTER 2ND PASSWORD) > ");
				if(pass2==pass1 or !checkPassword(pass2))
				{
					system("clear");
					about();
					std::cout << Red << "SORRY,  2ND PASSWORD NOT ENOUGH COMPLEX OR SAME AS 1ST PASSWORD. TRY AGAIN." << Reset << "\n";
					goto condition2;
				}
			std::string line;
			std::ifstream Ifile;
			Ifile.open("Salt.txt");
			while(getline(Ifile,line))
			{
				salt.emplace_back(line);
			}
			Ifile.close();
			int s = salt.size();
			s1 = sum(pass1)%s;
			s2 = sum(pass2)%s;
			std::ifstream infile;
			infile.open(filename);
			while(infile.get(car))
			{
				clr_msg+=car;	
			}
			infile.close();
			std::ofstream ofile;
			ofile.open(filename, std::ofstream::out | std::ofstream::trunc);
			ofile << crypt.aserp(clr_msg,pass1,salt[s1],pass2,salt[s2],choice);
			ofile.close();
			system("clear");
			about();
			std::cout << "\n" << Red <<"(FILE SUCCESSFULLY ENCRYPTED)" << Reset << "\n\n";
		}
		else if(choice == "d")
		{
			system("clear");
			about();
			labs:
				std::cout << "\n";
				std::cout << "(FILE TO DECRYPT (Input: /Absolute/path/to/file.extension)) > ";
				std::getline(std::cin,filename);


			if(!std::filesystem::is_regular_file(filename))
			{
				system("clear");
				about();
				std::cout << Red << "FILE DOESN'T EXIST. PLEASE TRY AGAIN." << Reset << "\n";
				goto labs;
			}
			std::cout << "\n";
			pass1 = getpass("(ENTER 1ST PASSWORD) > ");
			std::cout << "\n";
			pass2 = getpass("(ENTER 2ND PASSWORD) > ");
			std::string line;
			std::ifstream Ifile;
			Ifile.open("Salt.txt");
			while(getline(Ifile,line))
			{
				salt.emplace_back(line);
			}
			Ifile.close();
			int s = salt.size();
			s1 = sum(pass1)%s;
			s2 = sum(pass2)%s;
			std::ifstream infile;
			infile.open(filename);
			while(infile.get(car))
			{
				clr_msg+=car;
			}
			infile.close();
			std::ofstream ofile;
			ofile.open(filename, std::ofstream::out | std::ofstream::trunc);
			ofile << crypt.aserp(clr_msg,pass1,salt[s1],pass2,salt[s2],choice);
			ofile.close();

			system("clear");
			about();
			std::cout << "\n";
			std::cout << Red <<"(FILE SUCCESSFULLY DECRYPTED - CHECK YOUR FILE)" << Reset << "\n\n";	
		}
		else
		{
			system("clear");
			about();
			goto validChoice;
		}
	std::cout << "\n";
	return;
}

void SHADOW::folder()
{

	ASERP crypt;
	about();
	std::cout <<"\n";
	
	std::string foldername;
	std::string choice;
	std::string pass1, pass2;
	std::vector<std::string> vec, salt;
	int s1,s2;
	char car;

	validChoice:
		std::cout << "(ENCRYPT OR DECRYPT A FOLDER ? (e or d)) > ";
		std::cin >> choice;
		std::cin.ignore();

		system("clear");
		about();

		if(choice == "e")
		{
			directory:
				std::cout << "\n";
				std::cout << "(FOLDER TO ENCRYPT (Input: /Absolute/path/to/folder)) > ";
				std::getline(std::cin,foldername);

			if(!std::filesystem::is_directory(foldername))
			{
				system("clear");
				about();
				std::cout << Red << "FOLDER DOESN'T EXIST. PLEASE TRY AGAIN." << Reset << "\n";
				goto directory; 
			}
			condition1: 
				std::cout << "\n";
				pass1 = getpass("(ENTER 1ST PASSWORD) > ");
				if(!checkPassword(pass1))
				{
					system("clear");
					about();
					std::cout << Red << "SORRY, 1ST PASSWORD NOT ENOUGH COMPLEX. (REMEMBER THE PASSWORD RULES)" << Reset << "\n";
					goto condition1;
				}
			std::cout << "\n";
			condition2:
				pass2 = getpass("(ENTER 2ND PASSWORD) > ");
				if(pass2==pass1 or !checkPassword(pass2))
				{
					system("clear");
					about();
					std::cout << Red << "SORRY, 2ND PASSWORD NOT ENOUGH COMPLEX OR SAME AS 1ST PASSWORD. TRY AGAIN." << Reset << "\n\n";
					goto condition2;
				}
			for(const auto & entry : std::filesystem::recursive_directory_iterator(foldername))
			{
				if(std::filesystem::is_regular_file(entry.path()))
				{
					vec.emplace_back(entry.path());
				}
			}
			std::ifstream Ifile;
			std::string line;
			Ifile.open("Salt.txt");
			while(getline(Ifile,line))
			{
				salt.emplace_back(line);
			}
			Ifile.close();
			int s = salt.size();
			s1 = sum(pass1)%s;
			s2 = sum(pass2)%s;
			#pragma omp parallel for
			for(auto &file : vec)
			{
				std::string clr_msg = "";
				std::ifstream infile;
				infile.open(file);
				while(infile.get(car))
				{
					clr_msg+=car;	
				}
				infile.close();
				std::ofstream ofile;
				ofile.open(file, std::ofstream::out | std::ofstream::trunc);
				ofile << crypt.aserp(clr_msg,pass1,salt[s1],pass2,salt[s2],choice);
				ofile.close();
			}
			system("clear");
			about();
			std::cout << "\n" << Red <<"(FOLDER SUCCESSFULLY ENCRYPTED - CHECK YOUR FOLDER)" << Reset << "\n\n";			
		}
		else if(choice == "d")
		{
			system("clear");
			about();

			directory_condition:
				std::cout << "\n";
				std::cout << "(FOLDER TO DECRYPT (Input: /Absolute/path/to/folder)) > ";
				std::getline(std::cin,foldername);
				
			if(!std::filesystem::is_directory(foldername))
			{
				system("clear");
				about();
				std::cout << Red << "FOLDER DOESN'T EXIST. PLEASE TRY AGAIN." << Reset << "\n";
				goto directory_condition; 
			}
			std::cout << "\n";
			pass1 = getpass("(ENTER 1ST PASSWORD) > ");
			std::cout << "\n";
			pass2 = getpass("(ENTER 2ND PASSWORD) > ");
			for(const auto & entry : std::filesystem::recursive_directory_iterator(foldername))
			{
				if(std::filesystem::is_regular_file(entry.path()))
				{
					vec.emplace_back(entry.path());
				}
			}
			std::string line;
			std::ifstream Ifile;
			Ifile.open("Salt.txt");
			while(getline(Ifile,line))
			{
				salt.emplace_back(line);
			}
			Ifile.close();
			int s = salt.size();
			s1 = sum(pass1)%s;
			s2 = sum(pass2)%s;
			#pragma omp parallel for
			for(auto &file : vec)
			{
				std::string clr_msg = "";
				std::ifstream infile;
				infile.open(file);
				while(infile.get(car))
				{
					clr_msg+=car;
				}
				infile.close();
				std::ofstream ofile;
				ofile.open(file, std::ofstream::out | std::ofstream::trunc);
				ofile << crypt.aserp(clr_msg,pass1,salt[s1],pass2,salt[s2],choice);
				ofile.close();
			}
			system("clear");
			about();
			std::cout << "\n";
			std::cout << Red <<"(FOLDER SUCCESSFULLY DECRYPTED - CHECK YOUR FOLDER)" << Reset << "\n\n";	
		}
		else
		{
			system("clear");
			about();
			goto validChoice;
		}
	std::cout << "\n";
	return;
}

void SHADOW::run()
{

	int choice;
	
	system("clear");
	about();
	std::cout << Red << "[ PRESS ENTER TO START ]" << Reset;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	label:
		system("clear");
		about();
		std::cout << "Encrypt or Decrypt: 1) File" << "\n";
		std::cout << "                    2) Folder" << "\n\n";
		std::cout << "(Your choice ?) > ";
		std::cin >> choice;
		std::cin.ignore();

	if(choice == 1)
	{
		system("clear");
		file();
	}
	else if(choice == 2)
	{
		system("clear");
		folder();
	}
	else
	{
		std::cout << "\n";
		std::cout << Red << "(Choice not available. Try again)" << Reset << "\n\n";
		goto label;
	}
	return;
}

SHADOW::~SHADOW(void){ }
