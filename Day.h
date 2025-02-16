#include <thread>
#include<iostream>
#ifndef DAY_H
#define DAY_H
class Day {
private:
    int Current_Day; //holds the current day 
    std::thread Day_Thread; //another thread called day threa
    bool Stop_Thread; //a boliean that holds if the thread is on or off 
public:
    Day(); //constructor 
    ~Day(); //destructor 
    void GameTimer();
    int GetCurrentDay();
};

#endif