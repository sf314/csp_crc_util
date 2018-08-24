#ifndef CLIENT_H
#define CLIENT_H

/*
Define simple CSP Client
Send packet every second
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <common.h>

#include <csp/csp.h>
#include <csp/arch/csp_thread.h>
#include <csp/csp_crc32.h>

void* csp_client(void* args);
pthread_t startClient(void);

#endif