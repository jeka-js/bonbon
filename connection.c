#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "connection.h"
#include "funcs.h"

FILE* open_connection( char* hostname, char* username, char* password )
{
    char* command = (char*) malloc( COMMAND_BUFFER_SIZE );
    //sprintf(command, LOGIN_SCRIPT, username, hostname);
    sprintf( command, LOGIN_SCRIPT, hostname, username, password );
    FILE* pipe = popen( command, "w" );
    fputs( "ls\n", pipe );
    free( command );
    return( pipe );
}

void close_connection( FILE* pipe )
{
    fputs( "exit\n", pipe );
    pclose( pipe );
}

char* execute_command( FILE* pipe, const char* command )
{
    char* com = (char*) malloc( COMMAND_BUFFER_SIZE );
    sprintf( com, "sh -c \"%s\" &\n", command );
    g_print( "%s\n", com );
    fputs( com, pipe );
    fflush( pipe );
    fgets( com, COMMAND_BUFFER_SIZE, pipe );

    return( com );
}

int send_key( FILE* pipe, const char* key )
{
    char* com = (char*) malloc( COMMAND_BUFFER_SIZE );
    sprintf( com, "DISPLAY=:0.0 xdotool key %s", key );
    char* res = execute_command( pipe, com );
    free( res );
    free( com );

    return( EXIT_SUCCESS );
}

