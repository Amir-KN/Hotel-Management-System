#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <vector>
#define MAX_LEN_MESS 128

using namespace std;

class Client
{
public:
    Client()
    {
        ip = "127.0.0.1";
        port = 8000;
    }

    void Run()
    {
        ConnectToServer();
        string command;
        bool exit_or_not;
        while (true)
        {
            cout << "Write Command :\n  --> signin <username> <password>\n  --> signup <username>\n  --> exit\n"
                 << endl;
            cin >> command ;
            send(server_fd, command.c_str(), strlen(command.c_str()), 0);
            string recv_mess = Recv(server_fd);
            cout << recv_mess << endl;
            exit_or_not = ExitorNot(recv_mess);
            if (exit_or_not)
                break;
        }
    }

private:
    int server_fd;
    int port;
    string ip;

    void ConnectToServer()
    {
        struct sockaddr_in server_address;

        server_fd = socket(AF_INET, SOCK_STREAM, 0);

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        { // checking for errors
            cout << "Fail to connect server !" << endl;
        }
    }

    

    string Recv(int server_fd)
    {
        char buffer[MAX_LEN_MESS] = {0};
        memset(buffer, 0, MAX_LEN_MESS);
        recv(server_fd, buffer, MAX_LEN_MESS, 0);
        return string(buffer);
    }

    bool ExitorNot(string mess){
        if (mess == "exit")
            return true;
        else   
            return false;
    }


};

int main(int argc, char const *argv[])
{
    Client client;
    client.Run();

    return 0;
}