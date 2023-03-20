#ifndef _Logger_
#define _Logger_
#include "Inclue.hpp"
#include "Date.hpp"
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>

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
    void Book(string user, bool is_admin, string error_num, string room_num = "");
    void Cancel(string user, bool is_admin, string error_num, string room_num = "");
    void PassDay(string user, bool is_admin, string value);
    void EditInfo(string user, bool is_admin, vector<string> new_info);
    void LeavRoom(string user);
    void Rooms(string user, bool is_admin, string error_num, string room_num = "");
    void Logout(string user);

private:
    string GetPath(string user);
    string GetTime();
    string GetInitInfo(string user);
    Date date;
};


#endif