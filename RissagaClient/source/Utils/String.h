#pragma once

#include <string>

namespace Ris
{
	class String : public std::string
	{
	public:
		template <typename T>
		String(T n)
		{
			std::string::operator=(std::to_string(n));
		}
		String(std::string &s)
		{
			std::string::operator=(s);
		}
		String &operator=(std::string s)
		{
			std::string::operator=(s);
			return *this;
		}
		template <typename T>
		String &fromNumber(T n)
		{
			(*this) = std::to_string(n);
			return (*this);
		}
	};
};
