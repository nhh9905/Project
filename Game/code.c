//Created by nhh
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
int key_picked = 0, out = 0, inbox_key = 0, inbox_no_exit = 0, inbox_trap = 0, check = 0;
typedef struct {
    int x;
    int y;
} point;
//doi cho 2 toa do
void swap(char a[][16], int x1, int y1, int x2, int y2) {
    char tmp = a[x2][y2];
    a[x2][y2] = a[x1][y1];
    a[x1][y1] = tmp;
}
//di chuyen player
void move_player(char a[][16], int x1, int y1, int x2, int y2, int num_key) {
    //ra khoi ban co
    if (a[x2][y2] == 'E') {
        if (key_picked == num_key) {
            a[x2][y2] = 'P';
            a[x1][y1] = '-';
            out = 1;
        }
        else
            inbox_no_exit = 1;
    }
    //nhat chia khoa
    if (a[x2][y2] == 'K') {
        a[x2][y2] = 'P';
        a[x1][y1] = '-';
        key_picked++;
        inbox_key = 1;
    }
    if (a[x2][y2] == 'T') {
        a[x2][y2] = 'P';
        a[x1][y1] = '-';
        inbox_trap++;
    }
    if (a[x2][y2] != 'P' && a[x2][y2] != 'E' && a[x2][y2] != 'T' && a[x2][y2] != '*')
        swap(a, x1, y1, x2, y2);
}
//khoi tao ban co
void ktao(char a[][16], int n, int x1, int y1, point key[], int num_key, point exit, point trap[], point obstacle[], int num_obstacle) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            a[i][j] = '-';
    }
    a[x1][y1] = 'P';
    for (int i = 1; i <= num_key; i++) 
        a[key[i].x][key[i].y] = 'K';
    a[exit.x][exit.y] = 'E';
    for (int i = 1; i <= num_key + 1; i++)
        a[trap[i].x][trap[i].y] = 'T';
    for (int i = 1; i <= num_obstacle; i++)
        a[obstacle[i].x][obstacle[i].y] = '*';
}
//ve ban co
void print_board(char a[][16], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) 
            printf("%c ", a[i][j]);
        printf("\n");
    }
}
int random(int minn, int maxx) {
    return minn + rand() % (maxx - minn + 1);
}
//check xem toa do moi co trung toa do cu ko
int is_point_in_array(point k, point *point_array, int array_size) {
    for (int i = 0; i < array_size; ++i) {
        if (k.x == point_array[i].x && k.y == point_array[i].y) {
            return 1;  // toa do da ton tai trong mang
        }
    }
    return 0;  // toa do ko ton tai trong mang
}
//tao toa do moi
point generate_random_point(int minn, int maxx, point *old_points, int num_old_points) {
    point new_point;
    srand((unsigned int)time(NULL));
    do {
        new_point.x = minn + rand() % (maxx - minn + 1);
        new_point.y = minn + rand() % (maxx - minn + 1);
    } while (is_point_in_array(new_point, old_points, num_old_points));
    return new_point;
}
int main() {
    system("cls");
    //dat seed cho ham rand() = tgian hien tai de co so ngau nhien khac nhau moi lan chay
    srand((unsigned int)time(NULL));
    //kich thuoc ban co NxN, num_point: so toa do dac biet
    int n = random(10, 15), num_point = 0;
    char a[16][16], b[16][16];
    int x1 = random(1, n), y1 = random(1, n);
    int num_key = random(3, 5);
    int num_obstacle = n*n/6;
    point player = {x1, y1}, old_point[100], key[num_key + 1], trap[num_key + 2], obstacle[num_obstacle + 1];
    old_point[0] = player;
    num_point++;
    int tmp_x = x1, tmp_y = y1;
    for (int i = 1; i <= num_key; i++) {
        key[i] = generate_random_point(1, n, old_point, num_point);
        old_point[num_point] = key[i];
        num_point++;
    }
    point exit = generate_random_point(1, n, old_point, num_point);
    old_point[num_point] = exit;
    num_point++;
    for (int i = 1; i <= num_key + 1; i++) {
        trap[i] = generate_random_point(1, n, old_point, num_point);
        old_point[num_point] = trap[i];
        num_point++;
    }
    for (int i = 1; i <= num_obstacle; i++) {
        obstacle[i] = generate_random_point(1, n, old_point, num_point);
        old_point[num_point] = obstacle[i];
        num_point++;
    }
    ktao(a, n, x1, y1, key, num_key, exit, trap, obstacle, num_obstacle);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) 
            b[i][j] = a[i][j];
    }
    print_board(a, n);
    while (1) {
    	printf("P: Player\nK: Key\nT: Trap\nE: Exit\n*: Obstacle\n");
        char step;
        printf("Press W A S D to move: %c", step);
        step = getch();
        step = toupper(step);
        //di chuyen len tren
        if (step == 'W') {
            if (x1 > 1) {
                move_player(a, x1, y1, x1 - 1, y1, num_key);
                if (a[x1][y1] != 'P')
                    x1--;
            }
        }
        //di chuyen sang trai
        if (step == 'A')
        {
            if (y1 > 1) {
                move_player(a, x1, y1, x1, y1 - 1, num_key);
                if (a[x1][y1] != 'P')
                    y1--;
            }
        }
        //di chuyen xuong duoi
        if (step == 'S') {
            if (x1 < n) {
                move_player(a, x1, y1, x1 + 1, y1, num_key);
                if (a[x1][y1] != 'P')
                    x1++;
            }
        }
        //di chuyen sang phai
        if (step == 'D') {
            if (y1 < n) {
                move_player(a, x1, y1, x1, y1 + 1, num_key);
                if (a[x1][y1] != 'P')
                    y1++;
            }
        }
        //xoa ban co
        system("cls");
        print_board(a, n);
        //nhat duoc chia khoa
        if (inbox_key) {
            printf("You've acquired (%d/%d) keys\nPress any key to continue\n", key_picked, num_key);
            getch();
            system("cls");
            print_board(a, n);
            inbox_key = 0;
        }
        //ra khoi ban co ma ko co chia khoa
        if (inbox_no_exit) {
            printf("You must acquired (%d/%d) keys to exit\nPress any key to continue\n", num_key, num_key);
            getch();
            system("cls");
            print_board(a, n);
            inbox_no_exit = 0;
        }
        //dam vao bay lan 1
        if (inbox_trap == 1 && check == 0) {
            printf("You have stepped into a trap\nPress any key to continue\n");
            getch();
            check = 1;
            //reset ban co
            key_picked = 0, out = 0, inbox_key = 0, inbox_no_exit = 0;
            int trap_x = x1, trap_y = y1;
            x1 = tmp_x, y1 = tmp_y;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++)
                    a[i][j] = b[i][j];
            }
            a[trap_x][trap_y] = '-';
            system("cls");
            print_board(a, n);
        }
        //dam vao bay lan 2
        if (inbox_trap == 2) {
            printf("You lose\n");
            return 0;
        }
        //ra khoi ban co + chia khoa
        if (out) {
            printf("Congrats, you've just escaped the prison");
            return 0;
        }
    }
}
