#include <iostream>
#include <raylib.h>

using namespace std;

int player_score = 0;
int cpu_score = 0;

Color Yellow = Color{243,213,91,255};

class Ball{
    public:
    float x,y;
    int speed_x,speed_y;
    int radius;


    void Draw(){
        DrawCircle( x, y, radius , Yellow);

    };

    void Update(){
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *=-1;
        }
        if (x + radius >= GetScreenWidth())
        {
            cpu_score++;
            ResetBall();
        }
        if (x - radius <= 0)
        {
            player_score++;
            ResetBall();
        }
        
        
        
    };

    void ResetBall(){
        x = GetScreenWidth() /2;
        y = GetScreenHeight() /2;

        int speed_choices[2] = {-1,1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];
    };
};


class Paddle{

    protected:

    void LimitMovement(){
         
        if (y <= 0)
        {
            y = 0;
        }
        if (y + heigth >= GetScreenHeight())
        {
            y = GetScreenHeight() - heigth;
        }


    };


    public:
    float x,y;
    float width,heigth;
    int speed;

    void Draw(){
        DrawRectangle(x,y,width,heigth,WHITE);
    };

    void Update(){
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }
        LimitMovement();    
        

    };
};

class CPUPaddle: public Paddle{

    public:
    void Update(int ball_y){
        if (y + heigth/2 > ball_y)
        {
           y = y - speed;
        }
        if (y + heigth/2 <= ball_y)
        {
            y = y + speed;
        }
        
        LimitMovement();
    };


};

Ball ball;
Paddle player;
CPUPaddle cpu;

int main () {

    const int screenWidth = 1280;
    const int screenHeight = 800;
    
    cout << "Starting PONG!" << endl;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screenWidth/2;
    ball.y = screenHeight/2;
    ball.speed_x = 7;
    ball.speed_y = 7;


    player.width = 25;
    player.heigth = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight/2 - player.heigth/2;
    player.speed = 6;

    cpu.heigth = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screenHeight / 2 - cpu.heigth / 2;
    cpu.speed = 6;

    while (WindowShouldClose() == false){
        BeginDrawing();

        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player.x,player.y,player.width,player.heigth})){

            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x,cpu.y,cpu.width,cpu.heigth}))
        {
            ball.speed_x *= -1;
        }
        






        ClearBackground(BLACK);
        DrawLine(screenWidth / 2,0,screenWidth/2,screenHeight,WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();

        DrawText(TextFormat("%i",cpu_score),screenWidth/4 - 20,20,20,WHITE);
        DrawText(TextFormat("%i",player_score),3 * screenWidth/4 - 20,20,20,WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}