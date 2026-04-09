#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <time.h>
#include <float.h>
#include <string>

enum Direction{STOP, RIGHT, UPRIGHT, DOWNRIGHT, LEFT, UPLEFT, DOWNLEFT};
enum Controler{PAUSE, UP, DOWN};

class cBall
{
    private:
            int x, y;
            int originalX, originalY;

            Direction dir;

    public:
            cBall(int posX, int posY)
            {
                originalX = posX;
                originalY = posY;

                x = posX;
                y = posY;

                dir = STOP;
            }

            void reset()
            {
                x = originalX;
                y = originalY;

                dir = STOP;
            }

            void changeDirection(Direction direction)
            {
                dir = direction;
            }

            void randomDirection()
            {   
                dir = (Direction)((rand() % 6) + 1);
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

            Controler joystick;
    
    public:
            cPaddle(int posX, int posY)
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

            void changeDirection(Controler dir) {joystick = dir;}

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

class cGameManager
{
    private:
            int width, height;
            int score1, score2;

            bool quit;

            cBall* ball;
            cPaddle* player1;
            cPaddle *player2;

            std::string p1;
            std::string p2;

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

                SDL_CreateRenderer;
            }


            ~cGameManager()
            {
                delete ball;
                delete player1;
                delete player2;

                SDL_DestroyRenderer;
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
                int ballX = ball->getX();
                int ballY = ball->getY();
                int player1x = player1->getX();
                int player1y = player1->getY();
                int player2x = player2->getX();
                int player2y = player2->getY();

                std::string nome1 = p1;
                std::string nome2 = p2;

                for (int i = 0; i < width + 2; i++)
                    std::cout << SDL_RenderFillRect;

                std::cout << std::endl;

                for (int i = 0; i < height ; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        if (j == 0)
                            std::cout << "\xB1";

                        if (ballX == j && ballY == i)
                            std::cout << "o";

                        else if (player1x == j && (player1y >= i && player1y < i + 4))
                            std::cout << "\xDB";

                        else if (player2x == j && (player2y >= i && player2y < i + 4))
                            std::cout << "\xDB";
                        else
                            std::cout << " ";

                        if (j == width - 1)
                            std::cout << "\xB1";
                    }
                    std::cout << std::endl;
                }

                for (int i = 0; i < width + 2; i++)
                    std::cout << "\xB1";

                std::cout << std::endl;

                for (int i = 0; i < width / 2 - 10; i++)
                    std::cout << " ";

                std::cout << nome1 << score1 << ": "
                            << nome2 << score2 << std::endl;
            }

            void Input()
            {
                int player1y = player1->getY();
                int player2y = player2->getY();

                if (SDL_PollEvent())
                {
                    if (ball->getDir() == STOP)
                        ball->randomDirection();

                    switch (_getch())
                    {
                        case 'w':
                            if (player1y - 3 > 0)
                                player1->changeDirection(UP);
                            break;
                        case 's':
                            if (player1y + 1 < height)
                                player1->changeDirection(DOWN);
                            break;
                        case 'i':
                            if (player2y - 3 > 0)
                                player2->changeDirection(UP);
                            break;
                        case 'j':
                            if (player2y + 1 < height)
                                player2->changeDirection(DOWN);
                            break;
                        case 'q':
                            quit = true;
                            break;
                        default:
                            break;
                    }
                }
            }

            void Logic()
            {
                ball->move();
                player1->move();
                player2->move();

                int ballX = ball->getX();
                int ballY = ball->getY();
                int player1x = player1->getX();
                int player1y = player1->getY();
                int player2x = player2->getX();
                int player2y = player2->getY();

                if (ballX == player1x + 1)
                {
                    if (ballY == player1y -3)
                        ball->changeDirection(UPRIGHT);

                    else if (ballY == player1y - 2 || ballY == player1y - 1)
                        ball->changeDirection((Direction)(rand() % 3 + 1));

                    else if (ballY == player1y)
                        ball->changeDirection(DOWNRIGHT);
                }

                else  if (ballX == player2x -1)
                {
                    if (ballY == player2y - 3)
                        ball->changeDirection(UPLEFT);

                    else if (ballY == player2y - 2 || ballY == player2y - 1)
                        ball->changeDirection((Direction)(rand() % 3 + 4));

                    else if (ballY == player2y)
                        ball->changeDirection(DOWNLEFT);
                }

                if (ballY == height - 1)
                    ball->changeDirection(ball->getDir() == DOWNRIGHT ? UPRIGHT : UPLEFT);

                else if (ballY == 0)
                    ball->changeDirection(ball->getDir() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

                else if (ballX == width - 1)
                    ScoreUp(player1);

                else if (ballX == 0)
                    ScoreUp(player2);

                if (player1y - 4 < 0)
                    player1->changeDirection(PAUSE);

                else if (player1y + 2 > height)
                    player1->changeDirection(PAUSE);

                if (player2y - 4 < 0)
                    player2->changeDirection(PAUSE);

                else if (player2y + 2 > height)
                    player2->changeDirection(PAUSE);

                if (score1 == 10)
                    quit = true;
                
                else if (score2 == 10)
                    quit = true;
            }

            void Game()
            {
                SDL_CreateWindow;

                std::cout << "Player1: ";

                std::cin >> p1;
                
                std::cout << "Player2: ";

                std::cin >> p2;

                while (!quit)
                {
                    Draw();
                    Input();
                    Logic();

                    SDL_Delay(16);
                }

                if (score1 != score2)
                    score1 > score2 ? std::cout << p1 << " Ganho" :
                                                            std::cout << p2 << " Ganho";
                else
                    std::cout << "TIE";
            }
};

int main()
{
    SDL_Init;

    srand(time(0));

    cGameManager c;
    
    c.Game();

    SDL_Quit;

    return 0;
}