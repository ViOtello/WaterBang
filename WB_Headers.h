#pragma once
void rules();
void indent();
void print_field(char** field);
bool shoot(char** field, char** enemy_field_my_wiev, int x, int y);
void init_field(char**& my_field);
void init_fields(char**& my_field, char**& enemy_field, char**& my_field_enemy_wiev, char**& enemy_field_my_wiev);
void ask_the_player(int& x, int& y);
void one_player_turn(char player_name[], char** my_field, char** enemy_field, char** enemy_field_my_wiev);
bool cell_inside_the_field(char** my_field, int x, int y);
bool check_ship(char** my_field, int x, int y, int size_x, int size_y);
bool check_ship_surrounding(char** my_field, int x, int y, int size_x, int size_y);
void put_ships(char** my_field);
bool is_game_over(char player_name[], char**& field);