#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "WB_Headers.h"
using namespace std;

// обьявление глобальных переменных
char fn[20];
char sn[20];          // fn == firstname(имя первого игрока)    // sn == secondname(имя второго игрока)


int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	setlocale(LC_ALL, "russian");

	srand(time(NULL));

	cout << "\t\tПриветствую Вас, игроки в морской бой!" << "\n\n";
	rules();
	cout << "\n\t1й игрок, как Вас зовут?" << "\n\n";
	cin >> fn;
	cout << "\tПривет, " << fn << "\n\n";
	cout << "\t2й игрок, как Вас зовут?" << "\n\n";
	cin >> sn;
	cout << "\tПривет, " << sn << "\n\n";

	indent();
	char** my_field;
	char** my_field_enemy_wiev;
	char** enemy_field;
	char** enemy_field_my_wiev;
	init_fields(my_field, enemy_field, my_field_enemy_wiev, enemy_field_my_wiev);
	indent();
	system("pause");
	cout << "\n\n\n\nПоле игрока " << fn << ". Вы первый игрок" << "\n\n\n";
	put_ships(my_field);
	system("pause");
	indent();
	system("pause");
	cout << "\n\n\n\nПоле игрока " << sn << ". Вы второй игрок" << "\n\n\n";
	put_ships(enemy_field);
	system("pause");
	indent();
	bool game_continue_flag = true;
	do
	{
		one_player_turn(fn, my_field, enemy_field, enemy_field_my_wiev);
		game_continue_flag = is_game_over(fn, enemy_field); //передача имени и вражеского поля
		one_player_turn(sn, enemy_field, my_field, my_field_enemy_wiev);
		game_continue_flag = is_game_over(sn, my_field); //передача имени и моего поля
	} while (game_continue_flag);

	for (int i = 0; i < 10; i++) // удаление выделенной памяти под динамические массивы
	{                               // которые для полей
		delete[]my_field[i]; // сначала удаляем внутренности
		delete[]my_field_enemy_wiev[i];
		delete[]enemy_field[i];
		delete[]enemy_field_my_wiev[i];
	}
	delete[]my_field; // затем удаляем внешку
	delete[]my_field_enemy_wiev;
	delete[]enemy_field;
	delete[]enemy_field_my_wiev;
	indent();
	cout << "Игра окончена";
}