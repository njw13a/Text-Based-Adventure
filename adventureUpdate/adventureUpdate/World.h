//
//  Header.h
//  Text Based Adventure XCode
//
//  Created by Nicholas Weg on 11/10/15.
//  Copyright (c) 2015 Nicholas Weg. All rights reserved.
//

#include <math.h>
#include <vector>
using namespace std;
using std::vector;
class World
{
private:
    int map_size;
    vector<vector<char> > layout;
    int map_hold;
    int s_count = 0, z_count = 0, b_count = 0, i_count = 0;
    int line_count = 0;
    int buildings = 5;
    double safe_percent, zombie_percent, building_percent, impasse_percent;
    vector<char> bnames = {'L', 'M', 'H', 'F', 'T'};
    vector<vector<char> > map;
    World(int lineCount, int safePercent, int zombiePercent, int buildingPercent, int impassePercent);
public:
    static World& createWorld(int world_size, int safePercent, int zombiePercent, int buildingPercent, int impassePercent)
    {
        static World A(world_size, safePercent, zombiePercent, buildingPercent, impassePercent);
        return A;
    }
    int getMapHold() {return map_hold;}
    int getLineCount() {return line_count;}
    char checkMap(int coordinateX, int coordinateY) {return layout[coordinateX][coordinateY];}
    void setMap(int coordinateX, int coordinateY, char a) {layout[coordinateX][coordinateY] = a;}
    void render();
    void visualize();
    void decrementBuilding() {buildings--;}
    int getBuilding() {return buildings;}
    char getBNames(int n) {return bnames[n];}
    void setBNames(int n) {bnames.erase(bnames.begin()+n);}
    void scramble(int y, int a, int b);
    void printMap();
    double difficulty;
    void setMap2(int coordinateX, int coordinateY, char a) {map[coordinateX][coordinateY] = a;}
    char checkMap2(int coordinateX, int coordinateY) {return map[coordinateX][coordinateY];}
    void renderMap();
};
void World::scramble(int y, int a, int b)
{
    srand(time(NULL));
    for (int c = 0; c < y; c++)
    {
        for (int z = 0; z < y; z++)
        {
            if (layout[c][z] == 'S' || layout[c][z] == 'Z' || layout[c][z] == 'X' || layout[c][z] == 'D')
            {
                int p = rand() % 1000 + 1;
                //cout << "P = " << p << endl;
                if (p <=700)
                    layout[c][z] = 'S';
                else
                    layout[c][z] = 'Z';
            }
        }
    }
    layout[a][b] = 'X';
}

//Constructor for World
World::World(int lineCount, int safePercent, int zombiePercent, int buildingPercent, int impassePercent)
{
    map_size = lineCount * lineCount;                   //Set the map size
    map_hold = map_size;                                //map_hold set because map_size will be decremented
    safe_percent = safePercent;
    zombie_percent = safePercent + zombiePercent;
    building_percent = buildingPercent;
    impasse_percent = impassePercent;
    line_count = lineCount;
    layout.resize(line_count); //Set the size of the first vector for 2D array
    map.resize(line_count);
    for (int i = 0; i < line_count; i++)
    {
        layout[i].resize(line_count); //Set the size of the second vector for 2D array
        map[i].resize(line_count);
    }
    render();   //Create the world
}

void World::render()
{
    srand(time(NULL));                                  //Random seed for generator
    for(int c = 0; c < line_count; c++)
    {
    for(int x = 0; x < line_count; x++)
    {
        if (c == 7 && x == 7)
        {
            map_size--;
            safe_percent--;
            zombie_percent--;
            building_percent--;
            s_count++;
            layout[c][x] = 'X';
            map[c][x] = 'P';
        }
        else
        {
            int hold;
            hold = rand() % map_size + 1;
            //cout << hold << endl;
            map_size--;
            //cout << "map_size: " << map_size << endl;
            if (hold <= safe_percent)
            {
                safe_percent--;
                zombie_percent--;
                building_percent--;
                s_count++;
                layout[c][x] = 'S';
                map[c][x] = 'O';
            }
            else if (hold > safe_percent && hold <= zombie_percent)
            {
                zombie_percent--;
                building_percent--;
                z_count++;
                layout[c][x] = 'Z';
                map[c][x] = 'O';
            }
            else if (hold >zombie_percent && hold <= zombie_percent+impasse_percent)
            {
                impasse_percent--;
                building_percent--;
                layout[c][x] = 'I';
                map[c][x] = 'O';
                i_count++;
            }
            else
            {
                srand(time(NULL));
                int z = 0;
                z = rand() % getBuilding();
                vector<string> hold;
                for (int y = 0; y < getBuilding(); y++)
                {
                    if (z == y)
                    {
                        layout[c][x] = getBNames(z);
                        map[c][x] = 'O';
                        setBNames(y);
                    }
                }
                decrementBuilding();
                
                building_percent--;
                b_count++;
            }
        }
    }
    }
    //cout << s_count << " " << z_count << " " << b_count << " " << i_count << endl;
    //layout[(line_count-1)/2][(line_count-1)/2] = 'P';               //Set player in the middle of the map
}

void World::visualize()
{
    for(int x = 0; x < line_count; x++)
    {
        for(int y = 0; y < line_count; y++)
        {
            cout << layout[x][y] << " ";
        }
        cout << endl;
    }
}

string legend[6] = {"P = Player", "O = Unexplored space", "X = Visited space", "I = Impasse", "B = Building (only visible in easy mode)", "? = Looked at, but not visited space"};
void World::printMap()
{
    for(int x = 0; x < line_count; x++)
    {
        for(int y = 0; y < line_count; y++)
        {
            cout << map[x][y] << " ";
        }
        if(x < 6)
            cout << "       " << legend[x];
        cout << endl;
    }
}
void World:: renderMap()
{
    for(int x = 0; x < line_count; x++)
    {
        for(int y = 0; y < line_count; y++)
        {
            if (layout[x][y] == 'L' || layout[x][y] == 'M' || layout[x][y] == 'H' || layout[x][y] == 'F' || layout[x][y] == 'T')
                map[x][y] = 'B';
        }
    }
}