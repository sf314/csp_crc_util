#include <server.h>

pthread_t startServer() {
    pthread_t id;
    if (pthread_create(&id, NULL, csp_server, NULL) != 0) {
        printf("server: Could not start server!!!!]n");
        return NULL;
    }
    return id;
}

void* csp_server(void* args) {
    printf("server: started!\n");
    
    // Configure socket
    csp_socket_t* socket = csp_socket(CSP_SO_NONE);
    csp_bind(socket, CSP_ANY);
    csp_listen(socket, 10);
    
    csp_packet_t* packet;
    csp_conn_t* conn;
    
    while(1) {
        // Wait until connection is incoming. If not, skip.
        if ((conn = csp_accept(socket, 10000)) == NULL) {
            continue;
        }
        
        printf("server: Connection accepted\n");
        while ((packet = csp_read(conn, 100)) != NULL) {
            csp_id_t id;
            memcpy(&id, &(packet->id), sizeof(csp_id_t));
            int srcNode = id.src;
            printf("server: packet intercepted from src node %d!\n", srcNode);
            int dport = csp_conn_dport(conn);
            switch (dport) {
                case DEST_PORT:
                    printf("server: packet received on port %d: %s\n", dport, (char*)packet->data);
                    csp_buffer_free(packet); // MUST FREE PACKET AT DESTINATION
                    break;
                default:
                    csp_service_handler(conn, packet);
                    break;
            }
        }
        
        csp_close(conn);
    }
    
    
    return CSP_TASK_RETURN;
}