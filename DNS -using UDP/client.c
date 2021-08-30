#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>  
#define PORT     8080
#define MAXLINE 1024
  
// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char req[100] ;
    struct sockaddr_in     servaddr;
  
    // Creating socket file descriptor
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if ( sockfd < 0 ) 
    {
        printf("socket creation failed");
        exit(EXIT_FAILURE);
    }
  
    bzero(&servaddr,sizeof(servaddr));
      
    // Filling server information
    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
      
    int n, len;
    int c = 1;
    while(c == 1)
    {
    	    printf("\nEnter a Domain name or Ip address \n");
    	    scanf("%s",req);
	    sendto(sockfd, (char *)req, strlen(req),0, (struct sockaddr *) &servaddr,sizeof(servaddr));
	    printf("Request sent.\n");
		  
	    n = recvfrom(sockfd, (char *)buffer, MAXLINE,0, (struct sockaddr *) &servaddr,&len);
	    buffer[n] = '\0';
	    printf("Server : \n%s \n", buffer);
	    printf("Enter 1 to continue \n");
	    scanf("%d",&c);
    }
    strcpy(req,"exit");
    sendto(sockfd, (char *)req, strlen(req),0, (struct sockaddr *) &servaddr,sizeof(servaddr));
    close(sockfd);
    printf("Client Exit... \n");
    return 0;
}
