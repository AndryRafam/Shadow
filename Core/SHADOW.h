#ifndef _SHADOW_h
#define _SHADOW_h

#include <string>

class SHADOW{
	private:
		inline bool fileCheck(const std::string &filename);
		inline bool checkDigit(std::string str);
		inline bool checkUpper(std::string str);
		inline bool checkLower(std::string str);
		inline bool checkSpecChar(std::string str);
		inline bool checkPassword(std::string str);
		inline void about();
		void folderAll();
		void folder();
		void file();
		
	public:
		SHADOW(void);
		void run();
		~SHADOW(void);
};

#endif
