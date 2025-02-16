#ifndef WIN_H
#define WIN_H
#include"Item.h"
#include"User.h"

class Win : public Item {
private:
User* User1;  //sets a pointer the holds the user 
public:


Win(User* User1); // the constructor 
void BuyThisItem() override; 


};


#endif
