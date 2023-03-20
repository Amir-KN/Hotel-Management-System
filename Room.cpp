#include "includes/Room.hpp"

ResUserInfo::ResUserInfo(int _id, int _num_of_beds, string _res_date, string _checkout_date)
{
    id = _id;
    num_of_beds = _num_of_beds;
    res_date = Date(_res_date);
    checkout_date = Date(_checkout_date);
}

void ResUserInfo::PrintResInfo()
{
    cout << "id : " << id << endl;
    cout << "Number Of Beds : " << num_of_beds << endl;
    cout << "Reserve Date : ";
    res_date.PrintDay();
    cout << "checkout Date : ";
    checkout_date.PrintDay();
}

string ResUserInfo::GetUserInfo()
{
    string user_info;
    user_info = "   User Id : " + to_string(id) + "\n   Num of Beds : " + to_string(num_of_beds) + "\n   Reserve Date : " + res_date.GetStr() +
                "   Checkout Date : " + checkout_date.GetStr() + "  ---------------------------\n";
    return user_info;
}

Date ResUserInfo::getCheckoutDate()
{
    return checkout_date;
}

void ResUserInfo::cancelRes(int num)
{
    num_of_beds -= num;
}

int ResUserInfo::getId() { return id; }

int ResUserInfo::getNumOfBeds() { return num_of_beds; }

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

string Room::GetUserInRoom()
{
    string users_info;
    users_info = "---> Users in Room :\n";
    if (users.size() == 0)
        users_info += "   This Room Is Empty!\n";
    else
        for (int i = 0; i < users.size(); i++)
        {
            users_info += users[i]->GetUserInfo();
        }

    return users_info;
}

string Room::GetInfoRoom(bool is_admin)
{
    string room_info;
    room_info = "\n**************\nRoom Number : " + number + "\nStatus : " + to_string(status) + "\nPrice : " + to_string(price) +
                "\nMax Capacity : " + to_string(maxCapacity) + "\n" + GetUserInRoom();
    return room_info;
}

string Room::getNum()
{
    return number;
}

int Room::getCapacity()
{
    return capacity;
}

int Room::GetMaxCapacity()
{
    return maxCapacity;
}

int Room::getPrice()
{
    return price;
}

int Room::checkCapacity(Date reserveDate)
{
    int roomCapacity = capacity;
    for (ResUserInfo *rsi : users)
    {
        if (rsi->getCheckoutDate().IsBefore(reserveDate))
            roomCapacity++;
    }
    return roomCapacity;
}

void Room::checkRoomsRes(Date sysDate)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getCheckoutDate().IsBefore(sysDate))
        {
            capacity += users[i]->getNumOfBeds();
            users.erase(users.begin() + i);
        }
    }
}

void Room::reserve(int id, int numOfBeds, string resDate, string checkoutDate)
{
    ResUserInfo *newRes = new ResUserInfo(id, numOfBeds, resDate, checkoutDate);
    users.push_back(newRes);
    capacity -= numOfBeds;
    CheckStatus();
}

bool Room::cancelReservation(int id, int num)
{

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getId() == id && users[i]->getNumOfBeds() > num)
        {
            users[i]->cancelRes(num);
            capacity += num;
            return true;
        }
        else if (users[i]->getId() == id && users[i]->getNumOfBeds() == num)
        {
            users.erase(users.begin() + i);
            capacity += num;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false; // Amir added this line
}

int Room::GetStatus() { return status; }

json ResUserInfo::GetUserJson()
{
    json j = {
        {"id", id},
        {"numOfBeds", num_of_beds},
        {"reserveDate", res_date.GetStr("")},
        {"checkoutDate", checkout_date.GetStr("")}};
    return j;
}

json Room::GetUsersJson()
{
    vector<json> user_in_room;
    for (int i = 0; i < users.size(); i++)
    {
        json u = users[i]->GetUserJson();
        user_in_room.push_back(u);
    }
    json all_user =
        {"users", user_in_room};
    return all_user;
}

bool Room::leaveRoom(int uId)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getId() == uId)
        {
            capacity += users[i]->getNumOfBeds();
            users.erase(users.begin() + i);
            return true;
        }
    }
    return false;
}

vector<ResUserInfo *> Room::get_users()
{
    return users;
}

void Room::ModifyRoom(int new_max_c, int new_price)
{
    maxCapacity = new_max_c;
    price = new_price;
}

void Room::CheckStatus()
{
    if (capacity == 0)
    {
        status = 1;
    }
    else
        status = 0;
}
