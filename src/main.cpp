#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<resolv.h>
#include <unistd.h>

#include <string>
int main()
{
	char* hostname = "master-dev.antvcservice.com";
  int sockfd = socket(AF_INET,SOCK_DGRAM,0);
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(17000);

  struct hostent* dest = gethostbyname(hostname);
  memcpy((char*)&server.sin_addr.s_addr,(char*)dest->h_addr,dest->h_length);

  int ret = sendto(sockfd,hostname,strlen(hostname),0,(struct sockaddr*)&server,sizeof(server));
  printf("sent ret %d\n",ret);
  close(sockfd);

  std::string xx = "1,0";
  int idx = xx.find_first_of("0");
  printf("idx %d\n",idx);

  return 0;
}
