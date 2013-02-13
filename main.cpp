
#include <iostream>
#include <fstream>
#include "UniversalCompiler.h"

int main(int argc, char** argv) {

	// Load Universal Compiler with command line argument file names
	// arv[1..3] = { grammarFile, programFile, compiledFile }
	UniversalCompiler* uc;
	if( argc == 1 ){
		uc = new UniversalCompiler( NULL, NULL, NULL );
	}
	else if( argc == 2 ){
		uc = new UniversalCompiler( argv[1], NULL, NULL );
	}
	else if( argc == 3 ){
		uc = new UniversalCompiler( argv[1], argv[2], NULL );
	}
	else {
		uc = new UniversalCompiler( argv[1], argv[2], argv[3] );
	}

	// Run the program.
	uc->greeting();
	uc->initialize();
	while( uc->menu());
}