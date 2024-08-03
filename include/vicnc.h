void show_help( void );
void cmd_build( char *target );
void cmd_update( char *target );
void cmd_clean( void );
void cmd_run( void );
void cmd_clean_run( void );
void run_shell_command( char *cmd, char *args );

#define run_cmd_with_default( text, def, func ) \
	if( strcmp(argv[1], text ) == 0 ) { \
		char * arg_data_ ##func = argc == 3 ? argv[2] : def; \
		func( arg_data_ ##func ); \
		exit(0); \
	}

#define run_cmd( text, func ) \
	if( strcmp(argv[1], text ) == 0 ) { \
		func(); \
		exit(0); \
	}