#ifdef __linux__

#include <iostream>
#include <string>

#include "../Core/Shadow.h"

int main(int argc, char **argv){
	Shadow s;
	if(argc != 2){
		std::cout << argv[0] << " <encrypt>: encryption mode" << "\n";
		std::cout << argv[0] << " <decrypt>: decryption mode" << "\n";
		exit(0);
	}
	if(std::string(argv[1])!="encrypt" && std::string(argv[1])!="decrypt"){
		std::cout << argv[0] << " <encrypt>: encryption mode" << "\n";
		std::cout << argv[0] << " <decrypt>: decryption mode" << "\n";
		exit(0);
	}
	s.run(std::string(argv[1]));	
	return 0;
}

#endif
