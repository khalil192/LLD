#include<iostream>
#include<vector>
#include<map>

using namespace std;



class Dice{
    public:
    Dice(){
        srand(time(NULL));
    }

    int RollDice(int numFaces, int numDices){
        int yet = 0;
        for(int i =0;i<numDices;i++){
            yet += ((rand()%numFaces) + 1);
        }
        return yet;
    }
};

class Player{

    public:
        int id,positionOnBoard;
        string name;

    Player(string name){
        this->name = name;
        positionOnBoard = 0;
    }

};

class Game{

    public:

        vector<int> Board;
        vector<Player*> players;

        map<int,int> snakes;
        map<int,int> ladders;
        Dice* dice;

        vector<Player*> winners;
        bool endOnFirstPlayer;
        int numCells,numMovesYet,numPlayers, numDiceFaces,numDicesToRoll;

        Game(int numCells,int numDiceFaces, int numDicesToRoll, bool endOnFirstWin){
            this->numCells = numCells;
            Board.resize(numCells);
            this->numDiceFaces = numDiceFaces;
            this->numDicesToRoll = numDicesToRoll;
            numMovesYet = 0;
            numPlayers = 0;
            endOnFirstPlayer = endOnFirstWin;
            dice = new Dice();
        }

        void addPlayer(Player *p){
            players.push_back(p);
            numPlayers ++;
        }

        void AddSnake(int x, int y){
            snakes[x] = y;
        }

        void AddLadder(int x,int y){
            ladders[x] = y;
        }

        void StartGame(){
                while(winners.size() == 0 || (this->endOnFirstPlayer == false && winners.size() < numPlayers)){
                    MakeAMove();
                }
                cout<<winners[0]->name<<" won the game first\n";
        }

        Player* getCurrentPlayer(){
            int currIdx = numMovesYet %numPlayers;
            return players[currIdx];
        }

        void MakeAMove(){
            this->numMovesYet ++;
            Player *p = getCurrentPlayer();
            int pastPos = p->positionOnBoard;

            cout<<"player "<<p->name<<" is playing now at "<<p->positionOnBoard<<"\n";

            int rolledCount = this->dice->RollDice(this->numDiceFaces,this->numDicesToRoll);
            if(pastPos + rolledCount > numCells){
                cout<<"\n";
                return;
            }
            int currentPos = pastPos + rolledCount;
            cout<<p->name<<" rolled dice of value "<<rolledCount<<" and moved from "<<pastPos<<" to "<<currentPos<<"\n";
            do{
                if(snakes[currentPos] != 0){
                    cout<<p->name<<" landed on a snake "<<currentPos<<" -> "<<snakes[currentPos]<<"\n";
                    pastPos = currentPos;
                    currentPos = snakes[currentPos];
                }
                if(ladders[currentPos] != 0){
                    cout<<p->name<<" landed on a ladder "<<currentPos<<" -> "<<ladders[currentPos]<<"\n";
                    pastPos = currentPos;
                    currentPos = ladders[currentPos];
                }

            }while(pastPos == currentPos);

            cout<<p->name<<" is moving from "<<p->positionOnBoard<<" to "<<currentPos<<"\n\n";
            p->positionOnBoard = currentPos;

            if(currentPos == numCells){
                winners.push_back(p);
            }
        }

        void outputWinners(){
            cout<<"winners in order:\n";
            int rank = 1;
            for(Player *p : winners){
                cout<<rank<<"."<<p->name<<"\n";
                rank++;
            }
            cout<<"\n";
        }

        void resetGame(){
            winners.clear();
            numMovesYet = 0;
            for(Player *p : players){
                p->positionOnBoard = 0;
            }
            cout<<"successfully reset the game\n";

        }


};


int main(){

    int numCells, numDiceFaces, numDicesToRoll;
    cin>> numCells >> numDiceFaces>>numDicesToRoll;
    bool endOnFirstWin = true;

    Game *g = new Game(numCells,numDiceFaces,numDicesToRoll,endOnFirstWin);

    int numPlayers;
    cin>>numPlayers;
    
    for(int i =0;i<numPlayers;i++){
        string playerName;
        cin>>playerName;
        g->addPlayer(new Player(playerName));
    }

    int numSnakes;
    cin>>numSnakes;
    for(int i =0;i<numSnakes;i++){
        int l,r;
        cin>>l>>r;
        g->AddSnake(l,r);
    }

    int numLadders;
    cin>>numLadders;
    for(int i =0;i<numLadders;i++){
        int l,r;
        cin>>l>>r;
        g->AddLadder(l,r);
    }

    g->StartGame();


    return 0;
}