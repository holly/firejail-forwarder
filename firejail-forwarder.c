#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>

#define FIREJAIL_CMD         "/usr/bin/firejail"
#define JAIL_SUBSTITUTE_CMD  "/root/bin/substitute-user.py"
#define UID_MIN              10000
#define UID_MAX              15000

int main(int argc, char *argv[]) {

        char *account;
        if ( argc != 2 ) {
                /*
                fprintf(stderr, "Usage: %s JAILUSER\n", argv[0]);
                exit(EXIT_FAILURE);
                */
                account = getenv("USER");
        } else {
                account = argv[1];
        }

        struct passwd* pw = getpwnam(account);

        if( pw == NULL ){
                fprintf(stderr, "%s is not exists\n", account);
                exit(EXIT_FAILURE);
        }

        if (UID_MIN > pw->pw_uid || UID_MAX < pw->pw_uid) {
                fprintf(stderr, "%s uid(%i) range error %i < UID < %i\n", account, pw->pw_uid, UID_MIN, UID_MAX);
                exit(EXIT_FAILURE);
        }

        char join_str[200] = "--join=";
        strncat(join_str, account, sizeof(account));

        printf("account: %s\n", account);

        setuid(0);
        //uid_t real = getuid();
        //printf("uid: %d\n", real);

        char *const args[] = {
                FIREJAIL_CMD,
                "--quiet",
                join_str,
                JAIL_SUBSTITUTE_CMD,
                account,
                NULL
        };
        execvp(args[0], args);

        perror("firejail exec error");
        exit(EXIT_FAILURE);
}
