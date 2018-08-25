
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <csp/csp.h>
#include <csp/arch/csp_thread.h>
#include <csp/csp_crc32.h>

/*
Take input for header and data sections, place in malloc'd buffer
Generate CSP packet, run thru CRC calculator
Print packet, and result
*/
uint32_t calculateCrc(void);

/*
Print given int as hex in format: 0xNN
No leading or trailing spaces or control chars are given
*/
void printHex(int val);