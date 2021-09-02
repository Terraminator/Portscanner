#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <locale>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <thread>

using namespace std;
#pragma comment(lib,"ws2_32.lib")





class EasySock {
public:
    WSADATA wsaData;
    SOCKET Socket;
    SOCKADDR_IN SockAddr;
    struct hostent* host;
    struct sockaddr_in server, client;
    locale local;
    char buffer[1024];
    string response = "";
    string sip;
    unsigned int port;
    int response_length;


    EasySock(string in_ip, int in_port) {
        int lineCount = 0;
        int rowCount = 0;

        sip = in_ip;
        char ip[50]{};
        unsigned int i;
        for (i = 0; i < sip.length() + 1; i++) {
            ip[i] = sip[i];
        }

        port = in_port;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            cout << "WSAStartup failed." << endl;
            system("pause");
        }

        Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        SockAddr.sin_port = htons(port);
        SockAddr.sin_family = AF_INET;
        SockAddr.sin_addr.s_addr = inet_addr(ip);

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(ip);
        server.sin_port = htons(4444);
    }

    int connect_to_target() {
        if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
            return(1);
        }
        return(0);
    }

    void send_to_target(string raw) {
        send(Socket, raw.c_str(), strlen(raw.c_str()), 0);
    }

    int bind_to() {
        if (bind(Socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
        {
            return(1);
        }
        return(0);
    }

    int listen_for_clients(int i) {
        listen(Socket, i);
        return(0);
    }

    int accept_clients() {
        int c = sizeof(struct sockaddr_in);
        Socket = accept(Socket, (struct sockaddr*)&client, &c);
        if (Socket == INVALID_SOCKET)
        {
            return(1);
        }
        return(0);
    }

    void free_buffer() {
        memset(buffer, 0, sizeof(buffer));
    }

    string recv_response() {
        int timeout = 1000;
        setsockopt(Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(int));
        while ((response_length = recv(Socket, buffer, 1024, 0)) > 0) {
            cout << "Response len: " << response_length << endl;
            cout << "Buffer: " << buffer << endl;
            response += string(buffer);
        }
        string rresponse = response;
        response = "";
        response_length = 0;
        free_buffer();
        return(rresponse);
    }

    string recv_long_response(int timeout) {
            setsockopt(Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(int));
            while ((response_length = recv(Socket, buffer, 1024, 0)) > 0) {
                response += string(buffer);
            }
            string rresponse = response;
            response = "";
            response_length = 0;
            return(rresponse);

    }

    void clean_up() {
        closesocket(Socket);
        WSACleanup();
    }

};