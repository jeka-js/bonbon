#include "connection.h"
#include "funcs.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

FILE * open_connection(char * hostname, char * username, char * password)
{
    char * command = (char *) malloc(COMMAND_BUFFER_SIZE);
    sprintf(command, LOGIN_SCRIPT, username, hostname);
    FILE * pipe = popen(command, "w");

    if (!strcmp(password, EMPTY_STRING))
    {
        sleep(1);
        fputs(password, pipe);
        fputs("\n", pipe);
    }

    free(command);
    return pipe;
}

void close_connection(FILE * pipe)
{
    fputs("exit\n", pipe);
    pclose(pipe);
}

char * execute_command(FILE * pipe, const char * command)
{
    char * com = (char *) malloc(COMMAND_BUFFER_SIZE);
    sprintf(com, "sh -c \"%s\" &\n", command);

    fputs(com, pipe);
    fgets(com, COMMAND_BUFFER_SIZE, pipe);
    g_print("%s", com);

    return com;
}

int send_key(FILE * pipe, const char * key)
{
    char * com = (char *) malloc(COMMAND_BUFFER_SIZE);
    sprintf(com, "DISPLAY=:0.0 xdotool key %s", key);

    char * res = execute_command(pipe, com);

    printf("%s\n%s\n", com, res);
    free(res);
    free(com);

    return EXIT_SUCCESS;
}

