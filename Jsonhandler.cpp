#include "includes/Jsonhandler.hpp"

ResUserInfo::ResUserInfo(int _id, int _num_of_beds, string _res_date, string _checkout_date)
{
    id = _id;
    num_of_beds = _num_of_beds;
    res_date = _res_date;
    checkout_date = _checkout_date;
}

void ResUserInfo::PrintResInfo()
{
    cout << "id : " << id << endl
         << "Number Of Beds : " << num_of_beds << endl
         << "Reserve Date : " << res_date << endl
         << "checkout Date : " << checkout_date << endl;
}

User::User(int _id, string _user, string _pass)
{
    id = _id;
    user = _user;
    password = _pass;
}

string User::get_user() { return user; }

bool User::IsPassCorrect(string in_pass)
{
    return in_pass == password;
}

int User::GetId() { return id; }

Admin::Admin(int _id, string _user, string _pass) : User(_id, _user, _pass){};

void Admin::print_user()
{
    cout << "id : " << id << endl
         << "user : " << user << endl
         << "password : " << password << endl;
}

bool Admin::is_admin() { return true; }

NormalUser::NormalUser(int _id, string _user, string _pass, string _purse, string _phoneNumber, string _address)
    : User(_id, _user, _pass)
{
    purse = _purse;
    phoneNumber = _phoneNumber;
    address = _address;
}

void NormalUser::print_user()
{
    cout << "id : " << id << endl
         << "user : " << user << endl
         << "password : " << password << endl
         << "pursr : " << purse << endl
         << "phoneNumber : " << phoneNumber << endl
         << "address : " << address << endl;
}

bool NormalUser::is_admin() { return false; }

Room::Room(string _number, int _status, int _price, int _maxCapacity, int _capacity, vector<ResUserInfo *> _users)
{
    number = _number;
    status = _status;
    price = _price;
    maxCapacity = _maxCapacity;
    capacity = _capacity;
    users = _users;
}

void Room::print_room()
{
    cout << "number : " << number << endl
         << "status : " << status << endl
         << "price : " << price << endl
         << "maxCapacity : " << maxCapacity << endl
         << "capacity : " << capacity << endl
         << endl;
}

vector<ResUserInfo *> Room::get_users() { return users; }

JsonHandler::JsonHandler()
{
    ifstream room_file("JsonFiles/RoomsInfo.json");
    ifstream user_file("JsonFiles/UsersInfo.json");
    room_file >> room_data;
    user_file >> user_data;
    room_data = room_data["rooms"];
    user_data = user_data["users"];

    read_room();
    read_user();
}

void JsonHandler::read_room()
{
    string number;
    int status, price, maxCapacity, capacity;
    vector<ResUserInfo *> users;
    for (auto &room : room_data)
    {
        number = room["number"].get<string>();
        status = room["status"].get<int>();
        price = room["price"].get<int>();
        maxCapacity = room["maxCapacity"].get<int>();
        capacity = room["capacity"].get<int>();
        users = read_users_of_room(room["users"]);

        Room *r = new Room(number, status, price, maxCapacity, capacity, users);
        all_room.push_back(r);
    }
}

void JsonHandler::read_user()
{
    int id;
    string username, pass, admin, purse, phone, add;

    for (auto &user : user_data)
    {
        id = user["id"].get<int>();
        username = user["user"].get<string>();
        pass = user["password"].get<string>();
        admin = user["admin"].get<string>();
        if (admin == "true")
        {
            Admin *new_admin = new Admin(id, username, pass);
            all_user.push_back(new_admin);
        }
        else
        {
            purse = user["purse"].get<string>();
            phone = user["phoneNumber"].get<string>();
            add = user["address"].get<string>();
            NormalUser *new_user = new NormalUser(id, username, pass, purse, phone, add);
            all_user.push_back(new_user);
        }
    }
}

vector<ResUserInfo *> JsonHandler::read_users_of_room(json users)
{
    vector<ResUserInfo *> result;
    int id, num_of_beds;
    string res_date, check_date;
    for (auto &user : users)
    {

        id = user["id"].get<int>();
        num_of_beds = user["numOfBeds"].get<int>();
        res_date = user["reserveDate"].get<string>();
        check_date = user["checkoutDate"].get<string>();

        ResUserInfo *r = new ResUserInfo(id, num_of_beds, res_date, check_date);
        result.push_back(r);
    }
    return result;
}

vector<User *> JsonHandler::get_users() { return all_user; }

vector<Room *> JsonHandler::get_rooms() { return all_room; }

User *JsonHandler::FindUserByName(string in_user)
{
    for (User *user : all_user)
    {
        if (user->get_user() == in_user)
            return user;
    }
    return NULL;
}

bool JsonHandler::IsUserExist(string target_user)
{
    for (auto user : all_user)
    {
        if (user->get_user() == target_user)
            return true;
    }
    return false;
}

int JsonHandler::GetNewId()
{
    int last_index = all_user.size() - 1;
    return all_user[last_index]->GetId() + 1;
}

void JsonHandler::AddNewUser(NormalUser *new_user)
{
    all_user.push_back(new_user);
}
