#ifndef _Room_
#define _Room_

#include "Inclue.hpp"
#include "Date.hpp"
// #include "Jsonhandler.hpp"


class ResUserInfo
{
public:
    ResUserInfo(int _id, int _num_of_beds, string _res_date, string _checkout_date);
    void PrintResInfo();
    string GetUserInfo();
    Date getCheckoutDate();
    int getId();
    int getNumOfBeds();
    void cancelRes(int num);

private:
    int id;
    int num_of_beds;
    Date res_date;
    Date checkout_date;
};


class Room
{
public:
    Room(string _number, int _status, int _price, int _maxCapacity, int _capacity, vector<ResUserInfo *> _users) ;

    void print_room();

    string getNum();

    int getCapacity();

    int GetMaxCapacity();

    int getPrice();

    void reserve(int id, int numOfBeds, string resDate, string checkoutDate);

    vector<ResUserInfo *> get_users();

    int checkCapacity(Date reserveDate);

    bool cancelReservation(int id, int num);

    void checkRoomsRes(Date sysDate);

    bool leaveRoom(int uId);

    string GetUserInRoom();

    string GetInfoRoom(bool is_admin);

    void ModifyRoom(int new_max_c, int new_price);

    void CheckStatus();

private:
    string number;
    int status;
    int price;
    int maxCapacity;
    int capacity;
    vector<ResUserInfo *> users;
};


#endif
