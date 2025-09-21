#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>

char stoped_copy = 0;

char open_and_check_fill(FILE **origin, FILE **new, char **argv, char *nam_origin, char *nam_new){
    struct stat st;
    *origin = fopen(nam_origin,"r");
    if (!origin){ /*error with to open file*/
        perror(nam_origin);
        exit(2);
    }

    if (stoped_copy == (stat(nam_new, &st) == 0)){
        return 1;
    }else {
        *new = fopen(nam_new,"w");
        if (!new){ /*error with to open file*/
            perror(nam_new);
            exit(2);
        }
    }
    return 0;
};

int main(int argc, char **argv){
    FILE *origin, *new;
    char *nam_origin, *nam_new;
    int c;
    int opt;
    char cloused_checker = 0;

    //available flags
    static struct option long_options[] = {
        {"help",    no_argument,        0, 'h'},
        {"no-clobber",    no_argument,        0, 'n'},
        {"version", no_argument,        0, 'v'},
        {"info",    no_argument,        0, 'i'},
        {"block",    no_argument,        0, 'b'},
        {"standart",    no_argument,        0, 's'},
        {0, 0, 0, 0}
    };

    if (argc < 2){
        fprintf(stderr,"Too few arguments\n");
        exit(1);
    }

    nam_origin = argv[optind + 1];
    nam_new = argv[optind + 2];
    if (*nam_origin == *nam_new) {
        /*concatination*/
    }

    while ((opt = getopt_long(argc, argv, "hnvsbi", long_options, NULL)) != EOF) {
        switch (opt) {
            case 'h':
                printf("first what to copy then where\n");
                printf("-s standart-copy\n");
                printf("-b block-copy\n");
                printf("-v version\n");
                break;

    	    case 'n':
                stoped_copy = 1;
                break;

    	    case 'v':
                printf("Version 1.0\n");
                break;

            case 's':
                if(open_and_check_fill(&origin, &new, argv, nam_origin, nam_new))
                    break;
                while((c = fgetc(origin)) != EOF)
                     fputc(c, new);
                cloused_checker = 1;
                break;

            case 'b':
                if(open_and_check_fill(&origin, &new, argv, nam_origin, nam_new))
                    break;
                printf("block copy\n");
                fflush(stdout);
                cloused_checker = 1;
                break;

    	    case 'i':
                printf("'%s' -> '%s'\n", nam_origin, nam_new);
                break;
        }
    }
    if(cloused_checker){
        int fclose(FILE *origin);
        int fclose(FILE *new);
    } 
    return 0;
}
