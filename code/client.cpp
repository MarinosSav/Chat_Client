#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>
#include <thread>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main(){

    struct sockaddr_in client;
    int buffer_len = 256 , port = 5378, recv_buffer_len = buffer_len, temp;
    WSAData data;
    SOCKET connect_sock = INVALID_SOCKET;
    char recv_buffer[buffer_len] = "" , temp_char;
    string input;
    bool valid = false;

    while(true){
        WSAStartup(MAKEWORD(2,2), &data);

        connect_sock = socket(AF_INET, SOCK_STREAM, 0);

        client.sin_family = AF_INET;
        client.sin_addr.s_addr = inet_addr( "52.59.206.71" );
        client.sin_port = htons(port);

        connect(connect_sock, (SOCKADDR*) &client, sizeof(client));

        char send_buffer[buffer_len] = "HELLO-FROM ";
        cout << "> Enter a username: " << endl;
        getline(cin, input);
        input += '\n';
        strcat(send_buffer, input.c_str());

        send(connect_sock, send_buffer, (int)strlen(send_buffer), 0);
        Sleep(10);

        memset(send_buffer, 0, sizeof(send_buffer));

        temp = recv(connect_sock, recv_buffer, recv_buffer_len, 0);

        if (strstr(recv_buffer, "HELLO") != NULL){
            valid = true;
            cout << recv_buffer << endl;
            break;
        }
        else if (strstr(recv_buffer, "IN-USE") != NULL)
            cout << "[Username in use.]" << endl;
        else
            cout << "[Invalid username.]" << endl;
        memset(recv_buffer, 0, sizeof(recv_buffer));
    }

    while(true){

        cout << "> Available commands: !who, @<username> <msg>, !exit" << endl;

        char send_buffer[buffer_len] = "";
        bool comm = false;

        getline(cin, input);
        if (input == "!who")
            strcpy(send_buffer, "WHO\n");
        else if (input.at(0) == '@'){
            strcpy(send_buffer, "SEND ");
            input.erase(0,1);
            input += '\n';
            strcat(send_buffer, input.c_str());
            comm = true;
        }
        else if (input == "!exit")
            break;
        else{
            closesocket(connect_sock);
            WSACleanup();
            return 1;
        }

        send(connect_sock, send_buffer, (int)strlen(send_buffer), 0);
        Sleep(1);

        memset(send_buffer, 0, sizeof(send_buffer));

        temp = recv(connect_sock, recv_buffer, recv_buffer_len, 0);
        if (temp == 0){
            cout << "Connection closed." << endl;
            break;
        }
        else if (temp > 0){
            cout << recv_buffer;
            if (comm){
                recv(connect_sock, recv_buffer, recv_buffer_len, 0);
                cout << recv_buffer << endl;
            }
            memset(recv_buffer, 0, sizeof(recv_buffer));
        }
        else{
            cout << "There was an error during transmission" << endl;
            closesocket(connect_sock);
            WSACleanup();
            return 1;
        }
    }

    closesocket(connect_sock);
    WSACleanup();

    return 0;
}

