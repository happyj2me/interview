// #include<stdio.h>
// #include<string.h>
// #include<sys/types.h>
// #include<sys/socket.h>
// #include<arpa/inet.h>
// #include<netdb.h>
// #include<resolv.h>
// #include <unistd.h>

// #include <string>
// #include<stdio.h>
// #include<assert.h>
// char* my_strncpy(char* str1, const char* str2, int num)
// {
// 	assert(str1&&str2);
// 	while (num--)
// 	{
// 		*(str1 + num) = *(str2 + num);
// 	}
// 	return str1;
// }
// int main()
// {
// 	char s1[] = "abcdef";
// 	char s2[] = "abfcde";
// 	printf("%s\n", my_strncpy(s1+2, s2, 3));
//   printf("%s\n", s1);
//   printf("%s\n", s2);
// 	return 0;
// }

// int main()
// {
// 	char* hostname = "master-dev.antvcservice.com";
//   int sockfd = socket(AF_INET,SOCK_DGRAM,0);
//   struct sockaddr_in server;
//   server.sin_family = AF_INET;
//   server.sin_port = htons(17000);

//   struct hostent* dest = gethostbyname(hostname);
//   memcpy((char*)&server.sin_addr.s_addr,(char*)dest->h_addr,dest->h_length);

//   int ret = sendto(sockfd,hostname,strlen(hostname),0,(struct sockaddr*)&server,sizeof(server));
//   printf("sent ret %d\n",ret);
//   close(sockfd);

//   std::string xx = "1,0";
//   int idx = xx.find_first_of("0");
//   printf("idx %d\n",idx);

//   return 0;
// }

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
    int fd1[2],fd2[2];
    pipe(fd1);
    pipe(fd2);
    int32_t * pt = new int32_t();
    *pt = 100;
    if ( fork() ) {
        /* Parent process: echo client */
        int val = 0;

        printf( "parent pt data: %p %d\n", pt,*pt);
        printf( "parent fd1 data: %d %d\n", fd1[0],fd1[1]);
        printf( "parent fd2 data: %d %d\n", fd2[0],fd2[1]);
        close( fd1[0] );
        close(fd2[1]);
        while ( 1 ) {
            sleep( 1 );
            ++val;
            printf( "parent pt data: %p %d\n", pt,*pt);
            printf( "parent Sending data: %d\n", val );
            write( fd1[1], &val, sizeof(val) );
            read( fd2[0], &val, sizeof(val) );
            printf( "parent Data received: %d\n", val );
        }
    }
    else {
        /* Child process: echo server */
        int val ;
        printf( "child pt data: %p %d\n", pt,*pt);
        *pt = 200;
        printf( "child fd1 data: %d %d\n", fd1[0],fd1[1]);
        printf( "child fd2 data: %d %d\n", fd2[0],fd2[1]);
        close( fd1[1] );
        close(fd2[0]);
        while ( 1 ) {
            read( fd1[0], &val, sizeof(val) );
            printf( "son Data received: %d\n", val );
            ++val;
            write( fd2[1], &val, sizeof(val) );
            printf( "son send received: %d\n", val );
            printf( "son pt data: %p %d\n", pt,*pt);
        }
    }
}