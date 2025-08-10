#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <civetweb.h>
#include <signal.h>
#include "functions.h"
#include "functionslist.h"

#define ALPHABET_SIZE 27

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int functionId;
} TrieNode;

TrieNode* trie;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->functionId = -1;
    for(int i=0; i<ALPHABET_SIZE; i++) node->children[i] = NULL;
    return node;
}

void insert(const char *url, int functionId) {
    TrieNode *current = trie;
    while(*url) {
        int index = (*url == '/') ? 26 : (*url - 'a');
        if(current->children[index] == NULL) current->children[index] = createNode();
        current = current->children[index];
        url++;
    }

    current->functionId = functionId;
}

int search(const char *url) {
    TrieNode* current = trie;
    while(*url) {
        int index = (*url == '/') ? 26 : (*url-'a');
        if(current->children[index] == NULL) return -1;
        current = current->children[index];
        url++;  
    }
    return current->functionId;
}

void free_trie(TrieNode *node) {
    for(int i=0; i < ALPHABET_SIZE; i++) {
        if(node->children[i] != NULL) {
            free_trie(node->children[i]);
        }
    }
    free(node);
}

void initialize_trie() {
    trie = createNode();
    insert(URL_ROOT, ROOT);
    insert(URL_SQUARE, SQUARE);
    insert(URL_CUBE, CUBE);
    insert(URL_HELLOWORLD, HELLOWORLD);
    insert(URL_PINGPONG, PINGPONG);
    insert(URL_ARITHMETIC_PRIME, ARITHMETIC_PRIME);
    insert(URL_ARITHMETIC_FIBONACCI, ARITHMETIC_FIBONACCI);
}

int request_handler(struct mg_connection *conn) {
    const struct mg_request_info *request_info = mg_get_request_info(conn);
    char response[256];
    char arg[1024] = "";
    const char *uri = request_info->local_uri;
    int functionId = search(uri);

    if(functionId != -1) {
        if(request_info->query_string) {
            if((strcmp(uri, "/helloworld") == 0) || 
            (strcmp(uri, "/pingpong") == 0)) {
                mg_get_var(request_info->query_string, strlen(request_info->query_string), "str", arg, sizeof(arg));
            }
            else if((strcmp(uri, "/square") == 0) ||
            (strcmp(uri, "/cube") == 0) ||
            (strcmp(uri, "/arithmetic/prime") == 0) ||
            (strcmp(uri, "/arithmetic/fibonacci") == 0)) {
                mg_get_var(request_info->query_string, strlen(request_info->query_string), "num", arg, sizeof(arg));
            }

            functions_list[functionId](arg[0] ? arg : NULL, response);
        }

        else functions_list[functionId](NULL, response);

        mg_printf(conn,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: %ld\r\n\r\n%s",
            strlen(response), response);
    }

    else {
        mg_printf(conn,
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n\r\nURL not found.");
    }

    return 1;
}

volatile int server_running = 1;

void stop_server(int signo) {
    server_running = 0;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("USAGE: %s <PORT> <THREAD_POOL_SIZE>\n", argv[0]);
        return 0;
    }

    const char* port = argv[1];
    const int thread_pool_size = atoi(argv[2]);

    initialize_trie();

    struct mg_callbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));
    
    callbacks.begin_request = request_handler;
    
    const char* options[] = {
        "listening_ports",port,
        "num_threads", argv[2],
        NULL
    };

    struct mg_context *ctx = mg_start(&callbacks, NULL, options);

    if(!ctx) {
        printf("Failed to start server on port %s\n", port);
        return 0;
    }

    printf("Server started on port %s\n", port);

    printf("Press Ctrl+C to stop the server. \n");
    
    // getchar();

    // This signal handling and while loop is done to ensure that loadgen script works correctly,
    // You can revert back to getchar
    signal(SIGINT, stop_server);
    signal(SIGTERM, stop_server);
    while(server_running);

    mg_stop(ctx);
    printf("Server stopped.\n");
    free_trie(trie);
}
