#ifndef _INCLUDE_
#define _INCLUDE_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;
#define MAX_LEN_MESS 2048


const string SIGNIN = "signin";
const string SIGNUP = "signup";
const string EXIT = "exit";

const string VIEW_USER_INFO = "1";
const string VIEW_ALL_USER = "2";
const string VIEW_ROOM_INFO = "3";
const string BOOKING = "4";
const string CANCELING = "5";
const string PASS_DAY = "6";
const string EDIT_INFO = "7";
const string LEAVING_ROOM = "8";
const string ROOMS = "9";
const string LOGOUT = "0";



#endif