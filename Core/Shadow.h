#ifndef _Shadow_h
#define _Shadow_h

#include <string>

class Shadow
{
	private:
		std::string Aes256(std::string input, std::string pass1, std::string salt1, std::string pass2, std::string salt2, std::string mode);
		inline bool checkDigit(std::string str);
		inline bool checkUpper(std::string str);
		inline bool checkLower(std::string str);
		inline bool checkSpecChar(std::string str);
		inline bool checkPassword(std::string str);
		inline void about();
		inline int sum(std::string str);
		inline void usage();
		inline void pass_rules();
		inline void license();
		void folder(std::string mode, std::string path);
		void file(std::string mode, std::string path);
		
	public:
		Shadow(void);
		void run();
		~Shadow(void);
};

#endif
