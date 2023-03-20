#include "includes/User.hpp"

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

void User::editInfo(string newPassword)
{
    password = newPassword;
}

void NormalUser::editInfo(string newPass, string newPhone, string newAddress)
{
    password = newPass;
    phoneNumber = newPhone;
    address = newAddress;
}

Admin::Admin(int _id, string _user, string _pass) : User(_id, _user, _pass){};


json Admin::GetUserJson()
{
        json a = {
            {"id", id},
            {"user", user},
            {"password", password},
            {"admin", "true"}
            };

    return a;
}

int Admin::getPurse() { return -1; }

void Admin::print_user()
{
    cout << "id : " << id << endl
         << "user : " << user << endl
         << "password : " << password << endl;
}

bool Admin::is_admin() { return true; }

string Admin::GerUserInfo()
{
    string user_info;
    user_info = "*****************\nAdmin user : " + user + "\n" + "Id : " + to_string(id) + "\n";
    return user_info;
}

void Admin::payback(float amount) {}
void Admin::payment(float amount) {}

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

string NormalUser::GerUserInfo()
{
    string user_info;
    user_info = "*****************\nNormal User : " + user + "\n" + "Id : " + to_string(id) + "\n" + "Purse : " + purse + "\n" + "Phone Number : " + phoneNumber + "\n" + "Address : " + address + "\n";

    return user_info;
}

void NormalUser::payment(float amount)
{
    int p = stof(purse);
    p -= amount;
    purse = to_string(p);
}

void NormalUser::payback(float amount)
{
    int p = stof(purse);
    p += amount;
    purse = to_string(p);
}

bool NormalUser::is_admin() { return false; }

int NormalUser::getPurse() { return stoi(purse); }

json NormalUser::GetUserJson()
{
        json u = {
            {"id", id},
            {"user", user},
            {"password", password},
            {"admin", "false"},
            {"purse", purse},
            {"phoneNumber", phoneNumber},
            {"address", address}
            };

    return u;
}
