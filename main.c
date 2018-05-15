/*HTC program for Library Management System*/
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "htc.h"
#include <string.h>
#include <conio.h>

#define fn1 "memreg.htc"
#define fn2 "bookreg.htc"
#define fn3 "record.htc"
#define fn4 "temp.htc"
#define FINERATE 5
//File pointers
FILE *fp1,*fp2,*fp3;

//Global Variable:
int x_fix=65,y_initial=15;
int pre,post,hitent,place,count22322,found;
int mero;
char time1[10],date1[10];
char names[500][40],sem_writer[500][60];
int roll_year[500],id[500];

//Structures 
struct book{
	char name[50],writer[60],pub[20],edi[10],fac[30];
	int bid,pyear,piece;	
}b;

struct member{
		char name[40],dob[15],add[40],fac[30],lev[10],prog[10],sem[10],ph[20],email[30];
		int roll,mid ;	
}m;

struct date{
	int day,month,year;
}current;

a()
{
	fflush(stdin);
}

struct record{
	char mname[40],bname[50],writer[60],pub[20],edi[10],status[10];
	struct date doi,dtr,dor;
	int mid,bid,fine;
}r;

//Function prototypes
void currdate(void);
void main_menu(void);
void admin_menu(void);
void user_menu(void);
void mem_reg(void);
void mem_manage(void);
void single_mem_manage(void);
void book_reg(void);
void book_manage(void);
void clear_fine(void);
void mem_search(void);
void mem_search_id(void);
void mem_search_name(void);
void res_sm(int,int);
void book_search_id(void);
void book_search_name(void);
void book_search(void);
void res_sb(int,int);
void book_issue(void);
void book_renew(void);
void book_return(void);
void end(void);
void admin(void);
int htc_gfs(char ch[],int,int);
int htc_pfs(char cha[],int,int,char);
int htc_mmfs(char hair[],int,int,int,char,int pos[]);
void assign(int);
void rect(int,int,int,int,int);
void welcomepage(void);


int main()
{
	//SetConsoleDisplayMode(CONSOLE_FULLSCREEN_MODE);
	fullscreen();
	welcomepage();
	return 0;
}

void currdate()
{
	SYSTEMTIME curtime;
	GetSystemTime(&curtime);
	current.day=curtime.wDay;
	current.month=curtime.wMonth;
	current.year=curtime.wYear;
	}

void rect(int x1,int x2,int y1,int y2,int ind)
{
	int i,j;
	for (i=x1+1,j=0;i<x2;i++)
	{
		gotoxy(x1+1+j,y1);printf("_");
		j++;
	}
	for (i=y1+1,j=0;i<=y2;i++)
	{
		gotoxy(x1,y1+1+j);printf("|");
		j++;
	}
	for (i=x1+1,j=0;i<x2;i++)
	{
		gotoxy(x1+1+j,y2);printf("_");
		j++;
	}
	for (i=y1+1,j=0;i<=y2;i++)
	{
		gotoxy(x2,y1+1+j);printf("|");
		j++;
	}
	if (ind==1)
	{
	char tit[]="LIBRARY MANAGEMENT SYSTEM";
	gotoxy(x1+10,y1+3);printf("%s",tit);
	for (i=0;i<strlen(tit);i++)
		{
		gotoxy(x1+10+i,y1+4);printf("%c",42);
		}
	currdate();
	char mon[13][6]={" ","Jan","Feb","March","April","May","June","July","Aug","Sep","Oct","Nov","Dec"};
	gotoxy(x1+70,y1+3);printf("Date : %d %s %d",current.day,mon[current.month],current.year);
	for (i=x1+1,j=0;i<x2;i++)
	{
		gotoxy(x1+1+j,y1+5);printf("_");
		j++;
	}
	}		
}

void main_menu()
{
	int choose;
	system("cls");
	rect(x_fix-30,x_fix+60,y_initial-5,y_initial+20,1);
	char* menu[]={"Main menu","Administrator","User","Exit"};
	choose=htc_menumaker(menu,sizeof(menu)/sizeof(menu[0]),x_fix+5,y_initial+4);
	switch(choose)
	{
	case 1: admin(); break;
	case 2: user_menu(); break;
	default: end(); break;
	}
}

void admin_menu()
{
	int choose;
	system("cls");
	rect(x_fix-30,x_fix+60,y_initial-5,y_initial+20,1);
	char* menu[]={"Admin Panel","Member Register","Member Management","Book Registration","Book Management","Clear Fine","Log out"};
	choose=htc_menumaker(menu,sizeof(menu)/sizeof(menu[0]),x_fix+5,y_initial+4);
	switch(choose)
	{
	case 1: mem_reg(); break;
	case 2: mem_manage(); break;
	case 3: book_reg(); break;
	case 4: book_manage(); break;
	case 5: clear_fine(); break;
	default: main_menu(); break;
	}
}

void mem_manage()
{
	int choose;
	system("cls");
	rect(x_fix-30,x_fix+60,y_initial-5,y_initial+20,1);
	char* menu[]={"Member Management Menu","Manage single member","Upgrade Members","Delete Passed Out","Go back"};
	choose=htc_menumaker(menu,sizeof(menu)/sizeof(menu[0]),x_fix+5,y_initial+4);
	switch(choose)
	{
	case 1: single_mem_manage(); break;
	case 2:
		system("cls");
			if((fp1=fopen(fn1,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo data saved yet !!");
				fclose(fp1);
				Sleep(2000);
				admin_menu();				
			}
			fp3=fopen("temp17.htc","w");
			int inde,i;
			char sems[8][5]={"I","II","III","IV","V","VI","VII","VIII"};
			while(fread(&m,sizeof(m),1,fp1)==1)
			{
				if(strcmp(m.sem,sems[7])==0)
				strcpy(m.sem,"P.O");
				else
				{
					for (i=0;i<7;i++)
						if(strcmp(m.sem,sems[i])==0)
						{
						strcpy(m.sem,sems[i+1]);
						break;
						}
				}
				fwrite(&m,sizeof(m),1,fp3);
			}
			fclose(fp1);fclose(fp3);
			int count=0;
			_strtime(time1);
			_strdate(date1);
			char time23[8],date23[8];
			for(i=0;i<=7;i++)
		    if((int)time1[i]!=58)
		    {
			time23[count]=time1[i];
		    	count++;
		    }
		    time23[count]='\0';
		    count=0;
		    for(i=0;i<=7;i++)
		    if((int)date1[i]!=47)
		    {
			date23[count]=date1[i];
		    	count++;
		    }
		    date23[count]='\0';
		    char command[]="ren memreg.htc \"member ";
				strcat(command," ");                                
			    strcat(command,date23);
			    strcat(command," ");
				strcat(command,time23);
				strcat(command,".htc\"");
				system(command);
				system("ren temp17.htc memreg.htc");
				gotoxy(x_fix,y_initial);printf("Semesters Upgraded!!");
				Sleep(2000);
				admin_menu();		
		break;			
	case 3:
		system("cls");
			if((fp1=fopen(fn1,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo data saved yet !!");
				fclose(fp1);
				Sleep(2000);
				admin_menu();				
			}
			fp3=fopen("temp16.htc","w");
			while(fread(&m,sizeof(m),1,fp1)==1)
			{
					if(strcmp(m.sem,"P.O")!=0)
					fwrite(&m,sizeof(m),1,fp3);
			}
			fclose(fp1);fclose(fp3);
				system("del memreg.htc");
				system("ren temp16.htc memreg.htc");
				gotoxy(x_fix,y_initial);printf("Passed Outs cleared !!");
				Sleep(2000);
				admin_menu();		
		break;
	default: admin_menu(); break;
	}
}

void user_menu()
{
	int choose;
	system("cls");
	rect(x_fix-30,x_fix+60,y_initial-5,y_initial+20,1);
	char* menu[]={"User Menu","Member Search","Book search","Book Issue","Book Renew","Book Return","Log out"};
	choose=htc_menumaker(menu,sizeof(menu)/sizeof(menu[0]),x_fix+5,y_initial+4);
		switch(choose)
	{
	case 1: mem_search(); break;
	case 2: book_search(); break;
	case 3: book_issue(); break;
	case 4: book_renew(); break;
	case 5: book_return(); break;
	default: main_menu(); break;
	}
}

void mem_search()
{
	int choose;
	system("cls");
	rect(x_fix-30,x_fix+60,y_initial-5,y_initial+20,1);
	gotoxy(x_fix,y_initial+5+9);printf("Press ESC to go back");
	char* menu[]={"Member Search Menu","Search By ID","Search By Name"};
	choose=htc_menumaker(menu,sizeof(menu)/sizeof(menu[0]),x_fix+5,y_initial+4);
		switch(choose)
	{
	case 1: mem_search_id(); break;
	case 2: mem_search_name(); break;
	default:user_menu(); break;
	
	}
}

void mem_search_id()
{
	start:
			system("cls");
			if((fp1=fopen(fn1,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo member saved yet !!");
				fclose(fp1);
				Sleep(2000);
				mem_search();				
			}
			int found=0;
			int memid;
			gotoxy(x_fix,y_initial);printf("Enter your member ID : ");
			a();
			scanf("%d",&memid);
			while(fread(&m,sizeof(m),1,fp1)==1)
			{
					if(m.mid==memid)
					{	
						found=1;
					}
			}
			fclose(fp1);
			if(found==1)
		{
		res_sm(1,memid);
		re:
		gotoxy(x_fix,y_initial+18);printf("Press ENTER to search another record Or ESC to go back: ");
		char conf=getch();
		if(conf!=13&&conf!=27)
		goto re;
		if(conf==13)
		goto start;
		user_menu();
		}
		else
		{
				system("cls");
				gotoxy(x_fix,y_initial);
				printf("Record not found!");
				Sleep(2000);
		}
		mem_search();		
}

void mem_search_name()
{
	if((fp1=fopen(fn1,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo member saved yet !!");
				fclose(fp1);
				Sleep(2000);
				mem_search();				
			}
	fclose(fp1);
	assign(1);
	start:
	system("cls");
	char name[40];int out;
		gotoxy(x_fix,y_initial);printf("Enter your name : ");
	gotoxy(x_fix-15,y_initial+3);printf("Name: ");
	gotoxy(x_fix+30,y_initial+3);printf("ID: ");
	gotoxy(x_fix+40,y_initial+3);printf("Roll: ");
	gotoxy(x_fix+50,y_initial+3);printf("Semester: ");
	out=htc_gfs(name,x_fix,y_initial+1);
	system("cls");
	if(out==-2) mem_search();
	if(out>=0)
	{
		res_sm(2,out);
		re:
		gotoxy(x_fix,y_initial+18);printf("Press ENTER to search another record Or ESC to go back: ");
		char conf=getch();
		if(conf!=13&&conf!=27)
		goto re;
		if(conf==13)
		goto start;
		user_menu();
	}
	else
	{
			gotoxy(x_fix,y_initial);
			printf("\a No name Entered!");
			Sleep(2000);
	}
	mem_search();
}

void res_sm(int ind,int id_out)
{
		int i=0,initial=0;
		fp3=fopen(fn1,"r");
		if((fp1=fopen(fn3,"r"))==NULL)
			{
				gotoxy(x_fix-10,y_initial+10);printf("\aNo book issue recorded for any user yet !!");
				initial=1;
			}
			while(fread(&m,sizeof(m),1,fp3)==1)
			{
					if(ind==2&&i==id_out||ind==1&&id_out==m.mid)
					{
						system("cls");
						rect(x_fix-30,x_fix+80,y_initial-6,y_initial+20,0);
						gotoxy(x_fix+15,y_initial-4);printf("Record for Member ID %d :",m.mid);
						gotoxy(x_fix-10,y_initial-2);printf("Name: ");
						printf("%s",m.name);
						gotoxy(x_fix-10,y_initial);printf("Date of Birth: ");
						printf("%s",m.dob);
						gotoxy(x_fix-10,y_initial+2);printf("Address: ");
						printf("%s",m.add);
						gotoxy(x_fix-10,y_initial+4);printf("Faculty: ");
						printf("%s",m.fac);
						gotoxy(x_fix-10,y_initial+6);printf("Level: ");
						printf("%s",m.lev);
						gotoxy(x_fix+40,y_initial-2);printf("Program: ");
						printf("%s",m.prog);
						gotoxy(x_fix+40,y_initial);printf("Semester: ");
						printf("%s",m.sem);
						gotoxy(x_fix+40,y_initial+2);printf("Class roll no. : ");
						printf("%d",m.roll);	
						gotoxy(x_fix+40,y_initial+4);printf("Phone number : ");
						printf("%s",m.ph);
						gotoxy(x_fix+40,y_initial+6);printf("E-Mail : ");
						printf("%s",m.email);
						int counting=0,tot_fine=0,inde=0;
						if(initial!=1)
						{
							while(fread(&r,sizeof(r),1,fp1)==1)
							{
								if(r.mid==m.mid)
								{
								tot_fine+=r.fine;
								if(strcmp(r.status,"Issued")==0)
								counting++;
								}
							}
							rewind(fp1);
							gotoxy(x_fix-10,y_initial+8);printf("Total fine: ");
							printf("%d",tot_fine);
							if (counting>0)
							{
								gotoxy(x_fix-10,y_initial+10);printf("Book name");
								gotoxy(x_fix+20,y_initial+10);printf("Book ID");
								gotoxy(x_fix+30,y_initial+10);printf("Date of Issue");
								gotoxy(x_fix+55,y_initial+10);printf("Date to return");
								while(fread(&r,sizeof(r),1,fp1)==1)
								{
									if(strcmp(r.status,"Issued")==0&&r.mid==m.mid)
									{
										gotoxy(x_fix-10,y_initial+12+inde);printf("%s",r.bname);
										gotoxy(x_fix+20,y_initial+12+inde);printf("%d",r.bid);
										gotoxy(x_fix+30,y_initial+12+inde);printf("%d.%d.%d",r.doi.day,r.doi.month,r.doi.year);
										gotoxy(x_fix+55,y_initial+12+inde);printf("%d.%d.%d",r.dtr.day,r.dtr.month,r.dtr.year);
										inde+=2;
									}
								}
							}
							else
							{
									gotoxy(x_fix-10,y_initial+10);printf("No book issued by the member!");	
							}
						}
					}
					i++;
				}
		fclose(fp1);
		fclose(fp3);
}
void book_search()
{
	int choose;
	system("cls");
	rect(x_fix-30,x_fix+60,y_initial-5,y_initial+20,1);
	gotoxy(x_fix,y_initial+5+9);printf("Press ESC to go back");
	char* menu[]={"Book Search Menu","Search By ID","Search By Name"};
	choose=htc_menumaker(menu,sizeof(menu)/sizeof(menu[0]),x_fix+5,y_initial+4);
		switch(choose)
	{
	case 1: book_search_id(); break;
	case 2: book_search_name(); break;
	default:user_menu(); break;
	}
}

void book_search_id()
{
	start:
			system("cls");
			if((fp1=fopen(fn2,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo book saved yet !!");
				fclose(fp1);
				Sleep(2000);
				book_search();				
			}
			int found=0;
			int bookid;
			gotoxy(x_fix,y_initial);printf("Enter the Book ID : ");
			a();
			scanf("%d",&bookid);
			while(fread(&b,sizeof(b),1,fp1)==1)
			{
					if(b.bid==bookid)
					{	
						found=1;
					}
			}
			fclose(fp1);
			if(found==1)
		{
		res_sb(1,bookid);
		re:
		gotoxy(x_fix,y_initial+10);printf("Press ENTER to search another record Or ESC to go back: ");
		char conf=getch();
		if(conf!=13&&conf!=27)
		goto re;
		if(conf==13)
		goto start;
		user_menu();
		}
		else
		{
				system("cls");
				gotoxy(x_fix,y_initial);
				printf("Record not found!");
				Sleep(2000);
		}
		book_search();
}

void book_search_name()
{
	if((fp2=fopen(fn2,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo book saved yet !!");
				fclose(fp2);
				Sleep(2000);
				book_search();				
			}
	fclose(fp2);
	assign(2);
	start:
	system("cls");
	char name[40];int out;
	gotoxy(x_fix,y_initial);printf("Enter the name of book : ");
	gotoxy(x_fix-15,y_initial+3);printf("Name: ");
	gotoxy(x_fix+30,y_initial+3);printf("ID: ");
	gotoxy(x_fix+40,y_initial+3);printf("Year: ");
	gotoxy(x_fix+50,y_initial+3);printf("Writer: ");
	out=htc_gfs(name,x_fix,y_initial+1);
	system("cls");
	if(out==-2) book_search();
	if(out>=0)
	{
		res_sb(2,out);
		re:
		gotoxy(x_fix,y_initial+10);printf("Press ENTER to search another record Or ESC to go back: ");
		char conf=getch();
		if(conf!=13&&conf!=27)
		goto re;
		if(conf==13)
		goto start;
		user_menu();
	}
	else
	{
			gotoxy(x_fix,y_initial);
			printf("\a No name Entered!");
			Sleep(2000);
	}
	book_search();
}

void res_sb(int ind,int id_out)
{
		int i=0;
		fp3=fopen(fn2,"r");
			while(fread(&b,sizeof(b),1,fp3)==1)
			{
					if(ind==2&&i==id_out||ind==1&&id_out==b.bid)
					{
						system("cls");
						rect(x_fix-30,x_fix+80,y_initial-6,y_initial+20,0);
						gotoxy(x_fix+15,y_initial-4);printf("Record for Book ID %d :",b.bid);
						gotoxy(x_fix-15,y_initial-2);printf("Name: ");
						printf("%s",b.name);
						gotoxy(x_fix-15,y_initial);printf("Writer: ");
						printf("%s",b.writer);
						gotoxy(x_fix-15,y_initial+2);printf("Publication: ");
						printf("%s",b.pub);
						gotoxy(x_fix-15,y_initial+4);printf("Publication year: ");
						printf("%d",b.pyear);
						gotoxy(x_fix+40,y_initial-2);printf("Edition: ");
						printf("%s",b.edi);
						gotoxy(x_fix+40,y_initial);printf("Faculty: ");
						printf("%s",b.fac);
						gotoxy(x_fix+40,y_initial+2);printf("Pieces Available: ");
						printf("%d",b.piece);
					}
					i++;
				}
		fclose(fp3);
}

void book_issue()
{
	start:
			system("cls");
			fp3=fopen(fn3,"a");
			fclose(fp3);
			if((fp1=fopen(fn1,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aRecord Error in Member Record !!");
				Sleep(2000);
				fclose(fp1);
				main_menu();				
			}
			if((fp2=fopen(fn2,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aRecord Error in Books Record !!");
				Sleep(2000);
				fclose(fp1);fclose(fp2);
				main_menu();				
			}
			fp3=fopen(fn3,"r");
			int found=0,i=0,count=0,j;
			int memid;
			gotoxy(x_fix,y_initial);printf("Enter your member ID : ");
			scanf("%d",&memid);
			while(fread(&m,sizeof(m),1,fp1)==1)
			{
					if(m.mid==memid)
					{	
						found=1;
					}
			}
			rewind(fp1);
			if(found==1)
			{
							while(fread(&r,sizeof(r),1,fp3)==1)
				{
						if(r.mid==memid&&strcmp(r.status,"Issued")==0)
						{	
							id[i]=r.bid;
							i++;	
						}
				}
				rewind(fp3);
				system("cls");
				while(fread(&m,sizeof(m),1,fp1)==1)
				{
						if(m.mid==memid)
						{	
							gotoxy(x_fix+15,y_initial-4);printf("Record for Member ID %d :",memid);
							gotoxy(x_fix-10,y_initial-2);printf("Name: ");printf("%s",m.name);
						}
				}
				if(i>0)
				{
					gotoxy(x_fix-15,y_initial+3);printf("Book ID");
					gotoxy(x_fix-5,y_initial+3);printf("Book Name");
					gotoxy(x_fix+30,y_initial+3);printf("Publisher");
					gotoxy(x_fix+45,y_initial+3);printf("Edition");
					gotoxy(x_fix+65,y_initial+3);printf("Writer");
					while(fread(&b,sizeof(b),1,fp2)==1)
					{
						for(j=0;j<i;j++)
						{
							if(id[j]==b.bid)
							{
								gotoxy(x_fix-15,y_initial+count+5);printf("%d",b.bid);
								gotoxy(x_fix-5,y_initial+count+5);printf("%s",b.name);
								gotoxy(x_fix+30,y_initial+5+count);printf("%s",b.pub);
								gotoxy(x_fix+45,y_initial+5+count);printf("%s",b.edi);
								gotoxy(x_fix+65,y_initial+5+count);printf("%s",b.writer);
								count++;		
							}
						}
					}
					rewind(fp2);
					if(i==3)
					{
						re8:
						gotoxy(x_fix+15,y_initial+12);printf("You have already issued 3 books. Press ESC to go back");
						char conf2=getch();
						if(conf2!=27)
						goto re8;
						fclose(fp1);fclose(fp3);fclose(fp2);
						user_menu();
					}
				}
				else
				{
					gotoxy(x_fix+15,y_initial+3);printf("No book issued yet");
				}
				fclose(fp1);fclose(fp3);fclose(fp2);
					re10:
							gotoxy(x_fix,y_initial+10);printf("Press ENTER to search book to issue Or ESC to go back: ");
							char conf23=getch();
							if(conf23!=13&&conf23!=27)
							goto re10;
							if(conf23==27)
							user_menu();
				assign(2);
			system("cls");
			char name[40];int out,place=0,bookavail,bookid;
			gotoxy(x_fix,y_initial);printf("Enter the name of book : ");
			gotoxy(x_fix-15,y_initial+3);printf("Name: ");
			gotoxy(x_fix+30,y_initial+3);printf("ID: ");
			gotoxy(x_fix+40,y_initial+3);printf("Year: ");
			gotoxy(x_fix+50,y_initial+3);printf("Writer: ");
			out=htc_gfs(name,x_fix,y_initial+1);
			system("cls");
			if(out==-2) user_menu();
			if(out>=0)
			{
				res_sb(2,out);
				re14:
				gotoxy(x_fix,y_initial+10);printf("Press ENTER to issue this book Or ESC to go back: ");
				char conf14=getch();
				if(conf14!=13&&conf14!=27)
				goto re14;
				if(conf14==27)
				user_menu();
				fp2=fopen(fn2,"r");
				while(fread(&b,sizeof(b),1,fp2)==1)
				{
						if(place==out)
						{
							bookavail=b.piece;
							bookid=b.bid;
						}
						place++;
				}
				fclose(fp2);
				if (bookavail==0)
				{
						system("cls");
						gotoxy(x_fix,y_initial);
						printf("\a No book available! Please issue another book");
						Sleep(2500);
						goto start;
				}
				int daystoadd;
				gotoxy(x_fix,y_initial+12);printf("Enter days to issue for :");
				scanf("%d",&daystoadd);
				fp1=fopen(fn1,"r");
				fp2=fopen(fn2,"r");
				fp3=fopen(fn3,"a");
				while(fread(&m,sizeof(m),1,fp1)==1)
					{
							if(m.mid==memid)
							{	
								strcpy(r.mname,m.name);
								r.mid=m.mid;
							}
					}
				while(fread(&b,sizeof(b),1,fp2)==1)
					{
							if(bookid==b.bid)
							{	
								strcpy(r.bname,b.name);
								r.bid=b.bid;
								strcpy(r.pub,b.pub);
								strcpy(r.edi,b.edi);
								strcpy(r.writer,b.writer);
							}
					}
					strcpy(r.status,"Issued");
					currdate();
					r.doi.day=current.day;
					r.dtr.day=current.day;
					r.doi.month=current.month;
					r.dtr.month=current.month;
					r.doi.year=current.year;
					r.dtr.year=current.year;
					htc_dayadder(&r.dtr.day,&r.dtr.month,&r.dtr.year,daystoadd);
					r.dor.day=0;
					r.dor.month=0;
					r.dor.day=0;
					r.fine=0;
					fwrite(&r,sizeof(r),1,fp3);
					fclose(fp1);fclose(fp3);
					rewind(fp2);
					system("cls");
					gotoxy(x_fix,y_initial);
					printf("Issued successfully!");
					Sleep(2000);
					gotoxy(x_fix,y_initial+2);
					printf("Date of issue : %d.%d.%d",r.doi.day,r.doi.month,r.doi.year);
					Sleep(2000);
					gotoxy(x_fix,y_initial+4);
					printf("Date to return : %d.%d.%d",r.dtr.day,r.dtr.month,r.dtr.year);
					Sleep(3000);
					fp3=fopen("temp10.htc","w");
					while(fread(&b,sizeof(b),1,fp2)==1)
					{
							if(bookid==b.bid)
							{	
								b.piece-=1;
								fwrite(&b,sizeof(b),1,fp3);	
							}
							else
							{
							fwrite(&b,sizeof(b),1,fp3);	
							}
					}
					fclose(fp2);fclose(fp3);
					system("del bookreg.htc");
					system("ren temp10.htc bookreg.htc");		
				}
			else
			{
					gotoxy(x_fix,y_initial);
					printf("\a No name Entered!");
					Sleep(2000);
					user_menu();
			}		
			re:
			gotoxy(x_fix,y_initial+10);printf("Press ENTER to issue another book Or ESC to go back: ");
			char conf=getch();
			if(conf!=13&&conf!=27)
			goto re;
			if(conf==13)
			goto start;
			user_menu();
		}
		else
		{
				system("cls");
				gotoxy(x_fix,y_initial);
				printf("No member with the ID found!");
				fclose(fp1);fclose(fp3);fclose(fp2);
				Sleep(2000);
		}
		user_menu();
}

void book_renew()
{
start:
			system("cls");
			fp3=fopen(fn3,"a");
			fclose(fp3);
			if((fp1=fopen(fn1,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aRecord Error in Member Record !!");
				Sleep(2000);
				fclose(fp1);
				user_menu();				
			}
			if((fp2=fopen(fn2,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aRecord Error in Books Record !!");
				Sleep(2000);
				fclose(fp1);fclose(fp2);
				user_menu();				
			}
			fp3=fopen(fn3,"r");
			int found=0,i=0,count=0,j;
			int memid;
			gotoxy(x_fix,y_initial);printf("Enter your member ID : ");
			a();
			scanf("%d",&memid);
			while(fread(&m,sizeof(m),1,fp1)==1)
			{
					if(m.mid==memid)
					{	
						found=1;
					}
			}
			rewind(fp1);
			if(found==1)
			{
							while(fread(&r,sizeof(r),1,fp3)==1)
				{
						if(r.mid==memid&&strcmp(r.status,"Issued")==0)
						{	
							id[i]=r.bid;
							i++;	
						}
				}
				rewind(fp3);
				system("cls");
				while(fread(&m,sizeof(m),1,fp1)==1)
				{
						if(m.mid==memid)
						{	
							gotoxy(x_fix+15,y_initial-4);printf("Record for Member ID %d :",memid);
							gotoxy(x_fix-10,y_initial-2);printf("Name: ");printf("%s",m.name);
						}
				}
				if(i>0)
				{
					gotoxy(x_fix-15,y_initial+3);printf("Book ID");
					gotoxy(x_fix-5,y_initial+3);printf("Book Name");
					gotoxy(x_fix+30,y_initial+3);printf("Publisher");
					gotoxy(x_fix+45,y_initial+3);printf("Edition");
					gotoxy(x_fix+65,y_initial+3);printf("Writer");
					while(fread(&b,sizeof(b),1,fp2)==1)
					{
						for(j=0;j<i;j++)
						{
							if(id[j]==b.bid)
							{
								gotoxy(x_fix-15,y_initial+count+5);printf("%d",b.bid);
								gotoxy(x_fix-5,y_initial+count+5);printf("%s",b.name);
								gotoxy(x_fix+30,y_initial+5+count);printf("%s",b.pub);
								gotoxy(x_fix+45,y_initial+5+count);printf("%s",b.edi);
								gotoxy(x_fix+65,y_initial+5+count);printf("%s",b.writer);
								count++;		
							}
						}
					}
					rewind(fp2);
					int bookid,found2=0;
					re100:
				gotoxy(x_fix,y_initial+10);printf("Enter the book ID to renew : ");
				scanf("%d",&bookid);
				for(j=0;j<i;j++)
				{
					if(bookid==id[j])
					found2++;
				}
				if(found2==0)
				{
					htc_fieldclr(x_fix,x_fix+80,y_initial+10,y_initial+10);
					printf("\a");
					goto re100;
				}
			fclose(fp1);fclose(fp2);
			int newday,newmonth,newyear;
			fp2=fopen("temp5.htc","w");
					while(fread(&r,sizeof(r),1,fp3)==1)
					{
							if(bookid==r.bid&&strcmp(r.status,"Issued")==0&&r.mid==memid)
							{	
								re50:	
								gotoxy(x_fix,y_initial+10);printf("Enter today's date (dd.mm.yyyy): ");
								char newdate[15];
								get(newdate);
								int valid=htc_datecheck(newdate);
								newyear=(newdate[6]-48)*1000+(newdate[7]-48)*100+(newdate[8]-48)*10+(newdate[9]-48);
								newmonth=(newdate[3]-48)*10+(newdate[4]-48);
								newday=(newdate[0]-48)*10+(newdate[1]-48);
								if(valid!=0)
								{
									htc_fieldclr(x_fix+32,x_fix+60,y_initial+10,y_initial+10);
									printf("\a");
									goto re50;
								}
								r.dor.day=newday;r.dor.month=newmonth;r.dor.year=newyear;
								strcpy(r.status,"Returned");
								gotoxy(x_fix,y_initial+2);
								int check1=htc_daycalculator(1,1,1,r.dtr.day,r.dtr.month,r.dtr.year);
								int check2=htc_daycalculator(1,1,1,r.dor.day,r.dor.month,r.dor.year);
								if (check2>check1)
								r.fine=FINERATE*htc_daycalculator(r.dtr.day,r.dtr.month,r.dtr.year,r.dor.day,r.dor.month,r.dor.year);
								else r.fine=0;
								fwrite(&r,sizeof(r),1,fp2);
							}
							else
							{
							fwrite(&r,sizeof(r),1,fp2);	
							}
					}
				fclose(fp2);fclose(fp3);
				system("del record.htc");
				system("ren temp5.htc record.htc");
				int daystoadd;
				gotoxy(x_fix,y_initial+12);printf("Enter days to issue for :");
				scanf("%d",&daystoadd);
				fp1=fopen(fn1,"r");
				fp2=fopen(fn2,"r");
				fp3=fopen(fn3,"a");
				while(fread(&m,sizeof(m),1,fp1)==1)
					{
							if(m.mid==memid)
							{	
								strcpy(r.mname,m.name);
								r.mid=m.mid;
							}
					}
				while(fread(&b,sizeof(b),1,fp2)==1)
					{
							if(bookid==b.bid)
							{	
								strcpy(r.bname,b.name);
								r.bid=b.bid;
								strcpy(r.pub,b.pub);
								strcpy(r.edi,b.edi);
								strcpy(r.writer,b.writer);
							}
					}
					strcpy(r.status,"Issued");
					currdate();
					r.doi.day=newday;
					r.dtr.day=newday;
					r.doi.month=newmonth;
					r.dtr.month=newmonth;
					r.doi.year=newyear;
					r.dtr.year=newyear;
					htc_dayadder(&r.dtr.day,&r.dtr.month,&r.dtr.year,daystoadd);
					r.dor.day=0;
					r.dor.month=0;
					r.dor.day=0;
					r.fine=0;
					fwrite(&r,sizeof(r),1,fp3);
					fclose(fp1);fclose(fp3);fclose(fp2);
					system("cls");
					gotoxy(x_fix,y_initial);
					printf("Renewed successfully!");
					Sleep(2000);
					gotoxy(x_fix,y_initial+2);
					printf("Date of renew : %d.%d.%d",r.doi.day,r.doi.month,r.doi.year);
					Sleep(2000);
					gotoxy(x_fix,y_initial+4);
					printf("Date to return : %d.%d.%d",r.dtr.day,r.dtr.month,r.dtr.year);
					Sleep(3000);			
				}
				else
				{
				gotoxy(x_fix+15,y_initial+3);printf("No book issued yet");
				fclose(fp1);fclose(fp2);fclose(fp3);	
				}
			re:
			gotoxy(x_fix,y_initial+10);printf("Press ENTER to renew book of another member Or ESC to go back: ");
			char conf=getch();
			if(conf!=13&&conf!=27)
			goto re;
			if(conf==13)
			goto start;
			user_menu();
		}
		else
		{
				system("cls");
				gotoxy(x_fix,y_initial);
				printf("No member with the ID found!");
				fclose(fp1);fclose(fp3);fclose(fp2);
				Sleep(2000);
		}
		user_menu();
}

void book_return()
{
	start:
			system("cls");
			fp3=fopen(fn3,"a");
			fclose(fp3);
			if((fp1=fopen(fn1,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aRecord Error in Member Record !!");
				Sleep(2000);
				fclose(fp1);
				user_menu();				
			}
			if((fp2=fopen(fn2,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aRecord Error in Books Record !!");
				Sleep(2000);
				fclose(fp1);fclose(fp2);
				user_menu();				
			}
			fp3=fopen(fn3,"r");
			int found=0,i=0,count=0,j;
			int memid;
			gotoxy(x_fix,y_initial);printf("Enter your member ID : ");
			a();
			scanf("%d",&memid);
			while(fread(&m,sizeof(m),1,fp1)==1)
			{
					if(m.mid==memid)
					{	
						found=1;
					}
			}
			rewind(fp1);
			if(found==1)
			{
							while(fread(&r,sizeof(r),1,fp3)==1)
				{
						if(r.mid==memid&&strcmp(r.status,"Issued")==0)
						{	
							id[i]=r.bid;
							i++;	
						}
				}
				rewind(fp3);
				system("cls");
				while(fread(&m,sizeof(m),1,fp1)==1)
				{
						if(m.mid==memid)
						{	
							gotoxy(x_fix+15,y_initial-4);printf("Record for Member ID %d :",memid);
							gotoxy(x_fix-10,y_initial-2);printf("Name: ");printf("%s",m.name);
						}
				}
				if(i>0)
				{
					gotoxy(x_fix-15,y_initial+3);printf("Book ID");
					gotoxy(x_fix-5,y_initial+3);printf("Book Name");
					gotoxy(x_fix+30,y_initial+3);printf("Publisher");
					gotoxy(x_fix+45,y_initial+3);printf("Edition");
					gotoxy(x_fix+65,y_initial+3);printf("Writer");
					while(fread(&b,sizeof(b),1,fp2)==1)
					{
						for(j=0;j<i;j++)
						{
							if(id[j]==b.bid)
							{
								gotoxy(x_fix-15,y_initial+count+5);printf("%d",b.bid);
								gotoxy(x_fix-5,y_initial+count+5);printf("%s",b.name);
								gotoxy(x_fix+30,y_initial+5+count);printf("%s",b.pub);
								gotoxy(x_fix+45,y_initial+5+count);printf("%s",b.edi);
								gotoxy(x_fix+65,y_initial+5+count);printf("%s",b.writer);
								count++;		
							}
						}
					}
					rewind(fp2);
					int bookid,found2=0;
					re100:
				gotoxy(x_fix,y_initial+10);printf("Enter the book ID to return : ");
				scanf("%d",&bookid);
				for(j=0;j<i;j++)
				{
					if(bookid==id[j])
					found2++;
				}
				if(found2==0)
				{
					htc_fieldclr(x_fix,x_fix+80,y_initial+10,y_initial+10);
					printf("\a");
					goto re100;
				}
			fclose(fp1);fclose(fp2);
			fp2=fopen("temp3.htc","w");
					while(fread(&r,sizeof(r),1,fp3)==1)
					{
							if(bookid==r.bid&&strcmp(r.status,"Issued")==0&&r.mid==memid)
							{
								re50:
								gotoxy(x_fix,y_initial+10);printf("Enter today's date (dd.mm.yyyy): ");
								char newdate[15];
								get(newdate);
								int valid=htc_datecheck(newdate);
								r.dor.year=(newdate[6]-48)*1000+(newdate[7]-48)*100+(newdate[8]-48)*10+(newdate[9]-48);
								r.dor.month=(newdate[3]-48)*10+(newdate[4]-48);
								r.dor.day=(newdate[0]-48)*10+(newdate[1]-48);
								if(valid!=0)
								{
									htc_fieldclr(x_fix+32,x_fix+60,y_initial+10,y_initial+10);
									printf("\a");
									goto re50;
								}
								strcpy(r.status,"Returned");
								system("cls");
								gotoxy(x_fix,y_initial);
								printf("Returned successfully!");
								Sleep(2000);
								gotoxy(x_fix,y_initial+2);
								int check1=htc_daycalculator(1,1,1,r.dtr.day,r.dtr.month,r.dtr.year);
								int check2=htc_daycalculator(1,1,1,r.dor.day,r.dor.month,r.dor.year);
								printf("Date of return : %d.%d.%d",r.dor.day,r.dor.month,r.dor.year);
								if (check2>check1)
								r.fine=FINERATE*htc_daycalculator(r.dtr.day,r.dtr.month,r.dtr.year,r.dor.day,r.dor.month,r.dor.year);
								else r.fine=0;
								fwrite(&r,sizeof(r),1,fp2);
							}
							else
							{
							fwrite(&r,sizeof(r),1,fp2);	
							}
					}
				fclose(fp2);fclose(fp3);
				system("del record.htc");
				system("ren temp3.htc record.htc");
					fp2=fopen(fn2,"r");
					fp3=fopen("temp2.htc","w");
					while(fread(&b,sizeof(b),1,fp2)==1)
					{
							if(bookid==b.bid)
							{	
								b.piece+=1;
								fwrite(&b,sizeof(b),1,fp3);	
							}
							else
							{
							fwrite(&b,sizeof(b),1,fp3);	
							}
					}
					fclose(fp2);fclose(fp3);
					system("del bookreg.htc");
					system("ren temp2.htc bookreg.htc");	
				}
				else
				{
				gotoxy(x_fix+15,y_initial+3);printf("No book issued yet");
				fclose(fp1);fclose(fp2);fclose(fp3);	
				}
			re:
			gotoxy(x_fix,y_initial+10);printf("Press ENTER to return book of another ID Or ESC to go back: ");
			char conf=getch();
			if(conf!=13&&conf!=27)
			goto re;
			if(conf==13)
			goto start;
			user_menu();
		}
		else
		{
				system("cls");
				gotoxy(x_fix,y_initial);
				printf("No member with the ID found!");
				fclose(fp1);fclose(fp3);fclose(fp2);
				Sleep(2000);
		}
		user_menu();
}

void mem_reg()
{
	int con,valid,year,pos,i,err;
	char conf;
if((fp1=fopen(fn1,"r"))==NULL) con=0;
	else
	{
		while(fread(&m,sizeof(m),1,fp1)==1)
		con=m.mid;
	}
	fclose(fp1);
	fp1=fopen(fn1,"a+");
	start:
	system("cls");
	rect(x_fix-30,x_fix+80,y_initial-6,y_initial+20,0);
	gotoxy(x_fix,y_initial-4);printf("Enter your name: ");
	get(m.name);
	re1:gotoxy(x_fix,y_initial-2);printf("Enter your dob (dd.mm.yyyy): ");
	get(m.dob);
	valid=htc_datecheck(m.dob);
	year=(m.dob[6]-48)*1000+(m.dob[7]-48)*100+(m.dob[8]-48)*10+(m.dob[9]-48);
	if(valid!=0||year>2016)
	{
		htc_fieldclr(x_fix+29,x_fix+60,y_initial-2,y_initial-2);
		printf("\a");
		goto re1;
	}
	gotoxy(x_fix,y_initial);printf("Enter your address: ");
	get(m.add);
	gotoxy(x_fix,y_initial+2);printf("Enter your faculty: ");
	char* faculty[]={"Science & Technology","Management","Health & Science"};
	pos=htc_option(faculty,(sizeof(faculty)/sizeof(faculty[0])),x_fix+20,y_initial+2);
	strcpy(m.fac,faculty[pos]);
	gotoxy(x_fix,y_initial+4);printf("Enter your level: ");
	strcpy(m.lev,"Bachelor");printf("Bachelor"); 
	gotoxy(x_fix,y_initial+6);printf("Enter your program: ");
	if(pos==0){
		printf("BCA");
		strcpy(m.prog,"BCA");
	}
	if(pos==1){
		printf("BBA");
		strcpy(m.prog,"BBA");
	}
	if(pos==2){
		printf("BPH");
		strcpy(m.prog,"BPH");
	}
	re52:gotoxy(x_fix,y_initial+8);printf("Enter your semester: ");
	get(m.sem);
	char sems[8][5]={"I","II","III","IV","V","VI","VII","VIII"};int corr=0,o;
	for (o=0;o<8;o++)
	if(strcmp(m.sem,sems[o])==0)
	corr=1;
	if(corr!=1)
			{
				printf("\a");
				htc_fieldclr(x_fix+21,x_fix+70,y_initial+8,y_initial+8);
				goto re52;
			}
	gotoxy(x_fix,y_initial+10);printf("Enter class roll no. : ");
	scanf("%d",&m.roll);
	re3:gotoxy(x_fix,y_initial+12);printf("Enter your phone number : 00977");
	get(m.ph);
	for(i=0;i<strlen(m.ph);i++)
		if(m.ph[i]>57||m.ph[i]<48||i>9||strlen(m.ph)<5)
			{
				printf("\a");
			//	MessageBox(0,"Enter numbers of maximum 10 length","Error Input",0);
				htc_fieldclr(x_fix+30,x_fix+70,y_initial+12,y_initial+12);
				goto re3;
			}
	re2:gotoxy(x_fix,y_initial+14);printf("Enter your E-Mail : ");
	get(m.email);
	valid=htc_emailvalidator(m.email);
	year=(m.dob[6]-48)*1000+(m.dob[7]-48)*100+(m.dob[8]-48)*10+(m.dob[9]-48);
	if(valid!=0)
	{
		htc_fieldclr(x_fix+20,x_fix+60,y_initial+14,y_initial+14);
		printf("\a");
		goto re2;
	}
	m.mid=con+1;
	con++; 
	gotoxy(x_fix,y_initial+17);printf("Member ID number for %s is : %d",m.name,m.mid);
	fwrite(&m,sizeof(m),1,fp1);
	re:
	gotoxy(x_fix,y_initial+19);printf("Press ENTER to add another record Or ESC to go back: ");
	conf=getch();
	if(conf!=13&&conf!=27)
	goto re;
	if(conf==13)
	goto start;
	fclose(fp1);
	admin_menu();
}

void single_mem_manage()
{
			system("cls");
			if((fp1=fopen(fn1,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo data saved yet !!");
				fclose(fp1);
				Sleep(2000);
				mem_manage();				
			}
			int found=0;
			int memid;
			gotoxy(x_fix,y_initial);printf("Enter your member ID : ");
			a();
			scanf("%d",&memid);
			fp2=fopen(fn4,"w");
			while(fread(&m,sizeof(m),1,fp1)==1)
			{
					if(m.mid==memid)
					{	
						found=1;int choose;
						system("cls");
						rect(x_fix-30,x_fix+80,y_initial-6,y_initial+20,0);
						gotoxy(x_fix+15,y_initial-4);printf("Record for Member ID %d :",memid);
						gotoxy(x_fix-10,y_initial-2);printf("Name: ");
						printf("%s",m.name);
						gotoxy(x_fix-10,y_initial);printf("Date of Birth: ");
						printf("%s",m.dob);
						gotoxy(x_fix-10,y_initial+2);printf("Address: ");
						printf("%s",m.add);
						gotoxy(x_fix-10,y_initial+4);printf("Faculty: ");
						printf("%s",m.fac);
						gotoxy(x_fix-10,y_initial+6);printf("Level: ");
						printf("%s",m.lev);
						gotoxy(x_fix+40,y_initial-2);printf("Program: ");
						printf("%s",m.prog);
						gotoxy(x_fix+40,y_initial);printf("Semester: ");
						printf("%s",m.sem);
						gotoxy(x_fix+40,y_initial+2);printf("Class roll no. : ");
						printf("%d",m.roll);	
						gotoxy(x_fix+40,y_initial+4);printf("Phone number : ");
						printf("%s",m.ph);
						gotoxy(x_fix+40,y_initial+6);printf("E-Mail : ");
						printf("%s",m.email);
						char* menu[]={"Member Management","Modify this record","Delete this record"};
						gotoxy(x_fix+15,y_initial+18);printf("Press ESC to go back");
						choose=htc_menumaker(menu,sizeof(menu)/sizeof(menu[0]),x_fix+15,y_initial+10);
						switch(choose)
						{
						case 1:
							system("cls");
							rect(x_fix-30,x_fix+80,y_initial-8,y_initial+20,0);
							gotoxy(x_fix,y_initial-6);printf("Enter Modified record for Member ID %d :",memid);
							int valid,year,pos,err,i;
							gotoxy(x_fix,y_initial-4);printf("Enter your name: ");
							get(m.name);
							re1:gotoxy(x_fix,y_initial-2);printf("Enter your dob (dd.mm.yyyy): ");
							get(m.dob);
							valid=htc_datecheck(m.dob);
							year=(m.dob[6]-48)*1000+(m.dob[7]-48)*100+(m.dob[8]-48)*10+(m.dob[9]-48);
							if(valid!=0||year>2016)
							{
								htc_fieldclr(x_fix+29,x_fix+60,y_initial-2,y_initial-2);
								printf("\a");
								goto re1;
							}
							gotoxy(x_fix,y_initial);printf("Enter your address: ");
							get(m.add);
							gotoxy(x_fix,y_initial+2);printf("Enter your faculty: ");
							char* faculty[]={"Science & Technology","Management","Health & Science"};
							pos=htc_option(faculty,(sizeof(faculty)/sizeof(faculty[0])),x_fix+20,y_initial+2);
							strcpy(m.fac,faculty[pos]);
							gotoxy(x_fix,y_initial+4);printf("Enter your level: ");
							strcpy(m.lev,"Bachelor");printf("Bachelor"); 
							gotoxy(x_fix,y_initial+6);printf("Enter your program: ");
							if(pos==0){
								printf("BCA");
								strcpy(m.prog,"BCA");
							}
							if(pos==1){
								printf("BBA");
								strcpy(m.prog,"BBA");
							}
							if(pos==2){
								printf("BPH");
								strcpy(m.prog,"BPH");
							}
							gotoxy(x_fix,y_initial+8);printf("Enter your semester: ");
							get(m.sem);
							gotoxy(x_fix,y_initial+10);printf("Enter class roll no. : ");
							scanf("%d",&m.roll);
							re3:gotoxy(x_fix,y_initial+12);printf("Enter your phone number : 00977");
							get(m.ph);
							for(i=0;i<strlen(m.ph);i++)
								if(m.ph[i]>57||m.ph[i]<48||i>9||strlen(m.ph)<5)
									{
										printf("\a");
									//	MessageBox(0,"Enter numbers of maximum 10 length","Error Input",0);
										htc_fieldclr(x_fix+30,x_fix+70,y_initial+12,y_initial+12);
										goto re3;
									}
							re2:gotoxy(x_fix,y_initial+14);printf("Enter your E-Mail : ");
							get(m.email);
							valid=htc_emailvalidator(m.email);
							year=(m.dob[6]-48)*1000+(m.dob[7]-48)*100+(m.dob[8]-48)*10+(m.dob[9]-48);
							if(valid!=0)
							{
								htc_fieldclr(x_fix+20,x_fix+60,y_initial+14,y_initial+14);
								printf("\a");
								goto re2;
							}
							fwrite(&m,sizeof(m),1,fp2);
							gotoxy(x_fix,y_initial+16);printf("Record Modified Successfully !!");
							Sleep(2000);
							break;		
							
							
						case 2:
							re4:
						gotoxy(x_fix+15,y_initial+18);printf("Are you sure to delete it?(Y/N)");
						char conf2=getch();
						if(conf2!=78&&conf2!=89&&conf2!=110&&conf2!=121)
						goto re4;
						if((int)conf2==89||(int)conf2==121)
						{
						system("cls");					
						gotoxy(x_fix,y_initial);printf("Record Deleted Successfully!!! ");
						}
						else
						{
						fwrite(&m,sizeof(m),1,fp2);
						system("cls");
						gotoxy(x_fix,y_initial);printf("Record NOT Deleted !");
						}
						Sleep(2000);
						break;
					default:
						fwrite(&m,sizeof(m),1,fp2);	
					}
				}
				else
				{
					fwrite(&m,sizeof(m),1,fp2);
				}
			}
			if (found==0)
			{
				gotoxy(x_fix,y_initial+6);printf("No result found");
				Sleep(1000);
		}
			fclose(fp1);
			fclose(fp2);
			system("del memreg.htc");
			system("ren temp.htc memreg.htc");
			mem_manage();
			
}

void book_reg()
{
	int con,pos;
	char conf;
	if((fp1=fopen(fn2,"r"))==NULL) con=0;
	else
	{
		while(fread(&b,sizeof(b),1,fp1)==1)
		con=b.bid;
	}
	fclose(fp1);
	fp1=fopen(fn2,"a+");
	start:
	system("cls");
	rect(x_fix-30,x_fix+80,y_initial-6,y_initial+20,0);
	gotoxy(x_fix,y_initial-2);printf("Enter the name of book: ");
	get(b.name);
	gotoxy(x_fix,y_initial);printf("Enter the name of writer: ");
	get(b.writer);
	gotoxy(x_fix,y_initial+2);printf("Enter the publication name: ");
	get(b.pub);
	gotoxy(x_fix,y_initial+4);printf("Enter the publication year: ");
	scanf("%d",&b.pyear);
	gotoxy(x_fix,y_initial+6);printf("Enter edition of the book: ");
	get(b.edi);
	gotoxy(x_fix,y_initial+8);printf("Enter the appropriate faculty: ");
	char* faculty[]={"Science & Technology","Management","Health & Science","General","Others"};
	pos=htc_option(faculty,(sizeof(faculty)/sizeof(faculty[0])),x_fix+31,y_initial+8);
	strcpy(b.fac,faculty[pos]);
	gotoxy(x_fix,y_initial+10);printf("Enter pieces available : ");
	scanf("%d",&b.piece);
	b.bid=con+1;
	con++; 
	gotoxy(x_fix,y_initial+14);printf("ID no of %s is : %d",b.name,b.bid);
	fwrite(&b,sizeof(b),1,fp1);
	re:
	gotoxy(x_fix,y_initial+18);printf("Press ENTER to add another record Or ESC to go back: ");
	conf=getch();
	if(conf!=13&&conf!=27)
	goto re;
	if(conf==13)
	goto start;
	fclose(fp1);
	admin_menu();
}

void book_manage()
{
			system("cls");
			if((fp1=fopen(fn2,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo book saved yet !!");
				fclose(fp2);
				Sleep(2000);
				admin_menu();				
			}
			int found=0;
			int bookid;
			gotoxy(x_fix,y_initial);printf("Enter the Book ID : ");
			a();
			scanf("%d",&bookid);
			fp2=fopen("temp15.htc","w");
			while(fread(&b,sizeof(b),1,fp1)==1)
			{
					if(b.bid==bookid)
					{	
						found=1;int choose,ex_piece;
						system("cls");
						rect(x_fix-30,x_fix+80,y_initial-6,y_initial+20,0);
						gotoxy(x_fix+15,y_initial-4);printf("Record for Book ID %d :",bookid);
						gotoxy(x_fix-15,y_initial-2);printf("Name: ");
						printf("%s",b.name);
						gotoxy(x_fix-15,y_initial);printf("Writer: ");
						printf("%s",b.writer);
						gotoxy(x_fix-15,y_initial+2);printf("Publication: ");
						printf("%s",b.pub);
						gotoxy(x_fix-15,y_initial+4);printf("Publication year: ");
						printf("%d",b.pyear);
						gotoxy(x_fix+40,y_initial-2);printf("Edition: ");
						printf("%s",b.edi);
						gotoxy(x_fix+40,y_initial);printf("Faculty: ");
						printf("%s",b.fac);
						gotoxy(x_fix+40,y_initial+2);printf("Pieces Available: ");
						printf("%d",b.piece);
						char* menu[]={"Book Management","Modify this record","Add some pieces","Delete this record"};
						gotoxy(x_fix+15,y_initial+19);printf("Press ESC to go back");
						choose=htc_menumaker(menu,sizeof(menu)/sizeof(menu[0]),x_fix+15,y_initial+10);
						switch(choose)
						{
						case 1:
							system("cls");
							rect(x_fix-30,x_fix+80,y_initial-8,y_initial+20,0);
							gotoxy(x_fix,y_initial-6);printf("Enter Modified record for Book ID %d :",bookid);
							int pos;
							gotoxy(x_fix,y_initial-2);printf("Enter the name of book: ");
							get(b.name);
							gotoxy(x_fix,y_initial);printf("Enter the name of writer: ");
							get(b.writer);
							gotoxy(x_fix,y_initial+2);printf("Enter the publication name: ");
							get(b.pub);
							gotoxy(x_fix,y_initial+4);printf("Enter the publication year: ");
							scanf("%d",&b.pyear);
							gotoxy(x_fix,y_initial+6);printf("Enter edition of the book: ");
							get(b.edi);
							gotoxy(x_fix,y_initial+8);printf("Enter the appropriate faculty: ");
							char* faculty[]={"Science & Technology","Management","Health & Science","General","Others"};
							pos=htc_option(faculty,(sizeof(faculty)/sizeof(faculty[0])),x_fix+31,y_initial+8);
							strcpy(b.fac,faculty[pos]);
							gotoxy(x_fix,y_initial+10);printf("Enter pieces available : ");
							scanf("%d",&b.piece);
							fwrite(&b,sizeof(b),1,fp2);
							gotoxy(x_fix,y_initial+16);printf("Record Modified Successfully !!");
							Sleep(2000);
							break;		
						case 2:
							re6:gotoxy(x_fix+15,y_initial+19);printf("Enter the number of pieces to add : ");
								scanf("%d",&ex_piece);
								if (ex_piece>100||ex_piece<-100)
								{
								htc_fieldclr(x_fix+54,x_fix+70,y_initial+19,y_initial+19);
								printf("\a");
								goto re6;
								}
							system("cls");					
							gotoxy(x_fix,y_initial);printf("Pieces added Successfully!!! ");
							Sleep(1000);
							gotoxy(x_fix,y_initial+2);printf("Previous available pieces : %d",b.piece);
							b.piece+=ex_piece;
							gotoxy(x_fix,y_initial+4);printf("Current available pieces : %d",b.piece);
							Sleep(3000);
							fwrite(&b,sizeof(b),1,fp2);
							break;						
						case 3:
							re4:
							gotoxy(x_fix+15,y_initial+19);printf("Are you sure to delete it?(Y/N)");
							char conf2=getch();
							if(conf2!=78&&conf2!=89&&conf2!=110&&conf2!=121)
							goto re4;
							if((int)conf2==89||(int)conf2==121)
							{
							system("cls");					
							gotoxy(x_fix,y_initial);printf("Record Deleted Successfully!!! ");
							}
							else
							{
							fwrite(&b,sizeof(b),1,fp2);
							system("cls");
							gotoxy(x_fix,y_initial);printf("Record NOT Deleted !");
							}
							Sleep(2000);
							break;
						default:
							fwrite(&b,sizeof(b),1,fp2);	
					}
				}
				else
				{
					fwrite(&b,sizeof(b),1,fp2);
				}
			}
			if (found==0)
			{
				gotoxy(x_fix,y_initial+6);printf("No result found");
				Sleep(1000);
		}
			fclose(fp1);
			fclose(fp2);
			system("del bookreg.htc");
			system("ren temp15.htc bookreg.htc");
			admin_menu();
			
}

void clear_fine()
{
	start:
			system("cls");
			if((fp1=fopen(fn1,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo data saved yet !!");
				fclose(fp1);
				Sleep(2000);
				admin_menu();				
			}
			if((fp3=fopen(fn3,"r"))==NULL)
			{
				system("cls");
				gotoxy(x_fix,y_initial);printf("\aNo issue data recorded !!");
				fclose(fp1);fclose(fp3);
				Sleep(2000);
				admin_menu();				
			}
			int found=0;
			int memid,total_fine=0,count=0,count1=0,check1,check2;
			gotoxy(x_fix,y_initial);printf("Enter your member ID : ");
			a();
			scanf("%d",&memid);
			while(fread(&m,sizeof(m),1,fp1)==1)
			{
					if(m.mid==memid)
					{	
						found=1;
						system("cls");
						gotoxy(x_fix+15,y_initial-4);printf("Record for Member ID %d :",memid);
						gotoxy(x_fix-10,y_initial-2);printf("Name: ");
						printf("%s",m.name);
					}
			}
			fclose(fp1);
			if(found==1)
			{
				rewind(fp1);
				while(fread(&r,sizeof(r),1,fp3)==1)
				{
					if(r.mid==memid&&strcmp(r.status,"Returned")==0)
					{
						count++;
						total_fine+=r.fine;
					}
				}rewind(fp3);
				rect(x_fix-30,x_fix+80,y_initial-6,y_initial+12+count,0);
				if (count>0)
				{
					gotoxy(x_fix-25,y_initial);printf("Book: ");
					gotoxy(x_fix+25,y_initial);printf("Date to return");
					gotoxy(x_fix+42,y_initial);printf("Date of return ");
					gotoxy(x_fix+64,y_initial);printf("Days");
					gotoxy(x_fix+70,y_initial);printf("Fine");
					while(fread(&r,sizeof(r),1,fp3)==1)
					{
						if(r.mid==memid&&strcmp(r.status,"Returned")==0)
						{
							gotoxy(x_fix-25,y_initial+2+count1);printf("%s",r.bname);
							gotoxy(x_fix+25,y_initial+2+count1);printf("%d.%d.%d",r.dtr.day,r.dtr.month,r.dtr.year);
							gotoxy(x_fix+42,y_initial+2+count1);printf("%d.%d.%d",r.dor.day,r.dor.month,r.dor.year);
							check1=htc_daycalculator(1,1,1,r.dtr.day,r.dtr.month,r.dtr.year);
							check2=htc_daycalculator(1,1,1,r.dor.day,r.dor.month,r.dor.year);
							if (check2>check1)
							{
							gotoxy(x_fix+64,y_initial+2+count1);
							printf("%d",htc_daycalculator(r.dtr.day,r.dtr.month,r.dtr.year,r.dor.day,r.dor.month,r.dor.year));
							}
							else 
							{
							gotoxy(x_fix+64,y_initial+2+count1);
							printf("0");	
							}
							gotoxy(x_fix+70,y_initial+2+count1);printf("%d",r.fine);
							count1++;	
						}
					}
					gotoxy(x_fix+57,y_initial+3+count1);printf("Total fine : %d",total_fine);
					rewind(fp3);
					if(total_fine>0)
					{
						re:
						gotoxy(x_fix,y_initial+10+count);printf("Press ENTER to clear fine or ESC to cancel: ");
						char conf=getch();
						if(conf!=13&&conf!=27)
						goto re;
						if(conf==27)
						{
							fclose(fp3);
							admin_menu();
						}
					fp2=fopen("temp2.htc","w");
					while(fread(&r,sizeof(r),1,fp3)==1)
					{
						if(r.mid==memid)
						{
							r.fine=0;
							fwrite(&r,sizeof(r),1,fp2);
						}
						else
						fwrite(&r,sizeof(r),1,fp2);
					}
					fclose(fp2);fclose(fp3);				
					system("del record.htc");
					system("ren temp2.htc record.htc");
					system("cls");
					gotoxy(x_fix,y_initial);printf("Fine cleared Successfully!!! ");
					Sleep(2000);
					}
					else
					{
						re5:
						gotoxy(x_fix,y_initial+10+count);printf("No fine charged! Press ESC to go back: ");
						char conf5=getch();
						if(conf5!=27)
							goto re5;
						fclose(fp3);
						admin_menu();
					}
				}
				else
				{
					gotoxy(x_fix,y_initial+6);printf("No returned record found !");
					fclose(fp3);
				}
			}
			else
			{
			gotoxy(x_fix,y_initial+6);printf("No result found");
			Sleep(1000);
			fclose(fp3);
			}
			re50:
			gotoxy(x_fix,y_initial+10);printf("Press ENTER to clear fine of another record Or ESC to go back: ");
			char conf5=getch();
			if(conf5!=13&&conf5!=27)
			goto re50;
			if(conf5==13)
			goto start;
			admin_menu();		
}

void end()
{
	int i;
	system("cls");
	char exit_greet[50]="THANK YOU FOR USING PROGRAM !!";
	gotoxy(x_fix,y_initial);
	printf("%s",exit_greet);
	for (i=0;i<strlen(exit_greet);++i)
	{
		gotoxy(x_fix+i,y_initial+1);
		printf("%c",42);
		Sleep(100);
	}
	printf("\n\n\n\n\n");
	gotoxy(x_fix,y_initial+10);
	system("pause");
	exit(0);
}

void admin()
{
    char username[20], password[20]={0};
	int hit,count=0;
    do
    {
    hit=0;
    system("cls");
    rect(x_fix-10,x_fix+40,y_initial-4,y_initial+5,0);
    if (count!=0)
	{
    	gotoxy(x_fix,y_initial-2);printf("Attempt remaining : %d",4-count);
	}
    gotoxy(x_fix,y_initial);printf("Enter Admin name : ");
	get(username);
    gotoxy(x_fix,y_initial+2);printf("Password         : ");
	htc_password_maker(password);
	strcpy(username,strupr(username));
    strcpy(password,strupr(password));
    count++;
    if (count==4)
    {
    	system("cls");
        gotoxy(x_fix,y_initial); printf("Invalid Username or Password!!!! \a");
        gotoxy(x_fix,y_initial+5);printf("Program is redirecting to main menu !!");
        getch();
        main_menu();
    }
    if((strcmp(username,"ADMIN")==0&&strcmp(password,"ADMIN")==0)||(strcmp(username,"SAROJ")==0&&strcmp(password,"SAROJ")==0))hit=1;
    else
    {	system("cls");
        gotoxy(x_fix,y_initial); printf("Invalid Username or Password!!!!\a");
        getch();
	 }
	 } while(hit!=1);
	admin_menu();
}

//Functions for search
int htc_gfs(char ch[],int x1,int y1)
{
	char c;
	pre=post=count22322=0;
	int i=0,top;
	do
	{
		gotoxy(x1+i,y1);c=getch();
		if(c==9) continue;
		if((int)c==-32||c==13)
		{
			i--;
			goto new;
		}
		if(c==27)
		{
			return -2;
		}
		if (c==8)
		{
			if(i!=0)
			{
				i--;
				printf("\b \b");
			}			
		}
		if(c==0||c==224)
		{
			continue;
		}
	if(c!=8)ch[i]=c;else ch[i]='\0';
		new:ch[i+1]='\0';
		if(count22322==0&&c==13)
	{
		return -1;		
	}
		count22322++;
		top=htc_pfs(ch,x1,y1,c);
	if(c!=8)i++;
	}while (hitent!=1);
	return (top);	
}

int htc_pfs(char cha[],int x1,int y1,char r)
{
	found=0;
	hitent=0;
	pre=post;
	int len,pos[20],i,j,k=0,top;
	gotoxy(x1,y1);printf("%s",cha);
	len=strlen(cha);
	char temp[30],temp2[30];
	strcpy(temp2,cha);
	for (i=0;i<mero;i++)
	{
		for (j=0;j<len;j++)
		{
			temp[j]=names[i][j];
		}
		temp[j]='\0';
		if(strcmp(strupr(temp),strupr(temp2))==0)
		{
		pos[k]=i;		
		k++;
		found=1;
		}
	}
	top=htc_mmfs(temp2,k,x1,y1,r,pos);
	return (top);
}

int htc_mmfs(char hair[],int num,int x2,int y2,char r,int pos[])
{
	int x_fix=x2,y_initial=y2+1,i;
    char ch=r,newch;
	gotoxy(x_fix,y_initial+5);
 	while(1)
	{
		if ((int)ch==-32)
		 newch=getch();
 	 	switch((int)newch)
		{
	   		case 80: //Code for DOWN arrow equivalent to P
	    	place++;
	    	if (place==num) place=0;
		   	 break;
	   		case 72: //Code for UP arrow quivalent to H
	    	place--;
	   		 if(place<0) place=num-1;
	    	break;
		}
		if(post!=num) place=0;
		post=num;
		if((int)newch!=72&&(int)newch!=80)
		{
		htc_fieldclr(x2-17,x2+70,y2+3,y2+3+pre);
		}
		if(found!=1)
		{
			gotoxy(x_fix-15,y_initial+2);printf("No result!!");
			if(r==13){
				printf("\a");
				return 0;
			}
		}
		if(hair[0])
		{
		for(i=0;i<num;i++)
		{
			gotoxy(x_fix-17,y_initial+2+i);printf("  %s",names[pos[i]]);
			gotoxy(x_fix-17,y_initial+2+i);printf("  %s",hair);
			gotoxy(x_fix+30,y_initial+2+i);printf("%d",id[pos[i]]);
			gotoxy(x_fix+40,y_initial+2+i);printf("%d",roll_year[pos[i]]);
			gotoxy(x_fix+50,y_initial+2+i);printf("%s",sem_writer[pos[i]]);
		}
		for (i=0;i<num;i++)
			if (place==i)
			{
				gotoxy(x_fix-17,y_initial+2+i);printf("->%s",names[pos[i]]);
				gotoxy(x_fix-17,y_initial+2+i);printf("->%s",hair);
		
				break;
			}
		}
		else	
		{
			gotoxy(x_fix-15,y_initial+2);printf("Enter something!!");
			if(r==13){
				printf("\a");
				return 0;
			}
		}
		if(ch==13)
		{
			hitent=1;
			break;
		}
		break;
	}	
	return (pos[i]);
}

void assign(int ind)
{
	if(ind==1)
	{
			fp1=fopen(fn1,"r");			
			int i=0;
			while(fread(&m,sizeof(m),1,fp1)==1)
			{
				strcpy(names[i],m.name);strcpy(sem_writer[i],m.sem);id[i]=m.mid;roll_year[i]=m.roll;
				i++;
			}
			mero=i;
			fclose(fp1);				
			}
	else if(ind==2)
	{
			fp1=fopen(fn2,"r");	
			int i=0;
			while(fread(&b,sizeof(b),1,fp1)==1)
			{
				strcpy(names[i],b.name);strcpy(sem_writer[i],b.writer);id[i]=b.bid;roll_year[i]=b.pyear;
				i++;
			}
			mero=i;
			fclose(fp1);
	}
}

//End of functions for search

void welcomepage()
{
	system("cls");
	gotoxy(x_fix-3,y_initial-5);printf(" _      _  _             ");
	gotoxy(x_fix-2,y_initial+14);printf("       |___/");Sleep(150);
	gotoxy(x_fix-3,y_initial-4);printf("| |    |_|| |_ _ _    _ __ _ _    _ _   _ ");
	gotoxy(x_fix-2,y_initial+13);printf("|____/ \x5c__, |____/\x5c__\x5c____|_| |_| |_|");Sleep(150);
	gotoxy(x_fix-3,y_initial-3);printf("| |    | ||  _  \x5c\x5c \x5c/ // _` |\x5c \x5c/ /| | | |");
	gotoxy(x_fix-2,y_initial+12);printf(" ___) | |_| \x5c___ \x5c ||  ___/ | | | | |");Sleep(150);
	gotoxy(x_fix-3,y_initial-2);printf("| |_ _ | || |_| | |  || (_| | |  | | |_| |");
	gotoxy(x_fix-2,y_initial+11);printf("\x5c___ \x5c| | | / ___| __/ __ \x5c '_ ` _ \x5c ");Sleep(150);
	gotoxy(x_fix-3,y_initial-1);printf("|_ _ _||_||_ _ _| |__| \x5c__,_| |__|  \x5c__, |");
	gotoxy(x_fix-2,y_initial+10);printf("/ ___| _   _ ____| |_ ____ _ __ ___  ");Sleep(150);
	gotoxy(x_fix-3,y_initial);printf("                                    |_ _/");
	gotoxy(x_fix-2,y_initial+9);printf(" ____             _                  ");Sleep(150);
	gotoxy(x_fix-16,y_initial+2);printf(" __  __                                                     _   ");
	gotoxy(x_fix-16,y_initial+7);printf("                          |___/");Sleep(150);
	gotoxy(x_fix-16,y_initial+3);printf("|  \x5c/  | __ _ _ __   __ _  __ _  ____ _ __ ___   ____ _ __ | |_ ");
	gotoxy(x_fix-16,y_initial+6);printf("|_|  |_|\x5c__,_|_| |_|\x5c__,_|\x5c__, |\x5c____|_| |_| |_|\x5c____|_| |_|\x5c__|");Sleep(150);
	gotoxy(x_fix-16,y_initial+4);printf("| |\x5c/| |/ _` | '_ \x5c / _` |/ _` |/ __ \x5c '_ ` _ \x5c / __ \x5c '_ \x5c| __|");
	gotoxy(x_fix-16,y_initial+5);printf("| |  | | (_| | | | | (_| | (_| |  ___/ | | | | |  ___/ | | | |_ ");Sleep(150);
	
	int i;char tit[]="HTC(Eversoft)";
	gotoxy(x_fix+40,y_initial+17);
	printf("Developed by:");
	Sleep(600);
	gotoxy(x_fix+40,y_initial+18);
	for (i=0;i<=12;i++)
	{
		printf("%c",tit[i]);
		Sleep(600-i*45);
	}
	gotoxy(x_fix,y_initial+19);printf("<<Press any key to continue>>");
	getch();
	main_menu();
}

