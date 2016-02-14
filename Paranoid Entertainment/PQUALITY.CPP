// Aniruddha Varma R
// IT - A  Year 1
// MEC



#define ESPEED 1.3
#define PSPEED 7
#define BSPEED 1.8
#define TGAP 90


#define TOTAL_ENEMIES 5

#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <bios.h>
#include <dos.h>

void splash();
void load_bar();
void enemy_enter();

int on=1;

class me
{
	public:
	float x,y,side;int dir,clr,enabled;


	me()
	{
		dir=1;side=10;enabled=1;
	}

	void draw(float x2,float y2)
	{
		rectangle(x2,y2+side,x2+3*side,y2+4*side);
		//int r[8]={x2,y2+side,x2+3*side,y2+side,x2+3*side,y2+4*side,x2,y2+4*side};
		//fillpoly(4,r);
		switch(dir)
		{
			case 1:rectangle(x2+3*side,y2+2*side,x2+4*side,y2+3*side);break;
			case 4:rectangle(x2+side,y2,x2+2*side,y2+side);break;
			case 2:rectangle(x+side,y+4*side,x+2*side,y+5*side);break;
			case 3:rectangle(x-side,y+2*side,x,y+3*side);break;
		}

	}
	void move(float newx,float newy,int newdir)
	{
		if(block(newx,newy,newdir)==0) {return;}
		setcolor(BLACK);setfillstyle(1,BLACK);draw(x,y);
		x += newx; y += newy; dir = newdir;
		setcolor(clr);setfillstyle(1,clr);draw(x,y);
	}
	int block(int nx, int ny, int ndir)
	{

		if(ndir==4 && y+ny<=0) return 0;
		if(ndir==3 && x+nx-side<=0) return 0;
		if(ndir==2 && y+ny+5*side>=getmaxy()) return 0;
		if(ndir==1 && x+nx+4*side>=getmaxx()) return 0;


			//if(ndir==3)
			//if(x+nx-side<walls[0].x+walls[0].side)
			//if(y+ny>walls[0].y && y+ny+4*side<walls[0].y+walls[0].side)
			if(ndir==1)
			if(getpixel(x+4*side+PSPEED,y+side)==BLUE || getpixel(x+4*side+PSPEED,y+4*side)==BLUE)
			return 0;

			if(ndir==4)
			if(getpixel(x,y-PSPEED)==BLUE || getpixel(x+3*side,y-PSPEED))
			return 0;

			if(ndir==3)
			if(getpixel(x-side-PSPEED,y+side)==BLUE || getpixel(x-side-PSPEED,y+4*side)==BLUE)
			return 0;

			if(ndir==2)
			if(getpixel(x,y+5*side+PSPEED)==BLUE || getpixel(x+3*side,y+5*side+PSPEED)==BLUE)
			return 0;

		return 1;
	}


} player,enemy[TOTAL_ENEMIES];



class shot
{
	public:
	float x,y; int radius,dir,colour;   int on_screen;


	shot()
	{
		on_screen=0; colour=MAGENTA;
	}
	void init()
	{
		//x=player.x;y=player.y;
		radius=3;
		setcolor(colour);
		if(dir==1) circle(x=player.x+5*player.side,y=player.y+2*player.side,radius);
		if(dir==2) circle(x=player.x+player.side,y=player.y+6*player.side,radius);
		if(dir==3) circle(x=player.x-3*player.side,y=player.y+2*player.side,radius);
		if(dir==4) circle(x=player.x+player.side,y=player.y-player.side,radius);
		//circle(player.x,player.y,radius);
		on_screen=1;
	}
	void draw()
	{
		//if(on_screen==0) return;
		//float newx=player.x+player.side;float newy=player.y+2*player.side;
		float newx=x;float newy=y;
		if(dir==1)  newx+=BSPEED;
		if(dir==2)  newy+=BSPEED;
		if(dir==3)  newx-=BSPEED;
		if(dir==4)  newy-=BSPEED;

			//setfillstyle(1,BLACK);
			//floodfill(x,y,colour);
			setcolor(BLACK);
			circle(x,y,radius);


			setcolor(colour);
			x=newx;y=newy;
			circle(x,y,radius);
			//floodfill(x,y,colour);


		if(newx<0||newx>getmaxx()) {on_screen=0;setcolor(BLACK);circle(x,y,radius);}
		if(newy<0||newy>getmaxy()) {on_screen=0;setcolor(BLACK);circle(x,y,radius);}

		crack();
		hit();
	}

	void crack()
	{
		for(int i=0;i<TOTAL_ENEMIES;++i)
		{
		  if(x>enemy[i].x&&y>enemy[i].y&&x<enemy[i].x+3*enemy[i].side&&y<enemy[i].y+4*enemy[i].side)
		  if(enemy[i].enabled)
		  {
			  enemy[i].enabled=0;
			  setcolor(BLACK);
			  enemy[i].draw(enemy[i].x,enemy[i].y);
			  circle(x,y,radius);
			  on_screen=0;
		  }
		}
	}

	void hit()
	{
		int flag=0;

		if(dir==1)
		if (getpixel(x+radius+BSPEED+0.5,y)==BLUE)
		flag=1;

		if(dir==2)
		if(getpixel(x,y+radius+BSPEED+0.5)==BLUE)
		flag=1;

		if(dir==3)
		if(getpixel(x-radius-BSPEED-0.5,y)==BLUE)
		flag=1;

		if(dir==4)
		if(getpixel(x,y-radius-BSPEED-0.5)==BLUE)
		flag=1;


		if(flag==1)
		{
			setcolor(BLACK);
			circle(x,y,radius);
			on_screen=0;
		}
	}




}cracker;


class wall
{
	public:

	float x,y,side,clr;
	int enabled,texture;

	wall()
	{
		enabled=1;
		side=50;clr=BLUE;
		texture=5;
	}
	void draw()
	{
		setcolor(clr);
		setfillstyle(texture,clr);
		int p[8]={x,y,x+side,y,x+side,y+side,x,y+side};
		fillpoly(4,p);
		setfillstyle(texture+1,clr);
		fillpoly(4,p);
	}

	void delme()
	{
		setcolor(BLACK);
		rectangle(x,y,x+side,y+side);
		setfillstyle(1,BLACK);
		int p[8]={x,y,x+side,y,x+side,y+side,x,y+side};
		fillpoly(4,p);
	}

	void move()
	{
		delme();
		x+=random(3);
		y+=random(3);
		draw();
	}


}walls[5];




int main(void)
{

   sound(100);delay(500);nosound();

   randomize();


   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics mode */
   initgraph(&gdriver, &gmode, "");
						 //    X
   /* read result of initialization */           //   XXX
   errorcode = graphresult();                    //   XXX
						 //   XXX
   splash();

   //enemy_enter();

   setcolor(LIGHTBLUE);
   rectangle(0,0,getmaxx(),getmaxy());
   //int side=10;int movex=2;
   //int x = 50; int y = 50;
   //rectangle(x+side,y,x+2*side,y+side);
   //rectangle(x,y+side,x+3*side,y+4*side);


   walls[0].x=0;walls[0].y=0;walls[0].draw();
   walls[1].x=getmaxx()-walls[1].side;walls[1].y=0;walls[1].draw();
   walls[2].x=0;walls[2].y=getmaxy()-walls[2].side;walls[2].draw();
   walls[3].x=getmaxx()-walls[3].side;walls[3].y=getmaxy()-walls[3].side;walls[3].draw();
   walls[4].side=100;walls[4].x=getmaxx()/2-walls[4].side/2;walls[4].y=getmaxy()/2-walls[4].side/2;walls[4].draw();


   setcolor(GREEN);
  player.dir=4; player.side=10;player.x=100;player.y=100;player.draw(100,100);
  enemy[0].x=150;enemy[0].y=60;enemy[0].draw(150,60);
  enemy[1].x=300;enemy[1].y=70;enemy[1].draw(300,70);
  enemy[2].x=400;enemy[2].y=200;enemy[2].draw(400,200);
  enemy[3].x=500;enemy[3].y=100;enemy[3].draw(500,100);
  enemy[4].x=500;enemy[4].y=250;enemy[4].draw(650,250);
  for(int i=0;i<5;++i)
	enemy[i].clr=RED;



  player.clr=GREEN;
  int timer=0;int edir[6];long skip=0; long wdraw=0;
  edir[0]=1;edir[2]=3;edir[4]=1;
  edir[1]=2;edir[3]=4;//edir[5]=2;

   while(1)
   {
	skip++;if(skip<600000) continue; if(skip>600000) skip=0;
	int chk;
	if(bioskey(1))
	if(chk=bioskey(0))
	{
	  if(chk==283) break;
	  if(chk==19712) {player.move(PSPEED,0,1);continue;  }
	  if(chk==20480) {player.move(0,PSPEED,2);continue;  }
	  if(chk==19200) {player.move(-PSPEED,0,3);continue; }
	  if(chk==18432) {player.move(0,-PSPEED,4);continue; }
	  if(chk==14624 && cracker.on_screen==0) {cracker.dir=player.dir;cracker.init();}
       }
       //skip++;if(skip<100000) continue; if(skip>100000) skip=0;
       for(int i=0;i<TOTAL_ENEMIES;++i)
       {
	 if(enemy[i].enabled)
	 {
	  if(edir[i]==1) enemy[i].move(ESPEED,0,1);
	  if(edir[i]==2) enemy[i].move(0,ESPEED,2);
	  if(edir[i]==3) enemy[i].move(-ESPEED,0,3);
	  if(edir[i]==4) enemy[i].move(0,-ESPEED,4);
	 }
       }
       setcolor(GREEN);
       player.draw(player.x,player.y);
       if(cracker.on_screen) cracker.draw();
       timer++;
       if(timer==TGAP)
       {        for(int i=0;i<6;++i)
		edir[i]=random(4)+1;timer=0;
       }
       setcolor(LIGHTBLUE);
       rectangle(0,0,getmaxx(),getmaxy());
       //enemy_enter();

   }





   getch();
   closegraph();
   return 0;
}



void splash()
{
	randomize();
	float x=getmaxx()/2; int y=getmaxy()/2;
	float side=1;
	for(float i=0.5;i<400;++i,++side)
	{
		setcolor(random(5));
		rectangle(x-side,y-side,x+side,y+side);
		delay(5);
	}

	/*for(i=0;i<500;++i,--side)
	{
		setcolor(BLACK);
		rectangle(x-side,y-side,x+side,y+side);
		delay(6);
	}*/
	//	outtextxy(50,50,"Loading");
	int p[8]={0,0,getmaxx(),0,getmaxx(),getmaxy(),0,getmaxy()};
	setfillstyle(1,BLACK);
	fillpoly(4,p);
}


void load_bar()
{
	float x=getmaxx()/2;
	float y=getmaxy()/2;
	float side = 25;

	rectangle(x-side,y-side,x+side,y+side);

	/*float limit=side;
	for(int i=1;i<limit;i++)
	{
		rectangle(x-side,y-side,i,i+side);
		delay(10);
	} */
}

void enemy_enter()
{
	if(on==0) return;

	//setcolor(BLACK);
	//line(0,0,0,getmaxy());
	static float x=-100;
	static float y=getmaxy()/2;
	setcolor(RED);
	enemy[5].clr=RED;
	for(;x<60;)
	{
		setcolor(BLACK);
		enemy[5].draw(x,y);
		delay(10);
		x+=0.4;
		setcolor(RED);
		enemy[5].draw(x,y);
		return;
	}
	on=0;
	enemy[5].x=x;
	enemy[5].y=y;


}
