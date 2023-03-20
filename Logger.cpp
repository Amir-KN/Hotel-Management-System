#include "includes/Logger.hpp"


// Logger::Logger(Date _date){
//     date = _date;
// }

void Logger::UpdateDate(Date _date){
    date = _date;
}

void Logger::Signup(string user, bool is_ok){
    string path = FOLDER + user ;
    mkdir(path.c_str(), 0777);
    ofstream log(GetPath(user), ios::app);
    string is_successful = (is_ok) ? "Successfully Signed up !" : "He/She did't Succeed !" ;
    log << GetInitInfo(user)  << "Try to Signup and " << is_successful << endl ;
}

void Logger::Signin(string user, bool is_ok){
    string path = FOLDER + user ;
    mkdir(path.c_str(), 0777);
    ofstream log(GetPath(user), ios::app);
    string is_successful = (is_ok) ? "Successfully Signed in !" : "He/She did't Succeed !" ;
    log << GetInitInfo(user)  << "Try to Signin and " << is_successful << endl ;
}

void Logger::ViewUserInfo(string user){
    ofstream log(GetPath(user), ios::app);
    log << GetInitInfo(user)  << "Try to View User Information !" << endl ;
}

void Logger::ViewAllUser(string user, bool is_admin){
    ofstream log(GetPath(user), ios::app);
    string is_successful = (is_admin) ? "Successfully View !" : "He/She did't Succeed to View Because He/She doesn't be admin !" ;
    log << GetInitInfo(user)  << "Try to View All User and " << is_successful << endl ;
}

void Logger::ViewRoomInfo(string user){
    ofstream log(GetPath(user), ios::app);
    log << GetInitInfo(user)  << "Try to View Rooms Information !" << endl ;
}

void Logger::Rooms(string user, bool is_admin, string error_num, string room_num){
    ofstream log(GetPath(user), ios::app);
    if (!is_admin)
        log << GetInitInfo(user)  << "Try to Use Rooms Options but He/She Can't because doesn't Be Admin !! " << endl ;
    else {
        if (error_num == "503")
            log << GetInitInfo(user) << "Try to Use Rooms Options but He/She Can't because Enter Bad Sequence of input !! " << endl;
        else if (error_num == "111")
            log << GetInitInfo(user) << "This Admin Try to Add a Room that Exist Before !! " << endl;
        else if (error_num == "104")
            log << GetInitInfo(user) << "This Admin Successfuly Add a Room " << room_num << endl;
        else if (error_num == "101")
            log << GetInitInfo(user) << "This Admin Add a Room Number that Not Exist " << endl;
        else if (error_num == "109")
            log << GetInitInfo(user) << "This Admin Try to Modify/Remove The room thar it's capacity is full !! " << endl;
        else if (error_num == "105")
            log << GetInitInfo(user) << "This Admin Successfuly Modify Room " << room_num << endl;
        else if (error_num == "106")
            log << GetInitInfo(user) << "This Admin Successfuly Remove Room " << room_num << endl;
    }
}

void Logger::Book(string user){

}

void Logger::Cancel(string user){

}

void Logger::PassDay(string user){

}

void Logger::EditInfo(string user){

}

void Logger::LeavRoom(string user){

}

void Logger::Logout(string user){
    ofstream log(GetPath(user), ios::app);
    log << GetInitInfo(user)  << "Successfully Logged out ! " << endl ;
    log.close();
}

string Logger::GetPath(string user){
    string path = FOLDER + user + "/LOGs.txt";
    return path;
}

string Logger::GetTime(){
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    string curr_time = to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec) ;
    return curr_time;
}

string Logger::GetInitInfo(string user){
    stringstream init;
    init << "User <" << user << "> at < " << date.GetStr(" ") << ", " << GetTime() << "> : " ;
    return init.str();
}