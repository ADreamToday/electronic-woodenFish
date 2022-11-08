#include<graphics.h>		// 引用图形库头文件
#include<conio.h>
#include<easyx.h>
#include<cstdlib>
#include<ctime>
#include <Windows.h>
#include <mmsystem.h>
#include<iostream>
//#include <atlstr.h>
//#pragma comment (lib, "winmm.lib")

extern char _binary_sound_wav_start[]; //引用文件头指针
//extern char []; //引用文件末指针

extern char _binary_zhiyin_wav_start[]; //引用文件头指针
//extern char []; //引用文件末指针

using namespace std;
void loop();
int main()
{
	srand((int)time(0));	//随机数种子
	//设置字体


	initgraph(968, 644);	// 创建绘图窗口，大小为 640x480 像素
	settextcolor(WHITE);
	settextstyle(45 , 0 , _T("微软雅黑"));
	//设置背景
	setbkcolor(WHITE);	// !白背景  清屏的时候要把字体改成黑的
	cleardevice();
	loop();
	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}


//主循环
void loop()
{
	WCHAR muyu_sound[256];
	memset(muyu_sound , 0 , sizeof(muyu_sound));
	MultiByteToWideChar(CP_ACP,0,_binary_sound_wav_start,strlen(_binary_sound_wav_start)+1,muyu_sound,
		sizeof(muyu_sound)/sizeof(muyu_sound[0]));

	WCHAR zhiyin_sound[256];
	memset(zhiyin_sound , 0 , sizeof(zhiyin_sound));
	MultiByteToWideChar(CP_ACP,0,_binary_zhiyin_wav_start,strlen(_binary_zhiyin_wav_start)+1,zhiyin_sound,
		sizeof(zhiyin_sound)/sizeof(zhiyin_sound[0]));


	int iGongde = 0;	//功德值
	ExMessage m;		//消息体
	IMAGE muyu;
	loadimage(&muyu , _T("images/muyu.jpg") , 968 , 644);  //缩小了一倍

	while(true)
	{
		srand((int)time(0));
		char text[50];
		sprintf(text , "功德数：%d" , iGongde);
		setbkcolor(BLACK);
		BeginBatchDraw();
		putimage(0 , 0 , &muyu);	//绘制
		outtextxy(0 , 50 , _T("积电子功德，拜赛博佛祖，见初音未来"));
		outtextxy(0 , 0 , _T(text));
		EndBatchDraw();
		setbkcolor(WHITE);
		m = getmessage(EX_MOUSE | EX_KEY);



		switch(m.message)
		{
			case WM_LBUTTONDOWN:   //左键单击  敲木鱼
				iGongde++;	//功德+1
				PlaySound(_T(_binary_sound_wav_start), NULL,SND_NOSTOP | SND_MEMORY | SND_ASYNC);	//播放木鱼声
				//绘制+1
				setbkcolor(BLACK);
				outtextxy(m.x , m.y , _T("功德 +1"));
				setbkcolor(WHITE);
				Sleep(200);

				if((rand() % 5) == 3)  //?0.2概率 生成初音或只因bushi 
				{
					cleardevice();	//清屏
					if(rand()%10 == 5)	// ? 0.25初音
					{
						//文字输出
						settextcolor(BLACK);
						outtextxy(0 , 0 , _T("敲电子木鱼  梦初音未来"));
						outtextxy(0 , 600 , _T("右击继续攒功德"));
						IMAGE imChuyin;
						loadimage(&imChuyin , _T("images/chuyin.png"));	//加载
						putimage(120 , 50 , &imChuyin);	//绘制

						while(true)
						{
							m = getmessage(EX_MOUSE | EX_KEY);
							if (m.message == WM_RBUTTONDOWN)	//如果按下ctrl键 退出这个界面 继续敲木鱼
							{ break; }
						}

						//两张贴图

					}
					else if(rand()%4 == 2)	//? 0.25只因
					{
						settextcolor(BLACK);
						outtextxy(0 , 0 , _T("我去，只因未来"));
						outtextxy(0 , 600 , _T("右击继续攒功德"));
						//贴图
						IMAGE imZhiyin;
						loadimage(&imZhiyin , _T("images/zhiyin.jpg"));	//加载
						putimage(400 , 150 , &imZhiyin);	//绘制
						//阻塞
						m = getmessage(EX_MOUSE | EX_KEY);
						while (true)
						{
							if (m.message == WM_RBUTTONDOWN)	//如果按下ctrl键 退出这个界面 继续敲木鱼
							{ break; }
							else if (m.message == WM_LBUTTONDOWN)	//按下鼠标左键 出发声音
							{
								PlaySound(_T(_binary_zhiyin_wav_start), NULL , SND_NOSTOP | SND_MEMORY | SND_ASYNC);	//播放ji声
							}
							m = getmessage(EX_MOUSE | EX_KEY);

						}

					}
					settextcolor(WHITE);
				}
				break;
		}

		//Sleep(70);
	}
	
}