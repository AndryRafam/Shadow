#ifdef __linux__

#include <iostream>
#include <string>

#include "../Core/Shadow.h"

int main(int argc, char **argv){
	if(argc==1){
		Shadow s;
		s.run();
	}
	else{
		std::cout << "Usage: " << argv[0] << " <no argument>" << "\n";
	}
	return 0;
}

#endif
