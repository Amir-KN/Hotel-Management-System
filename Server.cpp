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
#include <string>
#include <sstream>
#include <vector>
#include "includes/json.hpp"

using namespace std;
using json = nlohmann::json;

#define MAX_LEN_MESS 512


vector<string> BreakString(string str)
{
    stringstream ss(str);
    string word;
    vector<string> words;

    while (ss >> word)
        words.push_back(word);
    return words;
}

class Server
{
public:
   Server(){
        ifstream C("includes/config.json"), E("includes/Errors.json");
        json Config;

        Config = json::parse(C);
        Errors = json::parse(E);

        port = Config["commandChannelPort"].get<int>();
    }

    void Run()
    {
        SetupServer();
        char buffer[1024] = {0};

        FD_ZERO(&master_set);
        max_sd = server_fd;
        FD_SET(server_fd, &master_set);
        FD_SET(fileno(stdin), &master_set);

        write(1, "*** Welcome to Hotel Management System ***\nPlese set time\n", 59);

        while (true)
        {
            working_set = master_set;
            select(max_sd + 1, &working_set, NULL, NULL, NULL);

            for (int i = 0; i <= max_sd; i++)
            {
                if (FD_ISSET(i, &working_set))
                {
                    if (i == 0)
                    { // get input from user with command
                        GetFromBuffer();
                    }

                    else if (i == server_fd)
                    { // new clinet
                        new_socket = AcceptClient(server_fd);
                        FD_SET(new_socket, &master_set);
                        if (new_socket > max_sd)
                            max_sd = new_socket;
                        cout << "New Client Connected. fd = " << new_socket << endl;
                    }

                    else
                    { // recv message from client
                        GiveMessFromClient(i);
                    }
                }
            }
        }
    }

private:
    int server_fd, new_socket, max_sd, port;
    char buffer[MAX_LEN_MESS] = {0};
    fd_set master_set, working_set;
    json Errors;

    void SetupServer()
    {
        struct sockaddr_in address;
        server_fd = socket(AF_INET, SOCK_STREAM, 0);

        int opt = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        bind(server_fd, (struct sockaddr *)&address, sizeof(address));

        listen(server_fd, 4);
    }

    int AcceptClient(int server_fd)
    {
        int client_fd;
        struct sockaddr_in client_address;
        int address_len = sizeof(client_address);
        client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t *)&address_len);
        return client_fd;
    }


    void GetFromBuffer()
    {
        
        memset(buffer, 0, MAX_LEN_MESS);
        read(0, buffer, MAX_LEN_MESS);
        // handle set time
    }

    void GiveMessFromClient(int client_fd)
    {
        int bytes_received;
        memset(buffer, 0, MAX_LEN_MESS);
        bytes_received = recv(client_fd, buffer, 1024, 0);

        if (bytes_received == 0)
        { // EOF
            printf("client fd = %d closed\n", client_fd);
            close(client_fd);
            FD_CLR(client_fd, &master_set);
            return;
        }

        printf("client %d: %s\n", client_fd, buffer);
        CommandHandler(string(buffer), client_fd);
    }

    string Recv(int client_fd)
    {
        memset(buffer, 0, MAX_LEN_MESS);
        recv(client_fd, buffer, MAX_LEN_MESS, 0);
        return string(buffer);
    }

    void CommandHandler(string command_line, int client_fd)
    {
        vector<string> command = BreakString(command_line);

        if (command[0] == "signup")
        {
            /*
            if (username exist)
                send("SIGNUP_NOT_OK")

            if (username not exist) {
                send("SIGNUP_OK");
                recv()
                bool is_info_ok = check_recv()
                if (recv is ok)
                    send("231")
                else
                    send("503")


                save info of new use in json;
            }

            */
            // delete 3 line below
            send(client_fd, "SIGNUP_OK", 10, 0);
            Recv(client_fd);
            send(client_fd, "231", 10, 0);
        }

        else if (command[0] == "signin")
        {
            /*
            if (ok) :
                send("SIGNIN_OK")

            send(client_fd, "--> signin command is recved from client <--", 45, 0);
            */

            // delete line below
            send(client_fd, "SIGNIN_OK", 10, 0);
        }

        else if (command[0] == "exit")
        {
            send(client_fd, "EXIT_OK", 8, 0);
        }
    }
};


int main(int argc, char const *argv[])
{
    Server Server;
    Server.Run();

    return 0;
}