#include <client.h>

// Print full packet out to terminal
void printPacket(csp_packet_t* packet);

pthread_t startClient() {
    pthread_t id;
    if (pthread_create(&id, NULL, csp_client, NULL) != 0) {
        printf("client: could not start client thread!!!\n");
        return NULL;
    }
    return id;
}

void* csp_client(void* args) {
    printf("client: started!\n");
    
    csp_packet_t* packet;
    // csp_conn_t* conn;
    
    while (1) {
        csp_sleep_ms(1000);
        
        int ping_res;
        
        // // ***** Ping nodes
        // printf("client: pinging DEBUG_NODE (%d)...\n", DEBUG_NODE);
        // ping_res = csp_ping(DEBUG_NODE, 100, 100, CSP_O_NONE);
        // printf("client: ping result = %d\n", ping_res);
        // csp_sleep_ms(1000);
        
        // printf("client: pinging A3200_NODE (%d)...\n", A3200_NODE);
        // ping_res = csp_ping(A3200_NODE, 100, 100, CSP_O_NONE);
        // printf("client: ping result = %d\n", ping_res);
        // csp_sleep_ms(1000);
        
        // printf("client: pinging AX100_NODE (%d)...\n", AX100_NODE);
        // ping_res = csp_ping(AX100_NODE, 100, 100, CSP_O_NONE);
        // printf("client: ping result = %d\n", ping_res);
        // csp_sleep_ms(1000);
        
        // printf("client: pinging TNC_NODE (%d)...\n", TNC_NODE);
        // ping_res = csp_ping(TNC_NODE, 100, 100, CSP_O_NONE);
        // printf("client: ping result = %d\n", ping_res);
        // csp_sleep_ms(1000);
        
        // printf("client: pinging GS_NODE (%d)...\n", GS_NODE);
        // ping_res = csp_ping(GS_NODE, 100, 100, CSP_O_NONE);
        // printf("client: ping result = %d\n", ping_res);
        // csp_sleep_ms(1000);
        
        
        
        
        
        
        // Get packet and send to server
        printf("\n\n\n");
        packet = csp_buffer_get(100);
        if (packet == NULL) {
            printf("client: could not reserve packet! Exiting...\n");
            return CSP_TASK_RETURN;
        }
        
        // conn = csp_connect(CSP_PRIO_NORM, AX100_NODE, 5, 1000, CSP_O_CRC32);
        // if (conn == NULL) {
        //     printf("client: could not get a connection! Exiting...\n");
        //     csp_buffer_free(packet);
        //     return CSP_TASK_RETURN;
        // }
        
        printf("client: An empty packet: \n");
        printPacket(packet);
        
        // Fill the data segment
        uint8_t buffer[] = {0x00, 0x04, 0x00, 0x00, 0xb0, 0x0b};
        // uint8_t buffer[] = {0, 0, 0, 0, 0, 0};
        // uint8_t buffer[] = {0x00, 0x04};
        memcpy((uint8_t*)packet->data, buffer, 6);
        packet->length = 6;
        
        printf("client: packet with new data segment: \n");
        printPacket(packet);
        
        // Overwrite the ID segment
        uint8_t newId[] = {0xd4, 0x51, 0xdf, 0x00};
        memcpy((uint8_t*)(&(packet->id)), newId, 4);
        /*
        Header: {0xd4, 0x51, 0xdf, 0x00};
        In binary: 1101 0100 0101 0001 1101 1111 0000 0000
        Prio, src, dest, dport, sport, flags
        2, 5, 5, 6, 6, 8
        11 01010 00101 000111 011111 00000000
        P: 3
        S: 10
        D: 5
        Dp: 7
        Sp: 31
        */
        
        // printf("client: sending packet ('%s') to target...\n", (char*)packet->data);
        printf("client: sending the following packet: \n");
        printPacket(packet);
        
        // Do CRC things?
        csp_crc32_append(packet, false);
        printf("client: sending the following packet after crc32_append: \n");
        printPacket(packet);
        // printf("Verification: %d\n", csp_crc32_verify(packet, true));
        
        // if (!csp_send(conn, packet, 1000)) {
        //     printf("Send failed\n");
        //     csp_buffer_free(packet);
        // }
        if (csp_sendto(CSP_PRIO_HIGH, AX100_NODE, 7, 31, CSP_O_NONE, packet, 1000)) {
            printf("client: Send failed!\n");
            csp_buffer_free(packet);
        }
        
        // csp_close(conn);
    }
    
    return CSP_TASK_RETURN;
}

// Print full packet out to terminal
void printPacket(csp_packet_t* packet) {
    
    // Padding, length, id, data
    printf("printPacket: raw packet = ");
    
    uint8_t* buf = (uint8_t*)&(packet->length);
    printf("0x%02x 0x%02x ", buf[0], buf[1]);
    
    buf = (uint8_t*)&(packet->id);
    for (int i = 0; i < 4; i++) {
        printf("0x%02x ", buf[i]);
    }
    
    buf = (uint8_t*)(packet->data);
    for (int i = 0; i < packet->length; i++) {
        printf("0x%02x ", buf[i]);
    }
    
    printf("\n");
    
    uint16_t length = packet->length;
}