#include <iostream>   // Standard Header
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>
#include <stdio.h>

using namespace std;

namespace snake{
class Snake{
    public:
        Snake();
        ~Snake();
        int _kbhit();
        void initialise_background(void);
        void initialise_snake(void);
        void update_snake_coordination(void);
        void draw_snake_in_background(const int number);
        void show_snake_frame(void);
        void clear_background(void);
        void update_snake_data(void);
        void sleep_ms(int milliseconds);
        void reaction_on_keyboard(const char k);
        void create_food(void);
        void capture_food(void);
        void check_over(void);
        void snake_main_loop(void);

    private:
        #define WIDTH 50
        #define HEIGHT 25
        #define FRAME_BLOCK '1'
        #define FOOD_BLOCK  '2'
        #define SNAKE_BLOCK '3'
        #define SPACE_BLOCK ' '
        #define CLEAR_CMD "clear"
        #define NUM_BLANK 0
        #define NUM_FRAME 1
        #define NUM_FOOD  2
        #define NUM_SNAKE 3
        #define SNAKE_X 0
        #define SNAKE_Y 1

        int background[HEIGHT][WIDTH];
        int snake[WIDTH][2];
        int food[2]={0,0};
        int score = 0;
        int snakelen = 4;
        int speedx = 1;
        int speedy = 1;
        int delaytime=200;

        int i;
        int length;
        int px,py,nx, ny;
        char ch;
        int h,w;
        int x = 0,y = 0;
        int movementx=speedx;
        int movementy=0;
        int frame=0;
};
}
