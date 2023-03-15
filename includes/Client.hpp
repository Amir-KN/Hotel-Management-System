#ifndef _Client_
#define _Client_
#include "Inclue.hpp"
#include "Function.hpp"

class Client
{
public:
    Client();

    void Run();

private:
    int server_fd;
    int port;
    string ip;
    json Errors;

    void PrintError(string error_number);
    void ConnectToServer();

    string GetUserInfo();

    bool CheckSign(vector<string> command, string recv_mess_from_ser, int server_fd);

    string GetCommand();

    string Recv(int server_fd);

    void Send(int serevr_fd, string mess);

    void Menu(string user);
};


#endif