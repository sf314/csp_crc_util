#ifndef SERVER_H
#define SERVER_H

/*
Define simple CSP Server
Find and accept packets
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <common.h>

#include <csp/csp.h>
#include <csp/arch/csp_thread.h>

void* csp_server(void* args);
pthread_t startServer(void);

#endif