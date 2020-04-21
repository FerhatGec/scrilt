/* GPLv3 License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the GPLv3 License.
#
# */


#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <string.h>
#include "synflang.hpp"

#define slashn printlnf("\n");

//FSync *fsync__ = new FSync();

class FMain  {
public:
    FMain();
    ~FMain();
    virtual void usage(); 
    virtual void Shell();
};





#endif // MAIN_H
