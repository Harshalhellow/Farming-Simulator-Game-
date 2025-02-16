#include"User.h"
#include<iostream>
using namespace std;
int main(){
User U1;
cout<<"default money is:" << U1.GetMoney() << "Default waterstorage is:" << U1.GetWaterStorage() <<endl;
U1.SetWaterStorage(300);
U1.SetMoney(1000);
cout<<"set money should be 1000 and the output is:" << U1.GetMoney() << "set money should be 300 adn the output is :" << U1.GetWaterStorage() <<endl;

}
