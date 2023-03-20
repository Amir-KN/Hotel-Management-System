#ifndef _User_
#define _User_
#include "Inclue.hpp"


class User
{
public:
    User(int _id, string _user, string _pass);
    virtual bool is_admin() = 0;
    virtual void print_user() = 0;
    string get_user();
    bool IsPassCorrect(string in_pass);
    int GetId();
    virtual int getPurse() = 0;
    virtual void payment(float amount) = 0;
    virtual void payback(float amount) = 0;
    virtual string GerUserInfo() = 0;
    void editInfo(string newPassword);
    virtual json GetUserJson() = 0;
    // void editInfo(string newPass, int newPurse, string newPhone, string newAddress);

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

    string GerUserInfo();
    json GetUserJson() ;
    bool is_admin();
    void payment(float amount);
    void payback(float amount);
    int getPurse();
};

class NormalUser : public User
{
public:
    NormalUser(int _id, string _user, string _pass, string _purse, string _phoneNumber, string _address);

    void print_user();

    bool is_admin();

    int getPurse();

    string GerUserInfo();

    void payment(float amount);
    void payback(float amount);

    void editInfo(string newPass, string newPhone, string newAddress);

    json GetUserJson() ;

private:
    string purse;
    string phoneNumber;
    string address;
};


#endif