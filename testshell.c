#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.

#define BUF_SIZE 256

// start main funciton.
int main( void )
{
    int   i = 0;
    char  buf[BUF_SIZE];
    char  *com[] = { buf, NULL };
    pid_t ret;

    // Receive DEFAULT_PATH's commands.
    while ( 1 ) {
        printf( "$ " );

        // Exit Shell
        if ( gets( buf ) == NULL ) {
            break;
        }

/*************************************************|
|                                                 |
|       スペースとかの処理をするところ            |
|       cdとかも入れておきたい.                   |
|                                                 |
**************************************************/

        // Case exit command
        if ( strcmp( buf, "exit" ) == 0 ) {
            break;
        }
        // End exit.

        ret = fork();

        // Start Error check fork.
        if ( ret < 0 ) {
            perror( "fork" );
            exit ( 1 );
        }
        // End Error check fork.

        // Check ( Childs or Parents ).
        if ( ret == 0 ) {
            // Case child process.
            if ( execvp( com[0], com ) < 0 ) {
                perror( "execvp" );
                exit ( 1 );
            }
        }
        // Case parent process.
        else {
            if ( wait( NULL ) < 0 ) {    // Wait for ( end of Child ).
                perror( "wait" );
                exit( 1 );
            }
        }
    }
    // End Shell and this Program.
    return 0;
}
