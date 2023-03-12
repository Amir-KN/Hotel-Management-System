#ifndef _Date_
#define _Date_

#include "Inclue.hpp"
#include "Function.hpp"

const int MAX_VALID_YR = 2024;
const int MIN_VALID_YR = 1800;

bool IsLeapYear(int year);

bool IsValidDate(int d, int m, int y);

bool CheckDate(string date_str);

class Date{
    public:
        Date(string date_str = "1-1-2023");
        void SetTime(string date_str);
        void PassDay(int num_day);
        void PrintDay();

    private:
        int day;
        int month;
        int year;

        void GoNextDay();

        int days_of_month(int m, int y);

};

#endif