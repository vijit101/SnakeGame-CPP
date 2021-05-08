#include<iostream>
#include<conio.h> //input fx
#include <Windows.h> // sleep fx
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
char snakeBody = 'x';
char devilFruit = '+';
Vector2 snakeTail[100];
int tailLength = 0;
int score , gameSpeed = 5;
Vector2 snakePos,fruitPos;
enum Dir{ STOP = 0 , LEFT = 1 , RIGHT = 2 , UP = 3 , DOWN = 4};
Dir snakeDir;

// Functions
void SpawnFruitAtRandom(){
    fruitPos.x = rand() % (mapWidth -3); // -3 as mapheight is from 0-18 as I already draw 1st and last row myself in other loop so 20 - 2 = 18
    fruitPos.y = rand() % (mapHeight -3);// so because of - 3 it will remain inside the map and also prevent it from max boundary
    // fruit not to spawn on boundary 
    if(fruitPos.x == 0 || fruitPos.y == 0){
        SpawnFruitAtRandom();
    }
}
void Setup(){
    gameOver = false;
    snakeDir = STOP;
    // initial position for snake and fruit
    snakePos.x = mapWidth/2;
    snakePos.y = mapHeight/2;
    SpawnFruitAtRandom();
    //cout<<"x"<<fruitPos.x<<"y"<<fruitPos.y<<"\n";
    score = 0;
}

void Draw(){
    // sends command to console to clear screen
    system("cls");
    //cout<<"x"<<fruitPos.x<<"y"<<fruitPos.y<<"\n";
    cout<<"Score :"<<score<<endl;
    // prints row 1 as *******
    for(int i=0; i <mapWidth;i++){
        cout<<mapBorder;
    }
    cout<<"\n";
    // prints as row 2 *       * to last row in height 
    for(int i=0; i <mapHeight -2;i++){
        for(int j=0; j <mapWidth;j++){
            if(j == 0 || j == mapWidth -1){
                cout<<mapBorder;//mapborder
            } 
            else{
                if(i == snakePos.x && j == snakePos.y){
                    cout<<snakeHead;
                }
                else if(i == fruitPos.x && j == fruitPos.y){
                    cout<<devilFruit;
                }
                else{
                    //printing tail
                    bool tailPrinted = false;
                    for(int k = 0;k < tailLength;k++){
                        if(i==snakeTail[k].x && j == snakeTail[k].y){
                            cout<<snakeBody;
                            tailPrinted = true;
                        }
                    }
                    if(tailPrinted == false){
                        cout<<" ";
                    }
                    
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
    // check keyboard input
    if(_kbhit()){
        switch (_getch())
        {
            case 'w':
            snakeDir = UP;
            break;
            case 'a':
            snakeDir = LEFT;
            break;
            case 's':
            snakeDir = DOWN;
            break;
            case 'd':
            snakeDir = RIGHT;
            break;
            case 'q':
            gameOver = true;
            break;
            default:
            break;
        }
    }
}

void Logic(){
    //snakeTail[0].x = snakePos.x;
    //snakeTail[0].y = snakePos.y;
    // if position of the two lines is changed to above a wierd behaviour can be observed
    int prevX = snakeTail[0].x; // previous pos of tail 
    int prevY = snakeTail[0].y;
    snakeTail[0].x = snakePos.x;
    snakeTail[0].y = snakePos.y;
    int previousX = 0,previousY = 0;
    for (int i = 1; i <tailLength; i++)
    {
        previousX = snakeTail[i].x;
        previousY = snakeTail[i].y;
        snakeTail[i].x = prevX;
        snakeTail[i].y = prevY;
        prevX = previousX;
        prevY = previousY;
    }
    for(int i = 1 ; i < tailLength;i++){
        if(snakeTail[i].x == snakePos.x  && snakeTail[i].y == snakePos.y){
            gameOver = true;
        }
    }
switch (snakeDir)
{
    // here the reason is that i is the row and we are moving snake in i so
    //row 1 2 3 4 5 6
    //    2
    //    3
    //    4  
    // x = row which is actually the y axis as I as developer set snakepos.x as
    // if(i == snakePos.x && j == snakePos.y){
    //                cout<<snakeHead;
    //           }
    // to make it right i == snakepos.y so now row is snakeposy and j is col so j is x
    case UP:
    snakePos.x--;
    break;
    case DOWN:
    snakePos.x++;
    break;
    case LEFT:
    snakePos.y--;
    break;
    case RIGHT:
    snakePos.y++;
    break;
    default:
    break;
    }
    // map check for snake to hit boundary 
    if(snakePos.x > mapHeight || snakePos.x <0 || snakePos.y >mapWidth || snakePos.y <0){
        gameOver = true;
    }
    // eat fruit logic 
    if(snakePos.x == fruitPos.x && snakePos.y == fruitPos.y){
        score ++;
        SpawnFruitAtRandom();
        tailLength++;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(gameSpeed);
    }
    cout<<"Game Over your Score is :"<<score;
    
    return 0;
}