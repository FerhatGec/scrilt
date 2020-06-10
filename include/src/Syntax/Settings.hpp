/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "FileFunction.hpp"
#include "Log.hpp"
#include "../Scrift.hpp"
#include <pwd.h>
#include "../synflang.hpp"

class FSettings {
public:
    FeLog *logsystem = new FeLog();
    FileFunction::FCreateFileFunction *createfile = new FileFunction::FCreateFileFunction();
    FileFunction::FReadFileFunction *readfile = new FileFunction::FReadFileFunction();	
    integer linenumber;
    std::string WelcomeEmoji = ":thinking_face:";
    
    std::string EraseAllSubString(std::string & mainString, const std::string & erase) {
    	size_t pos = std::string::npos;
   	while((pos = mainString.find(erase)) != std::string::npos)
    	{
      	mainString.erase(pos, erase.length());
    	}
    	return mainString;
    }
    
    std::string Path() {
    	uid_t fuid = geteuid();
    	struct passwd *password = getpwuid(fuid);
    	std::string Path;
    	Path.append("/home/");
    	Path.append(password->pw_name);
    	Path.append("/");
    	return Path.append(".scrift_settings");
    }
    
   std::string FWelcomeEmoji() {
    	std::string line;
    	std::string ftest;
    	std::ifstream readfile(Path());
    	if(readfile.is_open()) {
    		while(std::getline(readfile, line)) {
    			if(line.rfind("welcome_emoji", 0) == 0) {
    				return EraseAllSubString(line, "welcome_emoji ");
    			} else {
    				createfile->CreateSettingsFileFunction();
    			} 
    		}
    	}
    	//return EraseAllSubString(line, "welcome_emoji ");
    }
    
    int FeLogCleaner() {
    	std::string line;
    	std::string ftest;
    	std::ifstream readfile(Path());
    	if(readfile.is_open()) {
    		while(std::getline(readfile, line)) {
    			if(line.rfind("felog_cleaner", 0) == 0) {
    				if(atoi(EraseAllSubString(line, "felog_cleaner ").c_str()) <= 5) {
    					BOLD_RED_COLOR
    					printlnf("Please give 5 or higher value for felog_cleaner.\n");
    					BLACK_COLOR
    					return 20;
    				} else {
    					return atoi(EraseAllSubString(line, "felog_cleaner ").c_str());
    				}
    			} else {
    				createfile->CreateSettingsFileFunction();
    			} 
    		}
    	}
    }
    
    virtual func ReadFile() {
    	std::string line;
    	std::string ftest;
    	std::ifstream readfile(Path());
    	if(readfile.is_open()) {
    	while (std::getline(readfile, line))
    	{
        if(line.rfind("felog_cleaner", 0) == 0)
        {
        	std::string fsettings = EraseAllSubString(line, "felog_cleaner ");
        	linenumber = atoi(fsettings.c_str());
        } else {
        	createfile->CreateSettingsFileFunction();
        	return;
        }
        
        if(line.rfind("welcome_emoji", 0) == 0) {
        	WelcomeEmoji = EraseAllSubString(line, "welcome_emoji ");
        } else {
        	createfile->CreateSettingsFileFunction();
        	return;
        }
    	}
    }
}
};

#endif // RUN_FUNCTION_HPP_
