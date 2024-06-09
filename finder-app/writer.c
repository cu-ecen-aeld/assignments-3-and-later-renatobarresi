#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argvp[])
{
    FILE* fd;
    int retVal;

    if (argc < 3)
    {
        printf("Pass two arguments\r\n");
        exit(1);
    }

    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    syslog(LOG_DEBUG, "Writing %s to %s", argvp[1], argvp[2]);
    
    // Create file
    fd = fopen(argvp[1], "w");
    
    if (fd < 0)
    {
        syslog(LOG_ERR, "Unable to create the file\r\n");
        closelog();
        exit(1);
    }

    // Write to file
    retVal = fprintf(fd, argvp[2]);

    if (retVal < 0)
    {
        syslog(LOG_ERR, "Unable to write to file\r\n");
        fclose(fd);
        closelog();
        exit(1);
    }

    // Close file & log
    closelog();
    fclose(fd);

    return 0;
}
