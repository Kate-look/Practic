// Osnova_kurs.cpp: ������� ���� �������.

#include "stdafx.h" //����������� ��������� 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>

using namespace System;
using namespace std;
using namespace System::IO;

#define ENTER 13 //����������� ������
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79

const char dan[9][75]={
	"1. ����� ����� ����� ������?                                         ",
	"2. ����� ����� ��� ������� ������ ����?                              ",
	"3. ������ ������� � ����� ������� c ��������� ���� 7.0               ",
	"4. ������ � ���������� ������������������, �� ������� ��������       ",
	"5. ���������� ������ ����� �� ������� ������������������ �������     ",
	"6. ������ ������� � ������������ 18+ � ������������� ������ 115 ���  ",
	"7. ���������. ���������� ����������� ������� � ������ ������         ",
	"8. ����� ������� �� �������                                          ",
	"�����                                                                ",
}; //������� ������ �������� - ������� ����
const char gran[] = "|=====================|=============|=======|==============|=========|===================|=========|";
const char nazv[] = "|   �������� ������   |     ����    |  ���  | ������������ | ������� |      ������       | ������� |";
const char BlankLine[ ]="                                                                       ";
struct z {
	char name[30]; //�������� ������
	char zhanr[20]; //����
	int year; //��� �������
	long time; //�����������������
	float rating; //�������
	char strana[20]; //������ �������������
	char age[4]; //���������� �����������
}; //������ ��������� ��� �������� ������
struct sp {
	char strana[20];
	long time;
	int k;
	struct sp* sled;
	struct sp* pred;
};//������, ���������� �������� ��������� ������������ ������

int menu(int); //�������� �������� ������������ �������
void spisok_3(struct z*, int);
void maxim_1(struct z*, int);
void first_2(struct z*, int);
void alfalist(struct z*, struct sp**, int);
void vstavka(struct z*,char*,struct sp**, int);
void diagram(struct z *film, struct sp**, int);
void spisok_6(struct z* film, int);
void dop_vopros_4(struct z* film, int);
void poisk(struct z* film, int);


int main(array<System::String ^> ^args){
	//�� ��������� ������ ������������ �������� �����,
	//��������� ������ �� ����� � ���������� ������
    int i,n;
	int NC; //���������� ������� ������ ���������
	FILE *in, *out;
	struct z *films;
	setlocale(LC_CTYPE,"Russian"); //��������� �������� �����
	Console::CursorVisible::set(false); //��������� ��������� �������
	Console::BackgroundColor=ConsoleColor::White; 
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BufferHeight=Console::WindowHeight;//��������� ������� ������ �� ������
	Console::BufferWidth=Console::WindowWidth; //��������� ������� ������ �� ������

	if((in=fopen("����.txt","r"))==NULL){ //������� ������� ����
		printf("\n���� ����.txt �� ������ !"); //��� ��������� �������� ������� ���������� ����� �� ������!�
		getch(); exit(1);
	}
	
	fscanf(in,"%d",&NC);
	films=(struct z*)malloc(NC*sizeof(struct z)); //�������� ������

	for(i=0;i<NC;i++) //��������� ������ �� ������
		fscanf(in,"%s%s%d%ld%f%s%s",
		films[i].name,
		films[i].zhanr,
		&films[i].year,
		&films[i].time,
		&films[i].rating,
		films[i].strana,
		films[i].age);

	struct sp *spisok = NULL;
	//�������� �� ���� ������� � ��������� �� � ������
	for(i=0;i<NC;i++)
		vstavka(films, films[i].strana, &spisok, NC);

	printf(gran);
	printf("\n");
	printf(nazv);
	printf("\n");
	printf(gran);

	for(i=0;i<NC;i++) //������� ������ �� ������ �� �����
		printf("\n| %-20s| %-12s| %-6d| %9ld ���| %-8.2f| %-18s| %-8s|",
		films[i].name,
		films[i].zhanr,
		films[i].year,
		films[i].time,
		films[i].rating,
		films[i].strana,
		films[i].age);

	printf("\n");
	printf(gran);

	out=fopen("����_������.txt","w");

	fprintf(out,gran);
	fprintf(out,"\n");
	fprintf(out,nazv);
	fprintf(out,"\n");
	fprintf(out,gran);

	for(i=0;i<NC;i++) //������� ������ �� ������ � ����
		fprintf(out,"\n| %-20s| %-12s| %-6d| %9ld ���| %-8.2f| %-18s| %-8s|",
		films[i].name,
		films[i].zhanr,
		films[i].year,
		films[i].time,
		films[i].rating,
		films[i].strana,
		films[i].age);

	fprintf(out,"\n");
	fprintf(out,gran);

	getch();

	while(1) //� ����� ������� ������� ��� �������� � ���������� �� � �����
		//������������� ��� ���� ���� � ��������� ��� ���������� �������
	{
		Console::ForegroundColor=ConsoleColor::Gray;
		Console::BackgroundColor=ConsoleColor::DarkMagenta;
		Console::Clear();
		Console::ForegroundColor=ConsoleColor::Red;
		Console::BackgroundColor=ConsoleColor::Cyan;
		Console::CursorLeft=20;
		Console::CursorTop=3;
		cprintf("�������� ������ ��� ������ ������� � ������� ENTER");
		Console::ForegroundColor=ConsoleColor::Black;		
		Console::CursorLeft=10; //������ �����, ������ ����� ����������� ������� ����                          
		Console::CursorTop=4;
		printf(BlankLine);

		for(i=0;i<9;i++) //���������� �������� 
		{
			Console::CursorLeft=10;
			Console::CursorTop=i+5;
			printf(" %s ",dan[i]);
		}
		Console::CursorLeft=10; //��������� �����,��� ����� ������������� ���������� ������� ��� ���� 
		Console::CursorTop=13;
		printf(BlankLine);

		n = menu(9);  //����� ������� � ���� 
		switch(n) 
		{
			case 1: maxim_1(films, NC); break;
			case 2: first_2(films, NC); break;
			case 3: spisok_3(films, NC); break;
			case 4: dop_vopros_4(films, NC);break;
			case 5: alfalist(films, &spisok, NC); break;
			case 6: spisok_6(films, NC);break;
			case 7: diagram(films, &spisok, NC); break;
			case 8: poisk(films, NC); break;
			case 9: exit(0);
		}
	} // ����� while(1)... 
	return 0;
} // ����� main() 
int menu(int n) //n=9 
{
	int y1=0,y2=n-1; //������������� ��������� ��� ������� 
	char c=1;
	while (c!=ESC)  //��� ������� ������ ESC, ���� ��������� 
	{
		switch(c) //���������������� ������
		{
			case DOWN: y2=y1; y1++; break; //����������� ����
			case UP: y2=y1; y1--; break; //����������� �����
			case ENTER: return y1+1; //����� �������
			case HOME: y2=y1; y1=0; break; //������� � ������ ������
			case END: y2=y1; y1=n-1; break; //������� � ����� ������
		}
	if(y1>n-1){y2=n-1;y1=0;} //�������,����� ����������� ������ DOWN ; y1 ����; �2 �������
	if(y1<0) {y2=0;y1=n-1;} //�������,����� ����������� ������ UP 
	Console::ForegroundColor=ConsoleColor::White; //��� ������ �������� �������� ����� ����� ������
	Console::BackgroundColor=ConsoleColor::DarkBlue; //��� ������ �������� ��� �� ������� �������� ������� ������
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);

	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Cyan;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
	}// ����� while(c!=ESC)... 
exit(0);
}


//������ ������� � ����� ������� c ��������� ���� 7.0
void spisok_3(struct z* film, int NC){
	Console::BackgroundColor=ConsoleColor::Yellow; // ������������� ���� ���� ������� �� ������
	Console::ForegroundColor=ConsoleColor::Black; // ������������� ���� ������ ������� �� ������
	Console::Clear();

	Console::CursorTop=2;
	printf("   ������ ������� � ����� ������� c ��������� ���� 7.0\n");

	printf("   ===================================================\n");

	int i;
	for (i=1;i<NC;i++)
		// ���������, ��� ���� ������ "�������" � ������� ���� 7.0
		if ((strcmp(film[i].zhanr,"�������")==0) && (film[i].rating >= 7.0))
			// ������� ���������� � ������, ���� �� �������� �� ����� � ��������
			printf("   %-20s%-15s%-8.2f\n",film[i].name,film[i].zhanr,film[i].rating);
	getch();
}

// ����� ����� ����� ������? (������� ������ ���������) 
void maxim_1(struct z* film, int NC){
	int i=0; 
	// ���������� ��������� ��� �������� ���������� � ������ � ����� ������� ������������������
	struct z best;
	// �������� �������� ������� ������ � ��������� best
	strcpy(best.name,film[0].name);
	// �������� ����������������� ������� ������ � ��������� best
	best.time=film[0].time;
	for (i=1;i<NC;i++)
		if (film[i].time > best.time){ //������� ������ ������������� ���������� 
			strcpy(best.name,film[i].name);
			best.time=film[i].time;
		}
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkMagenta;
	Console::CursorLeft=10; //������ �������, ��� ����� �������� ����.����������  
	Console::CursorTop=15;
	printf("����� ������� ����������������� %ld �����",best.time); // ����� ������������� ���������� 
	Console::CursorLeft=10; //����?� �������,��� ����� �������� �������� ������ 
	Console::CursorTop=16;
	printf("� ������ \"%s\"",best.name);//����� ������
	getch();
}

//����� ����� ��� ������� ������ ����?
void first_2(struct z* film, int NC){
	int i=0; 
	struct z best; // ���������� ��������� ��� �������� ���������� � ������, �������� ������ ����
	strcpy(best.name,film[0].name); // �������� �������� ������� ������ � ��������� best
	best.year=film[0].year; // �������� ��� ������� ������ � ��������� best
	for (i=1;i<NC;i++)
		if (film[i].year < best.year){ //��������� �������� ������ � ������ �� ��������� best
			strcpy(best.name,film[i].name);
			best.year=film[i].year;
		}
	Console::ForegroundColor=ConsoleColor::White;// ������������� ���� ������ ������� �� �����
	Console::BackgroundColor=ConsoleColor::DarkMagenta;// ������������� ���� ���� ������� �� �����-����������
	Console::CursorLeft=10;//������ ������� ������
	Console::CursorTop=15;
	printf("� %d ���� ��� ������� �����",best.year); // ������� ���������� � ���� ������ ������� ������
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("\"%s\"",best.name); // ������� �������� ������� ��������� ������
	getch();
}
// ���������� ������ ����� �� ������� ������������������ ������� (������� ������ � ������������ �������) 
void alfalist(struct z* film, struct sp** spisok, int NC){ //������������ ������ 
	int i;
	struct sp* nt;
	struct sp* z;
	
	// ��������� ����� ������ ������� �� ������ � ����� ���� �� ������
	Console::ForegroundColor=ConsoleColor::Yellow;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();

	Console::Clear();
	printf("\n ���������� ������ ����� �� ������� ������������������ �������");
	printf("\n =============================================================");

	// ������ �� ������ spisok � ����� ���������� � ������� � �� ������� ����������������� �������
	for(nt=*spisok; nt!=0; nt=nt->sled)
		printf("\n %-20s %3d ���",nt->strana,nt->time/nt->k);
	Console::CursorTop=12;
	Console::CursorLeft=0;
	printf(" ==============================================================\n");
	printf(" �������� ������ ����� �� ������� ������������������ �������\n");
	printf(" =============================================================\n");

	// ����������� ��������� nt � ����� ������ � ����� ���������� � �������� �������
	for(nt=*spisok,z=0; nt!=0;z=nt, nt=nt->sled);
	for(nt=z,i=5; nt!=0; nt=nt->pred,i++){	
		printf(" %-20s %3d ���\n",nt->strana,nt->time/nt->k);
	}
  	getch();
}

// ������� ��� ������� ��������� � ������ � ������ ���������� ����������
void vstavka(struct z* film, char* strana, struct sp** spisok, int NC) {
    int i;
    struct sp *New, *nt, *z = 0;

    // ������ �� ������ spisok �� ��� ���, ���� �� ������� ����� ��� ������� ��� �� ��������� ����� ������
    for (nt = *spisok; nt != 0 && strcmp(nt->strana, strana) < 0; z = nt, nt = nt->sled);

    // ���� ������� � ����� ������� ��� ���� � ������, ������� �� �������
    if (nt && strcmp(nt->strana, strana) == 0) return;

    // ��������� ������ ��� ������ �������� ������
    New = (struct sp *) malloc(sizeof(struct sp));

    // ����������� �������� ������ � ����� ������� ������
    strcpy(New->strana, strana);

    // ��������� ���������� �������� ��� ������ ��������
    New->sled = nt;

    // ������������� ������� � ���������� ������� ��� ������ ��������
    New->time = 0;
    New->k = 0;

    // ������ �� ���� �������, ����� ����� ������ �� ��� �� ������ � �������� ����� � ����������
    for (i = 0; i < NC; i++) {
        if (strcmp(film[i].strana, strana) == 0) {
            New->time += film[i].time;
            New->k += 1;
        }
    }

    // ���� ������� ����������� � �������� ������, ��������� ���������� �������
    if (z)
        z->sled = New;

    // ��������� ����������� �������� ��� ������ ��������
    New->pred = z;

    // ���� ������� ����������� � �������� ������, ��������� ��������� �������
    if (nt)
        nt->pred = New;

    // ��������� ���������� �������� ��� ������ ��������
    New->sled = nt;

    // ���� ������� ����������� � ������ ������, ��������� ��������� �� ������ ������
    if (!z)
        *spisok = New;

    // ����� �� �������
    return;
}

//���������. ���������� ����������� ������� � ������ ������
void diagram(struct z *film, struct sp** spisok, int NC){
	struct sp *nt;
	int len,i,NColor;
	char str1[20];
	char str2[20];

	System::ConsoleColor Color;
	// ��������� ����� ������ ������� �� ������ � ����� ���� �� �����
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::Clear();

	Color=ConsoleColor::Black; NColor=0;
	// ������ �� ������ spisok � ����� ���������� � ������� � �� �������� �������
	for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++){
		sprintf(str1,"%s",nt->strana);
		sprintf(str2,"%3.1f%%",(nt->k*100./NC));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor=ConsoleColor::White;
		Console::CursorLeft=5; Console::CursorTop=i+1;
		printf(str1);  // ����� �������� ������
		Console::CursorLeft=20;
		printf("%s",str2); // ����� �������� �������
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=30;
		// ����� ��������� � ��������� �������
		for(len=0; len<nt->k*100/NC; len++) 
			printf(" ");
		if(NColor==14){
				Color=ConsoleColor::Black; 
				NColor=0; 
			}
	}
	getch();
	return;
}
//������ ������� � ������������ 18+ � ������������� ������ 115 ���
void spisok_6(struct z* film, int NC){
	Console::BackgroundColor=ConsoleColor::Yellow; // ��������� ����� ���� ������� �� ������
	Console::ForegroundColor=ConsoleColor::Black;// ��������� ����� ������ ������� �� ������
	Console::Clear();
	Console::CursorLeft=3;
	Console::CursorTop=2;
	printf("������ � ������������ 18+ � ������������� ������ 115 ���:\n");
	printf("=========================================================================\n");
	int i,k=0;
	for(i=1;i<NC;i++){
		// ��������, ��� ����� ����� ����������� 18+ � ������������ ������ 115 �����
		if (strcmp(film[i].age,"18+")==0 && (film[i].time >=115)){
			k++;
			// ����� ���������� � ������
			printf("\n  %-20s %-12s %-8s %ld ���",film[i].name,film[i].zhanr,film[i].age, film[i].time);
		}
	}
	
	getch();
}
//������ � ���������� ������������������, �� ������� �������� (������� ������ - ����� ������������)
void dop_vopros_4(struct z* film, int NC){
	int i,j;
	bool check = false;
	for(i=0;i<NC;i++){
		for(j=i+1;j<NC;j++){
			 // ��������, ��� ������ ������������ ������� ������ � ����������������� ����������
			if ((strcmp(film[i].strana,film[j].strana)!=0) && (film[i].time==film[j].time)){
				check = true;
				// ��������� ����� ������ ������� �� ����� � ����� ���� �� �����-����������
				Console::ForegroundColor=ConsoleColor::White;
				Console::BackgroundColor=ConsoleColor::DarkMagenta;
				Console::CursorLeft=10;
				Console::CursorTop=15;
				// ����� ���������� � �������
				printf("� ������� \"%s\" � \"%s\" ", film[i].name,film[j].name);
				printf("���������� ����������������� %ld ���, ",film[i].time);
				Console::CursorLeft=10;
				Console::CursorTop=16;
				 // ����� ����� ������������ �������
				printf("�� ������ ������������ %s � %s",film[i].strana, film[j].strana);
								
				getch();
				return;
			}
		}
	}
	// ���� ������ ������ �� �������
	if(check == false){
		Console::Clear;
		// ��������� ����� ������ ������� �� ����� � ����� ���� �� �����-����������
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::DarkMagenta;
		Console::CursorLeft=10;
		Console::CursorTop=15;
		// ����� ��������� � ���, ��� ������ �� �������
		printf("��� ������� �� �������!");}
		
_getch();
}
// ����� ������� �� ������� (���� �������� ������ � ����������) 
void poisk(struct z* film, int NC){
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::Clear();
	int i, kolvo=0;
	char search[20];
	
	printf (" ������ ������� �� ���������� ������ \n");
	printf (" ������� �������� ������ :");

	Console::CursorLeft+=1;
	Console::CursorVisible = true; //�������� ������
	SetConsoleCP(1251); //��� ���������� ������� ��������
	scanf("%s",search);//��������� ������ �����
	SetConsoleCP(866); //��������� �������, ����� ����� �������� ������� �������
	Console::CursorVisible = false;
	
	printf("\n|   �������� ������   |     ����    |  ���  | ������������ | ������� | ������� |");
	printf("\n|==============================================================================|");
	
	for (i=0;i<NC;i++){
		// ��������, ��� ����� ���������� � ��������� ������
		if(strcmp(film[i].strana,search)==0){
			printf("\n| %-20s| %-12s| %-6d| %9ld ���| %-8.2f| %-8s|",
			film[i].name,
			film[i].zhanr,
			film[i].year,
			film[i].time,
			film[i].rating,
			film[i].age);
			kolvo++;
		}
	}
	// ���� ������ �� ��������� ������ �� �������
	if (kolvo==0) 
		printf("\n������ �� ������ ������ �� �������");
	// ���� ������ �� ��������� ������ �������
	if (kolvo) 
		printf("\n\n���-�� ������� �� ������������ ������: %-7d",kolvo);
	getch();
	return ;
}
