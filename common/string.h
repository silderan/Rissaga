#pragma once

#include <string>

namespace Ris
{
	class String : public std::string
	{
	public:
		String() : std::string()
		{}
		String(const std::string &s) : std::string(s)
		{}
		String(const String &s) : std::string(s)
		{}
		String(const char *s) : std::string(s)
		{}
		String(char *s) : std::string(s)
		{}
		template <typename T>
		String(const T &n)
		{
			*this = std::to_string(n);
		}
		template <typename T>
		String &fromNumber(T n)
		{
			*this = std::to_string(n);
			return *this;
		}
	};
}
