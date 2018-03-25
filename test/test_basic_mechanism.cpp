#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char ** argv)
{

	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	char readBuff[1025];
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(readBuff, '0', sizeof(readBuff));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);
	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	listen(listenfd, 10);
	while(1)
	{
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);		std::cout << "connected" << std::endl;
		//요청 받음
		recv(connfd, readBuff, 1025, NULL);
		/*
			... 요청 분석 준비 ...
		*/
		
		std::cout << readBuff << std::endl;

		
		/*
			... 응답 코드 준비 ...
		*/
		char writeBuff[2048] = R"end(HTTP/1.1 200 OK
Date: Sun, 28 Jul 2018 15 : 37 : 37 GMT
Server : KijunKim
Last - Modified : Sun, 07 Jul 2013 06 : 13 : 43 GMT
Transfer - Encoding : chunked
Connection : Keep - Alive
Content - Type : text / html; charset = UTF - 8
)end";

		//응답 보냄
		std::cout << writeBuff << std::endl;
		send(connfd, writeBuff, 2048, NULL);

		
		//요청한 파일 준비
		memset(writeBuff, 0x00, 2048);
		sprintf(writeBuff, "<h2>sdasdasdasD<p>test");

		
		//요청한 파일 전송
		std::cout << writeBuff << std::endl;
		send(connfd, writeBuff, 2048, NULL);

		
		//종료
		close(connfd);
		sleep(1);
	}
}