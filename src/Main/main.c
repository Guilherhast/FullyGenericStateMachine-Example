#include "main.h"
#include <stdio.h>//FIXME remove after debug is complete

// Static variabes

static boolean running = true;

// Local functions

void proccesExit(int status){
	if (status){
		exit(status);
	}
	running = false;
}

// Main

int main(int argc, char* argv[]){

	setup();

	while(running){
		update();
	}

	return 0;
}
