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
    User *currUser;

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
        cout << "comman1 : " << command[1] << endl; // << "*** command2 : " << command[2] << endl;
        if (Data.IsUserExist(command[1]))
        {
            if (Data.FindUserByName(command[1])->IsPassCorrect(command[2]))
            {
                Send(client_fd, "SIGNIN_OK");
            }

            currUser = Data.FindUserByName(command[1]);
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
    else if (command[0] == "1")
    {
        string user = Recv(client_fd);
        User *user_ptr = Data.FindUserByName(user);
        Send(client_fd, user_ptr->GerUserInfo());
    }
    else if (command[0] == "2")
    {
        string user = Recv(client_fd);

        User *user_ptr = Data.FindUserByName(user);
        if (!user_ptr->is_admin())
        {
            Send(client_fd, "NO");
            return;
        }

        Send(client_fd, "YES" );
        sleep(1);

        vector<User *> users = Data.get_users();
        string users_info;
        for (int i = 0 ; i < users.size() ; i++)
        {
            users_info += users[i]->GerUserInfo();
        }
        Send(client_fd, users_info);
    }
    else if (command[0] == "3"){
        string user = Recv(client_fd);
        User *user_ptr = Data.FindUserByName(user);
        bool is_admin = user_ptr->is_admin();
        vector<Room*> rooms = Data.get_rooms();
        string rooms_info;
        for(int i = 0 ; i < rooms.size() ; i++){
            rooms_info += rooms[i]->GetInfoRoom(is_admin);
        }
        Send(client_fd, rooms_info);
    }
    else if (command[0] == "9"){
        string user = Recv(client_fd);
        User *user_ptr = Data.FindUserByName(user);
        if (!user_ptr->is_admin())
        {
            Send(client_fd, "NO");
            return;
        }
        Send(client_fd, "YES" );
        string recv_command = Recv(client_fd);
        HandleRoomsCommand(recv_command, client_fd);
    }

    else if (command[0] == "4")
    {
        string bookCommand;
        string numOfRoom;
        int numOfBed;
        string reserveDate;
        string checkoutDate;

        cin >> bookCommand >> numOfRoom >> numOfBed >> reserveDate >> checkoutDate;

        Room *tempRoom = Data.FindRoom(numOfRoom);
        Date *reservationDate = new Date(reserveDate);

        if (bookCommand != "book")
        {
            Send(client_fd, "Invalid Input");
        }

        if (tempRoom != nullptr)
        {

            if (tempRoom->checkCapacity(*reservationDate) >= numOfBed)
            {

                if (currUser->getPurse() >= numOfBed * tempRoom->getPrice())
                {
                    tempRoom->reserve(currUser->GetId(), numOfBed, reserveDate, checkoutDate);
                    currUser->payment(numOfBed * tempRoom->getPrice());
                    Send(client_fd, "Successfully reserved");
                }
                else
                {
                    Send(client_fd, "Not enough balance!");
                }
            }
            else
            {

                Send(client_fd, "Not enough capacity!");
            }
        }
        else
        {
            Send(client_fd, "Room Not Found!");
        }
    }
    else if (command[0] == "5")
    {
        Data.printUserReservations(currUser->GetId());
        string cancelCommand;
        string roomNum;
        int num;
        cin >> cancelCommand >> roomNum >> num;
        Room* tempRoom = Data.FindRoom(roomNum);

        if (cancelCommand != "cancel")
        {
            Send(client_fd, "Invalid Input");
        }

        if (tempRoom->cancelReservation(currUser->GetId(), num))
        {
            currUser->payback((num * tempRoom->getPrice()) / 2);
            Send(client_fd, "Successfully Canceled");
        }
        else
        {
            Send(client_fd, "There is no such a reservation");
        }
    }
    else if (command[0] == "6")
    {
        string passCommand;
        int value;
        cin >> passCommand >> value;

        if (currUser->is_admin())
        {
            for (int i = 0; i < value; i++)
            {
                date.PassDay();
                Data.checkCheckouts(date);
            }
            Send(client_fd, "Done");
        }
        else
        {
            Send(client_fd, "Invalid Request");
        }
    }
    else if (command[0] == "7")
    {
        string editCommand;

        if (currUser->is_admin())
        {
            string newPass;
            cout << "<new password>";
            cin >> newPass;
            currUser->editInfo(newPass);

            cout << "Succussfully edited" << endl;
        }
        else
        {
            string newPass;
            string newPhone;
            string newAddress;
            int newPurse;

            cout << "<new password>";
            cin >> newPass;
            cout << "<new phone>";
            cin >> newPhone;
            cout << "<new address>";
            cin >> newAddress;
            cout << "<new purse>";
            cin >> newPurse;

            //currUser->editInfo(newPass, newPurse, newPhone, newAddress);
            dynamic_cast<NormalUser*> (currUser)->editInfo(newPass, newPurse, newPhone, newAddress);


            cout << "Succussfully edited" << endl;
        }
    }
    else if (command[0] == "8")
    {
        string leaveCommand;
        string value;

        cout << "room <Room Number>";
        cin >> leaveCommand >> value;

        Room *tempRoom = Data.FindRoom(value);

        if (tempRoom == nullptr)
        {
            Send(client_fd, "503 : Invalid Input");
        }
        else if (tempRoom->leaveRoom(currUser->GetId()))
        {
            Send(client_fd, "403 : OK");
        }
        else
        {
            Send(client_fd, "102 : Invalid Input");
        }
    }

    else if (command[0] == "10")
    {
    }
}

void Server::HandleRoomsCommand(string command, int client_fd){
    
    vector<string> commands = BreakString(command);
    if (commands.size() < 2) {
        Send(client_fd, "503");
        return;
    }
    Room *room = Data.FindRoom(commands[1]);
    if (commands[0] == "add")
    {
        if (room != NULL)
        {
            Send(client_fd, "111");
            return;
        }

        vector<ResUserInfo *> temp ;
        Room *r = new Room(commands[1], 0, stoi(commands[3]), stoi(commands[2]), 0, temp);
        Data.AddNewRoom(r);
        Send(client_fd, "104");
    }
    else if (commands[0] == "modify")
    {
        if (room == NULL) // there is not room
        {
            Send(client_fd, "101");
            return;
        }
        if ((room->getCapacity() == 0) || (stoi(commands[2]) < room->GetMaxCapacity() - room->getCapacity())) // room is full or we cant remove any body
        {
            Send(client_fd, "109");
            return;
        }
        room->ModifyRoom(stoi(commands[2]), stoi(commands[3]));
        room->CheckStatus();
        Send(client_fd, "105");
    }
    else if (commands[0] == "remove"){
        if (room == NULL) // there is not room
        {
            Send(client_fd, "101");
            return;
        }
        if ( room->GetMaxCapacity() - room->getCapacity() > 0 ) 
        {
            Send(client_fd, "109");
            return;
        }
        Data.RemoveRoom(room->getNum());
        Send(client_fd, "106");
    }
    else {
        Send(client_fd, "503");
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