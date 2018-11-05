//
// Created by viktorl on 28.09.18.
//

#include <iostream>
#include <sstream>
#include <thread>
#include <assert.h>
#include "include/MailServer.h"
#include <ldap.h>

//void print_usage(char *program_name) {
//    fprintf(stderr, "Usage: %s -i IP -p PORT\n", program_name);
//    exit(EXIT_FAILURE);
//}


int main(int argc, char *argv[]) {

//    LDAP        *ld;
//    int         rc;
//    char        bind_dn[100];
//    LDAPMessage *result, *e;
//    char *dn;
//    int has_value;
//
//    sprintf( bind_dn, "cn=%s,dc=ashwin,dc=com", "manager" );
//    printf( "Connecting as %s...\n", bind_dn );
//
//    if( ldap_initialize( &ld, "ldap://192.168.1.95:389" ) )
//    {
//        perror( "ldap_initialize" );
//        return( 1 );
//    }


    /*
    int c;
    int error = 0;
    char *program_name = argv[0];
    int ip_set = 0;
    std::string ip;
    int port_set = 0;
    int port = 0;

    while ((c = getopt(argc, argv, "i:p:")) != EOF) {
        switch (c) {
            case 'i':
                if (ip_set) {
                    fprintf(stderr, "multiple usage of flags is not allowed\n");
                    error = 1;
                    break;
                }
                ip_set = 1;
                ip = optarg;
                break;
            case 'p':
                if (port_set) {
                    fprintf(stderr, "multiple usage of flags is not allowed\n");
                    error = 1;
                    break;
                }
                port_set = 1;
                port = atol(optarg);
                break;
            case '?':
                error = 1;
                break;
            default:
                //assert used when this code part can normally be never reached
                assert(0);
        }
    }

    // options were false
    if (error) {
        //print_usage(program_name);
    }

    // false count of options
    if ((argc != 5 || optind != 5)) {
        fprintf(stderr, "false number of arguments\n");
        //print_usage(program_name);
    }
    */
    MailServer mailServer = argc == 3
                            ? MailServer{argv[1], (uint16_t) atoi(argv[2])}
                            : MailServer("127.0.0.1", 10025);
    mailServer.listen();

}

