#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <unistd.h>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include <sys/types.h>
#include <cryptopp/hex.h>

#include "../Core/SHADOW.h"
#include "../Core/Colors.h"
#include "../Core/ASERP.h"

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
	return((checkDigit(str) && checkLower(str) && checkUpper(str) && checkSpecChar(str) && str.length()>=12) ? true:false);
}

inline bool SHADOW::fileCheck(const std::string &filename)
{
	for(auto i = 0; filename[i]; i++)
	{
		if(filename[i]=='.')
			return true;
	}
	return false;
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

void SHADOW::file()
{

	ASERP crypt;
	about();
	std::cout << "\n";
	passRules();

	std::string filename;
	std::string clr_msg = "";
	std::string choice;
	std::string password, passphrase;
	char car;

	validChoice:
		std::cout << "\n";
		std::cout << "(ENCRYPT OR DECRYPT A FILE ? (e or d)) > ";
		std::cin >> choice;
		std::cin.ignore();

		if(choice == "e")
		{

			system("clear");
			about();
			std::cout << "\n";
			passRules();
			label:
				std::cout << "\n";
				std::cout << "(FILE TO ENCRYPT (Input: /Absolute/path/to/file.extension)) > ";
				std::getline(std::cin,filename);

			if(!fileCheck(filename))
			{
				system("clear");
				about();
				std::cout << "\n";
				passRules();
				std::cout << "\n";
				std::cout << Red << "FILE DOESN'T EXIST. PLEASE TRY AGAIN." << Reset;
				goto label; 
			}
			std::ifstream infile;
			infile.open(filename);
			std::cout << "\n";
			condition: 
				password = getpass("(ENTER PASSWORD) > ");
				if(!checkPassword(password))
				{
					system("clear");
					std::cout << Red << std::setw(8) << "" << " SORRY, PASSWORD NOT ENOUGH COMPLEX. TRY AGAIN. READ THE PASSWORD RULES BELOW. " << Reset << "\n\n";
					passRules();
					std::cout << "\n";
					goto condition;
				}
			std::cout << "\n";
			passphrase = getpass("(CONFIRM PASSWORD) > ");
			if(passphrase!=password)
			{
				system("clear");
				std::cout << "\n";
				std::cout << Red << std::setw(8) << "" << " SORRY, PASSWORD DOESN'T MATCH. TRY AGAIN." << Reset << "\n\n";
				goto condition;
			}
			while(infile.get(car))
			{
				clr_msg+=car;	
			}
			infile.close();
			std::ofstream ofile;
			ofile.open(filename, std::ofstream::out | std::ofstream::trunc);
			ofile << crypt.aserp(clr_msg,password,choice);
			ofile.close();
			system("clear");
			about();
			std::cout << "\n";
			std::cout << Red << std::setw(8) << "" <<"(FILE SUCCESSFULLY ENCRYPTED)" << Reset << " (Check your file)" << "\n\n";
		}
		else if(choice == "d")
		{

			system("clear");
			about();
			std::cout << "\n";
			passRules();
			labs:
				std::cout << "\n";
				std::cout << "(FILE TO DECRYPT (Input: /Absolute/path/to/file.extension)) > ";
				std::getline(std::cin,filename);


			if(!fileCheck(filename))
			{
				system("clear");
				about();
				std::cout << "\n";
				passRules();
				std::cout << "\n";
				std::cout << Red << std::setw(8) << "" << " FILE DOESN'T EXIST. PLEASE TRY AGAIN." << Reset << "\n";
				goto labs;
			}
			std::ifstream infile;
			infile.open(filename);
			std::cout << "\n";
			password = getpass("(ENTER PASSWORD) > ");
			while(infile.get(car))
			{
				clr_msg+=car;
			}
			infile.close();
			std::ofstream ofile;
			ofile.open(filename, std::ofstream::out | std::ofstream::trunc);
			ofile << crypt.aserp(clr_msg,password,choice);
			ofile.close();

			system("clear");
			about();
			std::cout << "\n";
			std::cout << Red << std::setw(8) << "" <<"(FILE SUCCESSFULLY DECRYPTED)" << Reset << " (Check your file to see the result)" << "\n\n";	
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
	std::cout << "\n";
	passRules();
	
	std::string foldername;
	std::string choice;
	std::string password, passphrase;
	std::vector<std::string> vec;
	char car;

	validChoice:
		std::cout << "\n";
		std::cout << "(ENCRYPT OR DECRYPT A FOLDER ? (e or d)) > ";
		std::cin >> choice;
		std::cin.ignore();

		if(choice == "e")
		{

			system("clear");
			about();
			std::cout << "\n";
			passRules();
			std::cout << "\n";
			std::cout << "(FOLDER TO ENCRYPT (Input: /Absolute/path/to/folder)) > ";
			std::getline(std::cin,foldername);
			std::cout << "\n";

			condition: 
				password = getpass("(ENTER PASSWORD) > ");
				if(!checkPassword(password))
				{
					system("clear");
					std::cout << Red << std::setw(8) << "" << " SORRY, PASSWORD NOT ENOUGH COMPLEX. TRY AGAIN. READ THE PASSWORD RULES BELOW. " << Reset << "\n\n";
					passRules();
					std::cout << "\n";
					goto condition;
				}
			std::cout << "\n";
			passphrase = getpass("(CONFIRM PASSWORD) > ");
			if(passphrase!=password)
			{
				system("clear");
				std::cout << "\n";
				std::cout << Red << std::setw(8) << "" << " SORRY, PASSWORD DOESN'T MATCH. TRY AGAIN." << Reset << "\n\n";
				goto condition;
			}
			for(const auto & entry : std::filesystem::directory_iterator(foldername))
			{
				if(fileCheck(entry.path()))
				{
					vec.emplace_back(entry.path());
				}
			}
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
				ofile << crypt.aserp(clr_msg,password,choice);
				ofile.close();
			}
			system("clear");
			about();
			std::cout << "\n";
			std::cout << Red << std::setw(8) << "" <<"(FOLDER SUCCESSFULLY ENCRYPTED)" << Reset << " (Check your folder to see the result)" << "\n\n";
		}
		else if(choice == "d")
		{

			system("clear");
			about();
			std::cout << "\n";
			passRules();
			std::cout << "\n";
			std::cout << "(FOLDER TO DECRYPT (Input: /Absolute/path/to/folder)) > ";
			std::getline(std::cin,foldername);
			std::cout << "\n";
			password = getpass("(ENTER PASSWORD) > ");

			for(const auto & entry : std::filesystem::directory_iterator(foldername))
			{
				if(fileCheck(entry.path()))
				{
					vec.emplace_back(entry.path());
				}
			}
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
				ofile << crypt.aserp(clr_msg,password,choice);
				ofile.close();
			}
			system("clear");
			about();
			std::cout << "\n";
			std::cout << Red << std::setw(8) << "" <<"(FOLDER SUCCESSFULLY DECRYPTED)" << Reset << " (Check your folder to see the result)" << "\n\n";	
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

void SHADOW::folderAll()
{

	ASERP crypt;
	about();
	std::cout << "\n";
	passRules();
	
	std::string foldername;
	std::string choice;
	std::string password, passphrase;
	std::vector<std::string> vec;
	char car;

	validChoice:
		std::cout << "\n";
		std::cout << "(ENCRYPT OR DECRYPT A FOLDER ? (e or d)) > ";
		std::cin >> choice;
		std::cin.ignore();

		if(choice == "e")
		{

			system("clear");
			about();
			std::cout << "\n";
			passRules();
			std::cout << "\n";
			std::cout << "(FOLDER TO ENCRYPT (Input: /Absolute/path/to/folder)) > ";
			std::getline(std::cin,foldername);
			std::cout << "\n";

			condition: 
				password = getpass("(ENTER PASSWORD) > ");
				if(!checkPassword(password))
				{
					system("clear");
					std::cout << Red << std::setw(8) << "" << " SORRY, PASSWORD NOT ENOUGH COMPLEX. TRY AGAIN. READ THE PASSWORD RULES BELOW. " << Reset << "\n\n";
					passRules();
					std::cout << "\n";
					goto condition;
				}
			std::cout << "\n";
			passphrase = getpass("(CONFIRM PASSWORD) > ");
			if(passphrase!=password)
			{
				system("clear");
				std::cout << "\n";
				std::cout << Red << std::setw(8) << "" << " SORRY, PASSWORD DOESN'T MATCH. TRY AGAIN." << Reset << "\n\n";
				goto condition;
			}
			for(const auto & entry : std::filesystem::recursive_directory_iterator(foldername))
			{
				if(fileCheck(entry.path()))
				{
					vec.emplace_back(entry.path());
				}
			}
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
				ofile << crypt.aserp(clr_msg,password,choice);
				ofile.close();
			}
			system("clear");
			about();
			std::cout << "\n";
			std::cout << Red << std::setw(8) << "" <<"(FOLDER SUCCESSFULLY ENCRYPTED)" << Reset << " (Check your folder to see the result)" << "\n\n";
		}
		else if(choice == "d")
		{

			system("clear");
			about();
			std::cout << "\n";
			passRules();
			std::cout << "\n";
			std::cout << "(FOLDER TO DECRYPT (Input: /Absolute/path/to/folder)) > ";
			std::getline(std::cin,foldername);
			std::cout << "\n";
			password = getpass("(ENTER PASSWORD) > ");

			for(const auto & entry : std::filesystem::recursive_directory_iterator(foldername))
			{
				if(fileCheck(entry.path()))
				{
					vec.emplace_back(entry.path());
				}
			}
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
				ofile << crypt.aserp(clr_msg,password,choice);
				ofile.close();
			}
			system("clear");
			about();
			std::cout << "\n";
			std::cout << Red << std::setw(8) << "" <<"(FOLDER SUCCESSFULLY DECRYPTED)" << Reset << " (Check your folder to see the result)" << "\n\n";	
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
	std::cout << "\n";
	std::cout << std::setw(8) << "" << Red << "[ PRESS ENTER TO RUN ]" << Reset;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	label:
		system("clear");
		about();
		std::cout << "\n";
		std::cout << "Encrypt or Decrypt: 1) File" << "\n";
		std::cout << "                    2) Specific Folder" << "\n";
		std::cout << "                    3) An entire folder (including its subfolders)" << "\n\n";
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
	else if(choice == 3)
	{
		system("clear");
		folderAll();
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
