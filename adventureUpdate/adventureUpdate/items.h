

//class Inventory
//{
//public:
//    void search(string searchTerm);
//    void render() {for(int i = 0; i < inventoryItems.size; i++) inventoryItems[i].render();}
//
//private:
//    vector<Item> inventoryItems;
//};
#include <unistd.h>
ostream& operator<<(ostream& os, const char* input)
{
    for(int i = 0; input[i] != 0; i ++)
    {
        os << input[i];
        os.flush();
        usleep(15000);
    }
    return os;
}

ostream& operator<<(ostream& os, string input)
{
    for(int i = 0; input[i] != 0; i ++)
    {
        os << input[i];
        os.flush();
        usleep(15000);
    }
    return os;
}

using namespace std;
class Item
{
protected:
    string name;
    string description;
    bool isConsumable = false;
public:
    //    string name = "";
    //    string description = "";
    Item(string a, string b) {name = a, description = b;}
    virtual void render() = 0;
    virtual int attack() = 0;
    virtual int eat() = 0;
    virtual int drink() = 0;
    virtual void use() = 0;
    virtual void repair() = 0;
    virtual void countAdjuster(int value) = 0;
    string inspect() {return description;}
    const string getName() {return name;}
    virtual const int getCount() = 0;
    const bool consumableCheck() {return isConsumable;}
    virtual void reset(int a, int b) = 0;
};
class Weapon : public Item
{
protected:
    int durability;
    int attackPower;
public:
    void countAdjuster(int value) {};
    Weapon(string a, string b, int d, int pow) : Item(a, b) {durability = d; attackPower = pow;}
    void durabilityAdjuster(int value) {durability += value;}
    int drink() {cout << "This is not a liquid.\n"; return 0;}
    void repair() {cout << "Weapon repaired.\n"; durability += 5;}
    void use() {cout << "You should probably wait to use your weapons in combat.\n";}
    void render() {cout << name << " [" << attackPower << " damage, " << durability << " durability]"; if(durability <= 0) cout << " (broken, can't be repaired) "; cout << endl;}
    const int getCount() {return durability;}
    void reset(int a, int b);
};
void Weapon::reset(int a, int b)
{
    attackPower = a;
    durability = b;
}
class Gun : public Weapon
{
protected:
public:
    Gun(string a, string b, int d, int pow) : Weapon(a, b, d, pow) {};
};
class Consumable : public Item
{
protected:
    int count;
    int healthGain;
    int waterGain;
public:
    Consumable(string a, string b, int c, int health, int w) : Item(a, b) {count = c; healthGain = health; waterGain = w; isConsumable = true;}
    int attack() {cout << "This would be a very ineffective weapon.\n"; return 0;}
    void repair() {cout << "It's not broken. You like arts and crafts though, so you put some duct tape on it anyway. Pretty, but a waste of tape.\n";}
    void countAdjuster(int value) {count += value;}
    const int getCount() {return count;}
    void render() {cout << name << "(" << count << ")\n";}
    void reset(int a, int b) {return;}
};
class Crowbar : public Weapon
{
public:
    Crowbar() : Weapon("crowbar", "A metal crowbar.", 15, 20) {};
    int attack();
    int eat();
};
int Crowbar::attack()
{
    if (durability == 2)
    {
        cout << "Your weapon is about to break!" << endl;
    }
    if(durability > 0)
    {
        srand(time(NULL));
        int num = rand() % 3 + 1;
        if (num == 1)
        {
            cout << "You strike and make contact with a sickening crunch.\n"; durabilityAdjuster(-1); return attackPower;
        }
        else if (num == 2)
        {
            cout << "This is even better than the movies!\n"; durabilityAdjuster(-1); return attackPower;
        }
        else
        {
            cout << "You hit him so hard it bends the crowbar a little.\n"; durabilityAdjuster(-1); return attackPower;
        }
    }
    else
    {
        cout << "Crowbar is broken, you can't attack with it.\n"; return 0;
    }
}
int Crowbar::eat()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (num == 1)
    {
        cout << "You taste metal. You decide not to pursue this idea any further for the sake of your dental health.\n"; return 0;
    }
    else if (num == 2)
    {
        cout << "There's no way you can get the whole thing down. Better not try.\n"; return 0;
    }
    else
    {
        cout << "You spend a few minutes chewing on it before you give up.\n"; return 0;
    }
}
class Bat : public Weapon
{
public:
    Bat() : Weapon("bat", "A wooden baseball bat.", 10, 15) {};
    int attack();
    int eat();
};
int Bat::attack()
{
    if (durability == 2)
        cout << "Your weapon is about to break!" << endl;
    if(durability > 0)
    {
        srand(time(NULL));
        int num = rand() % 6 + 1;
        if (num == 1)
        {
            cout << "You remember your little league days and swing hard. You make contact with a satisfying smack.\n"; durabilityAdjuster(-1); return attackPower;
        }
        else if (num == 2)
        {
            cout << "Just like a piñata. A big, blood-filled piñata.\n"; durabilityAdjuster(-1); return attackPower;
        }
        else if (num == 3)
        {
            cout << "As you hit him, you realize you had a real shot to go to the MLB before that knee injury...\n"; durabilityAdjuster(-1); return attackPower;
        }
        else if (num == 4)
        {
            cout << "Flesh meets pine as you strike with all your might." << endl; durabilityAdjuster(-1); return attackPower;
        }
        else if (num == 5)
        {
            cout << "A bloody mist sprays out of his head. Who knew murder could be so fun?" << endl; durabilityAdjuster(-1); return attackPower;
        }
        else
        {
            cout << "WHACK. The sound echoes and your hands sting. A solid hit." << endl; durabilityAdjuster(-1); return attackPower;
        }
    }
    else
    {
        cout << "Bat is broken, you can't attack with it.\n"; return 0;
    }
    return 0;
}
int Bat::eat()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (num == 1)
    {
        cout << "Better not, you don't want to get splinters.\n"; return 0;
    }
    else if (num == 2)
    {
        cout << "You've had your fill of fiber today.\n"; return 0;
    }
    else
    {
        cout << "Memories of all those years chewing on pencils come flooding back, and you begin having second thoughts.\n"; return 0;
    }
}
class Knife : public Weapon
{
public:
    Knife() : Weapon("knife", "A six inch blade. Very sharp.", 10, 30) {};
    int attack();
    int eat();
};
int Knife::attack()
{
    if (durability == 2)
        cout << "Your weapon is about to break!" << endl;
    if(durability > 0)
    {
        srand(time(NULL));
        int num = rand() % 3 + 1;
        if (num == 1)
        {
            cout << "Your blade cuts deep.\n"; durabilityAdjuster(-1); return attackPower;
        }
        else if (num == 2)
        {
            cout << "You plunge the knife into his flesh.\n"; durabilityAdjuster(-1); return attackPower;
        }
        else
        {
            cout << "You slice and dice 'em.\n"; durabilityAdjuster(-1); return attackPower;
        }
    }
    else
    {
        cout << "Knife is broken, you can't attack with it.\n"; return 0;
    }
    return 0;
}
int Knife::eat()
{
    srand(time(NULL));
    int num = rand() % 3 + 1;
    if (num == 1)
    {
        cout << "Damn, I knew I should have taken that sword swallowing class.\n"; return 0;
    }
    else if (num == 2)
    {
        cout << "Don't eat that, it's sharp.\n"; return 0;
    }
    else
    {
        cout << "You've already had your tonsils removed. Don't wanna add anything else to that list.\n"; return 0;
    }
}
class Ammunition : public Consumable
{
public:
    Ammunition(string a, string b, int c) : Consumable(a, b, c, 0, 0) {};
    int attack() {cout << "This is just ammo. Won't do you much good. Try a gun.\n"; return healthGain;}
    int eat() {cout << "Choking hazard. Better not.\n"; return 0;}
    int drink() {cout << "No.\n"; return waterGain;}
    void use() {cout << "What do you plan to do with this? Save it for a fight.\n";}
};
class Jerky : public Consumable
{
public:
    Jerky(int c) : Consumable("jerky", "Dried beef. Apocalypse proof.", c, 20, 0) {};
    int eat() {countAdjuster(-1); return healthGain;}
    int drink() {cout << "Jerky is, by definition, devoid of all water.\n"; return waterGain;}
    void use() {cout << "The only thing you would want to use jerky for is filling your stomach. Try eating it." << endl;}
};
class Handgun : public Gun
{
public:
    Handgun() : Gun("handgun", "Rooty Tooty Point and Shooty.", 1, 75) {};
    int attack() {cout << "Crack!\n"; return attackPower;}
    int eat() {cout << "Putting a gun in your mouth sounds like a really terrible idea."; return 0;}
};
class Shotgun : public Gun
{
public:
    Shotgun() : Gun("shotgun", "Point and shoot becomes point and obliterate with this well crafted weapon.", 1, 125) {};
    int attack() {cout << "BOOM!\n"; return attackPower;}
    int eat() {cout << "Putting a gun in your mouth sounds like a really terrible idea."; return 0;}
};
class Medkit : public Consumable
{
public:
    Medkit(int c) : Consumable("medkit", "Fully restores health.", c, 100, 0) {};
    int eat() {countAdjuster(-1); return healthGain;}
    int drink() {cout << "Unfortunately, the zombie apocalypse occured before the invention of drinkable medkits.\n"; return waterGain;}
    void use() {cout << "It's full of pills, antibiotics and the like. Try eating them instead.\n";}
};
class WaterBottle : public Consumable
{
public:
    WaterBottle(int c) : Consumable("water", "20 fluid ounces of revitalizing H20.", c, 0, 30) {};
    int eat() {cout << "Don't eat that, it's plastic.\n"; return healthGain;}
    int drink() {countAdjuster(-1); return waterGain;}
    void use() {cout << "Use for what? You aren't a firefighter, save this for drinking.";}
};
class DuctTape : public Consumable
{
public:
    DuctTape(int c) : Consumable("duct tape", "Sticky magic. Can be used to repair weapons.", c, 0, 0) {};
    int eat() {cout << "I like sticky foods too, but this is just ridiculous.\n"; return healthGain;}
    int drink() {cout << "Duct tape is one adhesive you can't drink. Maybe try glue if that's your thing.\n"; return waterGain;}
    void use() {cout << "'Use' is kind of a broad term. Maybe try 'repair'.\n";}
};
class HandgunAmmo : public Ammunition
{
public:
    HandgunAmmo(int c) : Ammunition("hgbullet", "Ammo for your handgun you dummy.", c) {};
};
class ShotgunAmmo : public Ammunition
{
public:
    ShotgunAmmo(int c) : Ammunition("sgshell", "Buckshot. Deadly, but only if you have a shotgun. Otherwise, it's a decent paperweight.", c) {};
};