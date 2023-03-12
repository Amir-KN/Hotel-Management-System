#ifndef _Jsonhandler_
#define _Jsonhandler_
#include "Inclue.hpp"

class Date;

class ResUserInfo
{
public:
    ResUserInfo(int _id, int _num_of_beds, string _res_date, string _checkout_date);
    void PrintResInfo();

private:
    int id;
    int num_of_beds;
    string res_date;
    string checkout_date;
};

class User
{
public:
    User(int _id, string _user, string _pass);
    virtual bool is_admin() = 0;
    virtual void print_user() = 0;
    string get_user() { return user; }
    bool IsPassCorrect(string in_pass);
    int GetId() { return id; }

protected:
    int id;
    string user;
    string password;
};

class Admin : public User
{
public:
    Admin(int _id, string _user, string _pass);

    void print_user();

    bool is_admin();
};

class NormalUser : public User
{
public:
    NormalUser(int _id, string _user, string _pass, string _purse, string _phoneNumber, string _address);

    void print_user();

    bool is_admin() { return false; }

private:
    string purse;
    string phoneNumber;
    string address;
};

class Room
{
public:
    Room(string _number, int _status, int _price, int _maxCapacity, int _capacity, vector<ResUserInfo *> _users);

    void print_room();

    vector<ResUserInfo *> get_users() { return users; }

private:
    string number;
    int status;
    int price;
    int maxCapacity;
    int capacity;
    vector<ResUserInfo *> users;
};

class JsonHandler
{
public:
    JsonHandler();

    void read_room();

    void read_user();

    vector<ResUserInfo *> read_users_of_room(json users);

    User *FindUserByName(string in_user);

    bool IsUserExist(string target_user);

    int GetNewId();

    void AddNewUser(NormalUser *new_user);

    vector<User *> get_users();

    vector<Room *> get_rooms();

private:
    json room_data;
    json user_data;
    vector<Room *> all_room;
    vector<User *> all_user;
};

#endif