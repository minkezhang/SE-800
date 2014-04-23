/*
*
* CMSC 23800 / 33800 - Game Construction
* Server Model for Network
*
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
// #include "PhysicsEngine.h"
#include "globalData.h"
#include "structures.h"

extern pthread_mutex_t lock;
extern int num_ready_pthreads;

/* run_client:
* This is the function which each spawned p_thread will
* run. Parses commands from clients and responds to
* client accordingly.
*/
void *run_client(void *args){
    struct workerArgs *wa;
    wa = (struct workerArgs*) args;

    pthread_detach(pthread_self());


    // Create player-controllable ship for client.
    // client_ship_init(wa->socket, wa->worldEngine);

    // Send controllable ship ID to client (so client can identiy itself.)

    // This client is ready to render.
    pthread_mutex_lock(&lock);
    num_ready_pthreads++;
    pthread_mutex_unlock(&lock);
    // Sleep until other client is ready to render.
    // Start accepting UI input.


    // Setting total amount of chars buf can parse
    // at a time.
    int bufLen = 6000;
    int nbytes;
    int n;
    char inputBuf[bufLen];
    char buildBuf[bufLen];
    char **commandList;
    int buildLen = 0;
    memset(inputBuf, 0, bufLen);
    memset(buildBuf, 0, bufLen);
    int clientSocket = wa->socket;
    char * clientHost = wa->clientHost;
    int * worldEngine = wa->worldEngine;

    // Collect input from client until disconnect.
    // Build input buffer until buffer terminates with "\r\n".

    // (TODO): Parse received stream for UI input objects and pass to
    // Physics/Game Engine.
    while( (nbytes = recv(clientSocket, inputBuf, bufLen, 0)) )
    {
      if (nbytes + buildLen > bufLen)
        nbytes = bufLen - buildLen;
      memcpy(buildBuf+buildLen, inputBuf, nbytes);
      buildLen = buildLen + nbytes;
      // Handles case if string is too long for buffer
      if ((buildBuf[bufLen-1]) && (buildBuf[bufLen-1]!='\n'))
      {
        buildBuf[bufLen-2]='\r';
        buildBuf[bufLen-1]='\n';
      }
      // If input buffer ends with \r\n, print buffer.
      // (TODO) Replace this with UI input parser.
      if (buildBuf[buildLen-1]=='\n' && buildBuf[buildLen-2]=='\r')
      {
        printf("CLIENT SAID %s\n", buildBuf);

        buildLen = 0;
        memset(inputBuf, 0, bufLen);
        memset(buildBuf, 0, bufLen);
      }
    }
    free(wa);

    pthread_mutex_lock(&lock);
    num_ready_pthreads--;
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
  int opt;
  char port[] = "6667"; // (TODO): Make port modifiable.

  num_ready_pthreads = 0;
  int num_clients = 0;
  int serverSocket;
  int clientSocket;
  pthread_t worker_thread;
  struct sockaddr_in serverAddr, clientAddr;
  int yes = 1;
  socklen_t sinSize = sizeof(struct sockaddr_in);

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(port));
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  listen(serverSocket, 5);

  // (TODO): Initialize World/Physics Engine(because it's obviously not an int)
  int worldEngine;
  worldEngine = 1;

  struct workerArgs *wa;

  pthread_mutex_init(&lock, NULL);

  while(1)
  {

    clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &sinSize);
    num_clients++;
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    // Retrieve client hostname
    struct hostent *he;
    struct in_addr ipv4addr;
    char *IP = inet_ntoa(clientAddr.sin_addr);
    inet_pton(AF_INET, IP, &ipv4addr);
    he = gethostbyaddr(&ipv4addr, sizeof(ipv4addr), AF_INET);
    char *clientHost = he->h_name;
    // Pass on arguments to worker thread
    wa = (struct workerArgs *) malloc(sizeof(struct workerArgs));
    wa->socket = clientSocket;
    wa->clientHost = clientHost;
    wa->worldEngine = &worldEngine;
    if(pthread_create(&worker_thread, NULL, run_client, wa) != 0)
    {
      perror("Could not create a worker thread");
      num_clients--;
      free(wa);
      close(clientSocket);
      pthread_exit(NULL);
    }

    // Stop accepting connections if 2-player limit has been reached.
    if (num_clients == 2)
      break;
  }

  if (num_clients == 2)
  {
    // Start running Server Engine cycles upon 2-player connect.
    printf("TWO PLAYERS CONNECTED!\n");
    // Sleep until both clients are ready to render. (using mutex?)
    // Start Physics/Game Engine cycle.
    // Start AI Engine cycle.
    // Start rendering cycle (where network requests objects that each client
    // renders from Physics/Game engine) at around a 60 Hz rate.
  }
  else
  {
    close(serverSocket);
    pthread_mutex_destroy(&lock);
    return 0;
  }
}
