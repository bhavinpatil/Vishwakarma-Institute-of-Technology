#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
# define MS (157.2)*5
//for circle
float speed=50;
int sb1=700,sb2=100,sb3=1000,sb4=500;
int f1=25,f2=25;
int x=25,y=25,r=12;
int blx=10,bly=10,bls=10,score1=0;
// for bars
int x2=100,y2=340,rndx,rndy;
int x3=200,y3=380,rndx3,rndy3;
int x4=300,y4=300,rndx4,rndy4;
int x5=200,y5=380,rndx5,rndy5;
int gdriver=DETECT,gmode;
int c,a,hl=1,ttr=0;
int stack[5]={383,356,329,302,275},j=4,n=5,k=0,bcol=475;
int stack2[12]={383,356,329,302,275,248,221,194,167,140,113,86},n2=0,k2=0,bcol2=575,j2=0;
void move(int a);
void logo(void);
void codding(int score1);
void randomstar(void);
void won(void);
void gover(void);
void security(void);
void main2(void);
void mouse(void);
// mouse functions prototypes
void initmouse();
void showmp();
void hidemp();
int getmp(int *button,int *x,int *y);
void setmp();
int screen();
void button(int x1,int y1,int x2,int y2,char str[]);
int click(int x1,int y1,int x2,int y2,char str[]);
int press(int,int,int,int);
int unpress(int,int,int,int);
void sound1();
void instruction();

int main (){
	FILE *fp;
	int h;
	initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");
	cleardevice();
		security();
return 0;
}

void security(){
	int a=0,b=0,c=100;
	setcolor (RED);
	settextstyle (10,HORIZ_DIR,2);
	outtextxy (220,160,"LODDING.....\n");
	settextstyle (1,HORIZ_DIR,2);
	outtextxy (270,218,"%");
	while (a<600){
		setcolor (WHITE);
		settextstyle (0,HORIZ_DIR,3);
		outtextxy (a,410,"Þ");
		delay(5);
		a++;
		if (b<=100){
			gotoxy (38,15);
			printf ("%d",b);
			if (a==c||a==c+100||a==c+200||a==c+300||a==c+400||a==c+500)
				b=b+18;
		}
	}
	logo();
}

void logo(){
	cleardevice();
	setbkcolor (0);
	settextstyle (7,HORIZ_DIR,4);
	setcolor (10);
	outtextxy (280,10,"Welcome");
	setcolor (WHITE);
	setcolor (13);
	setcolor(100);
	outtextxy (230,430,"press any to continue");
	getch();
mouse();
}
 void mouse(){
   initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");
   cleardevice();
   initmouse();
   showmp();
   screen();
}

void initmouse(){
	union REGS i,o;
	i.x.ax=0x0;
	int86(0x33,&i,&o);
}

void showmp(){
	union REGS i,o;
	i.x.ax=0x1;
	int86(0x33,&i,&o);
}

void hidemp(){
	union REGS i,o;
	i.x.ax=0x2;
	int86(0x33,&i,&o);
}

int getmp(int *button,int *x,int *y){
	union REGS i,o;
	i.x.ax=0x3;
	int86(0x33,&i,&o);
	*button=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
return 0;
}

void setmp(){
	union REGS i,o;
	i.x.ax=0x4;
	i.x.cx=150;
	i.x.dx=150;
	int86(0x33,&i,&o);
}

int screen(){
	settextstyle(1,HORIZ_DIR,7);
	setcolor(14);
	outtextxy(170,8,"Rapid Roll");
	outtextxy(240,350,"Game");
	setmp();
	button(250,100,400,150,"New Game");
	button(250,150,400,200,"Sound");
	button(250,200,400,250,"Instruction");
	button(250,250,400,300,"Developer");
	button(250,300,400,350,"Exit");
	while(1){
		if(click(250,100,400,150,"New Game")==0){
			hidemp();
			cleardevice();
			main2();
			return 0;
		}

		if(click(250,150,400,200,"Sound")==0){
			hidemp();
			cleardevice();
			sound1();
			return 0;
		}
		if(click(250,200,400,250,"Instruction")==0){
			hidemp();
			instruction();
			return 0;
		}
		if(click(250,250,400,300,"Developer")==0){
			hidemp();
			cleardevice();
			logo();
			return 0;
		}
		if(click(250,300,400,350,"Exit")==0)
			exit(0);
	}
}

void button(int x1,int y1,int x2,int y2,char str[]){
	int xc,yc,i1=0,l1=0;
	while(i1<strlen(str)){
		l1+=4;
		i1++;
	}
	xc=(x2-x1)/2+x1-l1;
	yc=(y2-y1)/2+y1;
	unpress(x1,y1,x2,y2);
	settextstyle(0,0,0);
	setcolor(11);
	outtextxy(xc,yc,str);
}

int click(int x1,int y1,int x2,int y2,char str[]){
	int button,x,y;
	int xc,yc,i1=0,l1=0;
	while(i1<strlen(str)){
		l1+=4;
		i1++;
	}
	xc=(x2-x1)/2+x1-l1;
	yc=(y2-y1)/2+y1;
	getmp(&button,&x,&y);
	if( (x>x1 && x<x2) && (y>y1 && y<y2) && button==1){
		hidemp();
		press(x1,y1,x2,y2);
		setcolor(GREEN);
		settextstyle(0,0,0);
		outtextxy(xc,yc,str);
		showmp();
		while((button==1))
			getmp(&button,&x,&y);
		hidemp();
		unpress(x1,y1,x2,y2);
		showmp();
		setcolor(GREEN);
		settextstyle(0,0,0);
		outtextxy(xc,yc,str);
		for(i1=50;i1<500;i1=i1+50){
			delay(10);
			sound(i1+200);
		}
		showmp();
		nosound();
		setcolor(11);
		settextstyle(0,0,0);
		outtextxy(xc,yc,str);
		return 0;
	}else return 1;
}

int unpress(int x1,int y1,int x2,int y2){
	setlinestyle(0,1,1);
	setfillstyle(3,12);
	bar(x1,y1,x2,y2);
	setcolor(WHITE);
	line(x1,y1,x2,y1);
	line(x1,y1,x1,y2);
	line(x1,y2,x2,y2);
	line(x2,y1,x2,y2);
return 0;
}

int press(int x1,int y1,int x2,int y2){
	setlinestyle(0,1,1);
	setfillstyle(0,3);
	bar(x1,y1,x2,y2);
	setcolor(0);
	line(x1,y1,x2,y1);
	line(x1,y1,x1,y2);
	setcolor(WHITE);
	line(x1,y2,x2,y2);
	line(x2,y1,x2,y2);
return 0;
}

void sound1(){
	int ssb;
	settextstyle(1,HORIZ_DIR,2);
	outtextxy (200,200,"Press 1 for Sound on");
	outtextxy (200,100,"Press 0 for Sound off");
	scanf ("%d",&ssb);
	if (ssb==1){
		main2();
	}else if (ssb==0){
		sb1=0;
		sb2=0;
		sb3=0;
		sb4=0;
		main2();
	}else
		mouse();
	getch();
}
void instruction(){
	FILE *fp;
	char string[20];
	closegraph();
	fp=fopen("Instructions.c","r");
	if (fp==0){
		puts ("Can't open");
		getch();
		mouse();
	}
	while (fgets(string,19,fp)!=0)
		printf ("%s",string);
	printf ("\n");
	getch();
	fclose(fp);
	mouse();
}

void main2(){
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");
	cleardevice();
	rndx=+x2;
	rndy=+y2;

	rndx3=+x3;
	rndy3=+y3;

	rndx4=+x4;
	rndy4=+y4;

	rndx5=+x5;
	rndy5=+y5;

	randomstar();

	codding(score1);
	while((c=getch())!='\033'){
		//right
		if (c=='\115') a=1;
		//left
		if (c=='\113') a=2;
		move (a);
		}
}

void move (int a){
	void score(int f1,int f2,int ttr);
	while(!kbhit()){
	//clear remaining bars
	setfillstyle(0,0);
	bar (rndx5-198,rndy5-378,rndx5+198,rndy5-365);

	//bar codding
	setfillstyle(0,0);
	bar (rndx-25,rndy-3,rndx+25,rndy+3);
	rndy=rndy-1;
	setfillstyle(1,2);
	bar (rndx-25,rndy-3,rndx+25,rndy+3);
	if (rndy==10){
		rndy=+y2;
	}
	setfillstyle(0,0);
	bar (rndx3-25,rndy3-3,rndx3+25,rndy3+3);
	rndy3=rndy3-1;
	setfillstyle(1,2);
	bar (rndx3-25,rndy3-3,rndx3+25,rndy3+3);
	if (rndy3==10){
		rndy3=+y3;
	}
	setfillstyle(0,0);
	bar (rndx4-25,rndy4-3,rndx4+25,rndy4+3);
	rndy4=rndy4-1;
	setfillstyle(1,2);
	bar (rndx4-25,rndy4-3,rndx4+25,rndy4+3);
	if (rndy4==10){
		rndy4=+y4;
	}

	// food codding
	setfillstyle(5,14);
	bar3d(blx,bly,blx+bls,bly+bls,0,0);
	//circle codding
	setcolor (WHITE);
	circle(f1,f2,r);
	setfillstyle(SOLID_FILL,BLACK);
	floodfill(f1,f2,BLACK);

	//clear remaining circle
	bar (rndx5-198,rndy5+18,rndx5+198,rndy5-6);

	setcolor (WHITE);
	circle(f1,f2,r);
	setfillstyle(SOLID_FILL,RED);
	floodfill(f1,f2,WHITE);
	setcolor(0);

	if ((f2==rndy-18) && (f1==75 || f1==85 || f1==95 || f1==105 || f1==115 || f1==125))
	{
	f2=f2-1;
	}
	else if ((f2==rndy4-18) && (f1==275 || f1==285 || f1==295 || f1==305 || f1==315 || f1==325))
	{
	f2=f2-1;
	}
	else if ((f2==rndy3-18)&& (f1==175 || f1==185 || f1==195 || f1==205 || f1==215 || f1==225)){
	f2=f2-1;
	}else
	f2=f2+1;
	delay(speed);
	score (f1,f2,ttr);
	if (f2==387)
	{
	f2=25;
	ttr++;
	}
	else if (f2==14){
		f2=25+1;
		ttr++;
	}

	}
	if(a==1)f1=f1+5;
	if(a==2)f1=f1-5;

	if (f1==10) f1=20;
	if (f1==390) f1=385;
}

void score (int f1,int f2,int ttr){
	while (k<n-ttr){
		setcolor (WHITE);
		circle(bcol,stack[k],r);
		setfillstyle(SOLID_FILL,GREEN);
		floodfill(bcol,stack[k],WHITE);
		k++;
	}
	if (f2==383 || f2==14){
		setcolor (BLACK);
		circle(bcol,stack[j],r);
		setfillstyle(SOLID_FILL,BLACK);
		floodfill(bcol,stack[j],BLACK);
																																																							j--;
		sound(sb4);
		delay(50);
		nosound();
		if (j==-1){
			sound(sb2);
			delay(100);
			nosound();
			gover();
		}
	}
	if ((f2==bly || f2+11==bly || f2-11==bly) && (f1==blx+5 || f1+11==blx+5 || f1-11==blx+5)){
		sound(sb3);
		delay(50);
		score1+=2;
		nosound();
		codding (score1);
	if (score1==10){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==20){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==30){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==40){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==50){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==60){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==70){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==80){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==90){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==100){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==110){
		j2++;
		n2=j2;
		sound(sb1);
		delay(70);
		nosound();
		speed=speed-3.75;
	}else if (score1==120){
		j2++;
		n2=j2;
		sound(sb1);
		delay(100);
		nosound();
		speed=speed-3.75;
	}else if (score1>120){
		won ();
	}
	randomstar();
	}

	while (k2<n2){
		setcolor (WHITE);
		circle(bcol2,stack2[k2],r);
		setfillstyle(SOLID_FILL,YELLOW);
		floodfill(bcol2,stack2[k2],WHITE);
		k2++;
	}
}

void randomstar(){
	int ic=0,pr=0;
	randomize();
	ic=random(10000)%40;
	ic=ic*bls;
	pr=random(10000)%40;
	pr=pr*bls;
	blx=ic;
	bly=pr;

	if ((bly<30) || (bly>350)){
		bly=40;
	}
	if ((blx<30) || (blx>383)){
		blx=20;
	}
}
void codding (int score1){
	setcolor (WHITE);
	rectangle(0,0,400,400);
	gotoxy (60,5);
	circle (480,70,30);
	setcolor (WHITE);
	printf ("%d ",score1);
//Bonus
	setcolor (7);
	outtextxy (455,165,"BONUS");
	setcolor (WHITE);
	line (500,200,500,400);line (450,200,450,400);line (450,400,500,400);
//Score
	setcolor (7);
	outtextxy (550,25,"SCORE");
	outtextxy (550,40,"10 = 1");
	setcolor (WHITE);
	line (600,60,600,400);line (550,60,550,400);line (550,400,600,400);
}

void won (){
	cleardevice();
	rectangle (40,100,100,135);line (40,100,100,135);line (40,135,100,100);
	settextstyle (7,HORIZ_DIR,5);setcolor (GREEN);
	outtextxy (135,150,"Congratulation!");
	outtextxy (150,200,"You won the GAME");
	settextstyle (7,HORIZ_DIR,1);setcolor (YELLOW);
	setcolor (7);
getch();
exit(0);
}
void gover(){
cleardevice();
	rectangle (40,100,100,135);line (40,100,100,135);line (40,135,100,100);
	settextstyle (7,HORIZ_DIR,5);setcolor (RED);
	outtextxy (200,200,"GAME OVER");
	settextstyle (7,HORIZ_DIR,1);setcolor (YELLOW);
getch();
mouse();
}
