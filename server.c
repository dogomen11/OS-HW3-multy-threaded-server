#include "segel.h"
#include "request.h"
#include "thread_pool.h"

// 
// server.c: A very, very simple web server
//
// To run:
//  ./server <portnum (above 2000)>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
//

// HW3: Parse the new arguments too
void getargs(int *port, int *number_of_threads, int *queue_size, int *overload_policy, int argc, char *argv[])
{
    if (argc < 5) 
    {
	    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
	    exit(1);
    }
    *port = atoi(argv[1]);
    *number_of_threads = atoi(argv[2]);
    *queue_size = atoi(argv[3]);
    *overload_policy = atoi(argv[4]);

    if (*port < 0 || *number_of_threads < 0 || *queue_size < 0 || *overload_policy < 0)
    {
        fprintf(stderr, "Illegal arguments\n");
        exit(1);
    }
}


int main(int argc, char *argv[])
{
    int listenfd, connfd, port, clientlen, number_of_threads, queue_size, overload_policy;
    struct sockaddr_in clientaddr;

    getargs(&port, &number_of_threads, &queue_size, &overload_policy, argc, argv);

    pthread_cond_t condition;
    pthread_cond_init(&condition, NULL);
    //need another one
    pthread_mutex_t mutex_lock;
    pthread_mutex_init(&mutex_lock, NULL);
    //state is by queue_size;
    int currently_handled_requests_number = 0;
    
    // HW3: Create some threads...
    tpool_t* sddd = tpool_create(number_of_threads);


    listenfd = Open_listenfd(port);
    while (1) 
    {
	    clientlen = sizeof(clientaddr);
	    connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *) &clientlen);

	    // 
	    // HW3: In general, don't handle the request in the main thread.
	    // Save the relevant info in a buffer and have one of the worker threads 
	    // do the work. 
	    // 
	    requestHandle(connfd);

    	Close(connfd);
    }

}


    


 
