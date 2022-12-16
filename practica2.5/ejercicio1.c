// STANDARD
#include <stdlib.h>
// GETADDRINFO
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
// MANUAL
#include <stdio.h>
#include <unistd.h>
#include <string.h>
 
#define BUF_SIZE 500
 
int main(int argc, char *argv[]) {
 
   struct addrinfo *result, *rp;
   int sfd, s;
 
   if (argc != 2) {
       fprintf(stderr, "Usage: %s ip\n", argv[0]);
       exit(EXIT_FAILURE);
   }
 
   struct addrinfo hints;
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
   hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
   hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
   hints.ai_protocol = 0;          /* Any protocol */
   hints.ai_canonname = NULL;
   hints.ai_addr = NULL;
   hints.ai_next = NULL;
 
   s = getaddrinfo(argv[1], NULL, &hints, &result);
   if (s != 0) {
       fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
       exit(EXIT_FAILURE);
   }
  
   /*
       getaddrinfo() returns a list of address structures. Try each address until we
       successfully bind(2). If socket(2) (or bind(2)) fails, we (close the socket and)
       try the next address.
   */
 
   for (rp = result; rp != NULL; rp = rp->ai_next) {
       sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
       if (sfd == -1)
           continue;
 
       if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
           switch (rp->ai_family) {
               case AF_INET: {
                   struct sockaddr_in *sock = rp->ai_addr;
                   printf("DIR: %s\n","fd");
 
               } break;
               case AF_INET6: {
                   struct sockaddr_storage peer_addr;
                   socklen_t peer_addr_len;
                   char host[NI_MAXHOST], service[NI_MAXSERV];
 
                   peer_addr_len = sizeof(struct sockaddr_storage);
                   nread = recvfrom(sfd, buf, BUF_SIZE, 0,
                       (struct sockaddr *) &peer_addr, &peer_addr_len);
 
                   if (nread == -1)
                       continue;               /* Ignore failed request */
 
                   s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len,
                       host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST);
                   if (s == 0)
                       printf("Received %ld bytes from %s:%s\n",
                           (long) nread, host, service);
               } break;
           }
 
           printf("FAM: %i\nTYP: %i\n", rp->ai_family,rp->ai_socktype);
           break;                  /* Success */
 
       }
 
       close(sfd);
   }
 
   if (rp == NULL) {               /* No address succeeded */
       fprintf(stderr, "Could not bind\n");
       exit(EXIT_FAILURE);
   }
 
   freeaddrinfo(result);           /* No longer needed */
 
   return 0;
}
