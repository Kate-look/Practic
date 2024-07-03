// Osnova_kurs.cpp: главный файл проекта.

#include "stdafx.h" //подключение библиотек 
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

#define ENTER 13 //обозначение кнопок
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79

const char dan[9][75]={
	"1. Какой фильм самый долгий?                                         ",
	"2. Какой фильм был выпущен раньше всех?                              ",
	"3. Список фильмов в жанре комедия c рейтингом выше 7.0               ",
	"4. Фильмы с одинаковой продолжительностью, но разными странами       ",
	"5. Алфавитный список стран со средней продолжительностью фильмов     ",
	"6. Список фильмов с ограничением 18+ и длительностью больше 115 мин  ",
	"7. Диаграмма. Процентное соотношение фильмов в каждой стране         ",
	"8. Поиск фильмов по странам                                          ",
	"Выход                                                                ",
}; //задание списка вопросов - пунктов меню
const char gran[] = "|=====================|=============|=======|==============|=========|===================|=========|";
const char nazv[] = "|   Название фильма   |     Жанр    |  Год  | Длительность | Рейтинг |      Страна       | Возраст |";
const char BlankLine[ ]="                                                                       ";
struct z {
	char name[30]; //название фильма
	char zhanr[20]; //жанр
	int year; //год выпуска
	long time; //продолжительность
	float rating; //рейтинг
	char strana[20]; //страна производитель
	char age[4]; //возростное ограничение
}; //шаблон структуры для исходных данных
struct sp {
	char strana[20];
	long time;
	int k;
	struct sp* sled;
	struct sp* pred;
};//шаблон, глобальное описание структуры двустроннего списка

int menu(int); //указание шаблонов используемых функций
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
	//на локальном уровне осуществляем открытие файла,
	//считываем данные из файла в выделенную память
    int i,n;
	int NC; //количество позиций задано глобально
	FILE *in, *out;
	struct z *films;
	setlocale(LC_CTYPE,"Russian"); //поддержка русского языка
	Console::CursorVisible::set(false); //отключаем выдимость курсора
	Console::BackgroundColor=ConsoleColor::White; 
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BufferHeight=Console::WindowHeight;//установка размера буфера по высоте
	Console::BufferWidth=Console::WindowWidth; //установка размера буфера по ширине

	if((in=fopen("кино.txt","r"))==NULL){ //попытка открыть файл
		printf("\nФайл кино.txt не открыт !"); //при неудачном открытии выводим соообщение “Файл не открыт!”
		getch(); exit(1);
	}
	
	fscanf(in,"%d",&NC);
	films=(struct z*)malloc(NC*sizeof(struct z)); //выделяем память

	for(i=0;i<NC;i++) //считываем данные из списка
		fscanf(in,"%s%s%d%ld%f%s%s",
		films[i].name,
		films[i].zhanr,
		&films[i].year,
		&films[i].time,
		&films[i].rating,
		films[i].strana,
		films[i].age);

	struct sp *spisok = NULL;
	//проходим по всем фильмам и добавляем их в список
	for(i=0;i<NC;i++)
		vstavka(films, films[i].strana, &spisok, NC);

	printf(gran);
	printf("\n");
	printf(nazv);
	printf("\n");
	printf(gran);

	for(i=0;i<NC;i++) //выводим данные из списка на экран
		printf("\n| %-20s| %-12s| %-6d| %9ld мин| %-8.2f| %-18s| %-8s|",
		films[i].name,
		films[i].zhanr,
		films[i].year,
		films[i].time,
		films[i].rating,
		films[i].strana,
		films[i].age);

	printf("\n");
	printf(gran);

	out=fopen("кино_запись.txt","w");

	fprintf(out,gran);
	fprintf(out,"\n");
	fprintf(out,nazv);
	fprintf(out,"\n");
	fprintf(out,gran);

	for(i=0;i<NC;i++) //выводим данные из списка в файл
		fprintf(out,"\n| %-20s| %-12s| %-6d| %9ld мин| %-8.2f| %-18s| %-8s|",
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

	while(1) //в цикле создаем область для вопросов и окрашиваем ее в цвета
		//устанавливаем для букв цвет и подсветку для выбранного вопроса
	{
		Console::ForegroundColor=ConsoleColor::Gray;
		Console::BackgroundColor=ConsoleColor::DarkMagenta;
		Console::Clear();
		Console::ForegroundColor=ConsoleColor::Red;
		Console::BackgroundColor=ConsoleColor::Cyan;
		Console::CursorLeft=20;
		Console::CursorTop=3;
		cprintf("Выберите вопрос при помощи стрелок и нажмите ENTER");
		Console::ForegroundColor=ConsoleColor::Black;		
		Console::CursorLeft=10; //первая точка, откуда будем закрашивать область меню                          
		Console::CursorTop=4;
		printf(BlankLine);

		for(i=0;i<9;i++) //размещение вопросов 
		{
			Console::CursorLeft=10;
			Console::CursorTop=i+5;
			printf(" %s ",dan[i]);
		}
		Console::CursorLeft=10; //последняя точка,где будет заканчиваться выделенная область под меню 
		Console::CursorTop=13;
		printf(BlankLine);

		n = menu(9);  //выбор вопроса в меню 
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
	} // конец while(1)... 
	return 0;
} // конец main() 
int menu(int n) //n=9 
{
	int y1=0,y2=n-1; //устанавливаем выделение для строчки 
	char c=1;
	while (c!=ESC)  //при нажатии кнопки ESC, меню закроется 
	{
		switch(c) //программирование кнопок
		{
			case DOWN: y2=y1; y1++; break; //перемещение вниз
			case UP: y2=y1; y1--; break; //перемещение вверх
			case ENTER: return y1+1; //выбор вопроса
			case HOME: y2=y1; y1=0; break; //переход в начало списка
			case END: y2=y1; y1=n-1; break; //переход в конец списка
		}
	if(y1>n-1){y2=n-1;y1=0;} //условие,когда срабатывает кнопка DOWN ; y1 след; у2 текущая
	if(y1<0) {y2=0;y1=n-1;} //условие,когда срабатывает кнопка UP 
	Console::ForegroundColor=ConsoleColor::White; //при выборе воспроса окрасить буквы белым цветом
	Console::BackgroundColor=ConsoleColor::DarkBlue; //при выборе воспроса фон за буквами окрасить голубым цветом
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);

	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Cyan;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
	}// конец while(c!=ESC)... 
exit(0);
}


//Список фильмов в жанре комедия c рейтингом выше 7.0
void spisok_3(struct z* film, int NC){
	Console::BackgroundColor=ConsoleColor::Yellow; // Устанавливаем цвет фона консоли на желтый
	Console::ForegroundColor=ConsoleColor::Black; // Устанавливаем цвет текста консоли на черный
	Console::Clear();

	Console::CursorTop=2;
	printf("   Список фильмов в жанре комедия c рейтингом выше 7.0\n");

	printf("   ===================================================\n");

	int i;
	for (i=1;i<NC;i++)
		// Проверяем, что жанр фильма "комедия" и рейтинг выше 7.0
		if ((strcmp(film[i].zhanr,"комедия")==0) && (film[i].rating >= 7.0))
			// Выводим информацию о фильме, если он подходит по жанру и рейтингу
			printf("   %-20s%-15s%-8.2f\n",film[i].name,film[i].zhanr,film[i].rating);
	getch();
}

// Какой фильм самый долгий? (функция поиска максимума) 
void maxim_1(struct z* film, int NC){
	int i=0; 
	// Объявление структуры для хранения информации о фильме с самым длинным продолжительностью
	struct z best;
	// Копируем название первого фильма в структуру best
	strcpy(best.name,film[0].name);
	// Копируем продолжительность первого фильма в структуру best
	best.time=film[0].time;
	for (i=1;i<NC;i++)
		if (film[i].time > best.time){ //условие поиска максимального количества 
			strcpy(best.name,film[i].name);
			best.time=film[i].time;
		}
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkMagenta;
	Console::CursorLeft=10; //задаем область, где будет выведено макс.количество  
	Console::CursorTop=15;
	printf("Самая большая продолжительность %ld минут",best.time); // Вывод максимального количества 
	Console::CursorLeft=10; //зада?м область,где будет выведено название фильма 
	Console::CursorTop=16;
	printf("у фильма \"%s\"",best.name);//Вывод фильма
	getch();
}

//Какой фильм был выпущен раньше всех?
void first_2(struct z* film, int NC){
	int i=0; 
	struct z best; // Объявление структуры для хранения информации о фильме, вышедшем раньше всех
	strcpy(best.name,film[0].name); // Копируем название первого фильма в структуру best
	best.year=film[0].year; // Копируем год первого фильма в структуру best
	for (i=1;i<NC;i++)
		if (film[i].year < best.year){ //сравнение текущего фильма и фильма из структуры best
			strcpy(best.name,film[i].name);
			best.year=film[i].year;
		}
	Console::ForegroundColor=ConsoleColor::White;// Устанавливаем цвет текста консоли на белый
	Console::BackgroundColor=ConsoleColor::DarkMagenta;// Устанавливаем цвет фона консоли на темно-фиолетовый
	Console::CursorLeft=10;//задаем область вывода
	Console::CursorTop=15;
	printf("В %d году был вышущен фильм",best.year); // Выводим информацию о годе выхода первого фильма
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("\"%s\"",best.name); // Выводим название первого вышедшего фильма
	getch();
}
// Алфавитный список стран со средней продолжительностью фильмов (функция работы с двусторонним списком) 
void alfalist(struct z* film, struct sp** spisok, int NC){ //Формирование списка 
	int i;
	struct sp* nt;
	struct sp* z;
	
	// Установка цвета текста консоли на желтый и цвета фона на черный
	Console::ForegroundColor=ConsoleColor::Yellow;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();

	Console::Clear();
	printf("\n Алфавитный список стран со средней продолжительностью фильмов");
	printf("\n =============================================================");

	// Проход по списку spisok и вывод информации о странах и их средней продолжительности фильмов
	for(nt=*spisok; nt!=0; nt=nt->sled)
		printf("\n %-20s %3d мин",nt->strana,nt->time/nt->k);
	Console::CursorTop=12;
	Console::CursorLeft=0;
	printf(" ==============================================================\n");
	printf(" Обратный список стран со средней продолжительностью фильмов\n");
	printf(" =============================================================\n");

	// Перемещение указателя nt в конец списка и вывод информации в обратном порядке
	for(nt=*spisok,z=0; nt!=0;z=nt, nt=nt->sled);
	for(nt=z,i=5; nt!=0; nt=nt->pred,i++){	
		printf(" %-20s %3d мин\n",nt->strana,nt->time/nt->k);
	}
  	getch();
}

// Функция для вставки элементов в список с учетом алфавитной сортировки
void vstavka(struct z* film, char* strana, struct sp** spisok, int NC) {
    int i;
    struct sp *New, *nt, *z = 0;

    // Проход по списку spisok до тех пор, пока не найдено место для вставки или не достигнут конец списка
    for (nt = *spisok; nt != 0 && strcmp(nt->strana, strana) < 0; z = nt, nt = nt->sled);

    // Если элемент с такой страной уже есть в списке, выходим из функции
    if (nt && strcmp(nt->strana, strana) == 0) return;

    // Выделение памяти для нового элемента списка
    New = (struct sp *) malloc(sizeof(struct sp));

    // Копирование названия страны в новый элемент списка
    strcpy(New->strana, strana);

    // Установка следующего элемента для нового элемента
    New->sled = nt;

    // Инициализация времени и количества фильмов для нового элемента
    New->time = 0;
    New->k = 0;

    // Проход по всем фильмам, чтобы найти фильмы из той же страны и обновить время и количество
    for (i = 0; i < NC; i++) {
        if (strcmp(film[i].strana, strana) == 0) {
            New->time += film[i].time;
            New->k += 1;
        }
    }

    // Если элемент вставляется в середину списка, обновляем предыдущий элемент
    if (z)
        z->sled = New;

    // Установка предыдущего элемента для нового элемента
    New->pred = z;

    // Если элемент вставляется в середину списка, обновляем следующий элемент
    if (nt)
        nt->pred = New;

    // Установка следующего элемента для нового элемента
    New->sled = nt;

    // Если элемент вставляется в начало списка, обновляем указатель на начало списка
    if (!z)
        *spisok = New;

    // Выход из функции
    return;
}

//Диаграмма. Процентное соотношение фильмов в каждой стране
void diagram(struct z *film, struct sp** spisok, int NC){
	struct sp *nt;
	int len,i,NColor;
	char str1[20];
	char str2[20];

	System::ConsoleColor Color;
	// Установка цвета текста консоли на черный и цвета фона на белый
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::Clear();

	Color=ConsoleColor::Black; NColor=0;
	// Проход по списку spisok и вывод информации о странах и их проценте фильмов
	for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++){
		sprintf(str1,"%s",nt->strana);
		sprintf(str2,"%3.1f%%",(nt->k*100./NC));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor=ConsoleColor::White;
		Console::CursorLeft=5; Console::CursorTop=i+1;
		printf(str1);  // Вывод названия страны
		Console::CursorLeft=20;
		printf("%s",str2); // Вывод процента фильмов
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=30;
		// Вывод диаграммы с процентом фильмов
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
//Список фильмов с ограничением 18+ и длительностью больше 115 мин
void spisok_6(struct z* film, int NC){
	Console::BackgroundColor=ConsoleColor::Yellow; // Установка цвета фона консоли на желтый
	Console::ForegroundColor=ConsoleColor::Black;// Установка цвета текста консоли на черный
	Console::Clear();
	Console::CursorLeft=3;
	Console::CursorTop=2;
	printf("Фильмы с ограничением 18+ и длительностью больше 115 мин:\n");
	printf("=========================================================================\n");
	int i,k=0;
	for(i=1;i<NC;i++){
		// Проверка, что фильм имеет ограничение 18+ и длительность больше 115 минут
		if (strcmp(film[i].age,"18+")==0 && (film[i].time >=115)){
			k++;
			// Вывод информации о фильме
			printf("\n  %-20s %-12s %-8s %ld мин",film[i].name,film[i].zhanr,film[i].age, film[i].time);
		}
	}
	
	getch();
}
//Фильмы с одинаковой продолжительностью, но разными странами (Сложный вопрос - поиск соответствия)
void dop_vopros_4(struct z* film, int NC){
	int i,j;
	bool check = false;
	for(i=0;i<NC;i++){
		for(j=i+1;j<NC;j++){
			 // Проверка, что страны производства фильмов разные и продолжительность одинаковая
			if ((strcmp(film[i].strana,film[j].strana)!=0) && (film[i].time==film[j].time)){
				check = true;
				// Установка цвета текста консоли на белый и цвета фона на темно-фиолетовый
				Console::ForegroundColor=ConsoleColor::White;
				Console::BackgroundColor=ConsoleColor::DarkMagenta;
				Console::CursorLeft=10;
				Console::CursorTop=15;
				// Вывод информации о фильмах
				printf("У фильмов \"%s\" и \"%s\" ", film[i].name,film[j].name);
				printf("одинаковая продолжительность %ld мин, ",film[i].time);
				Console::CursorLeft=10;
				Console::CursorTop=16;
				 // Вывод стран производства фильмов
				printf("но страны производства %s и %s",film[i].strana, film[j].strana);
								
				getch();
				return;
			}
		}
	}
	// Если нужные фильмы не найдены
	if(check == false){
		Console::Clear;
		// Установка цвета текста консоли на белый и цвета фона на темно-фиолетовый
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::DarkMagenta;
		Console::CursorLeft=10;
		Console::CursorTop=15;
		// Вывод сообщения о том, что фильмы не найдены
		printf("Нет фильмов по запросу!");}
		
_getch();
}
// Поиск фильмов по странам (Ввод названия страны с клавиатуры) 
void poisk(struct z* film, int NC){
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Yellow;
	Console::Clear();
	int i, kolvo=0;
	char search[20];
	
	printf (" Список фильмов из конкретной страны \n");
	printf (" Введите название страны :");

	Console::CursorLeft+=1;
	Console::CursorVisible = true; //включаем курсор
	SetConsoleCP(1251); //для считывания русских символов
	scanf("%s",search);//вписываем нужный текст
	SetConsoleCP(866); //кодировка консоли, чтобы могли выводить русские символы
	Console::CursorVisible = false;
	
	printf("\n|   Название фильма   |     Жанр    |  Год  | Длительность | Рейтинг | Возраст |");
	printf("\n|==============================================================================|");
	
	for (i=0;i<NC;i++){
		// Проверка, что фильм произведен в введенной стране
		if(strcmp(film[i].strana,search)==0){
			printf("\n| %-20s| %-12s| %-6d| %9ld мин| %-8.2f| %-8s|",
			film[i].name,
			film[i].zhanr,
			film[i].year,
			film[i].time,
			film[i].rating,
			film[i].age);
			kolvo++;
		}
	}
	// Если фильмы из введенной страны не найдены
	if (kolvo==0) 
		printf("\nФильмы из данной страны не найдены");
	// Если фильмы из введенной страны найдены
	if (kolvo) 
		printf("\n\nКол-во фильмов из интересующей страны: %-7d",kolvo);
	getch();
	return ;
}
