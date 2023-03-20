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
        command = GetCommand();
        send(server_fd, command.c_str(), strlen(command.c_str()), 0);
        string recv_mess = Recv(server_fd);
        is_sign_ok = CheckSign(BreakString(command),recv_mess, server_fd);
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

bool Client::CheckSign(vector<string> command, string recv_mess_from_ser, int server_fd)
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
        Menu(command[1]);
        return false;
    }
    else if (recv_mess_from_ser == "SIGNIN_NOT_OK")
        PrintError("430");

    else if (recv_mess_from_ser == "EXIT_OK")
        return false;

    else
    {
        // Problem in CheckSign func.
        cout << "    --> Problem in Connect to server, Try again ! <--" << endl;
    }

    return true;
}

string Client::GetCommand()
{
    string command = "";
    vector<string> commands;
    while (true)
    {
        getline(cin, command);
        commands = BreakString(command);
        if ((command == "") || (command == " ") || (command == "\n") || (command == "  ") || (command == "\n\n"))
            continue;

        if (commands.size() == 0 || (!((commands[0] == "signup") || (commands[0] == "signin") || (commands[0] == "exit"))))
        {
            PrintError("503");
            cout << "Write Command :\n  --> signin <username> <password>\n  --> signup <username>\n  --> exit\n"
                 << endl;
            continue;
        }

        if (!CheckFirstCommand(command)){
            PrintError("503");
            cout << "Write Command :\n  --> signin <username> <password>\n  --> signup <username>\n  --> exit\n"
                 << endl;
            continue;
        }

        return command;
    }
}

bool Client::CheckFirstCommand(string command){
    vector<string> commands = BreakString(command);
    if (commands[0] == "signup")
    {
        if(commands.size() != 2) return false;
        return true;
    }
    else if (commands[0] == "signin")
    {
        if(commands.size() != 3) return false;
        return true;
    }
    else if (commands[0] == "exit")
    {
        if (commands.size() != 1) return false;
        return true;
    }
    return false;
}

string Client::Recv(int server_fd)
{
    char buffer[MAX_LEN_MESS] = {0};
    memset(buffer, 0, MAX_LEN_MESS);
    recv(server_fd, buffer, MAX_LEN_MESS, 0);
    return string(buffer);
}

void Client::Send(int serevr_fd, string mess)
{
    send(serevr_fd, mess.c_str(), mess.length(), 0);
}

void Client::Menu(string user)
{
    string command;
    while (true)
    {
        cout << endl
             << "      ** Choose Number :  **" << endl
             << "> 1. View User Information" << endl
             << "> 2. View All User" << endl
             << "> 3. View Rooms Information" << endl
             << "> 4. Booking" << endl
             << "> 5. Cancelling" << endl
             << "> 6. Pass Day" << endl
             << "> 7. Edit Information" << endl
             << "> 8. Leaving Room" << endl
             << "> 9. Rooms" << endl
             << "> 0. Logout" << endl
             << "--> " ;
        cin >> command;
        if ((!IsDigit(command)) || (command.length() != 1))
        {
            PrintError("503");
            continue;
        }
        Send(server_fd, command);

        if (command == VIEW_USER_INFO)
        {
            
            Send(server_fd, user);
            string user_info = Recv(server_fd);
            cout << user_info << endl;
        }
        else if (command == VIEW_ALL_USER)
        {
            Send(server_fd, user);

            string is_admin =  Recv(server_fd);

            if (is_admin == "NO")
            {
                PrintError("403");
                continue;;
            }

            string user_information = Recv(server_fd) ;
            cout << user_information << endl;
        }
        else if (command == VIEW_ROOM_INFO){
            Send(server_fd, user);
            string rooms_info ;
            rooms_info = Recv(server_fd);
            cout << rooms_info << endl ;
        }
        else if (command == BOOKING){
            Send(server_fd, user);
            string is_admin =  Recv(server_fd);

            if (is_admin == "YES")
            {
                PrintError("403");
                continue;;
            }
            cout << "Write Command :" << endl 
                << "    book <RoomNuum> <NumOfBeds> <CheckInDate> <CheckOutDate>" << endl 
                <<"--> " ;
            string command;getline(cin, command);
            getline(cin, command);
            Send(server_fd, command);

            string err_num = Recv(server_fd);
            PrintError(err_num);
        }
        else if(command == CANCELING){
            Send(server_fd, user);
            string is_admin =  Recv(server_fd);

            if (is_admin == "YES")
            {
                PrintError("403");
                continue;;
            }
            Send(server_fd, "TEMP");
            string res_info = Recv(server_fd);
            cout << res_info << endl;
            
            cout << "Write Command :" << endl 
                << "    cancel <RoomNuum> <Num>" << endl 
                <<"--> " ;
            string command;getline(cin, command);
            getline(cin, command);
            Send(server_fd, command);
            string err_num = Recv(server_fd);
            PrintError(err_num);
        }
        else if(command == EDIT_INFO){
            Send(server_fd, user);
            string is_admin =  Recv(server_fd);
            string new_info, err_num, temp;
            if (is_admin == "YES")
            {
                cout << "Enter Your New Password -->  " ;
                cin >> new_info;
                Send(server_fd, new_info);
            }
            else
            {
                cout << "Enter Your New Password -->  ";
                cin >> temp;
                new_info = temp + " ";
                cout << "Enter Your New Phone -->  ";
                cin >> temp;
                new_info += temp + " ";
                cout << "Enter Your New Address -->  ";
                cin >> temp;
                new_info += temp;
                Send(server_fd, new_info);
            }
            err_num = Recv(server_fd);
            PrintError(err_num);
        }
        else if (command == ROOMS) {
            Send(server_fd, user);
            string is_admin =  Recv(server_fd);

            if (is_admin == "NO")
            {
                PrintError("403");
                continue;;
            }
            cout << "Write Command :" << endl 
                << "    add <RoomNuum> <Max Capacity> <Price>" << endl 
                << "    modify <RoomNum> <new Max Capacity> <new Price>" << endl
                << "    remove <RoomNum>" << endl <<"--> " ;
            string command;getline(cin, command);
            getline(cin, command);
            
            Send(server_fd, command);

            string err_num = Recv(server_fd);
            PrintError(err_num);
        }
        else if (command == LOGOUT){
            Send(server_fd, user);
            PrintError("201");
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    Client client;
    client.Run();

    return 0;
}