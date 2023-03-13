#include "includes/Date.hpp"

bool IsLeapYear(int year)
{
    return ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)));
}

bool IsValidDate(int d, int m, int y)
{
    if (y > MAX_VALID_YR || y < MIN_VALID_YR)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;
    if (m == 2)
    {
        if (IsLeapYear(y))
            return (d <= 29);
        else
            return (d <= 28);
    }

    if (m == 4 || m == 6 || m == 9 || m == 11)
        return (d <= 30);

    return true;
}

bool CheckDate(string date_str)
{
    vector<string> date = BreakString(date_str, '-');
    if (date.size() != 3)
        return false;
    if ((!IsDigit(date[0])) || (!IsDigit(date[1])) || (!IsDigit(date[2])))
    {
        return false;
    }
    int year = stoi(date[2]);
    int month = stoi(date[1]);
    int day = stoi(date[0]);
    return IsValidDate(day, month, year);
}

Date::Date(string date_str)
{
    SetTime(date_str);
}

void Date::SetTime(string date_str)
{
    vector<string> date = BreakString(date_str, '-');
    year = stoi(date[2]);
    month = stoi(date[1]);
    day = stoi(date[0]);
}

void Date::PassDay(int num_day)
{
    for (int i = 0; i < num_day; i++)
    {
        GoNextDay();
    }
}

void Date::PrintDay()
{
    cout << day << " - " << month << " - " << year << endl;
}

bool Date::IsBefore(Date date)
{
    if (date.year > year)
    {
        return true;
    }
    else if (date.year == year && date.month > month)
    {
        return true;
    }
    else if (date.year == year && date.month == month && date.day >= day)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Date::GoNextDay()
{
    day++;
    if (day > days_of_month(month, year))
    {
        day = 1;
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }
}

int Date::days_of_month(int m, int y)
{
    if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
        return 31;
    else if (m == 2)
        return IsLeapYear(y) ? 29 : 28;
    else if ((m > 0) && (m < 13))
        return 30;
    else
        abort();
}
