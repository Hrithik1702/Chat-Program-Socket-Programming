#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h> 
#define PORT     8080
#define MAXLINE 1024
  
// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char msg[200] = "Not Found";
    struct sockaddr_in servaddr, cliaddr;
      
    // Creating socket file descriptor
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if ( sockfd < 0 ) {
        printf("socket creation failed");
        exit(EXIT_FAILURE);
    }
      
    bzero(&servaddr,sizeof(servaddr));
    bzero(&cliaddr,sizeof(cliaddr));
      
    // Filling server information
    servaddr.sin_family    = PF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
      
    // Bind the socket with the server address
    int b = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (  b < 0 )
    {
        printf("bind failed");
        exit(EXIT_FAILURE);
    }
    int len, n;
     
    len = sizeof(cliaddr);  
    while(1)
    {
    	    strcpy(msg,"Not Found");
	    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, ( struct sockaddr *) &cliaddr,&len);
	    buffer[n] = '\0';
	    if(strcmp(buffer,"exit")==0)
	    {
	    	break;
	    }
	    int flag =1;
	    for(int i=0 ; i<n;i++)
	    {
	    	if(buffer[i]!='.' && !(isdigit(buffer[i])) ) 
	    	{
	    		flag = 0;
	    		break;
	    	}
	    }
	    char fileName[100] = "dns";
	    FILE* file = fopen(fileName, "r"); 
	    if(!file)
	    {
		printf("\n Unable to open : %s ", fileName);
		return -1;
	    }
	    char line[500];
	    char ip[100];
	    char dom[100];
	    char temp[200];
	    while (fgets(line, sizeof(line), file)) 
	    {
	    	 int i = 0;
	         while(i < sizeof(line))
	         {
	         	if( !(isspace(line[i])) )
	         	{
	         	 	dom[i]= line[i];
	         	 	i++;
	         	}
	         	else
	         	{
	         		dom[i]='\0';
	         		i++;
	         		break;
	         	}
	         }

	         int j=0;
	         while(line[i] != '\n')
	         {
	         	 ip[j++]= line[i];
	         	 i++;

	         }
	        ip[j]='\0';

	         if(strcmp(dom,buffer)==0 && flag ==0)
	         {
	         	strcpy(msg,"Ip Address of Given Domain Name : ");
	         	strcat(msg,ip);
	         	break;
	         }
	         else if(strcmp(ip,buffer)==0 && flag ==1)
	         {
	         	strcpy(msg,"Domain Name of Given Ip Address : ");
	         	strcat(msg,dom);
	         	break;
	         }
	         
	    }
	    fclose(file);
	    
	    
	    sendto(sockfd, (char *)msg, strlen(msg), 0, (struct sockaddr *) &cliaddr,len);
	    printf("IP address or Domain sent.\n"); 
    }
    
    printf("Server Exit....\n");
    close(sockfd);
    return 0;
}
