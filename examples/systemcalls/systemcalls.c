#include "systemcalls.h"

#include <unistd.h>     // For fork and execv
#include <sys/wait.h>   // For wait
#include <stdlib.h>
#include <stdio.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{
    int retVal;

    retVal = system(cmd);

    if (retVal < 0)
    {
        return false;
    }

    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    bool retVal = true;

    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    //command[count] = command[count];

/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/
    // Execute fork
    fflush(stdout); // Ensure buffers are flushed
    pid_t pid = fork();

    switch (pid)
    {
        case -1:
        {
            va_end(args);
            retVal = false;
        }
        break;
        case 0:
        {
            execv(command[0], &command[0]);
            printf("ERROR WITH EXECV!!!\r\n");
            va_end(args);
            retVal = false;
        }
        break;
        default:
        {
            pid = waitpid(pid, NULL, 0);

            if (pid < 0)
            {
                va_end(args);
                retVal = false;
            }
        }
        break;
    }

    va_end(args);

    return retVal;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    bool retVal = true;
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    //command[count] = command[count];


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/
    FILE *fp = freopen(outputfile, "w", stdout);

    if (fp == NULL)
    {
        retVal = false;
    }

    // Execute fork
    if (retVal == true)
    {
        fflush(stdout); // Ensure buffers are flushed
        pid_t pid = fork();

        switch (pid)
        {
            case -1:
            {
                va_end(args);
                retVal = false;
            }
            break;
            case 0:
            {
                execv(command[0], &command[0]);
                printf("ERROR WITH EXECV!!!\r\n");
                va_end(args);
                retVal = false;
            }
            break;
            default:
            {
                pid = waitpid(pid, NULL, 0);

                if (pid < 0)
                {
                    va_end(args);
                    retVal = false;
                }
            }
            break;
        }

        fclose(fp);
    }

    va_end(args);

    return retVal;
}
