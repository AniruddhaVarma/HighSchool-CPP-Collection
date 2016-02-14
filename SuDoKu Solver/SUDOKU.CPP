/*
		SU-DO-KU

     00 01 02 | 03 04 05 | 06 07 08
     10 11 12 | 13 14 15 | 16 17 18
     20 21 22 | 23 24 25 | 26 27 28        Box Identification Number
     ------------------------------           ----------------
     30 31 32 | 33 34 35 | 36 37 38           1133  1436  1739
     40 41 42 | 43 44 45 | 46 47 48           4163  4466  4769
     50 51 52 | 53 54 55 | 56 57 58           7193  7496  7799
     ------------------------------
     60 61 62 | 63 64 65 | 66 67 68
     70 71 72 | 73 74 75 | 76 77 78
     80 81 82 | 83 84 85 | 86 87 88
*/

#include<fstream.h>
#include<process.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

int  get_poss(int i,int j);

void double_down(int box);

int in_col(int col,int val);
	//chk whether "val" is in column "col".
int in_row(int row,int val);
	//chk whether "val" is in row "row".
int in_box(int i,int j,int val);
	//chk whether val is contained in the box which contains i,j.
int ret_box_cds(int i,int j);
	//returns box coords (ie, coords of top-left and bot-right
	//cell) of the box which contains (i,j) , as the
	//digits of an integer, after adding 1 to each digit. The
	//orig coords can be obtained by seperating the integer into
	//four digits and subtracting 1 from each of them.
void elim(int,int);
	//if in a box, a particular value (from 1-9) is possible only
	//in a particular cell, that value is placed in the cell.
void rem_lin_pos(int);
	//if in a box, a particular value (from 1-9) is possible in
	//only two/three cells,and if these cells are in the same row
	//or column,then all other possibilities of that value which
	//are contained in the same row/column but are in a different box
	//are removed.
void elim_row_but(int,int,int);
	//if a cell has a value, then all other possibilities of the
	//value which come in the same row as the cell, are removed.
void elim_col_but(int,int,int);
	//the above function for a column.
void cell_one_pos(int,int);
	//if only one value (from 1-9) is possible for a cell, then that
	//value is placed in the cell.

ofstream fout("sdk-op.txt");



struct space_s
{
	int value;
	int poss[10];  //1-9
} space[9][9];

void unfilled()
{
	int nop=0;
	for(int i=0;i<=8;++i)
	for(int j=0;j<=8;++j)
	{
		for(int k=1;k<=9;++k)
			if(space[i][j].poss[k]==1)
				nop++;
		if(nop==1)
		if(space[i][j].value==0)
		{	cout<<"Unfilled Problem.";
		       //	getch();
		}
		if(nop==0)
		{
			cout<<"Impossibility Error";
			getch();
		}
	}
}
int boxes_filled=0;

void main()
{
	clrscr();
	char pwd[]="bigmanani";
	char ans[20];
	cout<<"Enter password : ";
	for(int k=0;k<20;++k)
	{
		char let=getch();
		if(isalpha(let))
		{
			ans[k]=let;
			cout<<"*";
		}
		else break;
	}
	if(strcmp(ans,pwd))
	{
		cout<<"\nIncorrect password.";
		getch();
		exit(0);
	}



	int op;
	clrscr();
	fout<<"main\n";
	ifstream fin("sdk.txt");
	// cout<<"Enter the puzzle row-wise (Use 0's for empty spaces) :\n";
	for(int i=0;i<=8;++i)
	for(int j=0;j<=8;++j)
	{
	  fin>>space[i][j].value;
	  if(space[i][j].value==0)
	  {
		for(int k=1;k<=9;++k)
			space[i][j].poss[k]=1;
	  }
	  else
	  {
		for(int k=1;k<=9;++k)
		{
			if(k!=space[i][j].value)
				space[i][j].poss[k]=0;
			else
				space[i][j].poss[k]=1;
		}
	  }
	}
	cout<<"Puzzle accepted. Starting Evaluation.\n";  //getch();
	for(int e=1;;++e)
	{
		fout<<"Starting Evaluation "<<e<<"\n";  // getch();
		for(i=0;i<=8;++i)
		{
			for(j=0;j<=8;++j)
			{
				int nop=0;
				cell_one_pos(i,j);
				int the_poss_val=0;
				cout<<"Evaluating space "<<i<<" "<<j<<"\n"; //getch();
				if(space[i][j].value!=0)  // already filled
				{
				   cout<<"space "<<i<<" "<<j<<" is already filled.\n";//getch();
				   continue;
				}
				else cout<<"space "<<i<<" "<<j<<" is empty\n";//getch();
				for(int k=1;k<=9;++k)
				{
					cout<<"Trying value "<<k<<"\n"; //getch ();
					if(!in_col(j,k)&&!in_row(i,k)&&!in_box(i,j,k))       //   check conds
					{
						nop++;
						cout<<k<<" is a possible value.\n";  //getch();
						space[i][j].poss[k]=1;
						the_poss_val=k;
					}

					else if(in_col(j,k)||in_row(i,k)||in_box(i,j,k))
					{
						space[i][j].poss[k]=0;
						cout<<k<<" is not a possible value\n"; // getch();
					}

				}
				if(nop==1)
					{	space[i][j].value=the_poss_val;
						cout<<i<<" "<<j<<" ="<<the_poss_val<<"\n";// getch();
						boxes_filled++;

						for(int d=1;d<=9;d++)
						{
							if(d!=the_poss_val)
								space[i][j].poss[d]=0;
						}
					}
			}
		}
		elim(0,0);elim(0,3);elim(0,6);
		elim(3,0);elim(3,3);elim(3,6);
		elim(6,0);elim(6,3);elim(6,6);
		rem_lin_pos(1133);rem_lin_pos(4769);
		rem_lin_pos(1436);rem_lin_pos(7193);
		rem_lin_pos(1739);rem_lin_pos(7496);
		rem_lin_pos(4163);rem_lin_pos(7799);
		rem_lin_pos(4466);
		cout<<"\nEvaluation "<<e<<" finished. A total of "<<boxes_filled<<" spaces have now been filled.\n";
		Menu :
		cout<<"\n1.View the puzzle solved this far.\n";
		cout<<"2.Continue Evaluation.\n";
		cout<<"3.View the possibilities of a space. [row col]\n";
		cout<<"4.Exit Program.\n";
		cout<<"6.Elimination\n";
		cout<<"7.Set Value. [row col val]\n";
		cout<<"Choose an Option : ";
		cin>>op;
		if(op==1)
		{
			for(i=0;i<=8;++i)
			{
				for(j=0;j<=8;++j)
				{
					//if(space[i][j].value!=0)
						cout<<" "<<space[i][j].value;
				  /*	else
					{
						cout<<" {";
						for(int g=1;g<=9;++g)
						{
							if(space[i][j].poss[g])
							  cout<<g;
						}
						cout<<"}";
					}                        */
				}
				cout<<"\n";
			}
		}
		if(op==2)
		{
			unfilled();
			continue;

		}
		if(op==3)
		{
			int i,j;
			cin>>i>>j;
			cout<<"Possibilities are : ";
			for(int k=1;k<=9;++k)
			{
				if(space[i][j].poss[k]==1)
					cout<<k<<" ";
			}
		}
		if(op==4)
			exit(0);
		if(op==5)
		{
			cout<<"Enter BIN : ";
			int bin;
			cin>>bin;
			double_down(bin);
		}
		if(op==6)
		{
		elim(0,0);elim(0,3);elim(0,6);
		elim(3,0);elim(3,3);elim(3,6);
		elim(6,0);elim(6,3);elim(6,6);
		}
		if(op==7)
		{
			int si,sj,sval;
			cin>>si>>sj>>sval;
			space[si][sj].value=sval;
			space[si][sj].poss[sval]=1;
			for(i=1;i<10;++i)
			{
				if(i!=sval)
					space[si][sj].poss[i]=0;
			}
		}

		goto Menu;
	}  // e loop
}

int in_col(int c, int val)
{
	for(int i=0;i<=8;++i)
	{
		if(space[i][c].value==val)
			return 1;
	}
	return 0;
}

int in_row(int r,int val)
{
	for(int i=0;i<=8;++i)
	{
		if(space[r][i].value==val)
			return 1;
	}
	return 0;
}

int in_box(int i,int j,int val)
{
	int box = ret_box_cds(i,j);      int flag=0;
	int p1,p2,p3,p4;p1=box/1000;box=box-p1*1000;
	p2=box/100;box=box-p2*100;p3=box/10;box=box-p3*10;
	p4=box;p1--;p2--;p3--;p4--;
	cout<<"Checking box "<<p1<<" "<<p2<<","<<p3<<" "<<p4<<"\n"; //getch();
	for(int a=p1;a<=p3;a++)
	for(int b=p2;b<=p4;b++)
	{
		if(space[a][b].value==val)
		{	flag=1;
			cout<<val<<" was found in box at "<<a<<" "<<b<<"\n";
		}

	}
	if(!flag)
		cout<<val<<" was not found at box\n";
	return flag;

}

int ret_box_cds(int i,int j)
{
	// returns box cds + 1 as digs of an int

	int r,c;
	if(i==0||i==1||i==2)
		r=1;
	else if(i==3||i==4||i==5)
		r=2;
	else if(i==6||i==7||i==8)
		r=3;
	if(j==0||j==1||j==2)
		c=1;
	else if(j==3||j==4||j==5)
		c=2;
	else if(j==6||j==7||j==8)
		c=3;
	if(r==1&&c==1) return 1133;  // 00,22
	if(r==1&&c==2) return 1436;  // 03,25
	if(r==1&&c==3) return 1739;  // 06,28
	if(r==2&&c==1) return 4163;  // 30,52
	if(r==2&&c==2) return 4466;  // 33,55
	if(r==2&&c==3) return 4769;  // 36,58
	if(r==3&&c==1) return 7193;  // 60,82
	if(r==3&&c==2) return 7496;  // 63,85
	if(r==3&&c==3) return 7799;  // 66,88
	return 0;
}

void elim(int i,int j)
{
	// chk single probs
	int box = ret_box_cds(i,j);
	cout<<"\nEvaluating Box "<<box<<"\n";
	int p1,p2,p3,p4;p1=box/1000;box=box-p1*1000;
	p2=box/100;box=box-p2*100;p3=box/10;box=box-p3*10;
	p4=box;p1--;p2--;p3--;p4--;

	int num[10],k;  //1-9
	for(int a=1;a<=9;++a)
		num[a]=0;

	for(a=p1;a<=p3;++a)
	for(int b=p2;b<=p4;++b)
	{
		cout<<"Evaluating Space "<<a<<" "<<b<<"\n";
		if(space[a][b].value==0)
		{
			cout<<"The space is empty.\n";
			for(k=1;k<=9;++k)
			{
				if(space[a][b].poss[k]==1)
				{
					cout<<k<<" is possible\n";
					num[k]=num[k]+1;
				}

			}
		}
		else
			cout<<"The space is not empty\n";
	}
	cout<<"num[1] = "<<num[1]<<"\n";
	for(k=1;k<=9;k++)
	{

		if (num[k]==1)
	      {
			cout<<"\nentered here\n";

			for(a=p1;a<=p3;++a)
			for(b=p2;b<=p4;++b)
			{
				if(space[a][b].poss[k]==1&&!in_box(a,b,k)&&space[a][b].value==0)
				{
					space[a][b].value=k;
					for(int d=1;d<=9;++d)
					{
						if(d!=k)
							space[a][b].poss[d]=0;
					}
					cout<<"Value given for "<<a<<" "<<b<<" = "<<k;
					boxes_filled++;
				}
			}

	      }
	}
}

void rem_lin_pos(int box)
{
	int orig_box=box;

	int p1,p2,p3,p4;p1=box/1000;box=box-p1*1000;
	p2=box/100;box=box-p2*100;p3=box/10;box=box-p3*10;
	p4=box;p1--;p2--;p3--;p4--;

	// p1,p2 = top left cell

	// p1,p2 	p1,p2+1		p1,p2+2
	// p1+1,p2      p1+1,p2+1	p1+1,p2+2
	// p1+2,p2	p1+2,p2+1	p3,p4
	fout<<"entered rem_lin_pos \n";
	for(int k=1;k<=9;++k)
	{
		if(space[p1][p2].poss[k]==1&&space[p1][p2+2].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(i!=p1)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_row_but(orig_box,p1,k);
				fout<<"elim_row_but \n";
			}
		}

		if(space[p1][p2].poss[k]==1&&space[p1][p2+1].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(i!=p1)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_row_but(orig_box,p1,k);
				fout<<"elim_row_but \n";
			}
		}

		if(space[p1][p2+1].poss[k]==1&&space[p1][p2+2].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(i!=p1)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_row_but(orig_box,p1,k);
				fout<<"elim_row_but \n";
			}
		}

		if(space[p1+2][p2].poss[k]==1&&space[p1+2][p2+1].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(i!=p1+2)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_row_but(orig_box,p1+2,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1+2][p2].poss[k]==1&&space[p3][p4].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(i!=p1+2)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_row_but(orig_box,p1+2,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1+2][p2+1].poss[k]==1&&space[p3][p4].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(i!=p1+2)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_row_but(orig_box,p1+2,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1+1][p2].poss[k]==1&&space[p1+1][p2+1].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(i!=p1+1)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_row_but(orig_box,p1+1,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1+1][p2+1].poss[k]==1&&space[p1+1][p2+2].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(i!=p1+1)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_row_but(orig_box,p1+1,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1+1][p2].poss[k]==1&&space[p1+1][p2+2].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(i!=p1+1)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_row_but(orig_box,p1+1,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1][p2].poss[k]==1&&space[p1+2][p2].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(j!=p2)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_col_but(orig_box,p2,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1][p2].poss[k]==1&&space[p1+1][p2].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(j!=p2)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_col_but(orig_box,p2,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1+1][p2].poss[k]==1&&space[p1+2][p2].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(j!=p2)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_col_but(orig_box,p2,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1][p2+1].poss[k]==1&&space[p1+1][p2+1].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(j!=p2+1)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_col_but(orig_box,p2+1,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1+1][p2+1].poss[k]==1&&space[p1+2][p2+1].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(j!=p2+1)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_col_but(orig_box,p2+1,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1][p2+1].poss[k]==1&&space[p1+2][p2+1].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(j!=p2+1)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_col_but(orig_box,p2+1,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1][p2+2].poss[k]==1&&space[p1+1][p2+2].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(j!=p2+2)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_col_but(orig_box,p2+2,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1+1][p2+2].poss[k]==1&&space[p3][p4].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(j!=p2+2)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_col_but(orig_box,p2+2,k);
				fout<<"elim_row_but \n";
			}
		}
		if(space[p1][p2+2].poss[k]==1&&space[p3][p4].poss[k]==1)
		{
			fout<<"1 and 3 have same poss for "<<k<<"\n";
			int flag=0;
			for(int i=p1;i<=p3;++i)
			for(int j=p2;j<=p4;++j)
			{
				if(j!=p2+2)
				if(space[i][j].poss[k]==1)
				{
					flag=1;
					fout<<"so does "<<i<<" "<<j<<"\n";
				}
			}
			if(flag==0)
			{
				elim_col_but(orig_box,p2+2,k);
				fout<<"elim_row_but \n";
			}
		}


	}
}

void elim_row_but(int box,int row,int k)
{
	for(int j=0;j<=8;++j)
	{
		if(ret_box_cds(row,j)!=box)
		{
			space[row][j].poss[k]=0;
			fout<<row<<" "<<j<<" poss "<<k<<" was removed\n";
		}
	}

}

void elim_col_but(int box,int col,int k)
{
	for(int i=0;i<=8;++i)
	{
		if(ret_box_cds(i,col)!=box)
		{
			space[i][col].poss[k]=0;
			fout<<col<<" "<<i<<" poss "<<k<<" was removed\n";
		}
	}

}

void cell_one_pos(int i,int j)
{
	if(space[i][j].value!=0) return;
	int num=0,the_poss_val=0;
	for(int k=1;k<=9;++k)
	{
		if(space[i][j].poss[k]==1)
		{
			num++;the_poss_val=k;
		}
	}
	if(num==1)
	{
		 space[i][j].value=the_poss_val;
		 boxes_filled++;
	}
}


int get_poss(int i,int j)
{
	int num[2]; int a=0;
	num[0]=0;num[1]=0;
	for(int k=1;k<=9;++k)
	{
		if(space[i][j].poss[k])
		{
			num[a]=k; a++;
			if(a==3) return -1;
		}
	}
	if(num[0]==0||num[1]==0) return -1;
	return num[0]*10+num[1];
}

void double_down(int box)
{
	cout<<"Entered double_down.\n";getch();
	int p1,p2,p3,p4;p1=box/1000;box=box-p1*1000;
	p2=box/100;box=box-p2*100;p3=box/10;box=box-p3*10;
	p4=box;p1--;p2--;p3--;p4--;
	cout<<"Finished inits.\n";getch();

for(int i_1=p1;i_1<=p3;++i_1)
for(int j_1=p2;j_1<=p4;++j_1)
{
	cout<<"loop 1.\n";getch();
	for(int i_2=p1;i_2<=p3;i_2++)
	for(int j_2=p2;j_2<=p4;j_2++)
	{
		cout<<"loop 2, "<<i_2<<" "<<j_2<<"\n";getch();
		if(!(i_1==i_2&&j_1==j_2))
		if(get_poss(i_1,j_1)==get_poss(i_2,j_2)&&get_poss(i_1,j_1)!=-1)
		{
			cout<<"poss's of "<<i_1<<","<<j_1<<" & "<<i_2<<","<<j_2<<" are equal to "<<get_poss(i_1,j_1)<<"\n";
			cout<<"Entered elimination area.\n";getch();
			int poss1=get_poss(i_1,j_1)/10;
			int poss2=get_poss(i_1,j_1)-poss1*10;

			for(int i_3=p1;i_3<=p3;i_3++)
			for(int j_3=p2;j_3<=p4;j_3++)
			{
				cout<<"Entered loop 3.\n";getch();
				if(get_poss(i_3,j_3)!=(poss1*10+poss2))
				if(space[i_3][j_3].value==0)
				{
					space[i_3][j_3].poss[poss1]=0;
					space[i_3][j_3].poss[poss2]=0;
				}
			}
		}
	}
}
	return;
}