#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <Windows.h>
#include "WB_Headers.h"
using namespace std;
string fn, sn;          // fn == firstname(имя первого игрока)    // sn == secondname(имя второго игрока)


int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	setlocale(LC_ALL, "russian");
	cout << "\t\tПриветствую Вас, игроки в морской бой!" << "\n\n";
	rules();
	cout << "\n\t1й игрок, как Вас зовут?" << "\n\n";
	cin >> fn;
	cout << "\tПривет, " << fn << "\n\n";
	cout << "\t2й игрок, как Вас зовут?" << "\n\n";
	cin >> sn;
	cout << "\tПривет, " << sn << "\n\n";
	indent();
	StartPadFirstGamer();
	StartPadSecondGamer();
}