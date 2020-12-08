#include <stdio.h>
#include <stdlib.h >
#include <windows.h>			//将用户从键盘获得的输入进行输出 
#include <conio.h>				//获得用户键盘的输入 

#define High 30
#define Width 50
#define EnemyNum 5         //敌机数目

int game[High][Width] = { 0 };               //画布显示的内容,0画空格，1画我机，2画子弹，3画敌机
int position_x, position_y;                  //飞机坐标位置
int bullet_x, bullet_y;                     //子弹坐标位置
int enemy_x[EnemyNum], enemy_y[EnemyNum];  //敌机坐标位置
int score;                                //得分
int flag;                                //飞机状态
int BulletWidth;                        //子弹宽度



void gotoxy(int x, int y); 
void HideCursor();
void show();
void dataInit();
void updateBullet();
void updateEnemy();
void hitEnemy();
void getUserInput();


// 让光标回到（0, 0）位置的函数
void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(handle, pos);//两个参数分别是指定哪个窗体，具体位置
};

//隐藏光标函数
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//第二个值为0表示隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void dataInit()   //游戏数据初始化
{
    position_x = High - 3;
    position_y = Width/2;
    game[position_x][position_y] = 1;
    int k;
    for (k = 0; k < EnemyNum; k++)
    {
        enemy_x[k] = rand() % 3;;
        enemy_y[k] = 2 + rand() % Width - 2;
        game[enemy_x[k]][enemy_y[k]] = 3;
    }
    BulletWidth = 0;
    score = 0;
    flag = 0;
    HideCursor();
};

void show()   //界面显示
{
    gotoxy(0, 0);  //重绘
    int i, j;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (flag == 1)
                break;
            else if (game[i][j] == 1)  //绘制飞机
                printf("*");  
            else if (game[i][j] == 2)  //绘制子弹
                printf("|");  //输出子弹
            else if (game[i][j] == 3)    //绘制敌机
                printf("@");
            else if ((j == Width - 1) || (i == High - 1) || (j == 0) || (i == 0)) //绘制边界 
                printf("-");
            else
                printf(" ");  //输出空格
        }
        printf("\n");
    }
    
    printf("得分：%d",score);
};

void updateBullet()   //更新子弹位置
{
    int i, j;
    for (i = 0; i < High - 1; i++)
    {
        for (j = 0; j < Width - 1; j++)
        {
            if (game[i][j] == 2)
            {
                game[i][j] = 0;
                if (i > 0)
                {
                    i--;
                    game[i][j] = 2;
                }
            }
        }
    }
};

void updateEnemy()    //更新敌机位置
{
    //控制敌机下落的速度
    static int speed = 10;
    if (speed < 10)
        speed++;
    if (speed == 10)
    {
        int k;
        for (k = 0; k < EnemyNum; k++)
        {
            if (enemy_x[k] < High)  //没有超过边界，敌机下移
            {
                game[enemy_x[k]][enemy_y[k]] = 0;
                enemy_x[k]++;
                game[enemy_x[k]][enemy_y[k]] = 3;
                speed = 0;
            }
            else      // 敌机超过边界，重新生成敌机
            {
                score--;
                game[enemy_x[k]][enemy_y[k]] = 0;
                enemy_x[k] = 1;
                enemy_y[k] = 2 + rand() % Width - 2;
                game[enemy_x[k]][enemy_y[k]] = 3;
               
            }
        }
        
    }
};

void hitEnemy() 
{
    int i, j, k;
    for (i = 0; i < High - 1; i++)
    {
        for (j = 0; j < Width - 1; j++)
        {
            if (game[i][j] == 2)     //子弹击中敌机
            {
                for (k = 0; k < EnemyNum; k++) 
                {
                    if ((i == enemy_x[k]) && (j == enemy_y[k]))
                    {
                        score++;            //击中加分
                        if (score % 5 == 0) //子弹变厉害
                            BulletWidth++;
                        game[enemy_x[k]][enemy_y[k]] = 0;
                        enemy_x[k] = rand()%2;      //产生新的敌机
                        enemy_y[k] = 2 + rand() % Width - 2;
                        game[enemy_x[k]][enemy_y[k]] = 3;
                        game[i][j] = 0;  //子弹消失
                        
                    }
                }
            }
            if (game[i][j] == 1)    //我机与敌机相撞
            {
                for (k = 0; k < EnemyNum; k++)
                {
                    if ((i == enemy_x[k]) && (j == enemy_y[k]))
                    {
                        printf("游戏结束!!!\n");    
                        flag = 1;
                    }
                }
            }
        }
    }
   
}

void gameOver() //飞机撞毁 游戏结束 
{
    
    exit(0);
}


void getUserInput() // 与用户输入有关的更新
{
    char input;
    if(_kbhit()) //当按键时
    {
        input = _getch();
        if ((input == 'a') && position_y > 1)
        {
            game[position_x][position_y] = 0;
            position_y--;
            game[position_x][position_y] = 1;
        }
        if ((input == 'd') && position_y < Width - 2)
        {
            game[position_x][position_y] = 0;
            position_y++;
            game[position_x][position_y] = 1;
        }
        if ((input == 'w') && position_x > 1)
        {
            game[position_x][position_y] = 0;
            position_x--;  
            game[position_x][position_y] = 1;
        }
        if ((input == 's') && position_x < High - 2)
        {
            game[position_x][position_y] = 0;
            position_x++;
            game[position_x][position_y] = 1;
        }
        if (input == ' ')
        {
            int left, right;
            left = position_y - BulletWidth;
            if (left < 0)
                left = 0;
            right = position_y + BulletWidth;
            if (right > Width-1)
                right = Width-1;
            int x;
            for (x = left; x <= right; x++)
            {
                bullet_x = position_x - 1;
                game[bullet_x][x] = 2;
            }
            

        }
    }
};

int main() {
    HideCursor();
    dataInit(); //数据初始化
    while (1)
    {
        HideCursor();
        show();
        if (flag == 1 || score < 0)
        { 
            gameOver();
        }
       
        updateBullet();
        hitEnemy();
        updateEnemy();
        getUserInput();
       // _getch();
    }
    return 0;
}
