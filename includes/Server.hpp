#ifndef _Server_
#define _Server_

#include "Inclue.hpp"

#include "Function.hpp"
#include "Jsonhandler.hpp"
#include "Date.hpp"
#include "Room.hpp"
#include "Logger.hpp"

class Server
{
public:
    Server();

    void Run();

private:
    int server_fd, new_socket, max_sd, port;
    char buffer[MAX_LEN_MESS] = {0};
    fd_set master_set, working_set;
    json Errors;
    Date date;
    JsonHandler Data;
    bool is_con;
    Logger Log;

    bool SetupServer();

    int AcceptClient(int server_fd);

    bool GetFromBuffer();

    void GiveMessFromClient(int client_fd);

    bool CheckUserInfo(vector<string> user_info);

    string SignupUser(int client_fd, string username, string in_user_info);

    string Recv(int client_fd);

    void Send(int client_fd, string mess);
    
    void CommandHandler(string command_line, int client_fd);

    void PrintError(string error_number) ;

    void HandleRoomsCommand(string user, string command,int client_fd);

    bool CheckBookCommand(string book_command);

    bool CheckCancelCommand(string cancel_command);
};

#endif