#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_RESP_LEN (65536)

char msg_buf[MAX_RESP_LEN];

int
main(argc, argv)
    int argc;
    char * argv[];
{
    int newsocket;
    ssize_t length;
    struct timeval timeout;
    unsigned long total_length;
    struct addrinfo hints, *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /*
     * resolve hostname to IP address: specify host and port num
     * (port num as string, not int)
     */
    if (getaddrinfo("www.example.com", "80", &hints, &result) != 0)
    {
        freeaddrinfo(result);
        perror("getaddrinfo: ");
        exit(-1);
    }

    /*
     * create socket
     */
    if ((newsocket = socket(result->ai_family, result->ai_socktype, 0)) == -1)
    {
        perror("socket: ");
        freeaddrinfo(result);
        close(newsocket);
        exit(-1);
    }

    /*
     * set socket timeouts
     */
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
    /* set timeout for a SEND */
    setsockopt(newsocket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    /* set timeout for a RECV */
    setsockopt(newsocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    /*
     * connect to website
     */
    if (connect(newsocket, result->ai_addr, result->ai_addrlen) == -1)
    {
        perror("connect: ");
        freeaddrinfo(result); // free addrinfo memory
        close(newsocket);
        exit(-1);
    }

    /*
     * send an HTTP GET request
     */
    if ((send(newsocket, "GET / HTTP/1.1\r\nHost: www.example.com\r\nUser-Agent: Mozilla/5.0 (compatible; MSIE 8.0; Windows NT 6.0)\r\nReferer: \r\nConnection: Close\r\n\r\n", 135, 0)) == -1) 
    {
        perror("send: ");
        freeaddrinfo(result);
        close(newsocket);
        exit(-1);
    }

    /*
     * read webpage from connection
     */
    total_length = 0UL;
    for (;;)
    {
        length = recv(newsocket, msg_buf, MAX_RESP_LEN-1, 0);
        if (length <= 0)
            break;
        msg_buf[length] = 0;
        fprintf(stdout, "%s", msg_buf);
        total_length += length;
    }

    printf("\n");
    printf("final status: %d.\n", length);
    printf("read %ld chars.\n", total_length);

    if (length == -1)
    {
        perror("recv: ");
        freeaddrinfo(result);
        close(newsocket);
        exit(-1);
    }

    /*
     * free addrinfo memory
     */
    freeaddrinfo(result);

    /*
     * close socket
     */
    close(newsocket);

    return 0;
}

