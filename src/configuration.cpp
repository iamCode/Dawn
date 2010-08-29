#include "configuration.h"

namespace Configuration {
	bool fullscreenenabled = true;
	bool soundenabled = true;
	int screenWidth = 1024;
	int screenHeight = 768;
	int bpp = 32;
	
	std::string logfile = "dawn-log.cpp"; // The logfile
	bool debug_stdout = false; // Write messages to stdout
	bool debug_fileout = false; // Write messages to a file
	bool show_info_messages = false; // Show or hide debug info
	bool show_warn_messages = false; // show or hide warnings
}
