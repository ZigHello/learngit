#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <Math.h>

#pragma warning(disable:4996)

#define High 480
#define Width 640
#define PI 3.14159
//#define Title "�ҵ�ʱ��"
//#define Note "[ʱ�룺��ɫ] [���룺��ɫ] [���룺��ɫ]"
int main()
{
	initgraph(Width, High);
	int center_x, center_y;  //�������꣬�������ʼ����
	center_x = Width/2;
	center_y = High/2;

	int secondLength;   //����ĳ���
	int minuteLength;   //����ĳ���
	int hourLength;     //ʱ��ĳ���
	secondLength = Width / 5;
	minuteLength = Width / 6;
	hourLength = Width / 8;

	int secondEnd_x, secondEnd_y;     //���ӵ��յ�����
	int minuteEnd_x, minuteEnd_y;     //������յ�����
	int hourEnd_x, hourEnd_y;		  //ʱ����յ�����


	float secondAngle = 0;//�����Ӧת���Ƕ�
	float minuteAngle = 0;//�����Ӧת���Ƕ�
	float hourAngle = 0;//ʱ���Ӧת���Ƕ�

	SYSTEMTIME ti;  //��������洢ϵͳʱ��
	BeginBatchDraw();
	while (1)
	{
		//���Ʊ��̱�Ե
		setlinestyle(PS_SOLID, 2); 
		setcolor(WHITE);
		circle(center_x, center_y, Width / 4);
		
		//���ƿ̶�
		int x, y;
		for (int i = 0; i < 60; i++)
		{
			x = center_x + int(Width / 4.5 * sin(i * 2 * PI / 60));
			y = center_y + int(Width / 4.5 * cos(i * 2 * PI / 60));
			if (i % 15 == 0) //0,15,30,45,60
			{
				bar(x - 5, y + 5, x + 5, y - 5);
			}
			else if (i % 5 == 0) //5,10,20,25,35,40,50,55
			{
				circle(x, y, 3);
			}
			else {
				putpixel(x, y, WHITE);
			}
		}

		outtextxy(center_x-20 , center_y + Width/6, "�ҵ�ʱ��");

		GetLocalTime(&ti);
		secondAngle = (double)ti.wSecond * 2 * PI / 60;   //һȦ�ĽǶ�Ϊ2PI��һȦ60�룬һ�����߹��ĽǶ�Ϊ2*PI/60
		minuteAngle = (double)ti.wMinute * 2 * PI / 60;  //һ�����߹��ĽǶ�Ϊ2*PI/60
		hourAngle = (double)ti.wHour * 2 * PI / 12;		//һСʱ�߹��ĽǶ�Ϊ2*PI/12

		//�ǶȾ��������յ�����
		secondEnd_x = (int)center_x + secondLength * sin(secondAngle);
		secondEnd_y = (int)center_y - secondLength * cos(secondAngle);
		//�ǶȾ��������յ�����
		minuteEnd_x = (int)center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = (int)center_y - minuteLength * cos(minuteAngle);
		//�ǶȾ���ʱ���յ�����
		hourEnd_x = (int)center_x + hourLength * sin(hourAngle);
		hourEnd_y = (int)center_y - hourLength * cos(hourAngle);

		//������
		setlinestyle(PS_SOLID, 2);  //��ʵ�ߣ����Ϊ2������
		setcolor(WHITE);
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		//������
		setlinestyle(PS_SOLID, 4);  //��ʵ�ߣ����Ϊ4������
		setcolor(YELLOW);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		//��ʱ��
		setlinestyle(PS_SOLID, 6);  //��ʵ�ߣ����Ϊ6������
		setcolor(RED);
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		FlushBatchDraw();
		Sleep(50);

		//����ǰ��һ֡������
		setcolor(BLACK);
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		line(center_x, center_y, hourEnd_x, hourEnd_y);
	}
	EndBatchDraw();
	getch();
	closegraph();

	return 0;
}