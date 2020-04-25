/* GPLv3 License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the GPLv3 License.
#
# */

#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include "../../include/src/main.h"
#include "../../include/src/Syntax/CommandFunc.h"
#include "../../include/src/File/File.h"
#include "../../include/src/File/Directory.h"
#include <pwd.h>
#include <string.h>
#include "../../include/src/synflang.hpp"
#include <experimental/filesystem>
namespace filesys = std::experimental::filesystem;

static const char *_uname;

FCommand::FCommand()
{
    

}

FCommand::~FCommand()
{
    delete[] _home_dir, _hello_str, _file_path_cd_function, _help_str, _uname;   
}



void 
FCommand::remove_character(char * _str, char ptr)
{
    if(_str == NULL)
        return;

    char * _pstr = _str;
    while(*_str)
    {
        if(*_str != ptr)
            *_pstr++ = *_str;
    _str++;
    }
    *_pstr = '\0';    
}

void
FCommand::echo_printlnf()
{
    fchar* _character = new fchar;
    std::cin >> _character; 
    if(_character != nullptr)
    {
    printlnf(_character);
    slashn
    } else  {
        printerror("ERR: CHAR IS NULL", 13, "ERR:CHISNULL");
        return;
    }
}

void
FCommand::get_username(fchar *_your_username)
{
      #ifdef __linux__
       uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    if (pw)
    {
      printlnf(pw->pw_name);
      _your_username = pw->pw_name;
     }
     // printlnf("\n", _your_username, "\n");
      #else 
      printlnf("\nFegeya Fusion Username:", "user", "or ",  _n_supported_()); // ; deleted
      #endif
}
void
FCommand::_os_kernel_name(fchar *_your_os_kernel)
{
    #ifdef _WIN32
    _your_os_kernel = "Windows NT 32-bit\n";
    printlnf("Windows NT is not supported for Fegeya Scrift!\n");
    return 1;
    #elif _WIN64
    _your_os_kernel "Windows NT 64-bit \n";
    printlnf("Windows NT is not supported for Fegeya Scrift!\n");
    return 1;
    printlnf("Win")
    #elif __APPLE__ || __MACH__
    _your_os_kernel  = "Darwin \n";
    #elif __linux__
    _your_os_kernel = "Linux <3 \n";
    #elif __FreeBSD__
    _your_os_kernel = "BSD \n";
    #elif __unix || __unix__
    _your_os_kernel = "Unix \n";
    #else
    _your_os_kernel = "Fegeya Fusion or not supported operating system :) \n";
    #endif
    printlnf(_your_os_kernel);
}


void
FCommand::_set_locale()
{
        printlnf("Set up -> Your system language");// setlocale(LC_CTYPE, NULL);
        setlocale(LC_CTYPE, NULL); // FOR UNIX AND FUSION
        printlnf(" \n"); 
}

void 
FCommand::clear_shell()
{
   std::cout << "\033[2J\033[1;1H"; 
}

int _cd_func_name;
void
FCommand::cd_func(fchar *_new_dir, bool _t)
{
    FMain * _main_ = new FMain();
    _new_dir = new fchar;
    
    // printlnf(_new_dir); for testing.
    _cd_func_name = strlen(_new_dir);
    if(_t == true)
    {
        std::strcpy(_file_path_cd_function, (getenv("HOME"), "/"));
        return;
    } else {
        std::cin >> _new_dir;
        if(_new_dir != nullptr)
        {
        if(_main_->_home != true)
        {
            std::strcat(_file_path_cd_function, "/");
            std::strcat(_file_path_cd_function, _new_dir);
        } else {
            _file_path_cd_function = "";
        }  
        } else {
        printerror("ERR:DIRECTORY IS NULL", 12, "ERR:DIRISNULL");
        return; 
        }
    }

}

void
FCommand::list_direc(bool _home)
{
        int files = 0;
        struct stat filestat;
        struct dirent *entry;
        DIR *dir;

        if(_home != false) {dir = opendir((getenv("HOME"), "/", _file_path_cd_function)); /*For Linux and *nix*/
        } else if(_home == false || _home == NULL)
        {
            dir = opendir(getenv("HOME"));
        }
        
        if (dir == NULL) 
        {
            printerror("ERR:DIRECTORY NOT FOUND", 12, "ERR:DIRNFND");
            return;
        }
        while ((entry = readdir(dir))) 
        {
            files++;
            char * _str = entry->d_name;
            remove_character(_str, '.');
            remove_character(_str, '..');
            stat(entry->d_name,&filestat);
            if(entry->d_type == DT_DIR) {
                BOLD_RED_COLOR
                printf("%4s: %s\n","Dir",entry->d_name); 
            }
            BLACK_COLOR
        }
        closedir(dir);
}

void 
FCommand::list_file(bool _home)
{
        int files = 0;
        struct stat filestat;
        struct dirent *entry;
        DIR *dir;

        if(_home != false) {dir = opendir((getenv("HOME"), "/", _file_path_cd_function)); /*For Linux and *nix*/
        } else if(_home == false || _home == NULL)
        {
            dir = opendir(getenv("HOME"));
        }
        
        if (dir == NULL) 
        {
            printerror("ERR:DIRECTORY NOT FOUND", 12, "ERR:DIRNFND");
            return;
        }
        while ((entry = readdir(dir))) 
        {
            files++;
            char * _str = entry->d_name;
            remove_character(_str, '.');
            remove_character(_str, '..');
            //printf("%d", entry->d_type, "\n");
            //printf("%d");
          //  printf("\033[0;34m");
            stat(entry->d_name,&filestat);
            if(entry->d_type == DT_DIR) {
            } else{
                BOLD_YELLOW_COLOR
                printf("%4s: %s\n"," File",entry->d_name);
            } 
            BLACK_COLOR
        }
        closedir(dir);
}
void
FCommand::list_dir(bool _home, bool _file, bool _dir) // default value
{
        int files = 0;
        struct stat filestat;
        struct dirent *entry;
        DIR *dir;

        if(_home != false) {dir = opendir((getenv("HOME"), "/", _file_path_cd_function)); /*For Linux and *nix*/
        } else if(_home == false || _home == NULL)
        {
            dir = opendir(getenv("HOME"));
        }
        
        if (dir == NULL) 
        {
            printerror("ERR:DIRECTORY NOT FOUND", 12, "ERR:DIRNFND");
            return;
        }
        while ((entry = readdir(dir))) 
        {
            files++;
            char * _str = entry->d_name;
            remove_character(_str, '.');
            remove_character(_str, '..');
            //printf("%d", entry->d_type, "\n");
            //printf("%d");
          //  printf("\033[0;34m");
            stat(entry->d_name,&filestat);
            if(entry->d_type == DT_DIR) {
                BOLD_RED_COLOR
                printf("%4s: %s\n","Dir",entry->d_name); 
            
            } else{
                BOLD_YELLOW_COLOR
                printf("%4s: %s\n"," File",entry->d_name);
            } 
            BLACK_COLOR
        }
        closedir(dir);
}
std::string chartostring(std::string const & s, char a)
{
    return s + a;
}


void
FCommand::create_file()
{
    fchar* _file_name = new fchar;
    std::cin >> _file_name;
    slashn
    fchar *_file_dir = new fchar;
    _file_dir = std::strcat(_file_dir, (_file_path_cd_function, "/", _file_name, ".txt"));
    std::ofstream _file(_file_dir, std::ios::app);
    _file << (_file_name, ".txt", "is created by Scrift.\n");
    _file.close();
}


void
FCommand::plus_num(uinteger64 first_num, uinteger64 sec_num)
{
        printlnf("First number: ");
        std::cin >> first_num;
        printlnf("Second number ");
        std::cin >> sec_num;
        uinteger64 fs_num = sec_num + first_num;
        std::cout << fs_num << "\n";
}


void
FCommand::_generated_hash_string(int size)
{
    std::cout << "Enter size : ";
    std::cin >> size;
    slashn
    std::string str;
    for (integer i = 0; i < size; i++)
    {
        auto d = rand() % 26 + 'a';
        str.push_back(d);
    }
    for (integer i = 0; i < size; i++)
    {
        std::cout << str[i];
    }
    slashn
}

void
FCommand::_your_ip()
{
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            fchar addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printlnf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            fchar addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printlnf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        } 
 }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return;
} 

void
FCommand::get_hostname() // username@hostname$|
{
    fchar hostbuffer[256];  
    struct hostent *host_entry; 
    integer hostname; 
    hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
    printlnf("%s", hostbuffer); 
}


void
FCommand::_term_(fchar *file_str)
{
    fchar *_uname;
    BOLD_CYAN_COLOR // Color code
    get_username(_uname);
    file_str = " $# ";
    printlnf("@");
    BOLD_MAGENTA_COLOR // Color code
    get_hostname();
    printlnf(":~");
    BOLD_YELLOW_COLOR  // Color code 
    printlnf(_file_path_cd_function);
    BOLD_RED_COLOR // Color code 
    printlnf(file_str);
    BLACK_COLOR //Reset (BLACK)
}
void
FCommand::help()
{
     printlnf(_help_str);    
}


void
FCommand::hello()
{ 
        printlnf(_help_str); // Fixed
}

void
FCommand::printerror(fchar *err_str, integer8 err_number, fchar * _error_code)
{
        printlnf(err_str, err_number);
}

void
FCommand::_n_supported_()
{
    printerror("Your os not supported!", 10, "1_n_support \n");
}
