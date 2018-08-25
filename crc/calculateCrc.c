
#include <calculateCrc.h>

// Print full packet out to terminal
void checkPacket(csp_packet_t* packet);

void printHex(int val) {
    printf("0x%02x", val);
}

uint32_t calculateCrc() {
    /* 1. Get info for header 
        Enter hex values , store in uint8_t array
    */
    
    int headerSize = 4;
    uint8_t header[4];
    printf("Enter the 4 header bytes in hex (hit enter after each): \n");
    for (int i = 0; i < headerSize; i++) {
        unsigned int temp;
        scanf("%x", &(temp));
        header[i] = (uint8_t)temp;
    }
    
    // CHECK: print to make sure
    printf("Header: { ");
    for (int i = 0; i < headerSize; i++) {
        printf("0x%02x ", header[i]);
    }
    printf(" }\n");
    
    /* 2. Get info for data section
            Get size, then enter values in array
    */
    
    int dataSize;
    printf("Number of bytes in data section: ");
    scanf("%d", &dataSize);
    printf("\n");
    
    uint8_t* data = (uint8_t*)malloc(dataSize);
    printf("Enter the %d bytes of data section in hex (hit enter after each): \n", dataSize);
    for (int i = 0; i < dataSize; i++) {
        unsigned int temp;
        scanf("%x", &(temp));
        data[i] = (uint8_t)temp;
    }
    
    // CHECK: print to make sure
    printf("Data: { ");
    for (int i = 0; i < dataSize; i++) {
        printf("0x%02x ", data[i]);
    }
    printf(" }\n");
    
    /* 3. Generate CSP packet in similar way as before
        memcpy into header
        memcpy into buffer
        call calculator
        print packet bytes 
    */
    
    printf("Generating packet and calculating CRC...\n");
    csp_packet_t* packet = csp_buffer_get(100);
    if (packet == NULL) {
        printf("calculateCrc: could not reserve packet! Exiting...\n");
        return;
    }
    
    // Overwrite header segment 
    memcpy((uint8_t*)(&(packet->id)), header, headerSize);
    
    // Overwrite data segment 
    memcpy((uint8_t*)packet->data, data, dataSize);
    packet->length = dataSize;
    
    // Check
    printf("Packet before append: \n");
    printPacket(packet);
    csp_crc32_append(packet, true);
    printf("Packet after append: \n");
    printPacket(packet);
    
    // Strip the 32 CRC bytes from the end of the packet and return as uint32_t
    uint32_t crc;
    memcpy(&crc, &(packet->data[dataSize]), 4); // Copy direction is weird, starts at end and goes backwards, cuz hey
    
    // Free yo buffers!
    csp_buffer_free(packet);
    free(data);
    
    return crc;
}








// Print full packet out to terminal
void checkPacket(csp_packet_t* packet) {
    
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