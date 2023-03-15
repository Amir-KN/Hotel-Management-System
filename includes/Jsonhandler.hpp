#ifndef _Jsonhandler_
#define _Jsonhandler_

#include "Inclue.hpp"
#include "Date.hpp"
#include "Room.hpp"
#include "User.hpp"

class JsonHandler
{
public:
    JsonHandler();

    void read_room();

    void read_user();

    vector<ResUserInfo *> read_users_of_room(json users);

    User *FindUserByName(string in_user);

    Room *FindRoom(string numOfRoom);

    bool IsUserExist(string target_user);

    int GetNewId();


    void AddNewUser(NormalUser *new_user);

    void printUserReservations(int uId);

    void checkCheckouts(Date sysDate);

    vector<User *> get_users();

    vector<Room *> get_rooms();

private:
    json room_data;
    json user_data;
    vector<Room *> all_room;
    vector<User *> all_user;
};

#endif