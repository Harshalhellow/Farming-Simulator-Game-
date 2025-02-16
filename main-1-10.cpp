#include"User.h"
#include"Item.h"
#include"Store.h"
#include"Win.h"
#include<iostream>
using namespace std;
int main(){
User*User1 = new User();
Store store(10);
Win* win = new Win(User1);
User1->SetMoney(1000);
store.AddItemToStore(win);
store.GetListOfItemsInStore();
store.BuyThisItem(1);
win->BuyThisItem();
win->BuyThisItem();
win->BuyThisItem();
win->BuyThisItem();


}