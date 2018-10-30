//
// Created by viktorl on 28.09.18.
//

#include <iostream>
#include <sstream>
#include <thread>
#include <assert.h>
#include "include/MailServer.h"
#include <ldap.h>

void print_usage(char *program_name) {
    fprintf(stderr, "Usage: %s -i IP -p PORT\n", program_name);
    exit(EXIT_FAILURE);
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ldap.h>

#define LDAP_URI "ldap://ldap.technikum-wien.at:389"
#define SEARCHBASE "dc=technikum-wien,dc=at"
#define SCOPE LDAP_SCOPE_SUBTREE
#define FILTER "(uid=if17b*)"
#define BIND_USER ""	/* anonymous bind with user and pw empty */
#define BIND_PW ""

int main()
{
    LDAP *ld;			/* LDAP resource handle */
    LDAPMessage *result, *e;	/* LDAP result handle */
    BerElement *ber;		/* array of attributes */
    char *attribute;
    BerValue **vals;

    BerValue *servercredp;
    BerValue cred;
    cred.bv_val = (char *)BIND_PW;
    cred.bv_len=strlen(BIND_PW);
    int i,rc=0;

    const char *attribs[] = { "uid", "cn", NULL };		/* attribute array for search */

    int ldapversion = LDAP_VERSION3;

    /* setup LDAP connection */
    if (ldap_initialize(&ld,LDAP_URI) != LDAP_SUCCESS)
    {
        fprintf(stderr,"ldap_init failed");
        return EXIT_FAILURE;
    }

    printf("connected to LDAP server %s\n",LDAP_URI);

    if ((rc = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &ldapversion)) != LDAP_SUCCESS)
    {
        fprintf(stderr, "ldap_set_option(PROTOCOL_VERSION): %s\n", ldap_err2string(rc));
        ldap_unbind_ext_s(ld, NULL, NULL);
        return EXIT_FAILURE;
    }

    if ((rc = ldap_start_tls_s(ld, NULL, NULL)) != LDAP_SUCCESS)
    {
        fprintf(stderr, "ldap_start_tls_s(): %s\n", ldap_err2string(rc));
        ldap_unbind_ext_s(ld, NULL, NULL);
        return EXIT_FAILURE;
    }

    /* anonymous bind */
    rc = ldap_sasl_bind_s(ld,BIND_USER,LDAP_SASL_SIMPLE,&cred,NULL,NULL,&servercredp);

    if (rc != LDAP_SUCCESS)
    {
        fprintf(stderr,"LDAP bind error: %s\n",ldap_err2string(rc));
        ldap_unbind_ext_s(ld, NULL, NULL);
        return EXIT_FAILURE;
    }
    else
    {
        printf("bind successful\n");
    }

    /* perform ldap search */
    rc = ldap_search_ext_s(ld, SEARCHBASE, SCOPE, FILTER, (char **)attribs, 0, NULL, NULL, NULL, 500, &result);

    if (rc != LDAP_SUCCESS)
    {
        fprintf(stderr,"LDAP search error: %s\n",ldap_err2string(rc));
        ldap_unbind_ext_s(ld, NULL, NULL);
        return EXIT_FAILURE;
    }

    printf("Total results: %d\n", ldap_count_entries(ld, result));

    for (e = ldap_first_entry(ld, result); e != NULL; e = ldap_next_entry(ld,e))
    {
        printf("DN: %s\n", ldap_get_dn(ld,e));

        /* Now print the attributes and values of each found entry */

        for (attribute = ldap_first_attribute(ld,e,&ber); attribute!=NULL; attribute = ldap_next_attribute(ld,e,ber))
        {
            if ((vals=ldap_get_values_len(ld,e,attribute)) != NULL)
            {
                for (i=0;i < ldap_count_values_len(vals);i++)
                {
                    printf("\t%s: %s\n",attribute,vals[i]->bv_val);
                }
                ldap_value_free_len(vals);
            }
            /* free memory used to store the attribute */
            ldap_memfree(attribute);
        }
        /* free memory used to store the value structure */
        if (ber != NULL) ber_free(ber,0);

        printf("\n");
    }

    /* free memory used for result */
    ldap_msgfree(result);
    printf("LDAP search suceeded\n");

    ldap_unbind_ext_s(ld, NULL, NULL);
    return EXIT_SUCCESS;
}




#ifdef NOT_LDAP
int main(int argc, char *argv[]) {

    LDAP        *ld;
    int         rc;
    char        bind_dn[100];
    LDAPMessage *result, *e;
    char *dn;
    int has_value;

    sprintf( bind_dn, "cn=%s,dc=ashwin,dc=com", "manager" );
    printf( "Connecting as %s...\n", bind_dn );

    if( ldap_initialize( &ld, "ldap://192.168.1.95:389" ) )
    {
        perror( "ldap_initialize" );
        return( 1 );
    }


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
    MailServer mailServer = argc == 2
                            ? MailServer{argv[0], atoi(argv[1])}
                            : MailServer("127.0.0.1", 10025);
    mailServer.listen();

}
#endif
