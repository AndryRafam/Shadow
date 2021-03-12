#ifdef __linux__

#include <iostream>
#include <string>

#include "../Core/Shadow.h"

int main(int argc, char **argv){
	Shadow s;
	if(argc != 2 or (std::string(argv[1])!="encrypt" && std::string(argv[1])!="decrypt")){
		std::cout << argv[0] << " <encrypt>: encryption mode" << "\n";
		std::cout << argv[0] << " <decrypt>: decryption mode" << "\n";
		exit(0);
	}
	if(std::string(argv[1])=="encrypt"){
		s.encrypt(std::string(argv[1]));
	}
	else{
		s.decrypt(std::string(argv[1]));
	}	
	return 0;
}

#endif
