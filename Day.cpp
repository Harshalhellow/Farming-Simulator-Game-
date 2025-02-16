#include "Day.h"
#include <iostream>


Day::Day() : Current_Day(0), Stop_Thread(false) {
    Day_Thread = std::thread(&Day::GameTimer, this); //so this starts are thread which holds a timer. So once intialsed there is going to be a timer in the background until day goes out of scope using the destrucotor 
}

Day::~Day() {
    Stop_Thread = true; // this destructor ends the therad this is important as even if the code has finished running if you dont have this destructor then you wont be able to access the terminal as there will be the game timer thread running in the background. 
    if (Day_Thread.joinable()) {
        Day_Thread.join(); //rejoins the thread to the orginal thread in the main program 
    }
}

void Day::GameTimer() {
    while (!Stop_Thread) { 
        std::this_thread::sleep_for(std::chrono::seconds(1)); // sleeps for a 1 sec and increasees the current day by 1 and this doesnt affect the main codes exsecution as it is on a seperate thread 
        Current_Day += 1;
    }
}

int Day::GetCurrentDay() {
    return Current_Day; //getter for  the currrend day 
}