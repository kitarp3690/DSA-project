#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>
//#include<stdio.h>
#include<stdlib.h> //for exit(0) function
#include<malloc.h>
#define loc 0
union REGS in,out;
//function to display the mouse
void showmouse(){
//set service AX=1 for displaying mouse
	in.x.ax=1;
	int86(0X33,&in,&out);
}
//function to inititalize the mouse pointer
int initmouse(){
//set service AX=0 for detecting mouse
	in.x.ax=0;
	int86(0X33,&in,&out);
	return out.x.ax;
}
//function to get the current clicked mouse position on the screen
void getmouseposition(int *click,int *x,int *y){
	in.x.ax=3;
	int86(0x33,&in,&out);
	//get the coordinates
	*click=out.x.bx;
	//update the x and y coordinate
	*x=out.x.cx;
	*y=out.x.dx;
}
void createbutton(int left,int top,int right,int bottom){
	rectangle(left,top,right,bottom);
}
void drawtext(int a,int b,const char* text){
	outtextxy(a,b,text);
}
void getmousestate(int* x,int* y,int* button){
	in.x.ax=3;
	int86(0x33,&in,&out);
	*x=out.x.cx;
	*y=out.x.dx;
	*button=out.x.bx;
}
void restrictmouse(int maxx,int maxy){
	//set horizontal limit
	in.x.ax=7;
	in.x.cx=0;
	in.x.dx=maxx-10;
	int86(0x33,&in,&out);

	//set vertical limit
	in.x.ax=8;
	in.x.cx=0;
	in.x.dx=maxy-10;
	int86(0x33,&in,&out);
}
void gotoa(int x,int y){
	union REGS inregs,outregs;
	inregs.h.ah=2;
	inregs.h.bh=0;
	inregs.h.dh=y-1;
	inregs.h.dl=x-1;
	int86(0x10,&inregs,&outregs);
}
void movecursor(int x,int y){
	cout<<"\03["<<y<<";"<<x<<"H";
}
void hidemouse(){
	in.x.ax=2;
	int86(0x33,&in,&out);
}
//******************************************************************
//******************************************************************
struct contact{
	char name[50];
	char address[50];
	char mob_num[10];
	char email[60];
	contact* next,*prev;
}*pfirst=NULL,*plast=NULL,*pthis,*pnew,*ptemp;
void rec(){
	rectangle(280,10,getmaxx(),getmaxy());
}
void newc(){
	pnew=(struct contact*)malloc(sizeof(struct contact));
	pnew->next=NULL;
	settextstyle(0,0,1);
	outtextxy(300,39,"Enter name : ");
	gotoa(118,4);
	cin>>pnew->name;
	outtextxy(300,82,"Enter Mobile number : ");
	gotoa(118,7);
	cin>>pnew->mob_num;
	outtextxy(300,125,"Enter Email address: ");
	gotoa(118,10);
	cin>>pnew->email;
	loc++;
}
void menu();
void newcontact(){
	clrscr();
	cleardevice();
	menu();
	hidemouse();
	rec();
	newc();
	if(pfirst==NULL){
		pfirst=pnew;
		plast=pnew;
		pfirst->prev=NULL;
	}
	else{
	    // If the list is not empty, add the new contact at the end
        pnew->prev = plast;
        plast->next = pnew;
        plast = pnew;
	}
	showmouse();
}
void display(){
	clrscr();
	cleardevice();
	menu();
	rec();
	hidemouse();
	if(pfirst==NULL)
	{
		outtextxy(370,82,"Phone Book is empty");
	}
	else if(pfirst->next==NULL)
	{
		settextstyle(0,0,1);
		gotoa(118,4);
		cout<<" Name: "<<pfirst->name;
		gotoa(118,7);
		cout<<" Mobile Number : "<<pfirst->mob_num;
		gotoa(118,10);
		cout<<" Email : "<<pfirst->email;
		pthis=pthis->next;
	}
	else{
	int i=1,x=118,y=4;
	pthis=pfirst;
	while(pthis!=NULL)
	{
		settextstyle(0,0,1);
		gotoa(x,i*y+1);
		cout<<" Name: "<<pthis->name;
		gotoa(x,i*y+2);
		cout<<" Mobile Number : "<<pthis->mob_num;
		gotoa(x,i*y+3);
		cout<<" Email : "<<pthis->email;
		pthis=pthis->next;
		i++;
	}
	}
	showmouse();
}
void search(){
	clrscr();
	cleardevice();
	menu();
	rec();
	hidemouse();
	if(pfirst==NULL)
	{
		settextstyle(0,0,1);
		outtextxy(330,79,"Phone Book is empty");
	}
	else
	{
		char name[50];
		outtextxy(300,39,"Enter name : ");
		settextstyle(0,0,1);
		gotoa(118,4);
		cin>>name;
		clrscr();
		cleardevice();
		menu();
		rec();
		int i=1,x=118,y=4;
		int found=0;
		pthis=pfirst;
		while(pthis!=NULL){
			if(strcmp(name,pthis->name)==0){
				found=1;
				settextstyle(0,0,1);
				gotoa(x,i*y+1);
				cout<<" Name: "<<pthis->name;
				gotoa(x,i*y+2);
				cout<<" Mobile Number : "<<pthis->mob_num;
				gotoa(x,i*y+3);
				cout<<" Email : "<<pthis->email;
				pthis=pthis->next;
			}
			pthis=pthis->next;
		}
		if(found==0){
			settextstyle(3,0,1);
			outtextxy(330,79,"No contacts found.");
		}
	}
}
void deletec(){
	clrscr();
	cleardevice();
	menu();
	rec();
	hidemouse();
	if(pfirst==NULL)
	{
		settextstyle(0,0,1);
		outtextxy(330,79,"Phone Book is empty");
	}
	else
	{
		char name[50];
		outtextxy(300,39,"Enter name : ");
		settextstyle(0,0,1);
		gotoa(118,4);
		cin>>name;
		clrscr();
		cleardevice();
		menu();
		rec();
		int i=1,x=118,y=4;
		int found=0;
		pthis=pfirst;
	      /*	while(pthis->next!=NULL){
			if(strcmp(name,pthis->name)==0){
				found=1;
				ptemp=pthis->next;
				free(pthis);
			}
			pthis=pthis->next;
		}*/
		for(int i=1;i<=loc;i++){
			if(strcmp(pthis->name,name)==0){
				pos=i;
				pthis=pfirst;
				for(int j=0;j<pos-1;j++){
					pthis=pthis->next;
				}
				ptemp=pthis->next->next;
				free(pthis->next);
				pthis->next=ptemp;
				loc--;
			}
			pthis=pthis->next;
			ppthis=pthis;
			i++;
		}
		if(found==0){
			settextstyle(3,0,1);
			outtextxy(330,79,"No contacts found.");
		}
	}

}
void menu(){
	rectangle(0,10,260,410);
	rectangle(10,20,250,400);
	settextstyle(8,0,1);
	outtextxy(87,50,"Phone Book");
	settextstyle(0,0,1);
	createbutton(50,100,210,130);
	drawtext(60,110,"Create New Contact");
	createbutton(50,150,210,180);
	drawtext(60,160,"All contacts");
	createbutton(50,200,210,230);
	drawtext(60,210,"Search Contact");
	createbutton(50,250,210,280);
	drawtext(60,260,"Exit");
}

int main(){
	clrscr();
	int  x,y,button,status;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"..//bgi");
	//get the status of mouse
	status=initmouse();
	//check if mouse is available or not
	if(status==0)
		cout<<"mouse support not available\n";
	else{
		int maxx=getmaxx(),maxy=getmaxy();
		menu();
		restrictmouse(maxx,maxy);
		//funtion to reset mouse
		in.x.ax=4;
		int86(0x33,&in,&out);
		int lastbuttonstate=0;
		int buttonclicked=0;
		while(1){
			showmouse();
			getmousestate(&x,&y,&button);
			if((button&1)&&!lastbuttonstate)
			{
				lastbuttonstate=1;
				buttonclicked=1;
			}
			else if((!button&1)&&lastbuttonstate)
			{
				lastbuttonstate=0;
			}
			if(buttonclicked)
			{
				if(x>=50&&x<=210&&y>=100&&y<=130)
				{
					newcontact();
				}
				else if(x>=50&&x<=210&&y>=150&&y<=180)
				{
					display();
				}
				else if(x>=50&&x<=210&&y>=200&&y<=230){
					search();
				}
				else if(x>=50&&x<=210&&y>=250&&y<=280)
				{
					exit(0);
				}
				buttonclicked=0;
				delay(200);
			}
		}
	}
	getch();
	closegraph();
	return 1;
}
