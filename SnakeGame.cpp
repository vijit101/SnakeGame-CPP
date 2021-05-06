#include<iostream>
using namespace std;
// class
class Vector2{
    public:
    int x;
    int y;
};

//Variables 
bool gameOver;
int mapWidth = 20;
int mapHeight = 20; 
char mapBorder = '#';
char snakeHead = 'O';
char devilFruit = '*';
int score;
Vector2 snakePos,fruitPos;
enum Dir{ STOP = 0 , LEFT = 1 , RIGHT = 2 , UP = 3 , DOWN = 4};
Dir snakeDir;

// Functions
void Setup(){
    gameOver = false;
    snakeDir = STOP;
    // initial position for snake and fruit
    snakePos.x = mapWidth/2;
    snakePos.y = mapHeight/2;
    fruitPos.x = rand() % mapWidth;
    fruitPos.y = rand() % mapHeight;
    score = 0;
}

void Draw(){
    // sends command to console to clear screen
    system("cls");
    // prints row 1 as *******
    for(int i=0; i <mapWidth;i++){
        cout<<mapBorder;
    }
    cout<<"\n";
    // prints as row 2 *       * to last row in height 
    for(int i=0; i <mapHeight -2;i++){
        for(int j=0; j <mapWidth;j++){
            if(j == 0 || j == mapWidth -1){
                cout<<mapBorder;
            } 
            else{
                if(i == snakePos.x && j == snakePos.y){
                    cout<<snakeHead;
                }
                else if(i == fruitPos.x && j == fruitPos.y){
                    cout<<devilFruit;
                }
                else{
                    cout<<" ";
                } 
            }
        }
        cout << "\n";
    }
    for(int i=0 ; i <mapWidth;i++){
        cout<<mapBorder;
    }
}

void Input(){

}

void Logic(){

}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
    return 0;
}