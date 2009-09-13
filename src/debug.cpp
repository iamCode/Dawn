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

/* The init values are the class
   defaults, these will usually be overwritten */
namespace dawn_configuration {
	std::string logfile = "dawn-log.cpp"; // The logfile
	bool debug_stdout = true; // Write messages to stdout
	bool debug_fileout = true; // Write messages to a file
	bool show_info_messages = true; // Show or hide debug info
	bool show_warn_messages = true; // show or hide warnings
}

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

void dawn_debug_info(const std::string& message)
{
	if(dawn_configuration::show_info_messages) {
		if(!log_started) {
			/* This will reset the file if this is the first write this session */
			std::ofstream temp(dawn_configuration::logfile.c_str());
			log_started = true;
			temp.close();
		}

		std::ofstream outputfile(dawn_configuration::logfile.c_str(), std::ios_base::app);

		if(dawn_configuration::debug_stdout)
			std::cout << date_time_string() << ": Information : " <<
				message << std::endl;
		if(dawn_configuration::debug_fileout)
			if(outputfile)
				outputfile << date_time_string() << ": Information : " <<
					message << std::endl;

		outputfile.close();
	}
}

void dawn_debug_warn(const std::string& message)
{
	if(dawn_configuration::show_warn_messages) {
		if(!log_started) {
			/* This will reset the file if this is the first write this session */
			std::ofstream temp(dawn_configuration::logfile.c_str());
			log_started = true;
			temp.close();
		}

		std::ofstream outputfile(dawn_configuration::logfile.c_str(), std::ios_base::app);

		if(dawn_configuration::debug_stdout)
			std::cout << date_time_string() << ": Warning : " <<
				message << std::endl;
		if(dawn_configuration::debug_fileout)
			if(outputfile)
				outputfile << date_time_string() << ": Warning : " <<
					message << std::endl;

	outputfile.close();
	}
}

void dawn_debug_fatal(const std::string& message)
{
	if(!log_started) {
		/* This will reset the file if this is the first write this session */
		std::ofstream temp(dawn_configuration::logfile.c_str());
		log_started = true;
		temp.close();
	}

	std::ofstream outputfile(dawn_configuration::logfile.c_str(), std::ios_base::app);

	if(dawn_configuration::debug_stdout)
		std::cout << date_time_string() <<
			": Fatal Error : " << message <<
			std::endl;
	if(dawn_configuration::debug_fileout)
		if(outputfile)
			outputfile << date_time_string() <<
				": Fatal Error : "<< message <<
				std::endl;

	outputfile.close();
	exit(1);
}
