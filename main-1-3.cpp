#include "Day.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    Day Day1; 
    cout << "The default day is: " << Day1.GetCurrentDay() << endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cout << "The current day after 5 seconds should be 4 and is : " << Day1.GetCurrentDay() << endl;

    return 0;
}