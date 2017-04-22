#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 59
#define HEIGHT 21
#define ROAD 0
#define WALL 1

int map[WIDTH][HEIGHT];
int dir_x[] = {0, 0, -1, 1};  /* 上,下,左,右 */
int dir_y[] = {-1, 1, 0, 0};

void make_maze(int x, int y)
{
    int d = rand() % 4;
    int dd = d;
    while (1) {
        int px = x+dir_x[d]*2;
        int py = y+dir_y[d]*2;
        if (px < 0 || px >= WIDTH || py < 0 || py >= HEIGHT || map[px][py] != WALL) {
            d++;
            if (d == 4)
                d = 0;
            if (d == dd)
                return;
            continue;
        }
        map[x+dir_x[d]][y+dir_y[d]] = ROAD;
        map[px][py] = ROAD;
        make_maze(px, py);
        d = dd = rand() % 4;
    }
}

int rand_odd(int mod)
{
    int r = 2 + rand() % mod;
    if (r % 2 == 0)
        r++;
    if (r > mod)
        r -= 2;
    return r;
}

void maze()
{
    int x = rand_odd(WIDTH - 4);
    int y = rand_odd(HEIGHT - 4);
    printf("(%d, %d)\n", x, y);
    make_maze(x, y);
}

void print()
{
    int x, y;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++)
            printf("%c", (map[x][y] == WALL) ? '#' : ' ');
        printf("\n");
    }
}

void maze_init()
{
    int x, y;
    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++)
            map[x][y] = WALL;
}

void init()
{
    time_t t;
    time(&t);
    srand(t);
}

int main()
{
    init();
    for (int i = 0; i < 3; i++) {
        maze_init();
        maze();
        print();
    }
    return 0;
}
