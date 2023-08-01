#ifndef _MESSAGE_H_GUARD_
#define _MESSAGE_H_GUARD_

#include <string>
#include <algorithm>

class Message
{
public:
	explicit Message(const std::string& str)
		:decryptStr(str)
	{}

	const std::string encrypt()
	{
		std::string out_str = "HELLO\0";
		for_each(decryptStr.begin(), decryptStr.end(), [&out_str](char ch)
		{
			out_str += (ch + 1);
		});

		return out_str;
	}

private:
	std::string decryptStr;
};

#endif
	// _MESSAGE_H_GUARD_
