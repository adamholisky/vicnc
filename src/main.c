#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "vicnc.h"

char build_default[] = "all";
char update_default[] = "all";

int main( int argc, char *argv[] ) {
	if( argc < 2 ) {
		show_help();
		exit(0);
	}

	run_cmd_with_default( "b", build_default, cmd_build );
	run_cmd_with_default( "build", build_default, cmd_build );

	run_cmd( "r", cmd_run );
	run_cmd( "run", cmd_run );

	run_cmd_with_default( "update", update_default, cmd_update );
	run_cmd_with_default( "u", update_default, cmd_update );

	run_cmd( "c", cmd_clean );
	run_cmd( "clean", cmd_clean );

	run_cmd( "cr", cmd_clean_run );
	run_cmd( "cleanrun", cmd_clean_run );
}

void run_shell_command( char *cmd, char *args ) {
	if( !vfork() ) {
		char *argv[] = {
			cmd,
			args,
			NULL
		};

		execvp( argv[0], argv );
	}
}

void cmd_build( char *target ) {
	run_shell_command( "make", target );
}

void cmd_update( char *target ) {
	if( strcmp( target, "all" ) == 0 ) {
		run_shell_command( "make", "cp_fs" );
	}
}

void cmd_run( void ) {
	run_shell_command( "make", "run" );
}

void cmd_clean( void ) {
	run_shell_command( "make", "clean" );
}

void cmd_clean_run( void ) {
	run_shell_command( "make", "clean" );
	run_shell_command( "make", "run" );
}

void show_help( void ) {
	printf( "vicnc\n" );
	printf( "VI OS Command and Control\n" );
	printf( "\n" );
	printf( "Usage:\n" );
	printf( "    c or clean             Executes make clean.\n" );
	printf( "    b or build <target>    Builds target, defaults to all.\n" );
	printf( "    r or run               Executes make run.\n" );
	printf( "    cr or cleanrun         Executes make clean && make run.\n" );
}