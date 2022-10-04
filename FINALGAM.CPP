#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <iostream>
#include <time.h>
using namespace std;

char far *lno[] = { "1" ,"2", "3", "4", "5", "6", "7" };

class timer {
	private:
		unsigned long begTime;
	public:
		void start() {
			begTime = clock();
		}

		unsigned long elapsedTime() {
			return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
		}

};

void start_game( );
void game_menu();
void Game( int , int &);
void initialize_draw_path( int & , int & , int [100][2] , int [10],int,int &);
void check_line( int [100][2] , int );
void check_path( int  , int [100][2] , int [10], int &, int, int );

void main()
{
clrscr();
   int gdriver=DETECT, gmode=DETECT;
   initgraph( &gdriver, &gmode, "..\\bgi ");
   cleardevice();

   randomize();
   start_game();
   closegraph();
}

void start_game( )
{

	for(int i=0;i<getmaxcolor()/2;i++)
	{

		setbkcolor(i);
		delay(50);
		cleardevice();
	}

	int midx=getmaxx()/2;
	int midy=getmaxy()/2;

	for(i=0;i<getmaxcolor();i++)
	{
		setbkcolor(BLUE);
		setcolor(i);
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		outtextxy(midx-10,midy,"DOWNWARDS");
		settextjustify(LEFT_TEXT,CENTER_TEXT);
		outtextxy(midx-5,midy+20,"BY:- Shreedutt VYAS");
		outtextxy(midx-5,midy+30,"& Aatish Choudhary ");
		outtextxy(midx-5,midy+40,"Class 12th ,HILLWOODS SCHOOL");
		delay(100);
	 //     cleardevice();
	}

	getch();

	cleardevice();

	game_menu();


}


void game_menu(  )
{

	cleardevice();
	int ch;

	setbkcolor(BLUE);
	setcolor(YELLOW);
	outtextxy(219,249,"1.START GAME");
	outtextxy(219,259,"2.RULES");
	outtextxy(219,269,"3.EXIT");
	gotoxy(20+4,20);
	cout<<"Enter your choice:";

	cin>>ch;

	switch(ch)
	{
		case 1:
				int gamecon;
				int lv=1;
				for(int i=0; ;i++)
				{

					Game(lv,gamecon);
					if(gamecon)
						lv++;

					else
					   break;

				}
				game_menu();
				break;

		case 2:     cleardevice();
				setcolor(BROWN);
				outtextxy(80,100,"RULES");
				outtextxy(80,110,"_______________________________________________________________");
				outtextxy(80,120,"1.Player must choose the path number that leads to target showen i.e T.");
				outtextxy(80,130,"  This must be done before 10 seconds.");
				outtextxy(80,150,"2.If player intputs any other value , then the it will be taken");
				outtextxy(80,160,"  as the last path.");
				outtextxy(80,180,"3.After this trajectory will run from choosen path till reached down.");
				outtextxy(80,200,"4.Trajectory is determined by the horizontal lines.");
				outtextxy(80,210,"5.");
				outtextxy(80,240,"  ");
				outtextxy(80,260,"Hint: Try to figure out the path from T till reached up to any ");
				outtextxy(80,270,"      path number");
				delay(2000);
				getch();
				cleardevice();
				game_menu( );
				break;

		case 3:  	exit(0);

		default:	game_menu( );
				break;

	}

}

void Game(int lv,int &gamecon)
{

	int tx;

	int v,h;

	int hxy[200][2],vxy[10];

	for(int dot=0;dot<200;dot++)
	{
		hxy[dot][0]=hxy[dot][1]=0;
	}

	for(dot=0;dot<10;dot++)
	{
		vxy[dot]=0;
	}

	setbkcolor(BLUE);
	setfillstyle(CLOSE_DOT_FILL,BROWN);
	bar(0,0,getmaxx(),getmaxy());
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL,CYAN);
	bar(30,119,getmaxx()-30,419);

	gotoxy(30+4,1);
	cout<<"level "<<lv;

	cout<<"\nENTER A PATH in 10 seconds";
	cout<<"\nPress any key to procced\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	getch();

	initialize_draw_path( v , h , hxy , vxy , lv , tx);

	int ch;

	unsigned long seconds = 10;

	timer t;
	int flag=1;

	t.start();

	//gotoxy(10,4);
	cout <<"\b\b\b\b\b\b\b\btimer started . . 10 sec";
	gotoxy(10,5);
	cout<<"ENTER ROUTE NO:";

	while(flag)
	{

		if(t.elapsedTime() > seconds)
		{
			flag=0;
		}

		if( kbhit() )
		{
			ch=getch();
			(int)ch;
			  ch=ch-48;
			  if(ch< 1||ch > (v) )
				ch=v;

			  cout<<ch;
			  --ch;

			 break;

		}

	}

	if( flag == 0)
	{
		gotoxy(10,5);
		cout << seconds <<  " seconds elapsed\n";
		delay(2000);
		floodfill(0,0,BLUE);
		gotoxy(30,10);
		cout << "!!GAME OVER!!";
		gamecon=0;
		getch();
	}

	else
	{
		if(gamecon)
		{
			int gx;
			check_path(  h , hxy , vxy , gx , ch ,1);

			if(gx==tx)
			{
				gotoxy(33,6);
				cout<<"Right choice";
				gotoxy(27,7);
				cout<<"You proceed to next level";
				gamecon=1;
			}

			else
			{
				gotoxy(30,6);
				cout<<"Wrong Choice";
				for(int i=0;i<v;i++)
				{
					check_path( h , hxy , vxy , gx ,i,0);

					if(gx==tx)
						break;
				}
				gotoxy(28,7);
				cout<<"Right Choise was "<<i+1;
				gamecon=0;

			}

	}

	}
	getch();

}

void initialize_draw_path(int &v,int &h,int hxy[100][2],int vxy[10],int lv,int &tx)
{
	char str[10];

	int x,p,temp;

	h=0;

	if(lv==1)
	{

		v=2;
		x=219;
		p=200;

	}
	else if(lv>1&&lv<=2)
	{
		v=3;
		x=169;
		p=150;
	}
	else if(lv>2&&lv<=3)
	{
		v=4;
		x=169;
		p=100;
	}

	else if(lv>3&&lv<=4)
	{
		v=5;
		x=169;
		p=75;
	}

	else if(lv>4&&lv<=5)
	{
		v=6;
		x=114;
		p=75;
	}

	else if(lv>5)
	{
		v=7;
		x=94;
		p=75;
	}

	tx=random(v)+1;

	for(int i=0;i<v;i++)
	{

		vxy[i]= x;
		x+=p;

	}

	for(i=0;i<v;i++)
	{
		if( (i+1) == tx )
		{

			outtextxy(vxy[i]-2,382,"T");
			tx=vxy[i];
		}

		else
		  outtextxy(vxy[i]-2,379,"X");

		  outtextxy(vxy[i]-2,159,lno[i]);

		  line(vxy[i],169,vxy[i],369);

	}

	int j=0;
	for( i=0 ;i<v-1; i++)
	{

		temp=4;
								 //
		for(;j<(h+(temp*2));j++)             //
		{                                    //
			hxy[j][0] = vxy[i];
			hxy[j][1] = random(171)+189;
			check_line(hxy,j);
			hxy[j+1][0] = vxy[1+i];
			hxy[j+1][1] = hxy[j][1];
			line(hxy[j][0],hxy[j][1],hxy[j+1][0],hxy[j+1][1]);
			++j;
		}
		h+=temp;
	}


}

////////////////////////////////////////////
//                                        //
////////////////////////////////////////////
void check_line(int hxy[100][2],int i)
{
	int q,temp=0;

	for(q=i-1;q>=0;q--)
	{

		for(int k=0;k<4;k++)
		{

			if( hxy[i][1] == (hxy[q][1]+k) || hxy[i][1] ==( hxy[q][1]-k) )
			{
				hxy[i][1]=random(171)+179;
				temp=-1;

			}

		}

	}

	if( temp == -1 )
		check_line(hxy,i);

}

void check_path(int h,int hxy[100][2],int vxy[10],int &gx,int ch,int checkc )
{

	setfillstyle(SOLID_FILL,RED);
	moveto(vxy[ch],139);

	for(int i=169;i!=369+1;i++)
	{
		moveto(vxy[ch],i);

		if(checkc)
		{
			setcolor(DARKGRAY);
			fillellipse(vxy[ch],i,2,2);
			putpixel(vxy[ch],i-2,RED);
			delay(5);
		}

		for(int j=0;j<h*2;j++)
		{
			if( getx()==hxy[j][0] && gety()==hxy[j][1])
			{

				if( hxy[j][1] ==  hxy[j+1][1] )
				{
					delay(7);
					for(int cx=vxy[ch];cx!=vxy[ch+1]+1;cx++)
					{
						moveto(cx,hxy[j][1]);
						if(checkc )
						{
							fillellipse(cx,hxy[j][1],2,2);
							putpixel(cx-2,hxy[j][1],RED);
							delay(7);
						}
					}
					++ch;
					break;
				}

				else if( hxy[j][1]  ==  hxy[j-1][1] )
				{
					delay(7);
					for(int cx=vxy[ch];cx!=vxy[ch-1]-1;cx--)
					{
						moveto(cx,hxy[j][1]);
						if(checkc )
						{
							fillellipse(cx,hxy[j][1],2,2);
							putpixel(cx+2,hxy[j][1],RED);
							delay(7);
						}
					}

					--ch;
					break;
				}
			}
		}

	}
	gx=getx();
}
