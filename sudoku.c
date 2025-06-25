#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 9 //само поле судоку
#define SUBGRID 3 //подкасты

// Инициализация пустой доски
void init_Board(int board[SIZE][SIZE]){
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            board[i][j] = 0; //обнуление доски
        }
    }
}
// Проверка, безопасно ли разместить число в данной позиции
bool is_Safe(int board[SIZE][SIZE], int row, int col, int num){
    // Проверка строки и столбца
    for(int x = 0; x<SIZE; x++){
        if(board[row][x] == num || board[x][col] == num){
            return false;
        }
    }
    // Проверка подквадрата 3x3
    int new_Row = row - row % SUBGRID;
    int new_Col = col - col % SUBGRID;
    for(int i = 0; i<SUBGRID; i++){
        for(int j = 0; j<SUBGRID; j++){
            if(board[i + new_Row][j + new_Col] == num){
                return false;
            }
        }
    }
    return true;
}
// Рекурсивная функция для заполнения доски
bool fill_board(int board[SIZE][SIZE], int row, int col){
    //проверка строк и столбцов соответственно
    if(row == SIZE - 1 && col == SIZE){
        return true;
    }
    //проверка столбцов
    if(col == SIZE){
        row++; //строка увеличивается
        col = 0; //столбец обнуляется
    }
    if(board[row][col] != 0){
        return fill_board(board, row, col + 1);
    }
    for(int num = 1; num<=SIZE; num++){
        //проверяем на безопасность
        if(is_Safe(board, row, col, num)){
            board[row][col] = num; // присваиваем номер
            if(fill_board(board, row, col+1)){
                return true; //вывод правды
            }
            board[row][col] = 0; //обнуление доски
        }
    }
    return false;
}
void fill_Diagonal_Subgrid(int board[SIZE][SIZE], int row, int col) {
    int num;
    for(int i = 0; i < SUBGRID; i++) {
        for(int j = 0; j < SUBGRID; j++) {
            do {
                num = rand() % SIZE + 1;
            } while(!is_Safe(board, row + i, col + j, num));
            board[row + i][col + j] = num;
        }
    }
}
// Создание решенной доски Судоку
void generate_Solved_Sudoku(int board[SIZE][SIZE]) {
    srand(time(0));
    // Заполняем диагональные подквадраты 3x3
    for(int i = 0; i<SIZE; i+= SUBGRID){
        fill_Diagonal_Subgrid(board, i, i);
    }
    // Заполняем остальную часть доски
    fill_board(board, 0, 0);
}
// Удаление чисел для создания головоломки
void create_Puzzle(int board[SIZE][SIZE], int difficulty){

    int remove_num; //уровень сложности

    switch (difficulty){
        case 1: remove_num(40); break; //легкий
        case 2: remove_num(50); break; //средний
        case 3: remove_num(60); break; //сложный
        default: remove_num(45);
    }
    //проверка уровня сложности
    while(remove_num > 0){
        int row = rand() % SIZE; //для строк
        int col = rand() % SIZE; //для столбцов
        
        //проверка всей доски целиком
        if(board[row][col] != 0){
            board[row][col] = 0;
            remove_num--; //уровень уменьшается
        }
    }
}
// Печать доски
void print_Board(int board[SIZE][SIZE]){
    //проверка строк
    for(int i = 0; i<SIZE; i++){
        if(i % SUBGRID == 0 && i != 0){
            printf("------+-------+------\n");
        }
        //проверка столбцов
        for(int j = 0; j<SIZE; j++){
            if(j % SUBGRID && j != 0){
                printf("| ");
            }
            //проверка всей доски
            if(board[i][j] == 0){
                printf(". ");
            }else{
                printf("%d", board[i][j]); //вывод доски
            }
        }
        printf("\n");
    }
}
int main(){
    int board[SIZE][SIZE]; //сама доска

    init_Board(board); // Инициализация пустой доски
    generate_Solved_Sudoku(board); // Создание решенной доски Судоку
    printf("Полностью решенное Судоку:\n");
    print_Board(board); //печать доски

    create_Puzzle(board, 2); // Средний уровень сложности
    printf("\nГоловоломка Судоку:\n");
    print_Board(board); //печать доски
    
    return 0;
}
