#ifndef MAIN_H
#define MAIN_H

// Includes
#include <stdlib.h>

#include "../consts.h"

#define MINNARGS 2

// Local functions
int main(int argc, char* argv[]);
void proccesExit(int status);

// External functions
void update();
void setup(int argc, char *argv[]);

#endif
