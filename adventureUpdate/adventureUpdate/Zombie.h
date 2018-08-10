//
//  Zombie.h
//  Text Based Adventure XCode
//
//  Created by Nicholas Weg on 11/14/15.
//  Copyright (c) 2015 Nicholas Weg. All rights reserved.
//
#include <iostream>
#include "Inventory.h"
#include "Survivor.h"
using namespace std;
class Zombie
{
protected:
    bool hasLoot;
    int health;
    struct stats{int damage; int hitRate;};
    stats zStats;
    bool runaway(int n);
    Item* Zloot;
public:
    Zombie() {srand(time(NULL)); int num = rand() % 5 + 1; if (num == 1) hasLoot = false; else{ hasLoot = true; /*cout << "Has loot"<< endl;*/}}
    void changeHealth(int a) {health += a;}
    int getHealth() {return health;}
    int getAttack() {return zStats.damage;}
    void getZloot(Player* p);
    virtual void isAttacking() = 0;
    virtual bool run() = 0;
    virtual void attack(Player* p, World* A);
    void boosLoot() {hasLoot = false;}
};

void Zombie::getZloot(Player* p)
{
    if (hasLoot == true)
    {
        if(p -> getBackpack().hasItem(Zloot -> getName()) == false)
        {
            cout << "You find ";
            
            if(Zloot -> consumableCheck() == true && Zloot -> getCount() > 1)
                cout << Zloot -> getCount() << " " << Zloot -> getName() << "s";
            else
                cout << "a " << Zloot -> getName();
            cout << " on the corpse! You picked it up and put it in your backpack.\n";
            p -> pickUp(Zloot);
        }
        else if(Zloot -> consumableCheck() == true)
        {
            cout << "You find some supplies! " << Zloot -> getName() << "(" << Zloot -> getCount() << ")" << " added to backpack.\n";
            p -> pickUpConsumable(Zloot);
        }
        else
        {
            if (p->getBackpack().searchVector("medkit") != string::npos)
            {
                p->changeConsumableCount("medkit", 1);
                cout << "You found another medkit. You throw it in your backpack." << endl;
            }
            else
            {
                cout << "You found a medkit!" << endl;
                Consumable* m = new Medkit (1);
                p->pickUp(m);
            }


        }
    }
    else
        cout << "You searched the corpse but didn't find anything notable.\n";
}

void Zombie::attack(Player* p, World* A)
{
    srand(time(NULL));
    if (rand() % 100 + 1 > zStats.hitRate)
    {
        p -> setHealth((-1)*(zStats.damage*A->difficulty));
        int num = rand() % 3 + 1;
        if (num == 1)
            cout << "The zombie was able to bite you!" << endl;
        else if( num == 2)
            cout << "The zombie sunk his teeth into your flesh." << endl;
        else
            cout << "You feel a shooting pain in your arm as the zombie bites into your skin." << endl;
        if (p -> checkDeath())
        {
            cout << "You have died. It isn't cowardly to run away. Try picking fights you think you can win. Thank you for playing!!!" << endl;
            exit(0);
        }
    }
    else
    {
        int num = rand() % 3 + 1;
        if (num == 1)
            cout << "The zombie tried to bite you but missed!" << endl;
        else if( num == 2)
            cout << "The zombie lunged towards you but you dove out of the way." << endl;
        else
            cout << "The zombie tried to grab you but you evaded him." << endl;
    }
}

//definitions
class standardZombie : public Zombie
{
public:
    standardZombie() : Zombie()
    {
        srand(time(NULL));
        zStats.damage = 10, zStats.hitRate = 30, health = 75;
        if (hasLoot == true)
        {
            int num = rand() % 6 + 1;
            if (num == 1)
            {
                Consumable* j = new Jerky (rand() % 2 + 1);
                Zloot = j;
            }
            else if (num == 2 || num == 3)
            {
                Consumable* w = new WaterBottle (rand() % 2 + 1);
                Zloot = w;
            }
            else if (num == 4)
            {
                Consumable* m = new Medkit (1);
                Zloot = m;
            }
            else if (num == 5 || num == 6)
            {
                Consumable* dt = new DuctTape (rand() % 2 + 1);
                Zloot = dt;
            }
        }
    }
    void isAttacking();
    bool run();
};
class armoredZombie : public Zombie
{
public:
    armoredZombie() : Zombie()
    {
        srand(time(NULL));
        zStats.damage = 15, zStats.hitRate = 40, health = 125;
        if (hasLoot == true)
        {
            int num = rand() % 4 + 1;
            if (num == 1)
            {
                if (num == rand() % 2 +1)
                {
                    Consumable* hgammo = new HandgunAmmo (rand() % 4 + 1);
                    Zloot = hgammo;
                }
                else
                {
                    Consumable* sgammo = new ShotgunAmmo (rand() % 4 + 1);
                    Zloot = sgammo;
                }
            }
            else if (num ==2)
            {
                if (num == rand() % 2 + 1)
                {
                   Consumable* sgammo = new ShotgunAmmo (rand() % 4 + 1);
                    Zloot = sgammo;
                }
                else
                {
                    Weapon* HG = new Handgun;
                    Zloot = HG;
                }
            }
            if (num == 3)
            {
                Consumable* m = new Medkit (rand() % 2 + 1);
                Zloot = m;
            }
            else
            {
                Weapon* SG = new Shotgun;
                Zloot = SG;
            }
        }
    }
    void isAttacking();
    bool run();
};
class crawlerZombie : public Zombie
{
public:
    crawlerZombie() : Zombie()
    {
        srand(time(NULL));
        zStats.damage = 5, zStats.hitRate = 50, health = 50;
        if (hasLoot == true)
        {
            int num = rand() % 2 + 1;
            if (num == 1)
            {
                Consumable* j = new Jerky (rand() % 2 + 1);
                Zloot = j;
            }
            else
            {
                Consumable* w = new WaterBottle (rand() % 2 + 1);
                Zloot = w;
            }
        }
    }
    void isAttacking();
    bool run();
};
class npc1 : public Zombie //Even though survivor is not a zombie it acts like one when you fight it.
{
public:
    npc1 () : Zombie() {zStats.damage = 40, zStats.hitRate = 20, health = 100;}
    void isAttacking();
    int dialogue()
    {
        srand(time(NULL));
        int num = rand() % 3 + 1;
        if (num == 1)
        {
            cout << "You encountered another survivor.....He greets you warmly, and tells you he is in dire need of a bottle of water. He is willing to trade you a some duct tape for it. He is holding a baseball bat, but he appears to be weak and desperate, and it looks like you could possibly overpower him...Do you fight him, trade, or refuse and leave." << endl;
            Consumable* dt = new DuctTape(rand() % 2 + 1);
            Zloot = dt;
            return num;
        }
        else if (num == 2)
        {
            cout << "You see a man in the distance. As you approach, he greets you and assures you he means no harm. He tells you he hasn't eaten for days, and would be willing to give you his last medkit for something to eat. He appears to be healthy and strong. There's a baseball bat among his things, but it may be out of reach if you decide to...you know, be aggressive...You could also take the high road: trade with him or refuse his offer and leave." << endl;
            Consumable* m = new Medkit(1);
            Zloot = m;
            return num;
        }
        else
        {
            cout << "A stranger aproaches you, bleeding heavily from the arm. He offers you 4 hgbullets in return for a medkit, saying that he lost his weapon when fleeing from a group of zombies and the ammo is worthless to him now. Given his injury, he seems vulnerable, but in his right hand he is tightly clutching a wooden bat. You can also simply refuse his trade request and leave the area. So what will it be?" << endl;
            Consumable* hg = new HandgunAmmo(4);
            Zloot = hg;
            return num;
        }
    }
    bool run();
    void attack(Player* p, World* A)
    {
        srand(time(NULL));
        if (rand() % 100 + 1 > zStats.hitRate)
        {
            p -> setHealth((-1)*(zStats.damage * A->difficulty));
            int num = rand() % 3 + 1;
            if (num == 1)
            {
                cout << "The survivor struck you with his bat!" << endl;
            }
            else if (num == 2)
            {
                cout << "He hits you over the head, leaving you disoriented for a moment.\n";
            }
            else
            {
                cout << "The survivor hits you in the jaw. You spit out some blood and get ready for the next attack.\n";
            }
            if (p -> checkDeath())
            {
                cout << "You have died. It isn't cowardly to run away. Try picking fights you think you can win. Thank you for playing!!!" << endl;
                exit(0);
            }
        }
        else
        {
            int num = rand() % 3 + 1;
            if (num == 1)
            {
                cout << "A swing and a miss! You evaded the survivor's attack." << endl;
            }
            else if (num == 2)
            {
                cout << "You barely dodged his swing at you. Better not let him get that close again.\n";
            }
            else
            {
                cout << "You jump back before he can hit you.\n";
            }
        }
    }
};
class hardBoss : public Zombie //Even though survivor is not a zombie it acts like one when you fight it.
{
public:
    hardBoss () : Zombie()
    {
        zStats.damage = 40, zStats.hitRate = 10, health = 200;
        if (hasLoot == true)
        {
            boosLoot();
        }
    }
    void isAttacking();
    int dialogue()
    {
        return 0;
    }
    bool run();
    void attack(Player* p, World* A)
    {
        srand(time(NULL));
        if (rand() % 100 + 1 > zStats.hitRate)
        {
            p -> setHealth((-1)*(zStats.damage * A->difficulty));
            int num = rand() % 3 + 1;
            if (num == 1)
            {
                cout << "The large, angry man struck you with his bat!" << endl;
            }
            else if (num == 2)
            {
                cout << "He punches you...very, very hard.\n";
            }
            else
            {
                cout << "He kicks you directly in the chest, knocking the wind out of you.\n";
            }
            if (p -> checkDeath())
            {
                cout << "You have died. Makes sense, he had way cooler stuff than you. And to think you were so close to victory. Too bad this game is so hard, now you have to start over.\n";
                exit(0);
            }
        }
        else
        {
            int num = rand() % 3 + 1;
            if (num == 1)
            {
                cout << "A swing and a miss! Good thing too, those spikes look really pointy." << endl;
            }
            else if (num == 2)
            {
                cout << "You barely dodged his swing at you. Better not let him get that close again.\n";
            }
            else
            {
                cout << "You jump back before he can hit you.\n";
            }
        }
    }
};
bool Zombie::runaway(int n)
{
    srand(time(NULL));
    int num = rand() % n + 1;
    if (num == 1)
        return false;
    return true;
}
void standardZombie::isAttacking()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (num == 1)
        cout << "A zombie is coming after you! What should you do?" << endl;
    else if (num == 2)
        cout << "Watch out! A zombie is attacking! What do you do?" << endl;
    else
        cout << "You came across a zombie! What do you want to do?" << endl;
}
bool standardZombie::run()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (runaway(3)==true)
        return true;
    if (num==1)
        cout << "The zombie caught you and bit your shoulder in the process. What are you going to do now?" << endl;
    else if (num ==2)
        cout << "You were cornered and bit! You manage to push it off but it's still coming! What do you do now?" << endl;
    else if (num ==3)
        cout << "You got away from the first zombie but ran right into another! It bit you and is still attacking! What do you do?" << endl;
    return false;
}
void armoredZombie::isAttacking()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (num == 1)
        cout << "Oh no! An armored zombie has noticed you! Given his military attire, he might have ammo. What do you do?\n";
    else if (num == 2)
        cout << "A zombie is attacking you! He's wearing body armor and might be harder to take down. What do you want to do?\n";
    else
        cout << "A zombie has found you! This one has a riot suit on, and may be holding valuable supplies. What do you do now?" << endl;
}
bool armoredZombie::run()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (runaway(4)==true)
        return true;
    if (num==1)
        cout << "You couldn't get away! It bit your arm during your failed attempt. What do you do now?" << endl;
    else if (num ==2)
        cout << "You tripped and got bit! The zombie is still after you! What do you do now?" << endl;
    else if (num ==3)
        cout << "You failed to escape! This zombie is more nimble than he looks. What should you do now?" << endl;
    return false;
}
void crawlerZombie::isAttacking()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (num == 1)
        cout << "A pesky crawler zombie is inching towards you. What do you want to do?" << endl;
    else if (num == 2)
        cout << "You've been inconvenienced by a puny crawler zombie. What do you do?" << endl;
    else
        cout << "You notice a zombie that has been severed in half making its way slowly towards you. What do you do?\n";
}
bool crawlerZombie::run()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (runaway(5)==true)
        return true;
    if (num==1)
        cout << "It blocked you off and bit your leg...you aren't very athletic are you? The thing doesn't even have legs! Whatever, what do you do now?" << endl;
    else if (num ==2)
        cout << "It grabbed you and took a chunk out of your leg! This was entirely avoidable if you just put the thing out of its misery. What do you want to do now?" << endl;
    else if (num ==3)
        cout << "You tripped and it was able to bite your hand! Great. Now you're bleeding and the crawler is in a frenzy. What do you do?" << endl;
    return false;
}
void npc1::isAttacking()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (num == 1)
        cout << "You chose to attack the survivor. He expected this, and is prepared to fight you." << endl;
    else if (num == 2)
        cout << "You try to kill the survivor but he's ready for it!" << endl;
    else
        cout << "You advance towards him, and he readies himself for defense!" << endl;
    //adjust health
}
bool npc1::run()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (num == 1)
        cout << "The survivor isn't as slow as the zombies! You failed to escape! He was able to deal a devastating blow to your rib cage during your attempt\n";
    else if (num == 2)
        cout << "He caught you with ease, hitting you with his bat! Before the infection this guy must have been an olympian or something." << endl;
    else
        cout << "This survivor is still really upset with you for trying to kill him. Wonder why. He swings and makes contact with your knee, stopping your foolish attempt to escape." << endl;
    return false;
}
void hardBoss::isAttacking()
{cout << endl << "Just as you've finished assembling the radio, a man steps out from the shadows. A really big, really well equipped man. Like seriously, finding this radio would have been so much easier if you had everything he does, he really outclasses you as far as gear is concerned. And is that a zombie head he's carrying? Hopefully he's friendly...(type 'go' when ready to continue)" << endl;
    string a;
    getline(cin, a);
    if (a != "go")
    {
        while (a != "go")
        {
            getline(cin,a);
        }
    }
    cout << "..." << endl;
    usleep(999999);
    cout << "..." << endl;
    usleep(999999);
    cout << "..." << endl;
    usleep(999999);
    cout << "He pulls out a very large, very bloody, spiked metal bat and rests it on his shoulder. It would appear the big brute does not want to be your friend...";
    usleep(1999999);
    cout << endl << endl << "'Thanks for collecting all these radio parts for me, I've been following you for quite some time, letting you do all the dirty work. Now hand it over.'" << endl <<  "'No chance!' you say stubbornly, foolishly even." << endl << "The behemoth releases an angry grunt. 'Fine then, guess you'll have to die. Such a pity, but you asked for it!!!'\n";}
bool hardBoss::run()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (num == 1)
        cout << "He's not going to let you go.\n";
    else if (num == 2)
        cout << "You tried escaping, but his shoes are just better than yours. Should have gotten some better shoes for the apocalypse." << endl;
    else
        cout << "He really wants that radio, it doesn't look like you're going to escape." << endl;
    return false;
}

