#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <csp/csp.h>
#include <csp/arch/csp_thread.h>
#include <csp/interfaces/csp_if_kiss.h>
#include <csp/drivers/usart.h>

#include <common.h>
#include <calculateCrc.h>

void printMenu() {
    printf("\n***** MENU ***** \n");
    printf("Choose an option: \n");
    printf("1: new CRC \n");
    printf("2: quit \n");
}

int main() {
    printf("Ping Project start\n");
    
    // Debug info
    csp_set_hostname("csp-client");
	csp_set_model("CSP Client");
    csp_debug_toggle_level(CSP_PACKET);
    csp_debug_toggle_level(CSP_INFO);
    
    // CSP config
    csp_buffer_init(10, 512); // REQ
    csp_init(GS_NODE); // REQ
    csp_route_start_task(500, 1); // REQ
    
    // Confirm with debug
    csp_sleep_ms(500);
    csp_conn_print_table();
    csp_route_print_table();
    csp_route_print_interfaces();
    
    // Start threads
    // pthread_t server_id = startServer();
    // pthread_t client_id = startClient();
    
    // Join on threads
    // pthread_join(server_id, NULL);
    // pthread_join(client_id, NULL);
    
    
    /* Start main runloop */
    csp_packet_t* packet;
    csp_conn_t* conn;
    while (1) {
        
        // Get input and perform action
        printMenu();
        int input;
        scanf("%d", &input);
        printf("Received %d\n", input);
        uint32_t crc;
        switch (input) {
            case 1:
                // Perform CRC actions
                crc = calculateCrc();
                printf("CRC was calculated to be 0x%02x\n", crc);
                break;
            case 2:
                exit(0);
                break;
            default:
                printf("Unknown command \'%d\'. Try again.\n", input);
        }
    }
    
    return 0;
}