#include <iostream>
#include <map>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <ctime>
using namespace std;

enum ObjectType{
    NOT_NUMBER,
    NUMBER
};

class System;

class Player{
private:
    int pinpos,id;
    string colour,name;
    static int cnt;
public:
    Player(string);
    void chooseColour(System&,string);
    int getPinPos();
    string getName();
    int getId();
    void setPinPos(int);
    int roll();
};

class System
{
    public:
        System(map<int,int>);
        bool isUniqueColour(string);
        bool isPlayable();
        int changePinPos(Player&,ObjectType,int);
        void declareWinner(Player&);
        bool addPlayer(Player&);
        void play();

    private:
        set<string> colours;
        vector<Player> players;
        map<int,int> ladders_snakes;
};

// System Methods
System::System(map<int,int> ladders_snakes){
    this->players.clear();
    this->ladders_snakes = ladders_snakes;
    this->colours.clear();
}

bool System::isUniqueColour(string colour){
    if(colours.find(colour)==colours.end()){
        colours.insert(colour);
        return true;
    }
    return false;
}

bool System::isPlayable(){
    if(players.size()>=2){
        return true;
    }
    return false;
}

void System::declareWinner(Player& p){
    cout<<"Game Over!!!\nWinner is "<<p.getName()<<endl;
    cout<<"Other Player Scores:\n";
    for(Player& player: players){
        if(player.getId() != p.getId()){
            cout<<player.getName()<<" : "<<player.getPinPos()<<endl;
        }
    }
}

bool System::addPlayer(Player& player){
    players.push_back(player);
    return true;
}

void System::play(){
    if(isPlayable()){
       bool winnerFound = false;
        while(!winnerFound){
            for(Player &player: players){
                int pos = player.getPinPos();
                int val = player.roll();
                if(ladders_snakes.find(val)!=ladders_snakes.end()){
                    pos = ladders_snakes[val];
                }
                else{
                    pos += val;
                }
                player.setPinPos(pos);
                if(pos == 100){
                    declareWinner(player);
                    winnerFound = true;
                    break;
                }
            }
        }
    }
    else{
        cout<<"Insufficient players!!! Required more players\n";
    }

}

// Player Methods
int Player::cnt = 0;

Player::Player(string name){
    this->name = name;
    id = ++cnt;
    pinpos = 0;
}

int Player::getPinPos(){
    return pinpos;
}

int Player::getId(){
    return id;
}

void Player::setPinPos(int val){
    pinpos = val;
}

string Player::getName(){
    return name;
}

void Player::chooseColour(System& s,string colour){
    if(s.isUniqueColour(colour)){
        this->colour = colour;
    }
}

int Player::roll(){
    srand((unsigned)time(0));
    return (rand()%6)+1;
}

int main()
{
    Player p1("Robert");
    Player p2("Stannis");
    Player p3("Renly");

    map<int,int> sl;
    sl[17] = 7;
    sl[54] = 34;
    sl[62] = 19;
    sl[64] = 60;
    sl[87] = 36;
    sl[92] = 73;
    sl[95] = 75;
    sl[98] = 79;
    sl[1] = 38;
    sl[4] = 14;
    sl[9] = 31;
    sl[21] = 42;
    sl[28] = 84;
    sl[51] = 67;
    sl[72] = 91;
    sl[80] = 99;

    System game(sl);
    game.addPlayer(p1);
    game.play();
    game.addPlayer(p2);
    game.addPlayer(p3);

    game.play();

    return 0;
}
