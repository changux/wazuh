/* Copyright (C) 2009 Trend Micro Inc.
 * All rights reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 *
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 *
 */

#ifndef _AUTHD_H
#define _AUTHD_H

#ifndef ARGV0
#define ARGV0 "ossec-authd"
#endif

#ifdef LIBOPENSSL_ENABLED

#include "addagent/manage_agents.h"
#include "os_net/os_net.h"

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

extern BIO *bio_err;
#define KEYFILE  "/etc/sslmanager.key"
#define CERTFILE "/etc/sslmanager.cert"
#define DEFAULT_PORT 1515

#define full(i, j) ((i + 1) % POOL_SIZE == j)
#define empty(i, j) (i == j)
#define forward(x) x = (x + 1) % POOL_SIZE

struct client {
    int socket;
    struct in_addr addr;
};

struct keynode {
    char *id;
    char *name;
    char *ip;
    struct keynode *next;
};

SSL_CTX *os_ssl_keys(int is_server, const char *os_dir, const char *cert, const char *key, const char *ca_cert, int auto_method);
SSL_CTX *get_ssl_context(int auto_method);
int load_cert_and_key(SSL_CTX *ctx, const char *cert, const char *key);
int load_ca_cert(SSL_CTX *ctx, const char *ca_cert);
int verify_callback(int ok, X509_STORE_CTX *store);

#endif /* LIBOPENSSL_ENABLED */
#endif /* _AUTHD_H */
