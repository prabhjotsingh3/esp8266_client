#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/in.h>

const char A[5] = {0x7e,0x11,0x11,0x11,0x7e};
const char B[5] = {0x7f,0x49,0x49,0x49,0x36};
const char C[5] = {0x3e,0x41,0x41,0x41,0x22};
const char D[5] =  {0x7f,0x41,0x41,0x22,0x1c};
const char E[5] = {0x7f,0x49,0x49,0x49,0x41};
const char F[5] = {0x7f,0x09,0x09,0x01,0x01};
const char G[5] = {0x3e,0x41,0x51,0x51,0x72};
const char H[5] = {0x7f,0x08,0x08,0x08,0x7f};	
const char I[5] = {0x41,0x41,0x7f,0x41,0x41};
const char J[5] = {0x20,0x40,0x41,0x3f,0x01};
const char K[5] = {0x7f,0x08,0x14,0x22,0x41};
const char L[5] = {0x7f,0x40,0x40,0x40,0x40};
const char M[5] = {0x7f,0x02,0x0C,0x02,0x7f};
const char N[5] = {0x7f,0x04,0x08,0x10,0x7f};
const char O[5] = {0x3e,0x41,0x41,0x41,0x3e};
const char P[5] = {0x7f,0x9,0x09,0x09,0x06};
const char Q[5] = {0x3e,0x41,0x51,0x21,0x5e};
const char R[5] = {0x7f,0x09,0x19,0x29,0x46};
const char S[5] = {0x46,0x49,0x49,0x49,0x31};
const char T[5] = {0x01,0x01,0x7f,0x01,0x01};
const char U[5] = {0x3f,0x40,0x40,0x40,0x3f};	
const char V[5] = {0x1f,0x20,0x40,0x20,0x1f};
const char W[5] = {0x3f,0x40,0x38,0x40,0x3f};
const char X[5] = {0x63,0x14,0x08,0x14,0x63};	
const char Y[5] = {0x07,0x08,0x70,0x08,0x07};
const char Z[5] = {0x61,0x51,0x49,0x45,0x43};
const char blank[5] = {0,0,0,0,0};

const char *alphabets[26] = {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};

enum color {
	red,
	green,
	blue
};

int sendChar(int sock_fd, unsigned char ch, enum color cl) {
	char buff[15] = {0};
	int i;

	for(i = 0; i < 5; i++) {
		buff[cl + i*3] = alphabets[ch-0x41][i];
	}
#if 0
	for(i = 0; i < 15; i++) {
		printf("%x\t",buff[i]);
	}
	printf("\n");
#endif
	return write(sock_fd,buff,sizeof(buff));
}

int main(int argc, char *argv[]) {

	int i,sock_fd;
	char *str = "PRABHJOT";
	char svr_ip_addr[15];
	unsigned int svr_port = 0;
	struct sockaddr_in svr_addr;

	if(argc < 3) {
		printf("Usage : ./esp8266_client <server-ip-address> <server-port-no\n");
		return 0;
	}

	strcpy(svr_ip_addr,argv[1]);
	sscanf(argv[2],"%u",&svr_port);

	printf("Server IP Address : %s\tPort No. : %d\n",svr_ip_addr,svr_port);


	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd == -1) {
		perror("socket() ");
		return -1;
	}
	
	memset(&svr_addr, '0', sizeof(svr_addr));
       	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(svr_port);
	if(inet_aton(svr_ip_addr,&svr_addr.sin_addr) == 0) {
		perror("inet_aton() ");
		close(sock_fd);
		return -1;
	}

	if(connect(sock_fd,(const struct sockaddr *)&svr_addr,sizeof(svr_addr)) == -1) {
		perror("connect() ");
		close(sock_fd);
		return -1;
	}

	printf("Connected to ESP8266 server successfully..\n");
	
	for( i = 0; str[i] != '\0'; i++) {
		sendChar(sock_fd,str[i],blue);
		sleep(1);
	}	

	close(sock_fd);

	return 0;
}
