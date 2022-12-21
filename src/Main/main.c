#include "main.h"

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

	setup(argc, argv);

	while(running){
		update();
	}

	return 0;
}
