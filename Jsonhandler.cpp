#include "includes/Jsonhandler.hpp"

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

Room *JsonHandler::FindRoom(string numOfRoom)
{
    for (Room *room : all_room)
    {
        if (room->getNum() == numOfRoom)
            return room;
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

string JsonHandler::GetUserReservations(int uId)
{
    string res = "";
    for (Room *room : all_room)
    {
        for (ResUserInfo *rui : room->get_users())
        {
            if (rui->getId() == uId)
            {
                res += "Room Number : " + room->getNum() + "\n";
                res += rui->GetUserInfo();
            }
        }
    }
    if (res == "")
        return "There Are No Reservation for This Users";
    return res;
}

void JsonHandler::checkCheckouts(Date sysDate)
{
    for (Room *room : all_room)
    {
        room->checkRoomsRes(sysDate);
    }
}

void JsonHandler::AddNewUser(NormalUser *new_user)
{
    all_user.push_back(new_user);
}

void JsonHandler::RemoveRoom(string num)
{
    for (int i = 0; i < all_room.size(); i++)
    {
        if (all_room[i]->getNum() == num)
        {
            all_room.erase(all_room.begin() + i);
            return;
        }
    }
}

void JsonHandler::AddNewRoom(Room *new_room)
{
    all_room.push_back(new_room);
}

json JsonHandler::GetRoomsJson()
{
    string num;
    int status, price, max_cap, cap;
    vector<json> rooms;
    for (int i = 0; i < all_room.size(); i++)
    {
        num = all_room[i]->getNum();
        status = all_room[i]->GetStatus();
        price = all_room[i]->getPrice();
        max_cap = all_room[i]->GetMaxCapacity();
        cap = all_room[i]->getCapacity();
        json j = {
            {"status", status},
            {"price", price},
            {"maxCapacity", max_cap},
            {"capacity", cap},
            {"number", num},
            all_room[i]->GetUsersJson()};
        rooms.push_back(j);
    }
    json rooms_json = {
        {"rooms", rooms}};

    return rooms_json;
}

json JsonHandler::GetUsersJson()
{
    vector<json> users;
    for (int i = 0; i < all_user.size(); i++)
    {
        json j = all_user[i]->GetUserJson();
        users.push_back(j);
    }

    json users_json = {
        {"users", users}};

    return users_json;
}

void JsonHandler::UpdateData()
{
    json rooms_json = GetRoomsJson();
    json users_json = GetUsersJson();

    ofstream Rooms("JsonFiles/RoomsInfo.json"), Users("JsonFiles/UsersInfo.json");

    Rooms << rooms_json << endl;
    Users << users_json << endl;
}