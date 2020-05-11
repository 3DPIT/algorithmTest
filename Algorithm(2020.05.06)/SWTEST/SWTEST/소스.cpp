#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winSock2.h>

#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")

// User and Game Server Information
#define NICKNAME "C Player"
#define HOST "127.0.0.1"
#define PORT 1447 // Do not modify Port Number

void ErrorHandling(char* message);

int main()
{
	// Predefined Variables(Do not modify these values)
	int TABLE_WIDTH = 254;
	int TABLE_HEIGHT = 127;
	int NUMBER_OF_BALLS = 5;
	int HOLES[6][2] = { {0, 0}, {127, 0}, {254, 0}, {0, 127}, {127, 127}, {254, 127} };

	int balls[5][2] = { 0, };

	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN sockAddr;

	char message[50];
	int strLen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup failure.");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (hSocket == INVALID_SOCKET)
		ErrorHandling("Socket Creating Failure.");

	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(HOST);
	sockAddr.sin_port = htons(PORT);

	printf("Trying Connect: %s:%d\n", HOST, PORT);
	if (connect(hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
		ErrorHandling("Connection Failure.");
	else
		printf("Connected: %s:%d\n", HOST, PORT);

	// Send Part
	char sendMessage[50];

	sprintf(sendMessage, "9901/%s", NICKNAME);
	printf("sending data: %s\n", sendMessage);
	send(hSocket, (char*)&sendMessage, sizeof(sendMessage), 0);

	while (1)
	{
		// Receive Part
		strLen = recv(hSocket, message, sizeof(message) - 1, 0);

		char* recvMessage;
		recvMessage = strtok(message, "/");
		int pos = atoi(recvMessage);

		if (pos == 9909) break;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				balls[i][j] = pos;
				recvMessage = strtok(NULL, "/");
				if (recvMessage != NULL)
				{
					pos = atoi(recvMessage);
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				printf("balls[%d][%d] %d\n", i, j, balls[i][j]);
			}
		}

		int angle = 0;
		int power = 0;

		/////////////////////////////////////////////////////////////////////////////////////
		// 주석을 지우고, 이 곳에 주어진 정보를 바탕으로 게임 로직을 구현하여 자동으로 플레이할 수 있도록 구현합니다.
		// 필요한 결괏값은 방향(angle)과 세기(power)로 두 변수의 값이 결정되도록 만들어야 합니다.
		/////////////////////////////////////////////////////////////////////////////////////


		sprintf(sendMessage, "%d/%d", angle, power);
		printf("sending data: %s\n", sendMessage);
		send(hSocket, (char*)&sendMessage, sizeof(sendMessage), 0);
	}

	closesocket(hSocket);
	WSACleanup();

	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}