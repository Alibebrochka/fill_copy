#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv){
    struct stat st;
    FILE *origin, *new;
    int opt;
    int elm_count = 0;
    int buffer_size = 1012;
    char *nam_origin, *nam_new;
    char cloused_checker = 0;
    char working_list[10];
    char stoped_copy = 0;

    //available flags
    static struct option long_options[] = {
        {"help",    no_argument,        0, 'h'},
        {"no-clobber",    no_argument,        0, 'n'},
        {"version", no_argument,        0, 'v'},
        {"info",    no_argument,        0, 'i'},
        {"block",    optional_argument,        0, 'b'},
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

    /*   setting parameters and configurations in working_list   */
    while ((opt = getopt_long(argc, argv, "hnvsb::i", long_options, NULL)) != EOF) {
        switch (opt) {
            case 'h':
                printf("first what to copy then where\n");
                printf("-s standart-copy\n");
                printf("-n no-clobber\n");
                printf("-b block-copy\n");
                printf("-v version\n");
                printf("-i info\n");
                exit(0);

            case 'n':
                stoped_copy = 1;
                break;

            case 'v':
                printf("Version 2.0\n");
                exit(0);

            case 's':
                working_list[elm_count] = opt;
                elm_count ++;
                cloused_checker = 1;
                break;

            case 'b':
                working_list[elm_count] = opt;
                elm_count ++;
                cloused_checker = 1;

                if (optarg) {
                    char *endptr;
                    errno = 0;  /* we throw an error before calling */
                    long val = strtol(optarg, &endptr, 10);

                    if (errno != 0) { /* system error (e.g. overflow) */
                        perror("strtol");
                        exit(EXIT_FAILURE);
                    }
                    if (*endptr != '\0') {/* checking for invalid arguments that are not numbers */
                        fprintf(stderr, "Invalid number: %s\n", optarg);
                        exit(EXIT_FAILURE);
                    }
                    if (val <= 0) {/* buffer positivity check */
                        fprintf(stderr, "Block size must be positive\n");
                        exit(EXIT_FAILURE);
                    }
                    buffer_size = (int)val;
                }
                break;

            case 'i':
                working_list[elm_count] = opt;
                elm_count ++;
                break;
        }
    }
    if (cloused_checker && !stoped_copy && (stat(nam_new, &st) == 0)){
        /* open file */
        origin = fopen(nam_origin,"r");
        if (!origin){ /*error with to open file*/
            perror(nam_origin);
            exit(EXIT_FAILURE);
        }
        new = fopen(nam_new,"w");
        if (!new){ /*error with to open file*/
            perror(nam_new);
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < elm_count; ++i){
            switch (working_list[i]) {
                case 's':
                    int c;
                    while((c = fgetc(origin)) != EOF)
                        fputc(c, new);
                    break;

                case 'b':
                    char *buff = malloc(sizeof(char) * buffer_size);
                    int nread;

                    while((nread = fread(buff, 1, buffer_size, origin)) > 0){
                        if(nread != fwrite(buff, 1, nread, new)){
                            printf("fwrite error\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    if (ferror(origin)) {
                        printf("read error\n");
                        exit(EXIT_FAILURE);
                    }
                    break;

                case 'i':
                    printf("'%s' -> '%s'\n", nam_origin, nam_new);
                    break;
            }
        }
        int fclose(FILE *origin);
        int fclose(FILE *new);
    }
    return 0;
}
