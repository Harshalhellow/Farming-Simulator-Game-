#include "WaterHole.h"
#include "User.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    User User1;
    WaterHole Waterhole1(&User1);
    cout << "Default waterhole storage should be 10 and is: " << Waterhole1.GetWaterHoleStorage() << " and the User1 water storage is: " << User1.GetWaterStorage() << endl;
    Waterhole1.GiveUserWater();
    cout << "The new User1 water storage is: " << User1.GetWaterStorage() << endl;
    this_thread::sleep_for(chrono::seconds(5));
     Waterhole1.GiveUserWater();
    cout << "After 5 seconds, the User1 water storage should be 50 and is : " << User1.GetWaterStorage() << endl;

   
}
