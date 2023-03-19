#include "includes/Logger.hpp"


// Logger::Logger(Date _date){
//     date = _date;
// }

void Logger::UpdateDate(Date _date){
    date = _date;
}

void Logger::Signup(string user, bool is_ok){
    ofstream log(GetPath(user), ios::app);
    string is_successful = (is_ok) ? "Successfully Signed up !" : "He/She did't Succeed !" ;
    log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "Try to Signup and " << is_successful << endl ;
}

void Logger::Signin(string user, bool is_ok){
    
    ofstream log(GetPath(user), ios::app);
    string is_successful = (is_ok) ? "Successfully Signed in !" : "He/She did't Succeed !" ;
    log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "Try to Signin and " << is_successful << endl ;
}

void Logger::ViewUserInfo(string user){
    ofstream log(GetPath(user), ios::app);
    log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "Try to View User Information !" << endl ;
}

void Logger::ViewAllUser(string user, bool is_admin){
    ofstream log(GetPath(user), ios::app);
    string is_successful = (is_admin) ? "Successfully View !" : "He/She did't Succeed to View Because He/She doesn't be admin !" ;
    log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "Try to View All User and " << is_successful << endl ;
}

void Logger::ViewRoomInfo(string user){
    ofstream log(GetPath(user), ios::app);
    log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "Try to View Rooms Information !" << endl ;
}

void Logger::Rooms(string user, bool is_admin, string error_num, string room_num){
    ofstream log(GetPath(user), ios::app);
    if (!is_admin)
        log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "Try to Use Rooms Options but He/She Can't because doesn't Be Admin !! " << endl ;
    else {
        if(error_num == "503")
            log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "Try to Use Rooms Options but He/She Can't because Enter Bad Sequence of input !! " << endl ;
        else if(error_num == "111")
          log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "This Admin Try to Add a Room that Exist Before !! " << endl ;
        else if(error_num == "104")
            log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "This Admin Successfuly Add a Room " << room_num << endl ;
        else if(error_num == "101")
            log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "This Admin Add a Room Number that Not Exist " << endl ;
        else if(error_num == "109")
            log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "This Admin Try to Modify/Remove The room thar it's capacity is full !! " << endl ;
        else if(error_num == "105")
            log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "This Admin Successfuly Modify Room " << room_num << endl ;
        else if(error_num == "106")
            log << "User <" << user << ">, Date : < " << date.GetStr(" ") << "> : " << "This Admin Successfuly Remove Room " << room_num << endl ;
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

}

string Logger::GetPath(string user){
    string path = FOLDER + "USER_" + user + ".txt";
    return path;
}