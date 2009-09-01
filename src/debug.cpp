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
