#ifndef SOCKET_H
#define SOCKET_H

#include "data_collect.h"

// 서버에 대한 소켓 연결을 설정하는 함수
int setup_server_connection(char* SERVER_IP);

// 데이터 패킷을 서버에 전송하는 함수
int send_data_to_server(int sock, DataPacket *packet);

// 데이터 전송 및 재연결 로직 함수
int send_data_with_reconnect(int sock, DataPacket *packet,char* SERVER_IP);

// 데이터 출력 함수
void print_data(const DataPacket *packet);

#endif // SOCKET_H
