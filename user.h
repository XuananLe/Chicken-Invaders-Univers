#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
class user
{
    public:
    std::string user_name = "";
    std::string time = "";
    int nums_of_wings = 0;
    int numbers_player_want_to_play_again = 0;
    user(std::string name, std::string time, int nums_of_wings) : user_name(name), time(time), nums_of_wings(nums_of_wings) {}
    user() {}
};
#endif