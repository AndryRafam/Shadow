#ifndef _ASERP_h
#define _ASERP_h

#include <string>

class ASERP
{
	public:
		ASERP(void);
		std::string aserp(std::string clr_msg, std::string password, std::string salt, std::string choice);
		~ASERP(void);
};

#endif
