#ifndef _ASERP_h
#define _ASERP_h

#include <string>

class ASERP
{
	public:
		ASERP(void);
		std::string aserp(std::string clr_msg, std::string password1, std::string salt1, std::string password2, std::string salt2, std::string choice);
		~ASERP(void);
};

#endif
