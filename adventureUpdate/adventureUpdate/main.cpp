
#include <iostream>     /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "fight.h"

using namespace std;
int pickZ;
int findS;
int dResult;
int tempX, tempY;
string command;
string input;
string tutorial;

//add more outputs. test armored zombie loot drop, zombie rush mode

int main()
{
    cout << "Would you like to see the tutorial? (y,n)" << endl;
    getline(cin, tutorial);
    if (tutorial == "y" || tutorial == "yes")
        cout << endl << "Welcome to Zombie Wasteland! The game world is randomly generated, being filled with zombies (obviously), open spaces (where you can find loot or encounter survivors), and buildings (5 set structures containing loot, and radio parts). The object of the game is to collect all 5 radio parts in order to build a working radio that you can use to call for evac. You have a persistent inventory and map that can be checked at any time you are not in an encounter by typing 'inventory' or 'map'. Picking up items and looting fallen enemies is handled automatically, but inventory management, such as repairing weapons (using duct tape) or consuming food/water is up to you. There are survivor encounters that offer you the opportunity to interact with non-dead characters, including a trading system. Check your status often (by typing 'status') to keep an eye on your thirst level and health. You would hate to die by thirst when you have water bottles sitting unused in your inventory. You will get thirstier as you walk around the game world as well as when attempting to flee from zombies when in battle. Combat is basic (you'll pick it up quickly), but you can run out of health quickly if you aren't careful. You can choose to run from zombies, but escape is not guaranteed, and consequences can be heavy. As you progress through the game you may find stronger weapons that will help you deal with the undead, namely the elusive but incredibly powerful shotgun (only attainable as a random drop from armored zombies). Enjoy!" << endl << endl << "Tip: Type 'help' at any time to see a list of possible commands." << endl << endl;
    double modifier;
    while (true)
    {
        cout << "Easy mode or Hard mode? (e/h/explain)" << endl;
        getline(cin, tutorial);
        if (tutorial == "e" || tutorial == "easy")
        {
            modifier = 1;
            break;
        }
        else if (tutorial == "h" || tutorial == "hard")
        {
            modifier = 1.2;
            break;
        }
        else
            cout << "Easy mode is the base game, and your map will show the locations of the buildings you need to reach. Hard mode is not for the faint of heart, and is not recommended for first time players. Hard mode features an increased number of zombies who also deal increased damage. In easy mode, zombie health will be displayed while you are in battle, but in hard mode it will not. You will start thirstier and with less health in hard mode, and you will start with fewer supplies. Your map will not show building locations, and the game world will scramble as zombies 'move', making it possible for previously visited spaces to no longer be safe. This scramble is indicated by a passage of time. Also, there is someone else trying to find a radio in hard mode, which may add an additional challenge." << endl << endl;
    }
    World A = World::createWorld(15, 186 - (modifier * 50), 19 + (modifier * 50), 5, 15);
    if (tutorial == "e" || tutorial == "easy")
    {
        A.difficulty = modifier;
        A.renderMap();
    }
    else
        A.difficulty = modifier;
    //Main notable features: natural language parsing (flexibility in text input) and delayed output (using thread stoppage via the sleep function).;
    //A.visualize();
    Player t(7, 7, 150 - (modifier * 50), 150 - (modifier * 50), 0);
    //    cout << t.checkBackpackSize();
    Weapon* b = new Bat;
    t.pickUp(b);
//    Weapon* hg = new Handgun;
//    t.pickUp(hg);
//    Consumable* hgammo = new HandgunAmmo(20);
//    t.pickUp(hgammo);

    if (A.difficulty == 1)
    {
        Consumable* w = new WaterBottle (1);
        Consumable* m = new Medkit (1);
        t.pickUp(w);
        t.pickUp(m);
    }
//    t.pickUp(&jerky);
//    t.pickUp(&ducttape);
    //    t.checkBackpack();
    //    cout << t.checkBackpackSize();
    //    t.dropItem(&bat);
    //    t.checkBackpack();
    //    t.checkBackpackSize();
    //cout backstory
    cout << "You wake up to the sound of groans in the distance. Another day in the zombie apocalypse has begun. You grab your bat and head out into the carnage." << endl;
    while(true)
    {
        tempX = t.getLocationX(), tempY = t.getLocationY();
        if (t.getSteps() == 5 && modifier == 1.2)
        {
            A.scramble(A.getLineCount(), t.getLocationX(), t.getLocationY());
            t.setSteps(-5);
            cout << "Several hours have passed..." << endl;
        }
        srand(time(NULL));
        int num = rand() % 3 + 1;
        if (num == 1)
            cout << "What now?" << endl;
        else if (num == 2)
            cout << "What's next?" << endl;
        else
            cout << "Now what?" << endl;
        getline(cin, command);
        handleString(command, &t, &A);
        if (A.checkMap(t.getLocationX(), t.getLocationY()) == 'Z')
            tempX-=4;
        if (tempX != t.getLocationX() || tempY != t.getLocationY())
        {
            if(A.checkMap(t.getLocationX(), t.getLocationY()) == 'D')
            {
                if (num == 1)
                    cout << "This area looks familiar. The zombie you killed earlier is lying on the pavement, rotting away." << endl;
                else if (num == 2)
                    cout << "You pass by the zombie you killed earlier" << endl;
                else if (num == 3)
                    cout << "The birds picking at the corpse of the zombie you killed recently scatter as you approach." << endl;
            }
            if (A.checkMap(t.getLocationX(), t.getLocationY()) == 'Z')
            {
                srand(time(NULL));
                pickZ = rand() % 10 + 1;
                if (pickZ >= 1 && pickZ <= 5)
                {
                    standardZombie z;
                    startFight(&z, &t, &A);
                }
                else if (pickZ >= 6 && pickZ <= 8)
                {
                    crawlerZombie z;
                    startFight(&z, &t, &A);
                }
                else
                {
                    armoredZombie z;
                    startFight(&z, &t, &A);
                }
            }
            if (A.checkMap(t.getLocationX(), t.getLocationY()) == 'Z')
            {
                srand(time(NULL));
                pickZ = rand() % 10 + 1;
                if (pickZ <=5)
                {
                    standardZombie z;
                    startFight(&z, &t, &A);
                }
                else if (pickZ >= 6 && pickZ <=8)
                {
                    crawlerZombie z;
                    startFight(&z, &t, &A);
                }
                else
                {
                    armoredZombie z;
                    startFight(&z, &t, &A);
                }
            }
            if (A.checkMap(t.getLocationX(), t.getLocationY()) == 'Z')
            {
                srand(time(NULL));
                pickZ = rand() % 10 + 1;
                if (pickZ <=5)
                {
                    standardZombie z;
                    startFight(&z, &t, &A);
                }
                else if (pickZ >= 6 && pickZ <=8)
                {
                    crawlerZombie z;
                    startFight(&z, &t, &A);
                }
                else
                {
                    armoredZombie z;
                    startFight(&z, &t, &A);
                }
            }
            if (A.checkMap(t.getLocationX(), t.getLocationY()) == 'Z')
            {
                srand(time(NULL));
                pickZ = rand() % 10 + 1;
                if (pickZ <=5)
                {
                    standardZombie z;
                    startFight(&z, &t, &A);
                }
                else if (pickZ >= 6 && pickZ <=8)
                {
                    crawlerZombie z;
                    startFight(&z, &t, &A);
                }
                else
                {
                    armoredZombie z;
                    startFight(&z, &t, &A);
                }
            }
            else if(A.checkMap(t.getLocationX(), t.getLocationY()) == 'X')
            {
                if (num == 1)
                    cout << "You've been here recently. Nothing seems to have changed." << endl;
                else if (num == 2)
                    cout << "You've already passed through this area. There is nothing to scavenge." << endl;
                else if (num == 3)
                    cout << "You see nothing new since the last time you were here." << endl;
            }
            if (A.checkMap(t.getLocationX(),t.getLocationY()) == 'F')
            {
                cout << "You stumble across a farm." << endl;
                cout << "The first thing you notice is the smell. You've been to farms before, but this is beyond that. Manure mixed with decaying corpses is not something you will want to smell again for a long time. There are some supports that are missing, presumably taken by other survivors to make their shelter. Out of the corner of your eye, you see a radio part next to the window. You pick it up." << endl;
                A.setMap(t.getLocationX(), t.getLocationY(), 'X');
                t.setRadio();
                
                if (t.getRadio() == 5)
                {
                    if(A.difficulty == 1)
                    {
                        cout << "You quickly assemble all the radio parts together. After a few minutes of yelling into the speaker, you hear a response. They say that they are sending a helicopter to your location. Finally. You look forward to being in the company of other people. You are grateful that you were able to get out alive. Now you can start rebuilding your life." << endl << endl;
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                    else
                    {
                        hardBoss z;
                        startFight(&z, &t, &A);
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                }
                
            }
            if (A.checkMap(t.getLocationX(),t.getLocationY()) == 'T')
            {
                cout << "You stumble across a school." << endl;
                cout << "You remember your years in school. You always hated it. Always trying to find a way to sneak out. Hopefully these kids were able to get out. What a terrible way to go, stuck in school. As you snap back into reality, you notice a radio part sitting in a locker. You take it." << endl;
                A.setMap(t.getLocationX(), t.getLocationY(), 'X');
                t.setRadio();
                
                if (t.getRadio() == 5)
                {
                    if(A.difficulty == 1)
                    {
                        cout << "You quickly assemble all the radio parts together. After a few minutes of yelling into the speaker, you hear a response. They say that they are sending a helicopter to your location. Finally. You look forward to being in the company of other people. You are grateful that you were able to get out alive. Now you can start rebuilding your life." << endl << endl;
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                    else
                    {
                        hardBoss z;
                        startFight(&z, &t, &A);
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                }
                
            }
            if (A.checkMap(t.getLocationX(),t.getLocationY()) == 'M')
            {
                cout << "You stumble across a factory." << endl;
                cout << "You used to work at a factory like this. Terrible hours, even worse pay. Your boss was terrible. But it paid the bills. If you could do it all over again, you'd still probably work here. It was all you knew. Mixed in with the broken machinery, you notice a radio part. You grab it." << endl;
                A.setMap(t.getLocationX(), t.getLocationY(), 'X');
                t.setRadio();
                
                if (t.getRadio() == 5)
                {
                    if(A.difficulty == 1)
                    {
                        cout << "You quickly assemble all the radio parts together. After a few minutes of yelling into the speaker, you hear a response. They say that they are sending a helicopter to your location. Finally. You look forward to being in the company of other people. You are grateful that you were able to get out alive. Now you can start rebuilding your life." << endl << endl;
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                    else
                    {
                        hardBoss z;
                        startFight(&z, &t, &A);
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                }
            }
            if (A.checkMap(t.getLocationX(),t.getLocationY()) == 'L')
            {
                cout << "You stumble across a laboratory." << endl;
                cout << "Before the infection, this must have been a very successful science facility. You see all sorts of machines that you couldn't name if your life depended on it. There are chemicals spilled everywhere. You can hear electricity sparking somewhere in the distance. You also see a radio part in a cabinet. You grab it." << endl;
                A.setMap(t.getLocationX(), t.getLocationY(), 'X');
                
                t.setRadio();
                
                if (t.getRadio() == 5)
                {
                    if(A.difficulty == 1)
                    {
                        cout << "You quickly assemble all the radio parts together. After a few minutes of yelling into the speaker, you hear a response. They say that they are sending a helicopter to your location. Finally. You look forward to being in the company of other people. You are grateful that you were able to get out alive. Now you can start rebuilding your life." << endl << endl;
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                    else
                    {
                        hardBoss z;
                        startFight(&z, &t, &A);
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                }
            }
            if (A.checkMap(t.getLocationX(),t.getLocationY()) == 'H')
            {
                cout << "You stumble across a house." << endl;
                cout << "Upon entering, you notice the furniture is overturned. Pictures are broken, the cabinets are open, and it smells of death. Whoever used to live here has been gone for a long time. It looks like it was used as a shelter recently. Hopefully they don't come back soon. You notice a piece of a radio on the table. You take it." << endl;
                A.setMap(t.getLocationX(), t.getLocationY(), 'X');
                t.setRadio();
                
                if (t.getRadio() == 5)
                {
                    if(A.difficulty == 1)
                    {
                        cout << "You quickly assemble all the radio parts together. After a few minutes of yelling into the speaker, you hear a response. They say that they are sending a helicopter to your location. Finally. You look forward to being in the company of other people. You are grateful that you were able to get out alive. Now you can start rebuilding your life." << endl << endl;
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                    else
                    {
                        hardBoss z;
                        startFight(&z, &t, &A);
                        cout << "CONGRATULATIONS! You have successfully survived the zombie apocalypse! But can you do it again? Try again and see if you are up to that task. Thanks for playing!!!";
                        exit(0);
                    }
                }
            }
            if (A.checkMap(t.getLocationX(), t.getLocationY()) == 'S')
            {
                srand(time(NULL));
                findS = rand() % 20 +1;
                if (findS == 1 || findS == 7)
                {
                    int temp;
                    npc1 s;
                    temp = s.dialogue();
                    getline(cin, input);
                    handleDialogueString(input, &t, &s, &A, temp);
                }
                else if (findS == 2)
                {
                    if (t.getBackpack().searchVector("crowbar") != string::npos)
                    {
                        cout << "You found another crowbar. This one has more weight to it, so you take this one and leave your old one." << endl;
                        t.getBackpack()[t.getBackpack().searchVector("crowbar")]->reset(25,15);
                    }
                    else{
                    Weapon* cb = new Crowbar;
                    t.pickUp(cb);
                    cout << "Found a crowbar. This will crack a few skulls." << endl;
                    }
                }
                else if (findS == 3)
                {
                    if (t.getBackpack().searchVector("knife") != string::npos)
                    {
                        cout << "You found another knife. This one is sharper, so you replace your older model with this one." << endl;
                        t.getBackpack()[t.getBackpack().searchVector("knife")]->reset(35,10);
                    }
                    else{
                    Weapon* k = new Knife;
                    t.pickUp(k);
                    cout << "Found a knife. A zombie killing machine." << endl;
                    }
                }
                else if (findS == 14)
                {
                    cout << "You found a bat. This one seems far more sturdy. You take it with you, leaving your old one behind" << endl;
                    t.getBackpack()[t.getBackpack().searchVector("bat")]->reset(15,15);
                }
                else if (findS == 19)
                {
                    srand(time(NULL));
                    if (1 == rand() % 2 + 1)
                    {
                        if (t.getBackpack().searchVector("handgun") != string::npos)
                        {
                            int ammochange = rand() % 3 + 2;
                            if (t.getBackpack().searchVector("hgbullet") != string::npos)
                            {
                                t.changeConsumableCount("hgbullet", ammochange);
                                cout << "You found another handgun, but since you already have one, you just scavenged the " << ammochange << " bullets left in this one." << endl;
                            }
                            else
                            {
                                Consumable* hgammo = new HandgunAmmo(ammochange);
                                t.pickUp(hgammo);
                                cout << "You found another handgun, but since you already have one, you just scavenged the " << ammochange << " bullets left in this one." << endl;
                            }
                        }
                        else
                        {
                            Weapon* HG = new Handgun;
                            t.pickUp(HG);
                            cout << "Found a handgun! This changes everything." << endl;
                        }
                    }
                    else
                    {
                        srand(time(NULL));
                        if (t.getBackpack().searchVector("hgbullet") != string::npos)
                        {
                            t.changeConsumableCount("hgbullet", rand() % 2 +1);
                            cout << "You found more hand gun ammo." << endl;
                        }
                        else{
                        Consumable* hgammo = new HandgunAmmo(rand() % 2 + 1);
                        t.pickUp(hgammo);
                        cout << "You found some handgun ammunition. This will be useful at some point." << endl;
                        }
                    }
                }
                else if (findS == 5 || findS == 6 || findS == 15)
                {
                    srand(time(NULL));
                    
                    if (t.getBackpack().searchVector("water") != string::npos)
                    {
                        t.changeConsumableCount("water", rand() % 2 + 1);
                        cout << "You found some more water. You throw it in your backpack." << endl;
                    }
                    else{
                    Consumable* w = new WaterBottle (2);
                    t.pickUp(w);
                    cout << "You found a couple of water bottles. Awesome." << endl;
                    }
                }
                else if (findS == 9)
                {
                    if (t.getBackpack().searchVector("duct tape") != string::npos)
                    {
                        t.changeConsumableCount("duct tape", rand() % 2 + 1);
                        cout << "You look around and see some duct tape. You grab it." << endl;
                    }
                    else{
                        Consumable* w = new DuctTape (2);
                        t.pickUp(w);
                        cout << "You scavenged some duct tape from a backpack abandoned on the ground!" << endl;
                    }
                }
                else
                {
                    findS = rand() % 5 +1;
                    if (findS == 1)
                        cout << "There doesn't appear to be anything worth scavenging in this area." << endl;
                    else if (findS == 2)
                        cout << "There is nothing of value here." << endl;
                    else if (findS == 3)
                        cout << "This area has been picked clean of all useable resources." << endl;
                    else if (findS == 4)
                        cout << "You look around but don't find anything." << endl;
                    else
                        cout << "There is just empty street here, nothing to search." << endl;
                        
                }
                
                A.setMap(t.getLocationX(), t.getLocationY(), 'X');
                t.setSteps(1);
            }
        }
    }
}