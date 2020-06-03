#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

static void on_connect(uv_connect_t* req, int status) {
    printf("Connected:%d\n", status);
}

int main () {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);
    uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, socket);

    uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));

    struct sockaddr_in dest;
    uv_ip4_addr("127.0.0.1", 80, &dest);
    
    uv_tcp_connect(connect, socket, (const struct sockaddr*)&dest, on_connect);

    printf("Now quitting.\n");
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);
    return 0;
}
