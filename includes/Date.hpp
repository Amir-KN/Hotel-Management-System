#ifndef _Date_
#define _Date_

#include "Inclue.hpp"
#include "Function.hpp"

const int MAX_VALID_YR = 2024;
const int MIN_VALID_YR = 2000;

bool IsLeapYear(int year);

bool IsValidDate(int d, int m, int y);

bool CheckDate(string date_str);

class Date
{
public:
    Date(string date_str = "1-1-2023");
    void SetTime(string date_str);
    void PassDay();
    void PrintDay();
    bool IsBefore(Date date);
    string GetStr();

private:
    int day;
    int month;
    int year;

    void GoNextDay();

    int days_of_month(int m, int y);
};

#endif