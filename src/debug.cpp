/**
    Copyright (C) 2009  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/

#include "debug.h"
#include <execinfo.h>

namespace dawn_configuration {
	std::string logfile = "dawn-log.cpp"; // The logfile
	bool debug_stdout = false; // Write messages to stdout
	bool debug_fileout = false; // Write messages to a file
	bool show_info_messages = false; // Show or hide debug info
	bool show_warn_messages = false; // show or hide warnings
}

static bool log_started = false; /* This gets set to true
	after the first write (so that the log file is
	cleared on the the first log) */


static std::string date_time_string()
{
	std::string _datetime;
	//std::stringstream ss;
	const int _stringmax = 20;
	char buf[_stringmax];

	time_t t = time(0);
	strftime(buf, _stringmax, "%X", localtime(&t));
	_datetime = buf;

	return _datetime;
}

static void debug_args(const char* message, std::va_list ap, debug_message_type debug)
{
	char buf[1024];
	std::string output_string;
	std::stringstream ss;
	bool should_output = false;

	vsnprintf(buf ,1024, message, ap);
	
	switch(debug) {
		case(DEBUG_INFO):
			ss << date_time_string() << ": Information : " << buf;
			output_string = ss.str();
			if(dawn_configuration::show_info_messages)
				should_output = true;
			break;
		case(DEBUG_WARN):
			ss << date_time_string() << ": Warning : " << buf;
			output_string = ss.str();
			if(dawn_configuration::show_warn_messages)
				should_output = true;
			break;
		case(DEBUG_FATAL):
			ss << date_time_string() << ": Fatal : " << buf;
			output_string = ss.str();
			should_output = true;
			break;
	}

	if(should_output) {
		if(!log_started) {
			/* This will reset the file if this is the first write this session */
			std::ofstream temp(dawn_configuration::logfile.c_str());
			log_started = true;
			temp.close();
		}

		std::ofstream outputfile(dawn_configuration::logfile.c_str(), std::ios_base::app);

		if(dawn_configuration::debug_stdout)
			std::cout << output_string << std::endl;
		if(dawn_configuration::debug_fileout)
			if(outputfile)
				outputfile << output_string << std::endl;

		outputfile.close();
	}
}

void dawn_debug_info(const std::string& message ...)
{
	std::va_list ap;
	
	va_start(ap, message);
		debug_args(message.c_str(), ap, DEBUG_INFO);
	va_end(ap);
}

void dawn_debug_warn(const std::string& message ...)
{
	std::va_list ap;
	
	va_start(ap, message);
		debug_args(message.c_str(), ap, DEBUG_WARN);
	va_end(ap);
}

void dawn_debug_fatal(const std::string& message ...)
{
	std::va_list ap;
	
	va_start(ap, message);
		debug_args(message.c_str(), ap, DEBUG_FATAL);
	va_end(ap);
	
	print_backtrace();

	exit(1);
}

void print_backtrace()
{
	void *array[100];
	size_t size;
	char **strings;
	size_t i;

	size = backtrace (array, 100);
	// remove functions print_backtrace and backtrace from stacktrace
	size-=2;
	strings = backtrace_symbols (array, size);

	printf( "./btdecode.sh << EOBT\n" );
	
	for (i = 0; i < size; i++)
		printf ("%s\n", strings[i]);

	printf( "EOBT\n" );

	free (strings);
}

