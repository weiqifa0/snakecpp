#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>
#include <stdio.h>
#include <string.h>
#include "snake.h"

using namespace std;
using namespace snake;

Snake::Snake() {
    memset(background, 0, sizeof(background));
}
Snake::~Snake(){

}

int Snake::_kbhit() {
  static const int STDIN = 0;
  static bool initialized = false;
  int b;
  if (! initialized) {
    termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    initialized = true;
  }
  ioctl(STDIN, FIONREAD, &b);
  return b;
}

/*初始化边框*/
void Snake::initialise_background(void) {
  for (i=0; i<WIDTH; i++) {
    background[0][i] = NUM_FRAME;
    background[HEIGHT-1][i] = NUM_FRAME;
  }

  for (i=0; i<HEIGHT; i++) {
    background[i][0] = NUM_FRAME;
    background[i][WIDTH-1] = NUM_FRAME;
  }
}

/*初始化蛇*/
void Snake::initialise_snake(void){
  for (length=0; length<snakelen; length++) {
    snake[length][SNAKE_X] = NUM_SNAKE + length;
    snake[length][SNAKE_Y] = NUM_SNAKE;
  }
}

/*更新蛇显示，关键代码*/
void Snake::update_snake_coordination(void){
  px = snake[0][0];
  py = snake[0][1];
  snake[0][0] = px + movementx;
  snake[0][1] = py + movementy;
  nx =snake[0][0];
  ny =snake[0][1];

  for (length=1; length<snakelen; length++) {
    nx = snake[length][SNAKE_X];
    ny = snake[length][SNAKE_Y];
    snake[length][0]=px;
    snake[length][1]=py;
    px = nx;
    py = ny;
  }
}

/*把蛇在背景二维数组上显示出来*/
void Snake::draw_snake_in_background(const int number) {
  for (length=0; length<snakelen; length++) {
    x = snake[length][SNAKE_X];
    y = snake[length][SNAKE_Y];
    if (x>0 && y>0 && x<WIDTH && y<HEIGHT) {
      background[y][x] = number;
    }
  }
}


/*把二维数组显示出来*/
void Snake::show_snake_frame(void) {
  for (h=0; h<HEIGHT; h++) {
    for (w=0; w<WIDTH; w++) {
      cout << background[h][w];
      switch (background[h][w])
      {
        case NUM_FRAME:
          cout << FRAME_BLOCK;
          break;
        case NUM_FOOD:
          cout << FOOD_BLOCK;
          break;
        case NUM_SNAKE:
          cout << SNAKE_BLOCK;
          break;
        default:
          cout << " ";
          break;
      }
    }
    cout << endl;
  }
}

/*清除背景显示*/
void Snake::clear_background(void) {
  system(CLEAR_CMD);
}

/*更新主循环*/
void Snake::update_snake_data(void){
  clear_background();
  draw_snake_in_background(NUM_SNAKE);
  show_snake_frame();
  draw_snake_in_background(NUM_BLANK);
}

/*延迟*/
void Snake::sleep_ms(int milliseconds) {
  clock_t time_end;
  time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
  while (clock() < time_end){}
}


/*按键获取*/
void Snake::reaction_on_keyboard(const char k) {
  if(k=='D'|| k=='d'||k=='6') {      // Right
    movementx = speedx;
    movementy = 0;
  }else if(k=='A'||k=='a'||k=='4') { // Left
    movementx = -speedx;
    movementy = 0;
  }else if(k=='W'||k=='w'||k=='8') { // UP
    movementx = 0;
    movementy = -speedy;
  }else if(k=='S'||k=='s'||k=='2') { // Down
    movementx = 0;
    movementy = speedy;
  }else if(k=='q'||k=='z'||k=='c') {
    cout << "[+] Exit Safely [+]"<<endl;
    exit(0);
  }
}

/*在键盘上显示食物*/
void Snake::create_food(void) {
  int x,y;
  if (food[SNAKE_X] == NUM_BLANK && food[SNAKE_Y] == NUM_BLANK) {
    x = rand() % (WIDTH -1);
    y = rand() % (HEIGHT - 1);
    food[SNAKE_X] = x;
    food[SNAKE_Y] = y;
    background[y][x] = NUM_FOOD;
  }
}


/*蛇身抓取到食物*/
void Snake::capture_food(void){
  x = food[SNAKE_X];
  y = food[SNAKE_Y];
  if ((x==snake[0][0])&&(y==snake[0][1])) {
    background[y][x] = NUM_BLANK;
    food[SNAKE_X] = food[SNAKE_Y] = NUM_BLANK;
    ++score;
    ++snakelen;
    create_food();
  }
}

/*游戏结束判断*/
void Snake::check_over(void) {
  px = snake[0][0];
  py = snake[0][1];
  if((px==0)||(px==(WIDTH-1))||(py==0)||(py==(HEIGHT-1))) {
    cout << "[#]        Game Over           [#]" << endl;
    exit(0);
  }
}

/*主循环*/
void Snake::snake_main_loop() {
  for(;x < 500;)
  {
    sleep_ms(delaytime);
    if (_kbhit()) {
      cin >> ch;
      reaction_on_keyboard(ch);
    }
    update_snake_data();
    update_snake_coordination();
    check_over();
    create_food();
    capture_food();
    cout << "< x : " << frame << "  | Score  : " << score << " > "<< endl;
    frame++;
  }
}

/*主函数*/
int main(void) {
  Snake Snake_;
  Snake_.initialise_background();
  Snake_.initialise_snake();
  Snake_.snake_main_loop();
  return 0;
}
