//
//  Survivor.h
//  Text Based Adventure XCode
//
//  Created by Nicholas Weg on 11/14/15.
//  Copyright (c) 2015 Nicholas Weg. All rights reserved.
//
using namespace std;

class Survivor
{
protected:
    Inventory backpack;
    int thirst;
    int health;
    //    int infection;
    int progress;
    //    bool isInfected;
    struct Location
    {
        int x;
        int y;
    };
    int steps = 0;
    int radio = 0;
public:
    Survivor() {};
    void setThirst (int amount) {thirst += amount;}
    void setHealth(int amount) {health += amount; if (health < 20) cout << "You are getting low on health. Be careful!" << endl;}
    
    int getProgress() {return progress;}
    
    int getHealth() const {return health;}
    int getThirst() const {return thirst;}
    bool checkDeath() {if(getHealth() <= 0) return true; return false;}
    void renderStatus() const {cout << "Health: " << health << " Thirst: " << thirst << endl;}
    // void infect() {isInfected = true;}
    // void cure() {isInfected = false;}
    Inventory getBackpack() {return backpack;}
    void pickUp(Item* item) {backpack.addItem(item);}
    void pickUpConsumable(Item* item) {backpack.addToConsumable(item);}
    void dropItem(Item* item) {backpack.removeItem(item);}
    void checkBackpack() {cout << "-------\n"; backpack.render(); cout << "-------\n";}
    long checkBackpackSize() {return backpack.getSize();}
    void inspectBackpackItem(string itemName) {backpack.inspectItem(itemName);}
    void changeConsumableCount(string itemName, int value) {backpack.changeCount(itemName, value);}
    void setSteps(int x) {steps += x;}
    int getSteps() {return steps;}
    int getRadio() {return radio;}
    void setRadio() {radio++;}
    void impasse()
    {
        srand(time(NULL));
        int num = rand() % 6 + 1;
        if (num == 1)
            cout << "You can't go that way, there's a large object obstructing your path." << endl;
        else if (num == 2)
            cout << "There is nowhere to go, it's just a wall of buildings." << endl;
        else if (num == 3)
            cout << "It's an impasse. There's a large overturned truck. You simply can't get through." << endl;
        else if (num == 4)
            cout << "There is a large pool of water in front of you and a downed power line nearby...better not go that way." << endl;
        else if (num == 5)
            cout << "You perceptively notice the area ahead is rigged with traps. Regardles of whether or not whoever set them is still around, it's still not a good idea to go in this direction." << endl;
        else
            cout << "You see a pack of rabid dogs scamper into the shadows. This is an area you should avoid." << endl;
    }
};

class Player : public Survivor
{
private:
    
    Location where;
public:
    //    Inventory backpack;
    Player (int startLocationX, int startLocationY, int startingThirst, int startingHealth, int startProgress);
    int getLocationX() {return where.x;}
    int getLocationY() {return where.y;}
    
    void walkNorth() {where.x--;}// cout << "Location is " << where.x << "," << where.y << endl;}
    void walkSouth(int line_count) {where.x++;}// cout << "Location is " << where.x << "," << where.y << endl;}
    void walkEast(int line_count) {where.y++;}//cout << "Location is " << where.x << "," << where.y << endl;}
    void walkWest() {where.y--;}// cout << "Location is " << where.x << "," << where.y << endl;}
    int attackWithItem(string item) {return backpack.attack(item);}
    void drinkItem(string item)
    {
        int num = rand() % 6 +1;
        if(getThirst()==100)
        {
            if (num == 1 || num == 2)
                cout << "You aren't thirsty." << endl;
            else if (num ==3 || num == 4)
                cout << "You couldn't possibly drink another drop." << endl;
            else
                cout << "Better save this until you need it more." << endl;
        }
        else if(getThirst()>70 && item == "water")
        {
            setThirst(100 - getThirst());
            backpack.drink(item);
            if (num == 1)
                cout << "[Drank water] You weren't too thirsty, but hydration is key I guess.\n";
            else if (num == 2)
                cout << "[Drank water] Why wait until you're thirsty to drink right? Staying ahead of the game I see." << endl;
            else if (num == 3)
                cout << "[Drank water] You probably could have waited to drink that, but hey, you're the boss." << endl;
            else if (num == 4)
                cout << "[Drank water] Saving resources is overrated right?" << endl;
            else if (num == 5)
                cout << "[Drank water] You were barely thirsty. Hopefull this wasteful decision doesn't end up hurting you..." << endl;
            else
                cout << "[Drank water] You weren't that thirsty, but I suppose you can waste water. It's your life after all." << endl;
        }
        else if (item == "water")
        {
            setThirst(backpack.drink(item));
            if (num == 1)
                cout << "[Drank water] You were parched. That was refreshing.\n";
            else if (num == 2)
                cout << "[Drank water] Mmmm. That's some high quality H2O." << endl;
            else if (num == 3)
                cout << "[Drank water] This was never your favorite brand, but hey, can't be picky during the apocalypse." << endl;
            else if (num == 4)
                cout << "[Drank water] Man that was refreshing. You feel a lot better." << endl;
            else if (num == 5)
                cout << "[Drank water] Ahhh water. The key building block to organic life, other than carbon, that is. Man you should have been a scientist." << endl;
            else
                cout << "[Drank water] You instantly feel better. Revitalized." << endl;
        }
        else
        {
            backpack.drink(item);
        }
    }
    void eatItem(string item)
    {
        if (getHealth()==100)
            cout << "You feel strong, like you could bench press 250. Probably shouldn't waste resources." << endl;
        else if (getHealth() > 79 && item == "jerky")
        {
            cout << "[Ate jerky]. You weren't all that hungry, but you're the boss.\n";
            setHealth(100-getHealth());
            backpack.eat(item);
        }
        else if (getHealth() < 80 && item == "jerky")
        {
            cout << "[Ate jerky]. Good for you for not using it as bait to mess with sasquatch.\n";
            setHealth(backpack.eat(item));
        }
        else if (item == "medkit")
        {
            cout << "[Health fully restored] Now that you're all drugged up, back into the apocalypse.\n";
            setHealth(100-getHealth());
            backpack.eat(item);
        }
        else
        {
            backpack.eat(item);
        }
    }
    void useItem(string item) {backpack.use(item);}
    void repairItem(string item) {backpack.repair(item);}
    bool lookedN = false;
    bool lookedS = false;
    bool lookedE = false;
    bool lookedW = false;
};

Player::Player(int startLocationX, int startLocationY, int startingThirst, int startingHealth, int startProgress) : Survivor()
{
    where.x = startLocationX;
    where.y = startLocationY;
    thirst = startingThirst;
    health = startingHealth;
    progress = startProgress;
}