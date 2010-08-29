#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

namespace Configuration
{
	extern bool fullscreenenabled;
	extern bool soundenabled;
	extern int screenWidth;
	extern int screenHeight;
	extern int bpp;
	
	extern std::string logfile; // The logfile
	extern bool debug_stdout; // Write messages to stdout
	extern bool debug_fileout; // Write messages to a file
	extern bool show_info_messages; // Show or hide debug info
	extern bool show_warn_messages; // show or hide warnings
}

#endif // CONFIGURATION_H
