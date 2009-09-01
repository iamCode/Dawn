#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <ctime>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

static bool log_started = false; /* This gets set to true 
	after the first write (so that the log file is 
	cleared on the the first log) */

namespace dawn_configuration {
	extern std::string logfile; // The logfile
	extern bool debug_stdout; // Write messages to stdout
	extern bool debug_fileout; // Write messages to a file
	extern bool show_info_messages; // Show or hide debug info	
	extern bool show_warn_messages; // show or hide warnings
}

void dawn_debug_info(const std::string& message); /* Logs useful 
						debug data */
void dawn_debug_warn(const std::string& message); /* Logs non fatal 
						problems */
void dawn_debug_fatal(const std::string& message); /* Logs fatal
						problems then quits */

#endif
