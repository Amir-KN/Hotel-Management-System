#include "includes/Client.hpp"

Client::Client()
{
    ifstream C("JsonFiles/config.json"), E("JsonFiles/Errors.json");
    json Config;

    Config = json::parse(C);
    Errors = json::parse(E);

    ip = Config["hostName"].get<string>();
    port = Config["commandChannelPort"].get<int>();
}

void Client::Run()
{
    ConnectToServer();
    string command;
    bool is_sign_ok;
    while (true)
    {
        cout << "Write Command :\n  --> signin <username> <password>\n  --> signup <username>\n  --> exit\n"
             << endl;
        command = GetFirstCommand();
        send(server_fd, command.c_str(), strlen(command.c_str()), 0);
        string recv_mess = Recv(server_fd);
        is_sign_ok = CheckSign(recv_mess, server_fd);
        if (!is_sign_ok)
            break;
    }
}

void Client::PrintError(string error_number)
{
    string fail = "Failed to read Error number " + error_number;
    cout << Errors.value(error_number, fail) << endl;
}

void Client::ConnectToServer()
{
    struct sockaddr_in server_address;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    { // checking for errors
        PrintError("404");
    }
}

string Client::GetUserInfo()
{
    string command = "", word;
    for (int i = 0; i < 4; i++)
    {
        cin >> word;
        command += word + " ";
    }
    cout << "*** " << command << " ***" << endl;
    ;
    return command;
}

bool Client::CheckSign(string recv_mess_from_ser, int server_fd)
{
    string error_number;

    if (recv_mess_from_ser == "SIGNUP_OK")
    {
        PrintError("311");
        string user_info = GetUserInfo();
        send(server_fd, user_info.c_str(), user_info.length(), 0);
        error_number = Recv(server_fd);
        PrintError(error_number);
    }
    else if (recv_mess_from_ser == "SIGNUP_NOT_OK")
    {
        PrintError("451");
    }

    else if (recv_mess_from_ser == "SIGNIN_OK")
    {
        PrintError("230");
        Menu();
    }
    else if (recv_mess_from_ser == "SIGNIN_NOT_OK")
        PrintError("430");

    else if (recv_mess_from_ser == "EXIT_OK")
        return false;

    else
    {
        // Problem in CheckSign func.
        cout << "Problem in CheckSign func." << endl;
    }

    return true;
}

string Client::GetFirstCommand()
{
    string command = "";
    vector<string> commands;
    while (true)
    {
        getline(cin, command);
        commands = BreakString(command);
        if ((command == "") || (command == " ") || (command == "\n") || (command == "  "))
            continue;
        if (commands.size() == 0 || (!((commands[0] == "signup") || (commands[0] == "signin") || (commands[0] == "exit"))))
        {
            cout << "Invalid Command" << endl;
            continue;
        }
        return command;
    }
}

string Client::Recv(int server_fd)
{
    char buffer[MAX_LEN_MESS] = {0};
    memset(buffer, 0, MAX_LEN_MESS);
    recv(server_fd, buffer, MAX_LEN_MESS, 0);
    return string(buffer);
}

void Client::Menu()
{
    cout << "IN MENU" << endl;
}

int main(int argc, char const *argv[])
{
    Client client;
    client.Run();

    return 0;
}