#pragma once

#include "String.h"
#include <iostream>

// TODO: Improve this!!!
namespace Ris
{
	class Log
	{
	public:
		// Adds a file to log to.
		void setFile(String fname);
		void logErr(String s, bool onFile = false)
		{
			std::cerr << "[ERR] " << s << std::endl;
		}
		void logLog(String s, bool onFile = false)
		{
			std::clog << "[LOG] " << s << std::endl;
		}
		void logWar(String s, bool onFile = false)
		{
			std::clog << "[WAR] " << s << std::endl;
		}
	};
	static Log g_log;
}
