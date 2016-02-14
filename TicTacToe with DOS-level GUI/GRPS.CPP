#include<all.h>
#include<dos.h>
#include<fstream.h>
#define time 250
#define COMPUTER 0
#define USER 1
#define true 1
#define false 0

/*

	Sets up a tic-tac-toe game using graphics.
	+ ENTER places ur symbol, ESCAPE quits program.
	+ use W,S,A,D for navigation.

	I had written this program for my XII Std Comp project.
	But I shifted later to "Arkanoid".

	You play against the not-dumb computer. The computer's placements
	were chosen randomly when I first wrote this program. Then I decided
	that the game was too easy, and put in some artificial intelligence.

	What does this mean ? 
	This means that this game is tougher than Mario.
	
	Have fun.
	
*/
struct point
{
	int x,y;
};
		     int bloo;
struct box
{
	char ch;
};

int retrndbox()
{
	int temp=random(5)+random(4)+random(3);   // 0 - 9
	while(!temp)
	{
		temp=random(5)+random(4)+random(3);
	}
	return temp;
}

void define_points();                      // initialize points
void draw_box(int box_num);                // draw "box_num" box

void drawl(point a, point b);              // helps call line()
void center(point top_left);               // helps call circle()
void drawb(point top_left, point bot_rt);  // helps call rectangle()

void goto_box(int box_num);    // move selection to "box_num" box

void draw_x(int box_num);      // draws an X on "box_num" box
void draw_o(int box_num);      // draws an O on "box_num" box

void computer_move();          // comp's turn
void get_key();                // user's turn

int artintel();                // artificial intelligence
int defy_tricks();             // [ the same ]

int player1,player2;           // player1 is whosoever plays first

void player_1()
{
	if(player1==COMPUTER)
	{   delay(1000); computer_move();   }
	else
		get_key();
}
void player_2()
{
	if(player2==COMPUTER)
	{   delay(1000); computer_move();   }
	else
		get_key();
}

void message(char text[])
{
	setcolor(GREEN);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy((getmaxx()/2)-(strlen(text)/2*20),getmaxy()-50,text);
	getch();
	setcolor(BLACK);
	outtextxy((getmaxx()/2)-(strlen(text)/2*20),getmaxy()-50,text);
}

// GLOBAL VARIABLES :-


   int bl=50,AI=100;        // small box length and artificial intelligence
   char key,my_symbol='o',name[15]="speedy";
   int selected = 5;
   int game_over=true;

   box b[10];               // b[0] won't be used

   point p1,p2,p3,p4,p5,p6,p7,p8,p9,p10;    // the vertices
   point p11,p12,p13,p14,p15,p16;           // the vertices

   ofstream fout("tttlog.txt");  // store everything which happens


void main()
{
	player1=USER;player2=COMPUTER;
	if(int(getch())==13) goto begin;
	cout<<"Welcome to Graphical TicTacToe\n\n";
	cout<<"What is your first name? ";
	cin>>name;
	cout<<"What Game Board size would you like ? (10-100) ";
	cin>>bl;
	cout<<"What symbol would you like ? ( o or x) ";
	cin>>my_symbol;
	cout<<"Tossing a coin...";
	randomize();
	if(random(100)<50)
	{
		player1 = COMPUTER;
		cout<<"Computer plays first.";
		fout<<"Computer plays first.";
		player2 = USER;
	}
	else
	{
		player1 = USER;
		cout<<name<<" plays first.";
		fout<<name<<" plays first.\n";
		player2 = COMPUTER;
	}
	cout<<"\n\nEntering graphics mode.....press any key";
	getch();
   begin:
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   int xmax, ymax;


   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "");
					     // graphics.h
   /* read result of initialization */
   errorcode = graphresult();
   /* an error occurred */
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }


   setcolor(BLUE);
   settextstyle(GOTHIC_FONT,HORIZ_DIR,5);


   /* draw a diagonal line */
   /*line(0,0,xmax,0);
  // gotoxy(40,3);
   line(0,36,xmax,36);
   line(0,0,0,ymax);
   line(xmax,0,xmax,ymax);
   line(0,ymax,xmax,ymax);  //
   setcolor(LIGHTBLUE);
   Text("    Cryptor : Encryption and Decryption",1,1,0.2,1);
   Text("1. Encrypt",1,1,0.1,1);
   Text("2. Decrypt",1,1,0.1,1);   */

    define_points();
    for(int i=1;i<10;++i)
	draw_box(i);
    goto_box(5);
    setlinestyle(DOTTED_LINE,1,1);
    rectangle(0,0,getmaxx(),getmaxy());
    setlinestyle(SOLID_LINE,1,1);
    outtextxy(130,0,"~ TIC TAC TOE ~");
    //outtextxy((getmaxx()/2)-(strlen(name)/2*20),getmaxy()-50,name);
    //message("boom !");

    setcolor(CYAN);
    while(1)
    {
	game_over=true;
	for(i=1;i<=9;++i) if(b[i].ch=='\0') game_over = false;
	if(game_over==true) break;
	player_1();
	player_2();
    }



    getch();



   //for(int i=1;i<=9;++i)
   //draw_box(i);


   /* clean up */
   closegraph();
   cout<<bloo<<"\n";

   cout<<b[1].ch<<b[2].ch<<b[3].ch<<"\n";
   cout<<b[4].ch<<b[5].ch<<b[6].ch<<"\n";
   cout<<b[7].ch<<b[8].ch<<b[9].ch<<"\n";

   fout<<"\nFinal Picture :\n";
   fout<<b[1].ch<<b[2].ch<<b[3].ch<<"\n";
   fout<<b[4].ch<<b[5].ch<<b[6].ch<<"\n";
   fout<<b[7].ch<<b[8].ch<<b[9].ch<<"\n";
   fout.close();

}

void draw_box(int box_num)
{
	switch(box_num)
	{
		case 1:	drawb(p1,p6);   break;
		case 2:	drawb(p2,p7);   break;
		case 3: drawb(p3,p8);   break;
		case 4: drawb(p5,p10);  break;
		case 5: drawb(p6,p11);  break;
		case 6: drawb(p7,p12);  break;
		case 7: drawb(p9,p14);  break;
		case 8: drawb(p10,p15); break;
		case 9: drawb(p11,p16); break;
	}

}





void drawl(point a, point b)
{
	line(a.x,a.y,b.x,b.y);
}

void define_points()
{

p1.x=(getmaxx()/2)-1.5*bl; p1.y=(getmaxy()/2)-1.5*bl;
p2.x=p1.x+bl; p2.y=p1.y;
p3.x=p2.x+bl; p3.y=p1.y;
p4.x=p3.x+bl; p4.y=p1.y;
p5.x=p1.x;    p5.y=p1.y+bl;
p6.x=p5.x+bl; p6.y=p5.y;
p7.x=p6.x+bl; p7.y=p5.y;
p8.x=p7.x+bl; p8.y=p5.y;
p9.x=p1.x;    p9.y=p5.y+bl;
p10.x=p9.x+bl;  p10.y=p9.y;
p11.x=p10.x+bl; p11.y=p9.y;
p12.x=p11.x+bl; p12.y=p9.y;
p13.x=p1.x;     p13.y=p9.y+bl;
p14.x=p13.x+bl; p14.y=p13.y;
p15.x=p14.x+bl; p15.y=p13.y;
p16.x=p15.x+bl; p16.y=p13.y;

// intialise boxes
   for(int i=1;i<=9;++i)
	b[i].ch='\0';

}

void goto_box(int box_num)
{
	int i;
	setcolor(BLUE);
	draw_box(selected);
	setcolor(GREEN);
	draw_box(box_num);     // redraw box to be selected
	selected=box_num;
}

void get_key()
{
	setcolor(CYAN);
	key = getch();
	switch(key)
	{
		case 13:
			switch(my_symbol)
			{
				case 'o':
					draw_o(selected);
					b[selected].ch='o';
					fout<<"\n"<<name<<" places an o at "<<selected;
					return;
				case 'x':
					draw_x(selected);
					b[selected].ch='x';
					fout<<"\n"<<name<<" places an x at "<<selected;
					return;
			}

		case 27:
			exit(0);
		case 'd':
			switch(selected)
			{
				case 1: goto_box(2); break;
				case 2: goto_box(3); break;
				case 4: goto_box(5); break;
				case 5: goto_box(6); break;
				case 7: goto_box(8); break;
				case 8: goto_box(9); break;
			} break;
		case 'w':
			switch(selected)
			{
				case 7: goto_box(4); break;
				case 4: goto_box(1); break;
				case 8: goto_box(5); break;
				case 5: goto_box(2); break;
				case 9: goto_box(6); break;
				case 6: goto_box(3); break;
			} break;
		case 's':
			switch(selected)
			{
				case 1: goto_box(4); break;
				case 4: goto_box(7); break;
				case 2: goto_box(5); break;
				case 5: goto_box(8); break;
				case 3: goto_box(6); break;
				case 6: goto_box(9); break;
			} break;
		case 'a':
			switch(selected)
			{
				case 3: goto_box(2); break;
				case 2: goto_box(1); break;
				case 6: goto_box(5); break;
				case 5: goto_box(4); break;
				case 9: goto_box(8); break;
				case 8: goto_box(7); break;
			} break;

		case 'o':
			draw_o(selected);
			b[selected].ch='o';
			fout<<"\n"<<name<<" sneaks an o at "<<selected;
			break;
		case 'x':
			draw_x(selected);
			b[selected].ch='x';
			fout<<"\n"<<name<<" sneaks an x at "<<selected;
			break;
		case ' ':
			setcolor(BLACK);
			if(b[selected].ch=='x') draw_x(selected);
			if(b[selected].ch=='o') draw_o(selected);
			fout<<"\n"<<name<<" deletes box number "<<selected;
			b[selected].ch='\0';
			break;
	}
	get_key();
}

void draw_x(int box_num)
{
	switch(box_num)
	{
		case 1:	drawl(p1,p6);   drawl(p2,p5);   break;
		case 2:	drawl(p2,p7);   drawl(p3,p6);   break;
		case 3:	drawl(p3,p8);   drawl(p4,p7);   break;
		case 4:	drawl(p5,p10);  drawl(p6,p9);   break;
		case 5:	drawl(p6,p11);  drawl(p7,p10);  break;
		case 6:	drawl(p7,p12);  drawl(p8,p11);  break;
		case 7:	drawl(p9,p14);  drawl(p10,p13); break;
		case 8:	drawl(p10,p15); drawl(p11,p14); break;
		case 9:	drawl(p11,p16); drawl(p12,p15); break;
	}
}

void center(point top_left)
{
	circle(top_left.x+(bl/2),top_left.y+(bl/2),(bl/2)-1);
}


void draw_o(int box_num)
{
	switch(box_num)
	{
		case 1:	center(p1);  break;
		case 2:	center(p2);  break;
		case 3:	center(p3);  break;
		case 4:	center(p5);  break;
		case 5:	center(p6);  break;
		case 6:	center(p7);  break;
		case 7:	center(p9);  break;
		case 8:	center(p10); break;
		case 9:	center(p11); break;
	}
}

void computer_move()
{
	for(int i=1,game_over=true;i<=9;++i)           //-------------
	{                                              // to prevent
	 if(b[i].ch=='\0') { game_over=false; break; } // infinite
	}                                              // recursion
	if(game_over==true) return;                    //-------------

	int rndbox = retrndbox();
	if(random(100)+1<=AI)
	{
		if((rndbox=artintel())==0)
			rndbox=retrndbox();
		else
			fout<<"\nAI finds a goodie at "<<rndbox;
	}
	if (b[rndbox].ch!='o' && b[rndbox].ch!='x')
	{
		if (my_symbol=='x')
		{	draw_o(rndbox); b[rndbox].ch='o';
			fout<<"\nComp places an o at "<<rndbox;
			return;
		}
		else
		{	draw_x(rndbox); b[rndbox].ch='x';
			fout<<"\nComp places an x at "<<rndbox;
			return;
			}
	}
	computer_move();

}

void drawb(point top_left, point bot_rt)
{
	rectangle(top_left.x,top_left.y,bot_rt.x,bot_rt.y);
}
int artintel()
{
	if(b[1].ch==b[2].ch && b[2].ch!='\0' &&  b[3].ch=='\0') return 3;
	if(b[3].ch==b[2].ch && b[2].ch!='\0' &&  b[1].ch=='\0') return 1;
	if(b[4].ch==b[5].ch && b[5].ch!='\0' &&  b[6].ch=='\0') return 6;
	if(b[6].ch==b[5].ch && b[5].ch!='\0' &&  b[4].ch=='\0') return 4;
	if(b[7].ch==b[8].ch && b[8].ch!='\0' &&  b[9].ch=='\0') return 9;
	if(b[9].ch==b[8].ch && b[8].ch!='\0' &&  b[7].ch=='\0') return 7;
	if(b[1].ch==b[4].ch && b[4].ch!='\0' &&  b[7].ch=='\0') return 7;
	if(b[7].ch==b[4].ch && b[4].ch!='\0' &&  b[1].ch=='\0') return 1;
	if(b[2].ch==b[5].ch && b[5].ch!='\0' &&  b[8].ch=='\0') return 8;
	if(b[8].ch==b[5].ch && b[5].ch!='\0' &&  b[2].ch=='\0') return 2;
	if(b[3].ch==b[6].ch && b[6].ch!='\0' &&  b[9].ch=='\0') return 9;
	if(b[9].ch==b[6].ch && b[6].ch!='\0' &&  b[3].ch=='\0') return 3;
	if(b[1].ch==b[5].ch && b[5].ch!='\0' &&  b[9].ch=='\0') return 9;
	if(b[9].ch==b[5].ch && b[5].ch!='\0' &&  b[1].ch=='\0') return 1;
	if(b[7].ch==b[5].ch && b[5].ch!='\0' &&  b[3].ch=='\0') return 3;
	if(b[3].ch==b[5].ch && b[5].ch!='\0' &&  b[7].ch=='\0') return 7;

	if(b[1].ch==b[3].ch && b[3].ch!='\0' &&  b[2].ch=='\0') return 2;
	if(b[4].ch==b[6].ch && b[6].ch!='\0' &&  b[5].ch=='\0') return 5;
	if(b[7].ch==b[9].ch && b[9].ch!='\0' &&  b[8].ch=='\0') return 8;
	if(b[1].ch==b[7].ch && b[7].ch!='\0' &&  b[4].ch=='\0') return 4;
	if(b[2].ch==b[8].ch && b[8].ch!='\0' &&  b[5].ch=='\0') return 5;
	if(b[3].ch==b[9].ch && b[9].ch!='\0' &&  b[6].ch=='\0') return 6;
	if(b[1].ch==b[9].ch && b[9].ch!='\0' &&  b[5].ch=='\0') return 5;
	if(b[3].ch==b[7].ch && b[7].ch!='\0' &&  b[5].ch=='\0') return 5;



	//cout<<"\nAI Found nothing.";
	return 0;
}

int defy_tricks()
{
	// This idea is incomplete.

	if(b[1].ch==my_symbol&&b[9].ch=='\0') return 9;        //123
	if(b[9].ch==my_symbol&&b[1].ch=='\0') return 1;        //456
	if(b[3].ch==my_symbol&&b[7].ch=='\0') return 7;        //789
	if(b[7].ch==my_symbol&&b[3].ch=='\0') return 3;

	return 0; // found no traps
}

