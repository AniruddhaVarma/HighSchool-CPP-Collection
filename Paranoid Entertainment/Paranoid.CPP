#include<fstream.h>    // file I/O ops
#include<conio.h>      // getch(), clrscr()
#include<bios.h>       // bioskey()
#include<process.h>    // exit()
#include<graphics.h>   // circle(),rectangle() etc
#include<stdlib.h>     // random()
#include<timer.h>      // for timer objects
#include<dos.h>        // delay()


float score=0;
ofstream log("log.txt");
Timer tick;

class bat
{
     public:
	float x,y,len,bth,s;
	int clr; char h;
       bat(float a,float b,float le,float bt,int c,float spd)
       {
	x=a;y=b;len=le;bth=bt;clr=c;s=spd;
	move(x,y);
       }
       void move(float a,float b)
       {
	setcolor(BLACK); draw();
	x=a;y=b;
	setcolor(clr); draw();
       }
       void draw()
       {
	rectangle(x,y,x+len,y+bth);
       }
};



class brick
{
       public:
	float x,y,len,bth; int enabled,clr;
       brick(float a,float b,float c,float d)
       {
	enabled=0; x=a;y=b;len=0;bth=0;
       }
       brick()
       {
	enabled=0;x=0;y=0;len=100;bth=10;
       }
       void parentb()
       {
	if(enabled)
	{
		setcolor(clr);
		drawb();
	}
	else
	{
		setcolor(BLACK);
		drawb();
	}
       }
       void drawb()
       {
	rectangle(x,y,x+len,y+bth);
       }
};


class ball
{
  public:
	float x, y, radius, speed;
	int clr; char h, v;

       ball(float a,float b,float r,int c,float s)
       {
	x=a;y=b;radius=r;clr=c;speed=s;h='l';v='d';
       }
       void move(float a,float b)
       {
	setcolor(BLACK); draw();
	x=a;y=b;
	setcolor(clr); draw();
       }
       void draw()
       {
	circle(x,y,radius);
       }
       void parent(bat obat,brick bricks[],int n)
       {
	if(x-radius<0) h='r';
	if(x+radius>getmaxx()) h='l';
	if(y-radius<0) v='d';
	if(y+radius>getmaxy())
	{       v='u';
		score-=(2-speed); tick.stop();
		log<<tick.time()<<" ..and the ball goes down. You lose "<<2-speed<<" points\n";
		tick.start();
	}
	if(x-radius>=obat.x-4&&x+radius<=obat.x+obat.len+4)
	if((int)(y+radius-obat.y)==0)
		v='u';

	for(int i=0;i<n;++i)
	{
		if(bricks[i].enabled==1)
		if(x>=bricks[i].x&&x+radius<=bricks[i].x+bricks[i].len)
		if((int)((bricks[i].y+bricks[i].bth+1)-y)==0)
		{
			bricks[i].enabled=0; bricks[i].parentb();
			score+=speed; tick.stop();
			log<<tick.time()<<" You cracked a brick and gained "<<speed<<" points\n";
			tick.start();
			v='d';
		}
	}

	float newx=x,newy=y;
	if(v=='d') newy+=speed; else newy-=speed;
	if(h=='l') newx-=speed; else newx+=speed;
	move(newx,newy);
       }
};


void main()
{
	char message[]="Arkanoid : The Game\n\nCredits : Aniruddha and Vinod\n\nThis game is based on the famous \"Paranoid\" series. The aim of the game is to crack away all the bricks on the screen. Use the arrow keys to move your bat and the Escape key to exit.You can create custom stages by modifying the brs.txt file\n\n Enjoy ! ";

	for(int i=0;message[i]!='\0';++i)
	{
		delay(50);
		if(bioskey(1)) break;  //to skip intro, press a key
		cout<<message[i];
	}
	if(message[i]=='\0') getch();  // when player didn't skip intro
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");

	ball oball(0,50,10,GREEN,1);
	bat obat(getmaxx()/2-30,getmaxy()-20,120,10,GREEN,7.5);
	brick bricks[30];
	randomize();
	ifstream fin("brs.txt"); int nob; fin>>nob;
	for(i=0;i<nob;++i)
	{
		fin>>bricks[i].x;
		fin>>bricks[i].y;
		bricks[i].clr=random(15)+1;
		bricks[i].enabled=1;
		bricks[i].parentb();
	}
	fin.close();

	long instant=0,bspeed=0; int key;
	tick.start();
	while(1)
	{
		instant++; if(instant<800000) continue;
		instant=0;
		bspeed++;
		if(bspeed>=2000 && oball.speed<2)
		{
			oball.speed+=0.1;
			obat.s+=0.5; tick.stop();
			log<<tick.time()<<" -and the game gets hotter and faster with a ball speed of "<<oball.speed<<"\n";
			tick.start();
			bspeed=0;
		}

		oball.parent(obat,bricks,nob);
		for(i=0;i<nob;++i) bricks[i].parentb();
		obat.move(obat.x,obat.y);

		if(bioskey(1)!=0)
		{
			key=bioskey(0);
			if(key==283)
			{
			closegraph(); tick.stop();
			log<<tick.time()<<" the game's over with a score of "<<score;
			exit(0);
			}
			else if(key==19712) obat.move(obat.x+obat.s,obat.y);
			else if(key==19200) obat.move(obat.x-obat.s,obat.y);

		}
	}

}