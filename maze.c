#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define WIDTH 59 /** gt or eq 5 */
//#define HEIGHT 25 /** gt or eq 5 */
#define WIDTH 9 /** gt or eq 5 */
#define HEIGHT 9 /** gt or eq 5 */
#define ROAD 0
#define WALL 1

int map[WIDTH][HEIGHT];
struct {
    int x;
    int y;
} dir[] = {
    {0, -1}, /** UP */
    {0, 1},  /** DOWN */
    {-1, 0}, /** LEFT */
    {1, 0}   /** RIGHT */
};

void make_maze(int x, int y)
{
    int d = rand() % 4;
    int dd = d;
    while (1) {
        int px = x+dir[d].x*2;
        int py = y+dir[d].y*2;
        if (px < 0 || px >= WIDTH || py < 0 || py >= HEIGHT || map[px][py] != WALL) {
            d++;
            if (d == 4)
                d = 0;
            if (d == dd)
                return;
            continue;
        }
        map[x+dir[d].x][y+dir[d].y] = ROAD;
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
    int x = rand_odd(WIDTH - 2);
    int y = rand_odd(HEIGHT - 2);
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
