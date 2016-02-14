#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>

void DrawFaces(int type=2,int y=wherey());
void DrawFaces2(int gap=1,int speed=0.01/*0.2*/,int y=wherey()); // type always 2
void Text(char text[],int make_center=0,int style=1, float speed=0.01/*0.1*/,int goto_next_line=1);
void goto_center();


void AddArrays();
void SubArrays();
void AscSort();

void main()
{
	char choice;
	textcolor(CYAN);
	clrscr();
	getch();
	//DrawFaces();
	//cout<<"\n";
	//Text("-+-+-Standard XI C++ PROJECT-+-+-",2,0.23);
	//cout<<"\n";
	//Text("-+-ARRAYS MANIPULATION-+-",2,0.23);
	//cout<<"\n";
	//DrawFaces();
	DrawFaces2(3,50);
	DrawFaces(1,45);
	gotoxy(1,10);
	cout<<"\n";
	Text("1 : Add Arrays",1);
	cout<<"\n";
	Text("2 : Subtract Arrays",1);
	cout<<"\n";
	Text("3 : Multiply Arrays",1);
	cout<<"\n";
	Text("4 : Sort an Array",1);
	cout<<"\n\n";
	Text("Your choice : ",1,1,0.1,0);
	choice = getch();
	if(choice=='1')
		AddArrays();
	else if(choice=='2')
		SubArrays();
	else if(choice=='3')
		AscSort();
	//DrawFaces2(wherey(),2);
	getch();

}

void DrawFaces(int type,int y)
{

	int i,rightx=80,leftx=1;
	char ch=2, flag='l';

	for(i=0;i<80;++i)
	{ 	delay(25);

		if(flag=='l')
		{
			gotoxy(leftx,y);
			leftx++;
			flag='r';
			cout<<ch;
			ch=((ch==2)?1:2);
			continue;
		}
		else
		{
			gotoxy(rightx,y);
			rightx--;
			flag='l';
			cout<<ch;
			if(type==1)
				ch=(ch==1)?2:1;
			//above lines commented for alternate faces
			continue;
		}

	}
	cout<<"\n";
}


void Text(char text[50], int make_center,int style, float speed,  int goto_next_line)
{
	//Style 1 Decl
	int i;
	//Style 2 Decl
	int posl,posr,printl,printr;

	speed=speed*1000; //convert to milliseconds

	if(make_center==1)
		gotoxy(40-(strlen(text)/2),wherey());

	if(style==2)
	{
		posl=40-strlen(text)/2;
		posr=40+strlen(text)/2;

		printl=0;
		printr=strlen(text)-1;

		for(;posl<=40;++posl,--posr,++printl,--printr)
		{
			delay(speed);
			gotoxy(posl,wherey());
			cout<<text[printl];
			gotoxy(posr,wherey());
			cout<<text[printr];
		}
	}
	else //style=1
	{
		for(i=0;text[i]!='\0';++i)
		{
			if(text[i]!=' ')
			delay(speed);
			cout<<text[i];
		}
	}
	if(goto_next_line==1)
		cout<<"\n";
}
void DrawFaces2(int gap,int speed, int y)
{
	int leftx1=0,y1=y,rightx2=80,y2=y+gap;
	char ch=2;

	for(;leftx1!=80||rightx2!=0;++leftx1,--rightx2)
	{
		delay(speed);
		gotoxy(leftx1,y1);
		cout<<ch;

		ch=(ch==2)?1:2;
		gotoxy(rightx2,y2);
		cout<<ch;
	}

}

void goto_center()
{
	gotoxy(getmaxx(),wherey());

}

void AddArrays()
{
	clrscr();
	int ar1[50],ar2[50];
	int size1,size2,i,j;

	Text("Array 1 : Enter the size required :  \n");
	cin>>size1;  cout<<"\n";
	Text("Enter Array elements : \n");
	for(i=0;i<size1;++i)
		cin>>ar1[i];
	cout<<"\n";
	Text("Array 2 : Enter the size required : \n");
	cin>>size2;  cout<<"\n";
	if(size1!=size2)
	{
		cout<<"Error : The sizes of the arrays are different.";
		getch();
		exit(0);
	}
	Text("Enter Array elements : \n");
	for(i=0;i<size2;++i)
		cin>>ar2[i];
	cout<<"\n";
	Text("Sum of the elements in the arrays is : \n");
	for(i=0;i<size1;++i)
		cout<<ar1[i]+ar2[i];
	getch();
}

void SubArrays()
{
	clrscr();
	int ar1[50],ar2[50];
	int size1,size2,i,j;

	Text("Array 1 : Enter the size required :  \n");
	cin>>size1;  cout<<"\n";
	Text("Enter Array elements : \n");
	for(i=0;i<size1;++i)
		cin>>ar1[i];
	cout<<"\n";
	Text("Array 2 : Enter the size required : \n");
	cin>>size2;  cout<<"\n";
	if(size1!=size2)
	{
		cout<<"Error : The sizes of the arrays are different.";
		getch();
		exit(0);
	}
	Text("Enter Array elements : \n");
	for(i=0;i<size2;++i)
		cin>>ar2[i];
	cout<<"\n";
	Text("Difference of the elements in the arrays is : \n");
	for(i=0;i<size1;++i)
		cout<<ar1[i]-ar2[i];
	getch();
}

void AscSort()
{

	int ar[50];
	int i,j,temp,size;

	clrscr();
	Text("Enter array size : \n");
	cin>>size; cout<<"\n";
	Text("Enter array elements : \n");
	for(i=0;i<size;++i)
		cin>>ar[i];
	cout<<"\n";
	for(i=0;i<size-1;++i)
	  for(j=i+1;j<size;++j)
		if(ar[i]>ar[j])
		{
			temp=ar[i];
			ar[i]=ar[j];
			ar[j]=temp;
		}
	Text("Sorted Array : \n");
	for(i=0;i<size;++i)
		cout<<ar[i];
	getch();
}








