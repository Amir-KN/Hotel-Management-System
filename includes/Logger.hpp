#ifndef _Logger_
#define _Logger_
#include "Inclue.hpp"
#include "Date.hpp"

const string FOLDER = "Logs/";

class Logger
{
public:
    // Logger(Date _date);
    void UpdateDate(Date _date);
    void Signup(string user, bool is_ok);
    void Signin(string user, bool is_ok);
    void ViewUserInfo(string user);
    void ViewAllUser(string user, bool is_admin);
    void ViewRoomInfo(string user);
    void Book(string user);
    void Cancel(string user);
    void PassDay(string user);
    void EditInfo(string user);
    void LeavRoom(string user);
    void Rooms(string user, bool is_admin, string error_num, string room_num = "");
    void Logout(string user);

private:
    string GetPath(string user);
    Date date;
};


#endif