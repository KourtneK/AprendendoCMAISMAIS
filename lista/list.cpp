#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>

enum eDirection{STOP, RIGHT, UPRIGHT, DOWNRIGHT, LEFT, UPLEFT, DOWNLEFT};
enum eControler{PAUSE, UP, DOWN};

class cBall
{
    private:
            int x, y;
            int originalX, originalY;

            std::eDirection dir;

    public:
            cBall(int posX, int posY)
            {
                originalX = posX;
                originalY = posY;

                x = posX;
                y = posY;

                dir = STOP;
            }

            void changeDirection(eDirection direction)
            {
                dir = direction;
            }

            void randomDirection()
            {
                srand(time(0));
                
                dir = (eDirection)((rand() % 6) + 1);
            }

            inline int getX() {return x;}
            inline int getY() {return y;}
            inline int getDir() {return dir;}

            void move()
            {
                switch (dir) 
                {
                    case STOP:
                        break;
                    case RIGHT:
                        x++;
                        break;
                    case UPRIGHT:
                        x++;
                        y--;
                        break;
                    case DOWNRIGHT:
                        x++;
                        y++;
                        break;
                    case LEFT:
                        x--;
                        break;
                    case UPLEFT:
                        x--;
                        y--;
                        break;
                    case DOWNLEFT:
                        x--;
                        y++;
                        break;
                    default:
                        break;
                }
            }
};

class cPaddle
{
    private:
            int x, y;
            int originalX, originalY;

            std::eControler joystick;
    
    public:
            cPddle(int posX, int posY)
            {
                originalX = posX;
                originalY = posY;

                x = posX;
                y = posY;

                joystick = PAUSE;
            }
            
            void reset()
            {
                x = originalX;
                y = originalY;

                joystick = PAUSE;
            }

            inline int getX() {return x;}
            inline int getY() {return y;}

            void changeDirection(eControler dir) {joystick = dir;}

            void move()
            {
                switch(joystick)
                {
                    case UP:
                        y--;
                        break;
                    case DOWN:
                        y++;
                        break;
                    case PAUSE:
                        break;
                    default:
                        break;
                }
            }
};

class cGameMnaganer
{
    private:
            int width, height;
            int score1, score2;

            bool quit;

            cBall* ball;
            cPaddle* player1;
            cPaddle *player2;

    public:
            cGameManager()
            {
                quit = false;
                height = 15;
                width = 50;
                score1 = 0;
                score2 = 0;
                ball = new cBall(width / 2, height / 2);
                player1 = new cPaddle(1, height / 2);
                player2 = new cPaddle(width - 2, height / 2);
            }

            ~cGameManager()
            {
                delete ball;
                delete player1;
                delete player2;
            }

            void ScoreUp(cPaddle* player)
            {
                if (player == player1)
                    score1++;
                else if (player == player2)
                    score2++;

                ball->reset();
                player1->reset();
                player2->reset();
            }

            void Draw()
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
                
                for (int i = 0; i < width + 2; i++)
                    std::cout << "\xB2";

                std::cout << std::endl;

                for (int j = 0; j < width ; j++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        int ballX = ball->getX();
                        int ballY = ball->getY();
                        int player1x = player1->getX();
                        int player1y = player1->getX();
                        int player2x = player2->getX();
                        int player2y = player2->getX();

                        if (j == 0)
                            std::cout << "\xB1";

                        if ()
                    }
                }
            }
}