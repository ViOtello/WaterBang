#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "WB_Headers.h"

using namespace std;
const char empty_field = ' '; //������
const char ship = 'O'; // ������� ��� ������ �������
const char ship_destroyed = 'X'; //���������
const char ship_completely_destroyed = '#';
const char miss = '.'; // ������


void indent() { // ������ ������
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void print_field(char** field) // ����� ����
{
	cout << "  ";
	for (int i = 0; i < 10; i++)
		cout << char('a' + i) << ' '; // ���� � ������� ��������� 1 ��������� �� ��������� ������
	cout << "\n";
	for (int i = 0; i < 10; i++)
	{
		cout << i << ' ';
		for (int j = 0; j < 10; j++)
			cout << field[i][j] << ' ';
		cout << "\n";
	}
}
bool check_1_direction(char** field, int x, int y, int dx, int dy)
{
	for (int i = 0; i < 3; i++)
	{
		x += dx;
		y += dy;
		if (cell_inside_the_field(field, x, y))
		{
			if (field[x][y] == ship)
				return true;
			if ((field[x][y] == empty_field) || (field[x][y] == miss))
				return false;
		}
	}
	return false;
}
void repaint_1_direction(char** field, int x, int y, int dx, int dy)
{
	for (int i = 0; i < 3; i++)
	{
		x += dx;
		y += dy;
		if (cell_inside_the_field(field, x, y))
		{
			if (field[x][y] == ship_destroyed)
				field[x][y] = ship_completely_destroyed;
			if ((field[x][y] == empty_field) || (field[x][y] == miss))
				return;
		}
	}
}

bool shoot(char** field, char** enemy_field_my_wiev, int x, int y) // ������ ���������� ��������
{
	if ((field[x][y] == ship) || (field[x][y] == miss))
	{
		if (field[x][y] == ship)
		{
			field[x][y] = ship_destroyed;
			enemy_field_my_wiev[x][y] = ship_destroyed;
			cout << "������� ������!" << "\n";
			bool flag = false;
			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
					if (i * j == 0)
						if (check_1_direction(field, x, y, i, j) == true)
							flag = true;
			if (flag == false)
				for (int i = -1; i <= 1; i++)
					for (int j = -1; j <= 1; j++)
						if (i * j == 0)
						{
							repaint_1_direction(field, x, y, i, j);
							repaint_1_direction(enemy_field_my_wiev, x, y, i, j);
						}
		} // � ����������� �������� �� ����������� ������� ���������
		else
			cout << "������. �� �� ������ ���������� � ��� �����. ���������� ��� ���" << "\n";
		return true;
	}
	else
	{
		field[x][y] = miss;
		enemy_field_my_wiev[x][y] = miss;
		cout << "������" << "\n";
		return false;
	}
}

void init_field(char**& my_field) // ������� ������������� ������ ������� �����
{
	my_field = new char* [10];
	for (int i = 0; i < 10; i++)
		my_field[i] = new char[10];
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			my_field[i][j] = empty_field;
}

void init_fields(char**& my_field, char**& enemy_field, char**& my_field_enemy_wiev, char**& enemy_field_my_wiev)
{ // ��� ���� ����� ������������� �������
	init_field(my_field); // ��� � ���� ���� ����
	init_field(my_field_enemy_wiev); // ��� ��������� ����� ��� ����
	init_field(enemy_field); // ��� ��������� ����� ����
	init_field(enemy_field_my_wiev); // ��� � ���� ���� ����������
}

bool is_game_over(char player_name[], char**& field) {
	int game_over = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j] == ship) {
				game_over++;
				break;
			}
		}
	}
	if (game_over == 0) {
		for (int i = 0; i < 10000; i++) {
			cout << "����� " << player_name << " �������";
		}
		return false;
	}
	return true;
}

void ask_the_player(int& x, int& y) //������ ������ �� ������������ �����
{
	cout << "�� ����� ����������� �� ������ ��������?" << "\n";
	cout << "������� \"x\" (������) and \"y\" (������) :" << "\n";
	char c;
	cin >> x >> c;
	y = c - 'a'; // ������ ����� �� ������

}
void one_player_turn(char player_name[], char** my_field, char** enemy_field, char** enemy_field_my_wiev)
{
	system("pause");
	indent();
	system("pause");
	cout << "��� ������ " << player_name << "\n";

	int x, y;
	cout << "���� ����" << "\n";
	print_field(my_field);
	cout << "��������� ����" << "\n";
	print_field(enemy_field_my_wiev);
	ask_the_player(x, y);
	while (shoot(enemy_field, enemy_field_my_wiev, x, y)) // ���� ����� ����� ��� ���
	{
		cout << "��������� ���� ����� �����" << "\n";
		print_field(enemy_field_my_wiev);
		ask_the_player(x, y);
	}
	cout << "��������� ���� ����� �����" << "\n"; // ���� �� ����� ������ ���������
	print_field(enemy_field_my_wiev);
}

bool cell_inside_the_field(char** my_field, int x, int y) // ������� �������� ���������� ������ ������ � ����
{
	if ((x >= 0) && (x < 10) && (y >= 0) && (y < 10))
		return true;
	return false;
}

bool check_ship(char** my_field, int x, int y, int size_x, int size_y) // ������� �������� ������� �� ������ �� ������� ���� � �� ������� ������������
{
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			if (!cell_inside_the_field(my_field, x + i, y + j)) // ���� ������ �� � ����
				return false;
	return true;
}

bool check_ship_surrounding(char** my_field, int x, int y, int size_x, int size_y) // �������� �� ���������� � �������� ������ ���� �������
{
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			if (cell_inside_the_field(my_field, x + i, y + j)) {
				if (my_field[x + i][y + j] == ship)
					return false;
			}
	return true;
}

void put_ships(char** my_field) //������� ����������� ��������
{
	for (int i = 4; i >= 1; i--)
		for (int j = 0; j < (5 - i); j++)
		{
			bool flag = false;
			while (flag == false)
			{
				bool horizontal = 0 + rand() % 2; //��������� ��������� ����������� �������
				int x, y;
				// ��������� ��������� ��������� ������ �������
				x = rand() % 10;
				y = rand() % 10;
				if (!horizontal)
				{// ���������� ������������� �������
					if (check_ship(my_field, x, y, i, 1) && (check_ship_surrounding(my_field, x - 1, y - 1, i + 2, 3)))
					{
						for (int k = 0; k < i; k++)
							my_field[x + k][y] = ship;
						flag = true;
					}
				}
				else // ����������� ��������������� �������
				{
					if (check_ship(my_field, x, y, 1, i) && (check_ship_surrounding(my_field, x - 1, y - 1, 3, i + 2)))
					{
						for (int k = 0; k < i; k++)
							my_field[x][y + k] = ship;
						flag = true;
					}
				}
			}
		}
	print_field(my_field);
}