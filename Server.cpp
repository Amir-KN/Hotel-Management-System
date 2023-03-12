#include "includes/Server.hpp"

Server::Server()
{
    ifstream C("JsonFiles/config.json"), E("JsonFiles/Errors.json");
    json Config;

    Config = json::parse(C);
    Errors = json::parse(E);

    port = Config["commandChannelPort"].get<int>();

    is_con = true;
}

void Server::Run()
{
    SetupServer();
    char buffer[1024] = {0};

    FD_ZERO(&master_set);
    max_sd = server_fd;
    FD_SET(server_fd, &master_set);
    FD_SET(fileno(stdin), &master_set);

    cout << "*** Welcome to Hotel Management System ***" << endl;

    while (is_con)
    {
        working_set = master_set;
        cout << "> Write Command:\n   --> settime: <setTime> <Date>\n   --> Close server: Exit" << endl;
        select(max_sd + 1, &working_set, NULL, NULL, NULL);

        for (int i = 0; i <= max_sd; i++)
        {
            if (FD_ISSET(i, &working_set))
            {
                if (i == 0)
                { // get input from user with command
                    is_con = GetFromBuffer();
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

void Server::SetupServer()
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

int Server::AcceptClient(int server_fd)
{
    int client_fd;
    struct sockaddr_in client_address;
    int address_len = sizeof(client_address);
    client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t *)&address_len);
    return client_fd;
}

bool Server::GetFromBuffer()
{
    memset(buffer, 0, MAX_LEN_MESS);
    read(0, buffer, MAX_LEN_MESS);
    vector<string> command = BreakString(string(buffer));
    if (command.size() == 1)
        command[0].pop_back();

    if (command[0] == "setTime")
    {
        command[1].pop_back();
        if (CheckDate(command[1]))
        {
            date.SetTime(command[1]);
            PrintError("600");
        }
        else
            PrintError("401");
        return true;
    }
    else if (command[0] == "exit")
    {
        return false;
    }
    else
    {
        PrintError("503");
        return true;
    }
}

void Server::GiveMessFromClient(int client_fd)
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

bool Server::CheckUserInfo(vector<string> user_info)
{
    if (user_info.size() != 4)
        return false;
    if ((!IsDigit(user_info[1])) || (!IsDigit(user_info[2])))
        return false;

    return true;
}

string Server::SignupUser(int client_fd, string username, string in_user_info)
{
    vector<string> user_info = BreakString(in_user_info);
    if (CheckUserInfo(user_info)) // input is correct
    {
        int new_id = Data.GetNewId();
        cout << user_info.size() << endl;
        NormalUser *new_user = new NormalUser(new_id, username, user_info[0], user_info[1], user_info[2], user_info[3]);
        Data.AddNewUser(new_user);
        return "231";
    }

    return "503";
}

string Server::Recv(int client_fd)
{
    memset(buffer, 0, MAX_LEN_MESS);
    recv(client_fd, buffer, MAX_LEN_MESS, 0);
    return string(buffer);
}

void Server::Send(int client_fd, string mess)
{
    send(client_fd, mess.c_str(), mess.length(), 0);
}

void Server::CommandHandler(string command_line, int client_fd)
{
    vector<string> command = BreakString(command_line);

    if (command[0] == "signup")
    {
        if (Data.IsUserExist(command[1]))
            Send(client_fd, "SIGNUP_NOT_OK");
        else
        {
            Send(client_fd, "SIGNUP_OK");
            string UserInfo = Recv(client_fd);
            string error_num = SignupUser(client_fd, command[1], UserInfo);
            Send(client_fd, error_num);
        }
    }

    else if (command[0] == "signin")
    {
        if (Data.IsUserExist(command[1]))
        {
            if (Data.FindUserByName(command[1])->IsPassCorrect(command[2]))
                Send(client_fd, "SIGNIN_OK");
        }
        else
        {
            Send(client_fd, "SIGNIN_NOT_OK");
        }
    }

    else if (command[0] == "exit")
    {
        Send(client_fd, "EXIT_OK");
    }
}

void Server::PrintError(string error_number)
{
    string fail = "Failed to read Error number " + error_number;
    cout << Errors.value(error_number, fail) << endl;
}


int main(int argc, char const *argv[])
{
    Server Server;
    Server.Run();

    return 0;
}