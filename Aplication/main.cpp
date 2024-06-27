#include <Windows.h>
#include <iostream>
#include "shop.h"

using namespace std;

int main()
{
    Logo();
    SetConsoleTitle(L"FEDOT");
    system("color F0");

    NumberOfDaysBetweenDates(7, 6, 2022, 1, 9, 2022);

    HANDLE hWnd = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
    INPUT_RECORD InputRecord;                              // используется для возвращения информации о входных сообщениях в консольном входном буфере
    DWORD Events;                                          // unsigned long

    /*Запретить выделение консоли*/
    DWORD prev_mode;
    GetConsoleMode(hWnd, &prev_mode);
    SetConsoleMode(hWnd, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleMode(hWnd, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши
    
    Menu(); 

    while (1)
    {
        ReadConsoleInput(hWnd, &InputRecord, 1, &Events); // считывание

        Logics(InputRecord.Event.MouseEvent.dwMousePosition.X,
                InputRecord.Event.MouseEvent.dwMousePosition.Y, 
                (int)InputRecord.Event.MouseEvent.dwButtonState);
    }

    return 0;
}

// ПЛАНЫ
//
// 1 - Добавить подсказки при использовании программы впервые
// 2 - Добавить вопросительный знак, помогающий разобраться почему файл выделен красным
// X_X Очистить консоль после меню
// 4 - ??? Можно ли обновлять таблицу нажатием на её название
// X_X Добавить сдвиг меню, если приближается к нижней границе
// 6 - При удалении добавить функциональность "Enter" и "Esc"
// 7 - 
// 
// X_X Сортировки 
// X_X Сохранине файлов
// X_X Нахождение самого дорогого/дешового продукта
// X_X Общая сумма продуктов
// X_X Исправить 9-ое задание
// X_X Функция добавления по позиции
// X_X Исправить создание нового файла
// X_X Доработать защиту от дурака для продуктов
// X_X Добавить эдит для категории
// X_X Сделать таблички Дорогие продукты | Общая стоимость | Дешевые продукты
