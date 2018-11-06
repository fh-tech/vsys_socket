//
// Created by viktorl on 03.11.18.
//

#ifndef VSYS_SOCKET_LDAPAUTHENTICATOR_H
#define VSYS_SOCKET_LDAPAUTHENTICATOR_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ldap.h>
#define LDAP_URI "ldap://ldap.technikum-wien.at:389"

class LDAPAuthenticator {
public:
    static bool authenticate(const std::string &username, const std::string &password) {
        std::string bind_user = "uid=" + username + ",ou=People,dc=technikum-wien,dc=at";
        LDAP *ld;            /* LDAP resource handle */
//        LDAPMessage *result, *e;    /* LDAP result handle */
//        BerElement *ber;        /* array of attributes */
//        char *attribute;
//        BerValue **vals;

        BerValue *servercredp;
        BerValue cred;
        cred.bv_val = const_cast<char *>(password.c_str());
        cred.bv_len = password.length();
        int i, rc = 0;

        const char *attribs[] = {"uid", "cn", NULL};        /* attribute array for search */

        int ldapversion = LDAP_VERSION3;

        /* setup LDAP connection */
        if (ldap_initialize(&ld, LDAP_URI) != LDAP_SUCCESS) {
            fprintf(stderr, ":Ldap_init failed");
//            return EXIT_FAILURE;
            return false;
        }

        printf("Connected to LDAP server %s\n", LDAP_URI);

        if ((rc = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &ldapversion)) != LDAP_SUCCESS) {
            fprintf(stderr, "ldap_set_option(PROTOCOL_VERSION): %s\n", ldap_err2string(rc));
            ldap_unbind_ext_s(ld, NULL, NULL);
//            return EXIT_FAILURE;
            return false;
        }

        if ((rc = ldap_start_tls_s(ld, NULL, NULL)) != LDAP_SUCCESS) {
            fprintf(stderr, "ldap_start_tls_s(): %s\n", ldap_err2string(rc));
            ldap_unbind_ext_s(ld, NULL, NULL);
//            return EXIT_FAILURE;
            return false;
        }

        /* anonymous bind */
        rc = ldap_sasl_bind_s(ld, bind_user.c_str(), LDAP_SASL_SIMPLE, &cred, NULL, NULL, &servercredp);

        if (rc != LDAP_SUCCESS) {
            fprintf(stderr, "Authentication failed.: %s\n", ldap_err2string(rc));
            ldap_unbind_ext_s(ld, NULL, NULL);
//            return EXIT_FAILURE;
            return false;
        } else {
            printf("Successfully authenticated.\n");
            return true;
        }

    }

//        /* perform ldap search */
//        rc = ldap_search_ext_s(ld, SEARCHBASE, SCOPE, FILTER, (char **) attribs, 0, NULL, NULL, NULL, 500, &result);
//
//        if (rc != LDAP_SUCCESS) {
//            fprintf(stderr, "LDAP search error: %s\n", ldap_err2string(rc));
//            ldap_unbind_ext_s(ld, NULL, NULL);
//          return EXIT_FAILURE;
//            return false;
//        }
//
//        printf("Total results: %d\n", ldap_count_entries(ld, result));
//
//        for (e = ldap_first_entry(ld, result); e != NULL; e = ldap_next_entry(ld, e)) {
//            printf("DN: %s\n", ldap_get_dn(ld, e));
//
//            /* Now print the attributes and values of each found entry */
//
//            for (attribute = ldap_first_attribute(ld, e, &ber);
//                 attribute != NULL; attribute = ldap_next_attribute(ld, e, ber)) {
//                if ((vals = ldap_get_values_len(ld, e, attribute)) != NULL) {
//                    for (i = 0; i < ldap_count_values_len(vals); i++) {
//                        printf("\t%s: %s\n", attribute, vals[i]->bv_val);
//                    }
//                    ldap_value_free_len(vals);
//                }
//                /* free memory used to store the attribute */
//                ldap_memfree(attribute);
//            }
//            /* free memory used to store the value structure */
//            if (ber != NULL) ber_free(ber, 0);
//
//            printf("\n");
//        }
//
//        /* free memory used for result */
//        ldap_msgfree(result);
//        printf("LDAP search suceeded\n");
//
//        ldap_unbind_ext_s(ld, NULL, NULL);
//        return EXIT_SUCCESS;
//    }

};


#endif //VSYS_SOCKET_LDAPAUTHENTICATOR_H
