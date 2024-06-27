#include "shop.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <string>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

Products product[102];
Products productCheap[102];
int productCheapN = 0;
Products productExpensive[102];
int productExpensiveN = 0;
Products oneCategory[102];
int oneCategoryN = 0;
Categories category[102];
float newPrice[102];

int n = 0, nn = 0, nnn = 0;
int demolition = 0, demolitionMostExpensiveProducts = 0, demolitionTheCheapestProducts = 0;
int width[8] = { 4, 50, 7, 10, 10, 14, 14, 10 };
int width2[3] = { 4, 65, 50 };
int activeFile = 0;

char pathToFirstFile[260];
char pathToSecondFile[260];
char firstFileName[260] = {};
char secondFileName[260] = {};
char thirdFileName[260] = {};

// Для курсора
HANDLE hWnd = GetStdHandle(STD_INPUT_HANDLE); 
INPUT_RECORD InputRecord; 
DWORD Events;

// Для открытия и сохранинеия файла
char filename[260];
OPENFILENAMEA ofn;

// Для времени
SYSTEMTIME st;

// Меню
bool createNew1 = 0, open1 = 0;
bool createNew2 = 0, open2 = 0;
int firstFile = 0, secondFile = 0;
bool crutch = 1;
bool animationOfTheFirstFile = 0, animationOfTheSecondFile = 0;
bool identicalFiles = 0, identicalFiles1 = 0, identicalFiles2 = 0;
bool go = 0, go1 = 0;
void Menu()
{
	HWND hwndFound;                  // This is what is returned to the caller.
	char pszNewWindowTitle[MAXBYTE]; // Contains fabricated
									 // WindowTitle.
	char pszOldWindowTitle[MAXBYTE]; // Contains original
									 // WindowTitle.
	GetConsoleTitleA(pszOldWindowTitle, MAXBYTE);

	hwndFound = FindWindowA(NULL, pszNewWindowTitle);

	SetOpenFileParams(hwndFound);

	int X = 32, Y = 9;
	SetPos(X, Y);
	SetColor(0, 7);
	cout << "                                                      ";
	SetPos(X, Y + 1);
	cout << "            Two files are required to work            ";
	SetPos(X, Y + 2);
	cout << "                                                      ";
	SetPos(X, Y + 3);
	cout << "                                                      ";
	SetPos(X, Y + 4);
	cout << "    First file               CREATE NEW     OPEN      ";
	SetPos(X, Y + 5);
	cout << "                                                      ";
	SetPos(X, Y + 6);
	cout << "                                                      ";
	SetPos(X, Y + 7);
	cout << "    Second file              CREATE NEW     OPEN      ";
	SetPos(X, Y + 8);
	cout << "                                                      ";
	SetPos(X, Y + 9);
	cout << "                                                      ";
	SetPos(0, 0);

	while (1)
	{
		ReadConsoleInput(hWnd, &InputRecord, 1, &Events);      // считывание

		int x = InputRecord.Event.MouseEvent.dwMousePosition.X;
		int y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

		// Подсветка кнопки "CREATE NEW (1)"
		if (X + 28 <= x && x <= X + 39 && Y + 3 <= y && y <= Y + 5 && createNew1 == 0)
		{
			createNew1 = 1;
			SetColor(0, 8);
			SetPos(X + 28, Y + 3);
			cout << "            ";
			SetPos(X + 28, Y + 4);
			cout << " CREATE NEW ";
			SetPos(X + 28, Y + 5);
			cout << "            ";
			SetPos(0, 0);
		}
		else if (!(X + 28 <= x && x <= X + 39 && Y + 3 <= y && y <= Y + 5) && createNew1 == 1)
		{
			createNew1 = 0;
			SetColor(0, 7);
			SetPos(X + 28, Y + 3);
			cout << "            ";
			SetPos(X + 28, Y + 4);
			cout << " CREATE NEW ";
			SetPos(X + 28, Y + 5);
			cout << "            ";
			SetPos(0, 0);
		}

		// Подсветка кнопки "OPEN (1)"
		if (X + 40 <= x && x <= X + 51 && Y + 3 <= y && y <= Y + 5 && open1 == 0)
		{
			open1 = 1;
			SetColor(0, 8);
			SetPos(X + 40, Y + 3);
			cout << "            ";
			SetPos(X + 40, Y + 4);
			cout << "    OPEN    ";
			SetPos(X + 40, Y + 5);
			cout << "            ";
			SetPos(0, 0);
		}
		else if (!(X + 40 <= x && x <= X + 51 && Y + 3 <= y && y <= Y + 5) && open1 == 1)
		{
			open1 = 0;
			SetColor(0, 7);
			SetPos(X + 40, Y + 3);
			cout << "            ";
			SetPos(X + 40, Y + 4);
			cout << "    OPEN    ";
			SetPos(X + 40, Y + 5);
			cout << "            ";
			SetPos(0, 0);
		}

		// Подсветка кнопки "CREATE NEW (2)"
		if (X + 28 <= x && x <= X + 39 && Y + 6 <= y && y <= Y + 8 && createNew2 == 0)
		{
			createNew2 = 1;
			SetColor(0, 8);
			SetPos(X + 28, Y + 6);
			cout << "            ";
			SetPos(X + 28, Y + 7);
			cout << " CREATE NEW ";
			SetPos(X + 28, Y + 8);
			cout << "            ";
			SetPos(0, 0);
		}
		else if (!(X + 28 <= x && x <= X + 39 && Y + 6 <= y && y <= Y + 8) && createNew2 == 1)
		{
			createNew2 = 0;
			SetColor(0, 7);
			SetPos(X + 28, Y + 6);
			cout << "            ";
			SetPos(X + 28, Y + 7);
			cout << " CREATE NEW ";
			SetPos(X + 28, Y + 8);
			cout << "            ";
			SetPos(0, 0);
		}

		// Подсветка кнопки "OPEN (2)"
		if (X + 40 <= x && x <= X + 51 && Y + 6 <= y && y <= Y + 8 && open2 == 0)
		{
			open2 = 1;
			SetColor(0, 8);
			SetPos(X + 40, Y + 6);
			cout << "            ";
			SetPos(X + 40, Y + 7);
			cout << "    OPEN    ";
			SetPos(X + 40, Y + 8);
			cout << "            ";
			SetPos(0, 0);
		}
		else if (!(X + 40 <= x && x <= X + 51 && Y + 6 <= y && y <= Y + 8) && open2 == 1)
		{
			open2 = 0;
			SetColor(0, 7);
			SetPos(X + 40, Y + 6);
			cout << "            ";
			SetPos(X + 40, Y + 7);
			cout << "    OPEN    ";
			SetPos(X + 40, Y + 8);
			cout << "            ";
			SetPos(0, 0);
		}

		SetColor(0, 15);

		// Обрабатываем нажатие
		if ((int)InputRecord.Event.MouseEvent.dwButtonState == 1)
		{
			// CREATE NEW (1)
			if (X + 28 <= x && x <= X + 39 && Y + 3 <= y && y <= Y + 5)
			{
				if (crutch)
				{
					crutch = 0;
					if (GetSaveFileNameA(&ofn))
					{
						n = 0;
						if (!CheckIfItIsATextFile()) strcat_s(filename, ".txt");
						strcpy_s(pathToFirstFile, filename);
						CreateNew(1);
						firstFile = 1;
						animationOfTheFirstFile = 1;
						identicalFiles = 0;
					}
				}
				else crutch = 1;
			}  // OPEN (1)
			else if (X + 40 <= x && x <= X + 51 && Y + 3 <= y && y <= Y + 5)
			{
				if (crutch)
				{
					crutch = 0;
					if (GetOpenFileNameA(&ofn))
					{
						n = 0;
						strcpy_s(pathToFirstFile, filename);
						firstFile = 0;
						animationOfTheFirstFile = 1;
						identicalFiles = 0;
						if (CheckIfItIsATextFile())
						{
							if (ReadFirstFile())
							{
								firstFile = 1;
							}
						} 
					}
				}
				else crutch = 1;
			} // CREATE NEW (2)
			else if (X + 28 <= x && x <= X + 39 && Y + 6 <= y && y <= Y + 8)
			{
				if (crutch)
				{
					crutch = 0;
					if (GetSaveFileNameA(&ofn))
					{
						nn = 0;
						if (!CheckIfItIsATextFile()) strcat_s(filename, ".txt");
						strcpy_s(pathToSecondFile, filename);
						CreateNew(2);
						secondFile = 1;
						animationOfTheSecondFile = 1;
						identicalFiles = 0;
					}
				}
				else crutch = 1;
			} // OPEN (2)
			else if (X + 40 <= x && x <= X + 51 && Y + 6 <= y && y <= Y + 8)
			{
				if (crutch)
				{
					crutch = 0;
					if (GetOpenFileNameA(&ofn))
					{
						nn = 0;
						strcpy_s(pathToSecondFile, filename);
						secondFile = 0;
						animationOfTheSecondFile = 1;
						identicalFiles = 0;
						if (CheckIfItIsATextFile())
						{
							if (ReadSecondFile())
							{
								secondFile = 1;
							}
						}
					}
				}
				else crutch = 1;
			} // "GO"
			else if (X + 22 <= x && x <= X + 32 && Y + 10 == y && go)
			{
				Clear(13);
				SetPos(0, 0);
				cout << " " << firstFileName << "  " << secondFileName;\
				SetPos(0, 0);
				break;
			}
		}

		// Анимация загрузки первого файла
		if (animationOfTheFirstFile)
		{
			if (identicalFiles1)
			{
				identicalFiles1 = 0;

				SetColor(0, 10);
				SetPos(X + 2, Y + 6);
				cout << "                        ";
				SetPos(X + 2, Y + 7);
				cout << "  " << left << setw(22) << secondFileName;
				SetPos(X + 2, Y + 8);
				cout << "                        ";
			}

			animationOfTheFirstFile = 0;
			
			strcpy_s(firstFileName, GetFileName(pathToFirstFile));

			if (strlen(firstFileName) > 20) strcpy_s(firstFileName, ShortenTheFileName(firstFileName, 20));

			SetColor(0, 3);
			for (int i = 0; i < 24; ++i)
			{
				Sleep(10);
				SetPos(X + 2 + i, Y + 3);
				cout << " ";
				SetPos(X + 2 + i, Y + 4);
				if (0 <= i - 2 && i - 2 < 20) {
					if (i - 2 < strlen(firstFileName)) cout << firstFileName[i - 2];
					else cout << " ";
				} else cout << " ";
				SetPos(X + 2 + i, Y + 5);
				cout << " ";
				SetPos(0, 0);
			}

			Sleep(250);
			if (firstFile) SetColor(0, 10);
			else
			{
				cout << "\a";
				SetColor(0, 4);
			}

				SetPos(X + 2, Y + 3);
				cout << "                        ";
				SetPos(X + 2 , Y + 4);
				cout << "  " << left << setw(22) << firstFileName;
				SetPos(X + 2 , Y + 5);
				cout << "                        ";
		}

		// Анимация загрузки второго файла
		if (animationOfTheSecondFile)
		{
			if (identicalFiles1)
			{
				identicalFiles1 = 0;

				SetColor(0, 10);
				SetPos(X + 2, Y + 3);
				cout << "                        ";
				SetPos(X + 2, Y + 4);
				cout << "  " << left << setw(22) << firstFileName;
				SetPos(X + 2, Y + 5);
				cout << "                        ";
			}

			animationOfTheSecondFile = 0;
			
			strcpy_s(secondFileName, GetFileName(pathToSecondFile));

			if (strlen(secondFileName) > 20) strcpy_s(secondFileName, ShortenTheFileName(secondFileName, 20));

			SetColor(0, 3);
			for (int i = 0; i < 24; ++i)
			{
				Sleep(10);
				SetPos(X + 2 + i, Y + 6);
				cout << " ";
				SetPos(X + 2 + i, Y + 7);
				if (0 <= i - 2 && i - 2 < 20) {
					if (i - 2 < strlen(secondFileName)) cout << secondFileName[i - 2];
					else cout << " ";
				} else cout << " ";
				SetPos(X + 2 + i, Y + 8);
				cout << " ";
				SetPos(0, 0);
			}

			Sleep(250);
			if (secondFile) SetColor(0, 10);
			else
			{
				cout << "\a";
				SetColor(0, 4);
			}

				SetPos(X + 2, Y + 6);
				cout << "                        ";
				SetPos(X + 2, Y + 7);
				cout << "  " << left << setw(22) << secondFileName;
				SetPos(X + 2, Y + 8);
				cout << "                        ";
		}

		if (!strcmp(pathToFirstFile, pathToSecondFile) && firstFile && secondFile && identicalFiles == 0)
		{
			identicalFiles = 1;
			identicalFiles1 = 1;

			cout << "\a";
			SetColor(0, 4);
			SetPos(X + 2, Y + 3);
			cout << "                        ";
			SetPos(X + 2, Y + 4);
			cout << "  " << left << setw(22) << firstFileName;
			SetPos(X + 2, Y + 5);
			cout << "                        ";
			SetPos(X + 2, Y + 6);
			cout << "                        ";
			SetPos(X + 2, Y + 7);
			cout << "  " << left << setw(22) << secondFileName;
			SetPos(X + 2, Y + 8);
			cout << "                        ";
		}

		// Появление кнопки "GO"
		if (firstFile && secondFile && go == 0 && strcmp(pathToFirstFile, pathToSecondFile))
		{
			go = 1;

			SetColor(0, 7);
			SetPos(X + 20, Y + 10);
			cout << "              ";
			
			Sleep(150);
			SetPos(X + 20, Y + 10);
			cout << "              ";
			SetPos(X + 20, Y + 11);
			cout << "              ";

			Sleep(150);
			SetColor(0, 10);
			SetPos(X + 22, Y + 10);
			cout << "    GO    ";
		}
		else if ((!(firstFile && secondFile) || !strcmp(pathToFirstFile, pathToSecondFile)) && go == 1)
		{
			go = 0;

			SetColor(0, 7);
			SetPos(X + 20, Y + 10);
			cout << "              ";

			Sleep(150);
			SetColor(0, 15);
			SetPos(X + 20, Y + 11);
			cout << "              ";

			Sleep(150);
			SetPos(X + 20, Y + 10);
			cout << "              ";
		}

		// Подсветка кнопки "GO"
		if (go)
		{
			if (X + 22 <= x && x <= X + 32 && Y + 10 == y && go1 == 0)
			{
				go1 = 1;

				SetPos(X + 22, Y + 10);
				SetColor(0, 2);
				cout << "    GO    ";
				SetPos(0, 0);
			}
			else if (!(X + 22 <= x && x <= X + 32 && Y + 10 == y) && go1 == 1)
			{
				go1 = 0;

				SetPos(X + 22, Y + 10);
				SetColor(0, 10);
				cout << "    GO    ";
				SetPos(0, 0);
			}
		}
	}
}

// Получение имени файла из известного пути
char* GetFileName(char* path)
{
	int length = 0;
	for (length = strlen(path) - 1; path[length] != '\\'; --length);
	
	char fileName[260];
	int i = 0;
	while (++length <= strlen(path))
		fileName[i++] = path[length];

	return fileName;
}

// Сокращение строки // Адаптация имени файла
char* ShortenTheFileName(char* fileName, int symbols)
{
	// Нужно доработать
	char newFileName[260];
	for (int i = 0; i < symbols / 2; ++i)
	{
		newFileName[i] = fileName[i];
		newFileName[symbols - i] = fileName[strlen(fileName) - i];
	}

	newFileName[symbols / 2] = '~';
	if (symbols % 2) newFileName[symbols / 2 + 1] = fileName[strlen(fileName) - symbols / 2];

	return newFileName;
}

bool CheckIfItIsATextFile()
{
	int l = strlen(filename);
	if (filename[l - 4] != '.' || tolower(filename[l - 3]) != 't' || tolower(filename[l - 2]) != 'x' || tolower(filename[l - 1]) != 't')
		return 0;
	return 1;
}

// Создание новых файлов
void CreateNew(int x)
{
	if (x == 1)
	{
		remove(filename);
		ofstream f(filename);
		f.close();
	}
	else if (x == 2)
	{
		remove(filename);
		ofstream g(filename);
		g.close();
	}
}

// Для открытия файла
void SetOpenFileParams(HWND hwnd)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = "*.txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

// Чтение первого файла
bool ReadFirstFile()
{
	fstream f(pathToFirstFile);

	while (!f.eof())
	{
		product[n].Id = n + 1;
		f >> product[n].Name;
		if (strlen(product[n].Name) > width[1]) Cut(product[n].Name, width[1] - 1);
		for (int i = 0; i < strlen(product[n].Name); ++i)
			if (product[n].Name[i] == '_') product[n].Name[i] = ' ';
		f >> product[n].UnitsOfMeasure >> product[n].CategoryCode >> product[n].Quantity;
		char date[16];
		f >> date;
		product[n].DateOfManufacture[0] = (date[0] - 48) * 10 + date[1] - 48;
		product[n].DateOfManufacture[1] = (date[3] - 48) * 10 + date[4] - 48;
		product[n].DateOfManufacture[2] = (date[6] - 48) * 1000 + (date[7] - 48) * 100 + (date[8] - 48) * 10 + date[9] - 48;
		f >> date;
		product[n].ExpiryDate[0] = (date[0] - 48) * 10 + date[1] - 48;
		product[n].ExpiryDate[1] = (date[3] - 48) * 10 + date[4] - 48;
		product[n].ExpiryDate[2] = (date[6] - 48) * 1000 + (date[7] - 48) * 100 + (date[8] - 48) * 10 + date[9] - 48;
		f >> product[n].Price;
		++n;

		if (n > 101)
		{
			n = 0;
			f.close();
			return 0;
		}
	}
	--n;

	f.close();

	return 1;
}

// Чтение второго файла
bool ReadSecondFile()
{
	fstream f(pathToSecondFile);

	while (!f.eof())
	{
		f >> category[nn].CategoryCode >> category[nn].Name;
		for (int i = 0; i < strlen(category[nn].Name); ++i)
			if (category[nn].Name[i] == '_') category[nn].Name[i] = ' ';
		++nn;

		if (nn > 101)
		{
			nn = 0;
			f.close();
			return 0;
		}
	}
	--nn;

	f.close();

	return 1;
}

// Показ таблиц
void Show(int x)
{
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT); // разрешаем обработку мыши

	int cl = strlen(firstFileName) + strlen(secondFileName) + 4;
	SetPos(cl, 0);
	SetColor(0, 15);
	cout << right << setw(119 - cl) << " ";
	
	switch (x)
	{
	case 1:
		activeFile = 1;
		SetPos(0, 0);
		SetColor(15, 0);
		cout << " " << firstFileName << " ";
		
		SetPos(0, 1); // Переход на начало таблицы
		cout << left
			<< setw(width[0]) << "N" 
			<< setw(width[1]) << "Name"
			<< setw(width[2]) << "Meas"
			<< setw(width[3]) << "Code"
			<< setw(width[4]) << "Quant"
			<< setw(width[5]) << "Date man."
			<< setw(width[6]) << "Expiry date"
			<< setw(width[7]) << "Price" << endl;
		SetColor(0, 15);

		// Цикл выводящий все элементы
		for (int i = 0; i < n; ++i) {

			if (i % 2) SetColor(0, 7);
			else SetColor(0, 15);

			cout << left 
				<< setw(width[0]) << i + demolition + 1 
				<< setw(width[1]) << product[i + demolition].Name
				<< setw(width[2]) << product[i + demolition].UnitsOfMeasure
				<< right << setfill('0') << setw(6) << product[i + demolition].CategoryCode << left << setfill(' ') 
				<< setw(width[3] - 6) << " " 
				<< setw(width[4]) << product[i + demolition].Quantity;
			
			if (product[i + demolition].DateOfManufacture[0] < 10) cout << 0;
			cout << product[i + demolition].DateOfManufacture[0] << ".";
			
			if (product[i + demolition].DateOfManufacture[1] < 10) cout << 0;
			cout << product[i + demolition].DateOfManufacture[1] << "." << setw(width[5] - 6) << product[i + demolition].DateOfManufacture[2];
			
			if (product[i + demolition].ExpiryDate[0] < 10) cout << 0;
			cout << product[i + demolition].ExpiryDate[0] << ".";
			
			if (product[i + demolition].ExpiryDate[1] < 10) cout << 0;
			cout << product[i + demolition].ExpiryDate[1] << "." << setw(width[6] - 6) << product[i + demolition].ExpiryDate[2]
				<< setw(width[7]) << product[i + demolition].Price << endl;

			if (i == 19) break; // Выход из цикла, если уже отобразилось 20 элементов
		}

		SetColor(0, 15);
		if (n < 20) Clear(20 - n); // Запуск функции "Очистка", если элементов меньше 20
		break;
	case 2:
		activeFile = 2;
		SetPos(strlen(firstFileName) + 2, 0);
		SetColor(15, 0);
		cout << " " << secondFileName << " ";

		SetPos(0, 1);
		cout << left
			<< setw(width2[0]) << "N"
			<< setw(width2[2]) << "Name"
			<< setw(width2[1]) << "Code" << endl;
		SetColor(0, 15);

		for (int i = 0; i < nn; ++i) {

			if (i % 2) SetColor(0, 7);
			else SetColor(0, 15);
			
			cout << left 
				<< setw(width[0]) << i + demolition + 1 
				<< setw(width2[2]) << category[i + demolition].Name
				<< right << setfill('0') << setw(6) << category[i + demolition].CategoryCode
				<< left << setfill(' ') << setw(width2[1] - 6) << " " << endl;

			if (i == 19) break; // Выход из цикла, если уже отобразилось 20 элементов
		}

		SetColor(0, 15);
		if (nn < 20) Clear(20 - nn);
		break;
	}
	SetPos(0, 0);
}

// Очистка незаполненной части таблицы
void Clear(int y)
{
	SetPos(0, 22 - y);
	for (int i = 0; i < y; ++i)
		cout << right << setw(119) << " " << endl;
}

// Основная логика
bool miniMenu = 0;
int miniMenuCordX, miniMenuCordY;
bool btnAdd = 0;
int btnAddCordX, btnAddCordY;
bool firstTab = 0, secondTab = 0, createNew = 0;
int selectedElement;
bool btnMiniMenu1 = 0, btnMiniMenu2 = 0, btnMiniMenu3 = 0, btnMiniMenu4 = 0, btnMiniMenu5 = 0;
void Logics(int x, int y, int m)
{
	// Нужно удалить
	//SetPos(50, 22);
	//cout << "x - " << x << " | y - " << y << "     m - " << m << "        ";

	// Скрол
	bool scrol = 0, scrolMostExpensiveProducts = 0, scrolTheCheapestProducts = 0;
	if (m == 7864320)
	{
		if (16 <= x && x <= 37 && 24 <= y && y <= 25)
		{
			if (demolitionMostExpensiveProducts > 0)
			{
				scrolMostExpensiveProducts = 1;
				--demolitionMostExpensiveProducts;
			}
		}
		else if (92 <= x && x <= 113 && 24 <= y && y <= 25)
		{
			if (demolitionTheCheapestProducts > 0)
			{
				scrolTheCheapestProducts = 1;
				--demolitionTheCheapestProducts;
			}
		}
		else if (demolition > 0)
		{
			scrol = 1;
			--demolition;
		}
	}
	else if (m == -7864320)
	{
		if (16 <= x && x <= 37 && 24 <= y && y <= 25)
		{
			if (demolitionMostExpensiveProducts < productExpensiveN - 2)
			{
				scrolMostExpensiveProducts = 1;
				++demolitionMostExpensiveProducts;
			}
		}
		else if (92 <= x && x <= 113 && 24 <= y && y <= 25)
		{
			if (demolitionTheCheapestProducts < productCheapN - 2)
			{
				scrolTheCheapestProducts = 1;
				++demolitionTheCheapestProducts;
			}
		}
		else
		{
			switch (activeFile)
			{
			case 1:
				if (demolition < n - 20) ++demolition, scrol = 1;
				break;
			case 2:
				if (demolition < nn - 20) ++demolition, scrol = 1;
			case 3:
				if (demolition < oneCategoryN - 20) ++demolition, scrol = 1;
				break;
			}
		}

	}

	// Скрытие мини меню при скроле и обновление таблицы
	if (scrol)
	{
		miniMenu = 0;
		miniMenuCordX = -1;
		miniMenuCordY = -1;

		if (activeFile == 1 || activeFile == 2) Show(activeFile);
		else ShowAllCategory(selectedElement);
	}

	// Обновление списка самых дорогих продуктов
	if (scrolMostExpensiveProducts)
	{
		ShowMostExpensiveProducts();
	}

	// Обновление списка самых дорогих продуктов
	if (scrolTheCheapestProducts)
	{
		ShowTheCheapestProducts();
	}

	// Обработка правого клика
	int borderBottom = 21;
	if (m == 2)
	{
		switch (activeFile)
		{
		case 1:
			if (n < 20) borderBottom = n + 1;
			break;
		case 2:
			if (nn < 20) borderBottom = nn + 1;
			break;
		case 3:
			if (nnn < 20) borderBottom = nnn + 1;
			break;
		}

		if ((activeFile == 1 || activeFile == 2) && 0 <= x && x <= 117 && y == 1)
		{
			bool b = 1;
			if (activeFile == 1 && nn == 0) b = 0;
			
			if (b)
			{
				btnAdd = 1;

				switch (activeFile)
				{
				case 1:
					selectedElement = n;
					break;
				case 2:
					selectedElement = nn;
					break;
				}

				btnAddCordX = x + 1;
				btnAddCordY = y + 1;

				if (97 <= btnAddCordX) { btnAddCordX -= 21; }
			}
		}

		if ((activeFile == 1 || activeFile == 2) && 0 <= x && x <= 117 && 2 <= y && y <= borderBottom)
		{
			miniMenu = 1;

			selectedElement = y - 2 + demolition;

			miniMenuCordX = x + 1;
			miniMenuCordY = y;
			if (97 <= miniMenuCordX) { miniMenuCordX -= 21; }
			if (borderBottom - 4 <= miniMenuCordY && miniMenuCordY > 6) { miniMenuCordY -= 5; }
		}
		// Показ мини меню
		if (miniMenu)
		{
			Sleep(100);
			Show(activeFile);

			SetPos(miniMenuCordX, miniMenuCordY);
			SetColor(0, 8);
			cout << "                     ";
			SetPos(miniMenuCordX, miniMenuCordY + 1);
			cout << "  Edit               ";
			SetPos(miniMenuCordX, miniMenuCordY + 2);
			cout << "  Add                ";
			SetPos(miniMenuCordX, miniMenuCordY + 3);
			cout << "  Show all category  ";
			SetPos(miniMenuCordX, miniMenuCordY + 4);
			SetColor(4, 8);
			cout << "  Delete             ";
			SetPos(miniMenuCordX, miniMenuCordY + 5);
			SetColor(0, 8);
			cout << "                     ";
			SetColor(0, 15);
			SetPos(0, 0);
		}

		// Показ кнопки "Add"
		if (btnAdd)
		{
			SetPos(btnAddCordX, btnAddCordY);
			SetColor(0, 8);
			cout << "                     ";
			SetPos(btnAddCordX, btnAddCordY + 1);
			cout << "  Add                ";
			SetPos(btnAddCordX, btnAddCordY + 2);
			cout << "                     ";
			SetPos(0, 0);
		}
	}

	// Подсветка кномок мини меню
	if (miniMenu)
	{
		if (miniMenuCordX + 2 <= x && x <= miniMenuCordX + 18 && y == miniMenuCordY + 1 && btnMiniMenu1 == 0)
		{
			btnMiniMenu1 = 1;
			SetPos(miniMenuCordX + 2, miniMenuCordY + 1);
			SetColor(0, 7);
			cout << "Edit             ";
			SetPos(0, 0);
		}
		else if (!(miniMenuCordX + 2 <= x && x <= miniMenuCordX + 18 && y == miniMenuCordY + 1) && btnMiniMenu1 == 1)
		{
			btnMiniMenu1 = 0;
			SetPos(miniMenuCordX + 2, miniMenuCordY + 1);
			SetColor(0, 8);
			cout << "Edit             ";
			SetPos(0, 0);
		}

		if (miniMenuCordX + 2 <= x && x <= miniMenuCordX + 18 && y == miniMenuCordY + 2 && btnMiniMenu2 == 0)
		{
			btnMiniMenu2 = 1;
			SetPos(miniMenuCordX + 2, miniMenuCordY + 2);
			SetColor(0, 7);
			cout << "Add              ";
			SetPos(0, 0);
		}
		else if (!(miniMenuCordX + 2 <= x && x <= miniMenuCordX + 18 && y == miniMenuCordY + 2) && btnMiniMenu2 == 1)
		{
			btnMiniMenu2 = 0;
			SetPos(miniMenuCordX + 2, miniMenuCordY + 2);
			SetColor(0, 8);
			cout << "Add              ";
			SetPos(0, 0);
		}

		if (miniMenuCordX + 2 <= x && x <= miniMenuCordX + 18 && y == miniMenuCordY + 3 && btnMiniMenu3 == 0)
		{
			btnMiniMenu3 = 1;
			SetPos(miniMenuCordX + 2, miniMenuCordY + 3);
			SetColor(0, 7);
			cout << "Show all category";
			SetPos(0, 0);
		}
		else if (!(miniMenuCordX + 2 <= x && x <= miniMenuCordX + 18 && y == miniMenuCordY + 3) && btnMiniMenu3 == 1)
		{
			btnMiniMenu3 = 0;
			SetPos(miniMenuCordX + 2, miniMenuCordY + 3);
			SetColor(0, 8);
			cout << "Show all category";
			SetPos(0, 0);
		}

		if (miniMenuCordX + 2 <= x && x <= miniMenuCordX + 18 && y == miniMenuCordY + 4 && btnMiniMenu4 == 0)
		{
			btnMiniMenu4 = 1;
			SetPos(miniMenuCordX + 2, miniMenuCordY + 4);
			SetColor(4, 7);
			cout << "Delete           ";
			SetPos(0, 0);
		}
		else if (!(miniMenuCordX + 2 <= x && x <= miniMenuCordX + 18 && y == miniMenuCordY + 4) && btnMiniMenu4 == 1)
		{
			btnMiniMenu4 = 0;
			SetPos(miniMenuCordX + 2, miniMenuCordY + 4);
			SetColor(4, 8);
			cout << "Delete           ";
			SetPos(0, 0);
		}
	}

	if (btnAdd)
	{
		if (btnAddCordX + 2 <= x && x <= btnAddCordX + 18 && y == btnAddCordY + 1 && btnMiniMenu5 == 0)
		{
			btnMiniMenu5 = 1;
			SetPos(btnAddCordX + 2, btnAddCordY + 1);
			SetColor(0, 7);
			cout << "Add              ";
			SetPos(0, 0);
		}
		else if (!(btnAddCordX + 2 <= x && x <= btnAddCordX + 18 && y == btnAddCordY + 1) && btnMiniMenu5 == 1)
		{
			btnMiniMenu5 = 0;
			SetPos(btnAddCordX + 2, btnAddCordY + 1);
			SetColor(0, 8);
			cout << "Add              ";
			SetPos(0, 0);
		}
	}

	// Скрытие мини меню, если курсор далеко
	if (miniMenu && miniMenuCordX - 4 > x ||
		miniMenu && miniMenuCordY - 2 > y ||
		miniMenu && miniMenuCordX + 25 < x ||
		miniMenu && miniMenuCordY + 7 < y)
	{
		miniMenu = 0;
		miniMenuCordX = -1;
		miniMenuCordY = -1;

		if (activeFile == 1)
		{
			Show(1);
		}
		else if (activeFile == 2)
		{
			Show(2);
		}
	}

	if (btnAdd && btnAddCordX - 4 > x ||
		btnAdd && btnAddCordY - 2 > y ||
		btnAdd && btnAddCordX + 25 < x ||
		btnAdd && btnAddCordY + 4 < y)
	{
		btnAdd = 0;
		btnAddCordX = -1;
		btnAddCordY = -1;

		if (activeFile == 1)
		{
			Show(1);
		}
		else if (activeFile == 2)
		{
			Show(2);
		}
	}

	// Подсветка первой вкладки
	if (activeFile != 1)
	{
		if (0 <= x && x <= strlen(firstFileName) + 1 && y == 0 && firstTab == 0)
		{
			firstTab = 1;

			SetPos(0, 0);
			SetColor(0, 7);
			cout << " " << firstFileName << " ";
			SetPos(0, 0);
		}
		else if (!(0 <= x && x <= strlen(firstFileName) + 1 && y == 0) && firstTab == 1)
		{
			firstTab = 0;

			SetPos(0, 0);
			SetColor(0, 15);
			cout << " " << firstFileName << " ";
			SetPos(0, 0);
		}
	}

	// Подсветка второй вкладки
	if (activeFile != 2)
	{
		if (strlen(firstFileName) + 2 <= x && x <= strlen(firstFileName) + strlen(secondFileName) + 3 && y == 0 && secondTab == 0)
		{
			secondTab = 1;

			SetPos(strlen(firstFileName) + 2, 0);
			SetColor(0, 7);
			cout << " " << secondFileName << " ";
			SetPos(0, 0);
		}
		else if (!(strlen(firstFileName) + 2 <= x && x <= strlen(firstFileName) + strlen(secondFileName) + 3 && y == 0) && secondTab == 1)
		{
			secondTab = 0;

			SetPos(strlen(firstFileName) + 2, 0);
			SetColor(0, 15);
			cout << " " << secondFileName << " ";
			SetPos(0, 0);
		}
	}

	// Обработка левого клика
	if (m == 1)
	{
		if (!activeFile && 0 <= x && x <= strlen(firstFileName) + strlen(secondFileName) + 3 && y == 0)
		{
			CalculationOfNewPrices();
			MostExpensiveProducts();
			TheCostOfAllProducts();
			TheCheapestProducts();
			UpArrow(4, 23);
			Coin(42, 23);
			ArrowToDown(80, 23);
			CreateNewFile();
		}

		if (0 <= x && x <= strlen(firstFileName) + 1 && y == 0) // Нажата первая вкладка
		{
			demolition = 0;
			activeFile = 1;
			Show(activeFile);
		}
		else if (strlen(firstFileName) + 2 <= x && x <= strlen(firstFileName) + strlen(secondFileName) + 3 && y == 0) // Нажата вторая вкладкка
		{
			demolition = 0;
			activeFile = 2;
			Show(activeFile);
		}
		else if (miniMenu) // Проверка, если мини меню активно
		{
			if (miniMenuCordX + 2 <= x && x <= miniMenuCordX + 18 && miniMenuCordY + 1 <= y && y <= miniMenuCordY + 4) // Если нажато в облости кнопок мини меню
			{
				if (y == miniMenuCordY + 1) // Если нажата первая кнопка (Edit)
				{
					Edit(selectedElement);
				}
				else if (y == miniMenuCordY + 2) // Если нажата вторая кнопка (Add)
				{
					Add(selectedElement);
				}
				else if (y == miniMenuCordY + 3) // Если нажата третья кнопка (Show all category)
				{
					if (activeFile == 1)
					{
						if (CheckIfThereIsACode(product[selectedElement].CategoryCode))
						{
							demolition = 0;
							ShowAllCategory(selectedElement);
							activeFile = 3;
						}
						else
						{
							Show(activeFile);
							CategoryNotFound();
							Show(activeFile);
						}
					} 
					else
					{
						demolition = 0;
						ShowAllCategory(selectedElement);
						activeFile = 3;
					}
				}
				else if (y == miniMenuCordY + 4) // Если нажата четвёртая кнопка (Delete)
				{
					Show(activeFile);

					if (Attention(selectedElement))
					{
						Delete(selectedElement);
					}
					else
					{
						Show(activeFile);
					}
				}

				if (!(y == miniMenuCordY + 3))
				{
					CalculationOfNewPrices();
					MostExpensiveProducts();
					TheCostOfAllProducts();
					TheCheapestProducts();
					demolitionMostExpensiveProducts = 0;
					UpArrow(4, 23);
					Coin(42, 23);
					demolitionTheCheapestProducts = 0;
					ArrowToDown(80, 23);
					CreateNewFile();
					Save();
				}

				miniMenu = 0;
				miniMenuCordX = -1;
				miniMenuCordY = -1;
			}
		}
		else if (btnAdd && btnAddCordX + 2 <= x && x <= btnAddCordX + 18 && y == btnAddCordY + 1)
		{
			switch (activeFile)
			{
			case 1:
				if (n > 19) demolition = n - 19;
				Add(n);
				break;
			case 2:
				if (nn > 19) demolition = nn - 19;
				Add(nn);
				break;
			}

			CalculationOfNewPrices();
			MostExpensiveProducts();
			TheCostOfAllProducts();
			TheCheapestProducts();
			demolitionMostExpensiveProducts = 0;
			UpArrow(4, 23);
			Coin(42, 23);
			demolitionTheCheapestProducts = 0;
			ArrowToDown(80, 23);
			CreateNewFile();
			Save();

			btnAdd = 0;
			btnAddCordX = -1;
			btnAddCordY = -1;
		}
	}
}

// Редактирование элемента
void Edit(int pos)
{
	Show(activeFile);

	char charIgnore[64];
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), 487);
	
	SetPos(4, pos - demolition + 2);
	if ((pos + demolition) % 2) SetColor(0, 7);
	cout << right << setw(115) << " ";
	
	switch (activeFile)
	{
	case 1:
	{
		SetPos(4, pos - demolition + 2);
		cin.ignore();
		gets_s(product[pos].Name);
		if (strlen(product[pos].Name) > width[1]) Cut(product[pos].Name, width[1] - 1);
	
		SetPos(54, pos - demolition + 2);
		cout << right << setw(65) << " ";
		SetPos(54, pos - demolition + 2);
		cin >> product[pos].UnitsOfMeasure;
		if (strlen(product[pos].UnitsOfMeasure) > width[2]) Cut(product[pos].UnitsOfMeasure, width[2] - 1);
	
		if (pos - demolition < 18) product[pos].CategoryCode = CodeSelection(61, pos - demolition + 2, 3);
		else product[pos].CategoryCode = CodeSelection(61, pos - demolition, 3);
		Show(1);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), 487);
		if ((pos + demolition) % 2) SetColor(0, 7);

		do
		{
			SetPos(71, pos - demolition + 2);
			cout << right << setw(48) << " ";

			SetPos(71, pos - demolition + 2);
			cin >> charIgnore;
			product[pos].Quantity = atof(charIgnore);

		} while (product[pos].Quantity <= 0);
	
		GetLocalTime(&st);
		int d = st.wDay;
		int m = st.wMonth;
		int y = st.wYear;

		do
		{	
			do
			{
				SetPos(81, pos - demolition + 2);
				cout << right << setw(38) << " ";
				SetPos(81, pos - demolition + 2);
				cin >> charIgnore;
				product[pos].DateOfManufacture[0] = atoi(charIgnore);
			} while (product[pos].DateOfManufacture[0] < 1 || 31 < product[pos].DateOfManufacture[0]);

			do
			{
				SetPos(84, pos - demolition + 2);
				cout << right << setw(35) << " ";
				SetPos(84, pos - demolition + 2);
				cin >> charIgnore;
				product[pos].DateOfManufacture[1] = atoi(charIgnore);

			} while (product[pos].DateOfManufacture[1] < 1 || 12 < product[pos].DateOfManufacture[1]);

			do
			{
				SetPos(87, pos - demolition + 2);
				cout << right << setw(32) << " ";
				SetPos(87, pos - demolition + 2);
				cin >> charIgnore;
				product[pos].DateOfManufacture[2] = atoi(charIgnore);
			} while (product[pos].DateOfManufacture[2] < y - 100 || y + 100 < product[pos].DateOfManufacture[2]);

		} while (!CheckingIfTheDateIsCorrect(product[pos].DateOfManufacture[0], product[pos].DateOfManufacture[1],  product[pos].DateOfManufacture[2]) || !DateSequenceCheck(product[pos].DateOfManufacture[0], product[pos].DateOfManufacture[1], product[pos].DateOfManufacture[2], d, m, y));

		do
		{
			do
			{
				SetPos(95, pos - demolition + 2);
				cout << right << setw(24) << " ";
				SetPos(95, pos - demolition + 2);
				cin >> charIgnore;
				product[pos].ExpiryDate[0] = atoi(charIgnore);

			} while (product[pos].ExpiryDate[0] < 1 || 31 < product[pos].ExpiryDate[0]);

			do
			{
				SetPos(98, pos - demolition + 2);
				cout << right << setw(21) << " ";
				SetPos(98, pos - demolition + 2);
				cin >> charIgnore;
				product[pos].ExpiryDate[1] = atoi(charIgnore);

			} while (product[pos].ExpiryDate[1] < 1 || 12 < product[pos].ExpiryDate[1]);

			do
			{
				SetPos(101, pos - demolition + 2);
				cout << right << setw(18) << " ";
				SetPos(101, pos - demolition + 2);
				cin >> charIgnore;
				product[pos].ExpiryDate[2] = atoi(charIgnore);

			} while (product[pos].ExpiryDate[2] < y - 100 || y + 100 < product[pos].ExpiryDate[2]);

		} while (!CheckingIfTheDateIsCorrect(product[pos].ExpiryDate[0], product[pos].ExpiryDate[1], product[pos].ExpiryDate[2]) || !DateSequenceCheck(product[pos].DateOfManufacture[0], product[pos].DateOfManufacture[1], product[pos].DateOfManufacture[2], product[pos].ExpiryDate[0], product[pos].ExpiryDate[1], product[pos].ExpiryDate[2]));

		do
		{
			SetPos(109, pos - demolition + 2);
			cout << right << setw(10) << " ";

			SetPos(109, pos - demolition + 2);
			cin >> charIgnore;
			product[pos].Price = atof(charIgnore);

		} while (product[pos].Price < 0);

		break;
	}
	case 2:
	{
		SetPos(4, pos - demolition + 2);
		cin.ignore();
		gets_s(category[pos].Name);
		if (strlen(category[pos].Name) > width[1]) Cut(product[pos].Name, width[1] - 1);

		int previousCategoryNumber = category[pos].CategoryCode;
		category[pos].CategoryCode = 0;
		
		do
		{
			SetPos(54, pos - demolition + 2);
			cout << right << setw(65) << " ";

			SetPos(54, pos - demolition + 2);
			cin >> charIgnore;
		} while (atoi(charIgnore) <= 0 || 999999 < atoi(charIgnore) || CheckIfThereIsACode(atoi(charIgnore)));
		category[pos].CategoryCode = atoi(charIgnore);

		if (previousCategoryNumber != category[pos].CategoryCode)
		{
			SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (487 & ~ENABLE_QUICK_EDIT_MODE));
			SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT); // разрешаем обработку мыши
			bool yes = 0;
			for (int i = 0; i < n; ++i)
			{
				if (product[i].CategoryCode == previousCategoryNumber)
				{
					yes = 1;
				}
			}

			if (yes) OverwritingProductCode(previousCategoryNumber, category[pos].CategoryCode);
		}

		break;
	}
	}

	Show(activeFile);
	
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (487 & ~ENABLE_QUICK_EDIT_MODE));
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT); // разрешаем обработку мыши
}

// Выбор кода
int CodeSelection(int x, int y, int amount)
{
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (487 & ~ENABLE_QUICK_EDIT_MODE));
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT); // разрешаем обработку мыши

	SetColor(0, 8);
	
	int beginningWith = 0;
	if (amount > nn) amount = nn;
	ShowCodeList(x, y, amount, beginningWith);

	bool a = 0;
	int b = -1;

	while (1)
	{
		ReadConsoleInput(hWnd, &InputRecord, 1, &Events); // считывание

		int X = InputRecord.Event.MouseEvent.dwMousePosition.X;
		int Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
		int m = (int)InputRecord.Event.MouseEvent.dwButtonState;

		if (m == 7864320)
		{
			if (x <= X && X < x + 6 && y <= Y && Y < y + amount)
			{
				if (beginningWith > 0)
				{
					beginningWith--;
					ShowCodeList(x, y, amount, beginningWith);
				}
			}
		}
		else if (m == -7864320)
		{
			if (x <= X && X < x + 6 && y <= Y && Y < y + amount)
			{
				if (beginningWith < nn - amount)
				{
					beginningWith++;
					ShowCodeList(x, y, amount, beginningWith);
				}
			}
		}
		else if (m == 1)
		{
			if (x <= X && X < x + 6 && y <= Y && Y < y + amount)
			{
				return category[Y - y + beginningWith].CategoryCode;
			}
		}

		if (x <= X && X < x + 6 && y <= Y && Y < y + amount)
		{
			a = 1;
			
			ShowCodeList(x, y, amount, beginningWith);
			
			SetColor(0, 7);
			SetPos(x, Y);
			cout << right << setfill('0') << setw(6) << category[Y - y + beginningWith].CategoryCode;
			cout << left << setfill(' ');
			SetColor(0, 8);

			SetPos(0, 0);
		}
		else if (!(x <= X && X < x + 6 && y <= Y && Y < y + amount))
		{
			a = 0;
			ShowCodeList(x, y, amount, beginningWith);
		}
	}
}

// Показать список кодов
void ShowCodeList(int x, int y, int amount, int beginningWith)
{
	for (int i = 0; i < amount; ++i)
	{
		SetPos(x, y + i);
		cout << right << setfill('0') << setw(6) << category[i + beginningWith].CategoryCode;
	}

	cout << left << setfill(' ');
	SetPos(0, 0);
}

// Перезапись кода продуктов при редактировании кода категории
void OverwritingProductCode(int oldCode, int newCode)
{
	SetColor(15, 0);
	SetPos(32, 7);
	cout << "                                                      ";
	SetPos(32, 8);
	cout << "                      ATTENTION!                      ";
	SetPos(32, 9);
	cout << "                                                      ";
	SetPos(32, 10);
	cout << "  You have changed the category code, want to clear   ";
	SetPos(32, 11);
	cout << "  the product code or change to a new one?            ";
	SetPos(32, 12);
	cout << "                                                      ";
	SetPos(32, 13);
	cout << "                                                      ";
	SetPos(32, 14);
	cout << "         |     Clear      ||     Change     |         ";
	SetPos(32, 15);
	cout << "                                                      ";
	SetPos(32, 16);
	cout << "                                                      ";
	SetColor(0, 15);

	bool clear = 0, change = 0;
	while (1)
	{
		ReadConsoleInput(hWnd, &InputRecord, 1, &Events);      // считывание

		int x = InputRecord.Event.MouseEvent.dwMousePosition.X;
		int y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

		// Подсветка кнопки "Clear"
		if (41 <= x && x <= 58 && 13 <= y && y <= 15 && clear == 0)
		{
			clear = 1;

			SetColor(0, 8);
			SetPos(41, 13);
			cout << "                  ";
			SetPos(41, 14);
			cout << "      Clear       ";
			SetPos(41, 15);
			cout << "                  ";
			SetPos(0, 0);
		}
		else if (!(41 <= x && x <= 58 && 13 <= y && y <= 15) && clear == 1)
		{
			clear = 0;

			SetColor(15, 0);
			SetPos(41, 13);
			cout << "                  ";
			SetPos(41, 14);
			cout << "      Clear       ";
			SetPos(41, 15);
			cout << "                  ";
			SetPos(0, 0);
		}

		// Подсветка кнопки "Change"
		if (59 <= x && x <= 76 && 13 <= y && y <= 15 && change == 0)
		{
			change = 1;

			SetColor(0, 8);
			SetPos(59, 13);
			cout << "                  ";
			SetPos(59, 14);
			cout << "      Change      ";
			SetPos(59, 15);
			cout << "                  ";
			SetPos(0, 0);
		}
		else if (!(59 <= x && x <= 76 && 13 <= y && y <= 15) && change == 1)
		{
			change = 0;

			SetColor(15, 0);
			SetPos(59, 13);
			cout << "                  ";
			SetPos(59, 14);
			cout << "      Change      ";
			SetPos(59, 15);
			cout << "                  ";
			SetPos(0, 0);
		}

		SetColor(0, 15);

		// Обрабатываем нажатие
		if ((int)InputRecord.Event.MouseEvent.dwButtonState == 1)
		{
			if (41 <= x && x <= 58 && 13 <= y && y <= 15) { newCode = 0; break; }
			else if (59 <= x && x <= 76 && 13 <= y && y <= 15) break;
			else cout << "\a";
		}

		//SetPos(50, 25);
		//cout << "x - " << x << " | y - " << y << "     m -      ";
	}

	for (int i = 0; i < n; ++i)
	{
		if (product[i].CategoryCode == oldCode)
		{
			product[i].CategoryCode = newCode;
		}
	}
}

// Проверить есть ли код
bool CheckIfThereIsACode(int cod)
{
	for (int i = 0; i < nn; ++i)
		if (cod == category[i].CategoryCode)
			return 1;
	return 0;
}

// Сообщение о том, что категория не была найдена
void CategoryNotFound()
{
	int X = 45, Y = 10;

	cout << "\a";

	SetColor(15, 0);
	SetPos(X, Y);
	cout << "                              ";
	SetPos(X, Y + 1);
	cout << "    Category not found ";
	SetColor(4, 0);
	cout << "X_X    ";
	SetColor(15, 0);
	SetPos(X, Y + 2);
	cout << "                              ";
	SetPos(X, Y + 3);
	cout << "              OK              ";
	SetPos(X, Y + 4);
	cout << "                              ";
	SetPos(0, 0);

	bool ok = 0;
	while (1)
	{
		ReadConsoleInput(hWnd, &InputRecord, 1, &Events); // считывание

		int x = InputRecord.Event.MouseEvent.dwMousePosition.X;
		int y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

		if (X + 14 <= x && x <= X + 15 && y == Y + 3 && ok == 0)
		{
			ok = 1;
			SetColor(10, 0);
			SetPos(X + 14, Y + 3);
			cout << "OK";
			SetColor(0, 0);
		}
		else if (!(X + 14 <= x && x <= X + 15 && y == Y + 3) && ok == 1)
		{
			ok = 0;
			SetColor(14, 0);
			SetPos(X + 14, Y + 3);
			cout << "OK";
			SetColor(0, 0);
		}
		SetPos(0, 0);

		if ((int)InputRecord.Event.MouseEvent.dwButtonState == 1)
		{
			if (X + 14 <= x && x <= X + 15 && y == Y + 3) break;
			else cout << "\a";
		}
	}
}

// Обрезать строку
void Cut(char* str, int simbols)
{
	str[simbols] = str[strlen(str)];
}

// Добавление нового элемента // Нужно проверить
void Add(int pos)
{
	switch (activeFile)
	{
	case 1:
		for (int i = n; i >= pos; --i)
			product[i] = product[i - 1];
		++n;
		Edit(pos);
		break;
	case 2:
		for (int i = nn; i > pos; --i)
			category[i] = category[i - 1];
		++nn;
		Edit(pos);
		break;
	}
}

// Показ определённой категории
void ShowAllCategory(int pos)
{
	if (activeFile != 3)
	{
		int cod;
		switch (activeFile)
		{
		case 1:
			cod = product[pos].CategoryCode;
			for (int i = 0; i < nn; ++i)
				if (cod == category[i].CategoryCode)
					strcpy_s(thirdFileName, category[i].Name);
			break;
		case 2:
			cod = category[pos].CategoryCode;
			strcpy_s(thirdFileName, category[pos].Name);
			break;
		}

		oneCategoryN = 0;
		for (int i = 0; i < n; ++i)
			if (cod == product[i].CategoryCode)
				oneCategory[oneCategoryN++] = product[i];

		for (int i = 0; i < oneCategoryN - 1; ++i)
			for (int j = 0; j < oneCategoryN - 1 - i; ++j)
				if (strcmp(oneCategory[j].Name, oneCategory[j + 1].Name) > 0)
					swap(oneCategory[j], oneCategory[j + 1]);
	}

		SetPos(0, 0);
		SetColor(0, 15);
		cout << " " << firstFileName << "  " << secondFileName << " ";
	
		SetColor(15, 0);
		cout << " " << thirdFileName << " ";
	
		SetPos(0, 1);
		cout << left
			<< setw(width[0]) << "N"
			<< setw(width[1]) << "Name"
			<< setw(width[2]) << "Meas"
			<< setw(width[3]) << "Code"
			<< setw(width[4]) << "Quant"
			<< setw(width[5]) << "Date man."
			<< setw(width[6]) << "Expiry date"
			<< setw(width[7]) << "Price" << endl;

		SetColor(0, 15);

	for (int i = 0; i < oneCategoryN; ++i)
	{
		if (i % 2) SetColor(0, 7);
		else SetColor(0, 15);

		cout << left
			<< setw(width[0]) << i + demolition + 1
			<< setw(width[1]) << oneCategory[i + demolition].Name
			<< setw(width[2]) << oneCategory[i + demolition].UnitsOfMeasure
			<< right << setfill('0') << setw(6) << oneCategory[i + demolition].CategoryCode << left << setfill(' ')
			<< setw(width[3] - 6) << " "
			<< setw(width[4]) << oneCategory[i + demolition].Quantity;

		if (oneCategory[i + demolition].DateOfManufacture[0] < 10) cout << 0;
		cout << oneCategory[i + demolition].DateOfManufacture[0] << ".";

		if (oneCategory[i + demolition].DateOfManufacture[1] < 10) cout << 0;
		cout << oneCategory[i + demolition].DateOfManufacture[1] << "." << setw(width[5] - 6) << oneCategory[i + demolition].DateOfManufacture[2];

		if (oneCategory[i + demolition].ExpiryDate[0] < 10) cout << 0;
		cout << oneCategory[i + demolition].ExpiryDate[0] << ".";

		if (oneCategory[i + demolition].ExpiryDate[1] < 10) cout << 0;
		cout << oneCategory[i + demolition].ExpiryDate[1] << "." << setw(width[6] - 6) << oneCategory[i + demolition].ExpiryDate[2]
			<< setw(width[7]) << oneCategory[i + demolition].Price << endl;

		if (i == 19) break;
	}

	SetColor(0, 15);
	if (oneCategoryN < 20) Clear(20 - oneCategoryN);
}

// Удаление элемента
void Delete(int y)
{
	if (demolition > 0) --demolition;
	
	switch (activeFile)
	{
	case 1:
		--n;
		for (int i = y; i < n; ++i)
			product[i] = product[i + 1];
		Show(1);
		break;
	case 2:
		for (int i = 0; i < n; ++i)
			if (product[i].CategoryCode == category[y].CategoryCode)
				product[i].CategoryCode = 0;

		--nn;
		for (int i = y; i < nn; ++i)
			category[i] = category[i + 1];
		Show(2);
		break;
	}
}

// Стоимость всей продукции
float costOfAllProducts = 0, costOfAllProductsBefore = 0;
void TheCostOfAllProducts()
{
	float sum = 0;
	for (int i = 0; i < n; ++i)
		sum += newPrice[i];

	if (sum != costOfAllProducts)
	{
		costOfAllProductsBefore = costOfAllProducts;
		costOfAllProducts = sum;
	}
}

void ShowTheCostOfAllProducts()
{
	// Нужно проверить
	SetPos(54, 24);
	SetColor(10, 0);
	cout << left << setw(19) << costOfAllProducts << " ";
	if (costOfAllProducts - costOfAllProductsBefore > 0)
	{
		SetPos(54, 27);
		cout << "+" << left << setw(9) << costOfAllProducts - costOfAllProductsBefore;
	}
	else
	{
		SetPos(54, 27);
		if (costOfAllProducts - costOfAllProductsBefore < 0) SetColor(4, 0);
		else SetColor(15, 0);
		cout << left << setw(19) << costOfAllProducts - costOfAllProductsBefore;
	}
}

// Подтверждение удаления
bool Attention(int elementToBeRemoved)
{
	cout << "\a";

	SetColor(15, 0);
	SetPos(32, 7);
	cout << "                                                      ";
	SetPos(32, 8);
	cout << "                      ATTENTION!                      ";
	SetPos(32, 9);
	cout << "                                                      ";
	SetPos(32, 10);
	cout << "      Are you sure you want to delete this item?      ";
	SetPos(32, 11);
	cout << "                                                      ";
	SetPos(32, 12);
	if (activeFile == 1) cout << "  " << left << setw(52) << product[elementToBeRemoved].Name;
	else if (activeFile == 2) cout << "  " << left << setw(52) << category[elementToBeRemoved].Name;
	SetPos(32, 13);
	cout << "                                                      ";
	SetPos(32, 14);
	cout << "                                                      ";

	SetColor(8, 0);
	SetPos(32, 15);
	cout << "                    YES        NOT                    ";
	SetPos(32, 16);
	cout << "                                                      ";
	SetColor(0, 15);

	int flashingSpeed = 300;
	Sleep(flashingSpeed);
	SetPos(54, 8);
	SetColor(6, 0);
	cout << "ATTENTION!";
	SetPos(0, 0);

	Sleep(flashingSpeed);
	SetPos(54, 8);
	SetColor(15, 0);
	cout << "ATTENTION!";
	SetPos(0, 0);

	Sleep(flashingSpeed);
	SetPos(54, 8);
	SetColor(6, 0);
	cout << "ATTENTION!";
	SetPos(0, 0);

	Sleep(flashingSpeed);
	SetPos(54, 8);
	SetColor(15, 0);
	cout << "ATTENTION!";
	SetPos(0, 0);

	Sleep(flashingSpeed);
	SetPos(54, 8);
	SetColor(6, 0);
	cout << "ATTENTION!";
	SetPos(0, 0);

	bool yes = 0, no = 0;
	while (1)
	{
		ReadConsoleInput(hWnd, &InputRecord, 1, &Events);      // считывание

		int x = InputRecord.Event.MouseEvent.dwMousePosition.X;
		int y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

		// Подсветка кнопки "YES"
		if (52 <= x && x <= 54 && y == 15 && yes == 0)
		{
			yes = 1;
			SetPos(52, 15);
			SetColor(4, 0);
			cout << "YES";
			SetPos(0, 0);
		}
		else if (!(52 <= x && x <= 54 && y == 15) && yes == 1)
		{
			yes = 0;
			SetPos(52, 15);
			SetColor(8, 0);
			cout << "YES";
			SetPos(0, 0);
		}
		
		// Подсветка кнопки "NOT"
		if (63 <= x && x <= 65 && y == 15 && no == 0)
		{
			no = 1;
			SetPos(63, 15);
			SetColor(10, 0);
			cout << "NOT";
			SetPos(0, 0);
		}
		else if (!(63 <= x && x <= 65 && y == 15) && no == 1)
		{
			no = 0;
			SetPos(63, 15);
			SetColor(8, 0);
			cout << "NOT";
			SetPos(0, 0);
		}

		SetColor(0, 15);

		// Обрабатываем нажатие
		if ((int)InputRecord.Event.MouseEvent.dwButtonState == 1)
		{
			if (52 <= x && x <= 54 && y == 15) return 1;
			else if (63 <= x && x <= 65 && y == 15) return 0;
			else cout << "\a";
		}
		
		//SetPos(50, 25);
		//cout << "x - " << x << " | y - " << y << "     m -      ";
	}

	return 0;
}

// Проверка правильности даты
bool CheckingIfTheDateIsCorrect(int d, int m, int y)
{	
	// 31      1
	// 28/29   2   
	// 31      3
	// 30      4
	// 31      5
	// 30      6
	// 31      7
	// 31      8
	// 30      9
	// 31      10
	// 30      11
	// 31      12

	int daysInAMonth = 28;
	if (!(y % 400) || y % 100 && !(y % 4)) daysInAMonth = 29;

	if (1 <= m && m <= 12)
	{
		switch (m)
		{
		case 4:
		case 6:
		case 9:
		case 11:
			daysInAMonth = 30;
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			daysInAMonth = 31;
			break;
		}
		if (1 <= d && d <= daysInAMonth) return 1;
	}
	
	return 0;
}

// Подсчёт дней между двумя датами
int NumberOfDaysBetweenDates(int d1, int m1, int y1, int d2, int m2, int y2)
{
	int days = 0;

	while (d1 != d2 || m1 != m2 || y1 != y2)
	{
		NextDate(d1, m1, y1);
		++days;
	}
	return days;
}

// Определение следующей даты
void NextDate(int& d, int& m, int& y)
{
	++d;

	int f = 28;
	if (!(y % 400) || y % 100 && !(y % 4)) f = 29;

	if ((m == 2 && d > f) ||
	    ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) ||
		((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10) && d > 31)) {
		d = 1;
		++m;
	}
	else if (m == 12 && d > 31) {
		d = 1;
		m = 1;
		++y;
	}
}

// Проверка последовательности дат
bool DateSequenceCheck(int d1, int m1, int y1, int d2, int m2, int y2)
{
	if ((y1 < y2) || 
		(y1 == y2 && m1 < m2) ||
		(y1 == y2 && m1 == m2 && d1 <= d2)) return 1; // Если первая дата раньше второй
	return 0; 
}

// Создание нового файла с обновлёнными ценнами
void CreateNewFile()
{
	ofstream f("Sale.txt");

	for (int i = 0; i < n; ++i) 
	{
		bool x = 1;
		f << left
			<< setw(width[1]) << product[i].Name
			<< setw(width[2]) << product[i].UnitsOfMeasure;
		for (int j = 0; j < nn; ++j)
			if (product[i].CategoryCode == category[j].CategoryCode)
			{
				x = 0;
				f << setw(width2[1]) << category[j].Name;
				j = nn;
			}

		if (x) f << setw(width2[1]) << 0;
		
		f << setw(width[4]) << product[i].Quantity;
		
		if (product[i].DateOfManufacture[0] < 10) f << 0;
		f << product[i].DateOfManufacture[0] << ".";

		if (product[i].DateOfManufacture[1] < 10) f << 0;
		f << product[i].DateOfManufacture[1] << "." << setw(width[5] - 6) << product[i].DateOfManufacture[2];

		if (product[i].ExpiryDate[0] < 10) f << 0;
		f << product[i].ExpiryDate[0] << ".";

		if (product[i].ExpiryDate[1] < 10) f << 0;
		f << product[i].ExpiryDate[1] << "." << setw(width[6] - 6) << product[i].ExpiryDate[2]
			<< setw(width[7]) << newPrice[i] << endl;
	}

	f.close();
}

// Расчёт новых цен
void CalculationOfNewPrices()
{
	GetLocalTime(&st);
	int d = st.wDay;
	int m = st.wMonth;
	int y = st.wYear;

	int days1 = 0, days2 = 0;

	for (int i = 0; i < n; ++i)
	{
		days1 = NumberOfDaysBetweenDates(product[i].DateOfManufacture[0], product[i].DateOfManufacture[1], product[i].DateOfManufacture[2], product[i].ExpiryDate[0], product[i].ExpiryDate[1], product[i].ExpiryDate[2]);
		days2 = NumberOfDaysBetweenDates(product[i].DateOfManufacture[0], product[i].DateOfManufacture[1], product[i].DateOfManufacture[2], d, m, y);

		if (DateSequenceCheck(product[i].ExpiryDate[0], product[i].ExpiryDate[1], product[i].ExpiryDate[2], d, m, y)) // Проверка, если срок годности истёк
		{
			newPrice[i] = 0;
		}
		else if (days1 / 2 <= days2)
		{
			newPrice[i] = 80 * product[i].Price / 100; // Скидка на товар - 20%
		}
		else if (days1 / 4 <= days2 * 3)
		{
			newPrice[i] = product[i].Price / 2; // Скидка на товар - 50%
		}
		else
		{
			newPrice[i] = product[i].Price; // Скидка на товар - 0%
		}
	}
}

// Поиск самой большой цены
float  maximumPrice = 0, maximumPriceBefore = 0;
void MostExpensiveProducts()
{
	float maxPrice = 0;
	productExpensiveN = 0;
	for (int i = 0; i < n; ++i)
		if (maxPrice < newPrice[i])
			maxPrice = newPrice[i];

	if (maxPrice != maximumPrice)
	{
		maximumPriceBefore = maximumPrice;
		maximumPrice = maxPrice;
	}

	for (int i = 0; i < n; ++i)
		if (maxPrice == newPrice[i])
		{
			productExpensive[productExpensiveN] = product[i];
			if (strlen(productExpensive[productExpensiveN].Name) > 19) Cut(productExpensive[productExpensiveN].Name, 19);
			++productExpensiveN;
			// Нужно добавить запись новой цены ???
		}
}

// Показ самых дорогих продуктов
void ShowMostExpensiveProducts()
{
	SetColor(15, 0);
	for (int i = 0; i < productExpensiveN; ++i)
	{
		SetPos(16, 24 + i);
		cout << left << setw(3) << i + 1 + demolitionMostExpensiveProducts << setw(19) << productExpensive[i + demolitionMostExpensiveProducts].Name;

		if (i == 1) break;
	}

	SetPos(16, 27);
	SetColor(10, 0);
	cout << left << setw(9) << maximumPrice << " ";
	if (maximumPrice - maximumPriceBefore > 0)
	{
		cout << "+" << left << setw(9) << maximumPrice - maximumPriceBefore;
	}
	else
	{
		if (maximumPrice - maximumPriceBefore < 0) SetColor(4, 0);
		else SetColor(15, 0);
		cout << left << setw(9) << maximumPrice - maximumPriceBefore;
	}
	SetPos(0, 0);
}

// Поиск самой маленькой цены
float minimumPrice = 0, minimumPriceBefore = 0;
void TheCheapestProducts()
{
	float minPrice = newPrice[0];
	productCheapN = 0;
	for (int i = 1; i < n; ++i)
		if (minPrice > newPrice[i])
			minPrice = newPrice[i];

	if (minPrice != minimumPrice)
	{
		minimumPriceBefore = minimumPrice;
		minimumPrice = minPrice;
	}

	for (int i = 0; i < n; ++i)
		if (minPrice == newPrice[i])
		{
			productCheap[productCheapN] = product[i];
			if (strlen(productCheap[productCheapN].Name) > 19) Cut(productCheap[productCheapN].Name, 19);
			++productCheapN;
			// Нужно добавить запись новой цены ???
		}
}

// Показ самых дешевых продуктов
void ShowTheCheapestProducts()
{
	SetColor(15, 0);
	for (int i = 0; i < productCheapN; ++i)
	{
		SetPos(92, 24 + i);
		cout << left << setw(3) << i + 1 + demolitionTheCheapestProducts << setw(19) << productCheap[i + demolitionTheCheapestProducts].Name;

		if (i == 1) break;
	}

	SetPos(92, 27);
	SetColor(10, 0);
	cout << left << setw(9) << minimumPrice << " ";
	if (minimumPrice - minimumPriceBefore > 0)
	{
		cout << "+" << left << setw(9) << minimumPrice - minimumPriceBefore;
	}
	else
	{
		if (minimumPrice - minimumPriceBefore < 0) SetColor(4, 0);
		else SetColor(15, 0);
		cout << left << setw(9) << minimumPrice - minimumPriceBefore;
	}
	SetPos(0, 0);
}

// Сохранение двух основных файлов
void Save()
{
	// Сохранение первого файла
	ofstream f(pathToFirstFile);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < strlen(product[i].Name); ++j)
			if (product[i].Name[j] == ' ')
				product[i].Name[j] = '_';

		f << left
			<< setw(width[1]) << product[i].Name
			<< setw(width[2]) << product[i].UnitsOfMeasure
			<< right << setfill('0') << setw(6) << product[i].CategoryCode << left << setfill(' ')
			<< setw(width[3] - 6) << " "
			<< setw(width[4]) << product[i].Quantity;

		for (int j = 0; j < strlen(product[i].Name); ++j)
			if (product[i].Name[j] == '_')
				product[i].Name[j] = ' ';

		if (product[i].DateOfManufacture[0] < 10) f << 0;
		f << product[i].DateOfManufacture[0] << ".";

		if (product[i].DateOfManufacture[1] < 10) f << 0;
		f << product[i].DateOfManufacture[1] << "." << setw(width[5] - 6) << product[i].DateOfManufacture[2];

		if (product[i].ExpiryDate[0] < 10) f << 0;
		f << product[i].ExpiryDate[0] << ".";

		if (product[i].ExpiryDate[1] < 10) f << 0;
		f << product[i].ExpiryDate[1] << "." << setw(width[6] - 6) << product[i].ExpiryDate[2]
			<< setw(width[7]) << product[i].Price << endl;
	}

	f.close();

	// Сохранение второго файла
	ofstream g(pathToSecondFile);

	for (int i = 0; i < nn; ++i)
	{
		for (int j = 0; j < strlen(category[i].Name); ++j)
			if (category[i].Name[j] == ' ')
				category[i].Name[j] = '_';

		g << right << setfill('0') << setw(6) << category[i].CategoryCode
		  << left  << setfill(' ') << setw(width2[1] - 6) << " "
		  << setw(width2[2]) << category[i].Name << endl;

		for (int j = 0; j < strlen(category[i].Name); ++j)
			if (category[i].Name[j] == '_')
				category[i].Name[j] = ' ';
	}

	g.close();
}

//// СОРТИРОВКИ

/// Первая стрктура

// По Name // Нужно проверить
void SortProductsByName(int inOrder)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (inOrder)
			{
				if (strcmp(product[j].Name, product[j + 1].Name) > 0)
					swap(product[j], product[j + 1]);
			}
			else
			{
				if (strcmp(product[j].Name, product[j + 1].Name) < 0)
					swap(product[j], product[j + 1]);
			}
		}
	}
}

// По UnitsOfMeasure // Нужно проверить
void SortProductsByUnitsOfMeasure(int inOrder)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (inOrder)
			{
				if (strcmp(product[j].UnitsOfMeasure, product[j + 1].UnitsOfMeasure) > 0)
					swap(product[j], product[j + 1]);
			}
			else
			{
				if (strcmp(product[j].UnitsOfMeasure, product[j + 1].UnitsOfMeasure) < 0)
					swap(product[j], product[j + 1]);
			}
		}
	}
}

// По CategoryCode // Нужно проверить
void SortProductsByCategoryCode(int inOrder)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (inOrder)
			{
				if (product[j].CategoryCode > product[j].CategoryCode)
					swap(product[j], product[j + 1]);
			}
			else
			{
				if (product[j].CategoryCode < product[j].CategoryCode)
					swap(product[j], product[j + 1]);
			}
		}
	}
}

// По Quantity // Нужно проверить
void SortProductsByQuantity(int inOrder)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (inOrder)
			{
				if (product[j].Quantity > product[j].Quantity)
					swap(product[j], product[j + 1]);
			}
			else
			{
				if (product[j].Quantity < product[j].Quantity)
					swap(product[j], product[j + 1]);
			}
		}
	}
}

// По DateOfManufacture // Нужно доработать
void SortProductsByDateOfManufacture(int inOrder)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (inOrder)
			{
				if (/* product[j].Quantity > product[j].Quantity */ 1)
					swap(product[j], product[j + 1]);
			}
			else
			{
				if (/* product[j].Quantity < product[j].Quantity */ 1)
					swap(product[j], product[j + 1]);
			}
		}
	}
}

// По ExpiryDate // Нужно доработать
void SortProductsByExpiryDate(int inOrder)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (inOrder)
			{
				if (/* product[j].Quantity > product[j].Quantity */ 1)
					swap(product[j], product[j + 1]);
			}
			else
			{
				if (/* product[j].Quantity < product[j].Quantity */ 1)
					swap(product[j], product[j + 1]);
			}
		}
	}
}

// По Price // Нужно проверить
void SortProductsByPrice(int inOrder)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (inOrder)
			{
				if (product[j].Price > product[j].Price)
					swap(product[j], product[j + 1]);
			}
			else
			{
				if (product[j].Price < product[j].Price)
					swap(product[j], product[j + 1]);
			}
		}
	}
}

/// Вторая структура

// По CategoryCode // Нужно проверить
void SortCategoriesByCategoryCode(int inOrder)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (inOrder)
			{
				if (category[j].CategoryCode > category[j].CategoryCode)
					swap(category[j], category[j + 1]);
			}
			else
			{
				if (category[j].CategoryCode < category[j].CategoryCode)
					swap(category[j], category[j + 1]);
			}
		}
	}
}

// По Name // Нужно проверить
void SortCategoriesByName(int inOrder)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (inOrder)
			{
				if (strcmp(category[j].Name, category[j].Name) > 0)
					swap(category[j], category[j + 1]);
			}
			else
			{
				if (strcmp(category[j].Name, category[j].Name) < 0)
					swap(category[j], category[j + 1]);
			}
		}
	}
}

////

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void SetColor(int text, int bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void SetPos(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Logo()
{
	//120
	//30

	//for (int i = 0; i < 16; ++i)
	//{
	//	SetColor(i, i);
	//	cout << " ";
	//}

	system("color 0F");

	Sleep(1000);
	SetColor(15, 15);
	SetPos(59, 14);
	cout << "  ";
	Sleep(100);
	cout << "  ";
	SetPos(0, 0);
	Sleep(200);
	SetPos(61, 15);
	cout << "  ";
	SetPos(0, 0);
	Sleep(50);
	SetPos(59, 15);
	cout << "  ";
	SetPos(0, 0);
	Sleep(2000);

	for (int i = 0; i < 9; ++i)
	{
		SetColor(15, 15);
		SetPos(59, 16 + i);
		cout << "    ";
		SetColor(0, 0);
		SetPos(59, 14 + i);
		cout << "    "; 
		SetPos(0, 0);
		Sleep(25 + i);
	}

	SetPos(59, 23);
	cout << "    ";
	SetColor(15, 15);
	SetPos(0, 0);
	Sleep(25);

	for (int i = 0; i < 20; ++i)
	{
		SetPos(57 - i * 2, 24);
		cout << "  ";
		SetPos(63 + i * 2, 24);
		cout << "  ";
		SetPos(0, 0);
		Sleep(25 + i);
	}
	
	SetColor(0, 0);
	for (int i = 0; i < 20; ++i)
	{
		SetPos(19 + i * 2, 24);
		cout << "  ";
		SetPos(101 - i * 2, 24);
		cout << "  ";
		SetPos(0, 0);
		Sleep(25 - i);
	}

	SetColor(15, 15);
	for (int i = 0; i < 20; ++i)
	{
		SetPos(57, 24 - i);
		cout << "        ";
		SetPos(0, 0);
		Sleep(10);
	}

	for (int i = 0; i < 8; ++i)
	{
		SetPos(55 - i * 2, 5);
		cout << "  ";
		SetPos(55 - i * 2, 6);
		cout << "  ";
		SetPos(55 - i * 2, 7);
		cout << "  ";
		SetPos(55 - i * 2, 8);
		cout << "  ";
		
		SetPos(65 + i * 2, 5);
		cout << "  ";
		SetPos(65 + i * 2, 6);
		cout << "  ";
		SetPos(65 + i * 2, 7);
		cout << "  ";
		SetPos(65 + i * 2, 8);
		cout << "  ";

		if (i < 6)
		{
			SetPos(65 + i * 2, 13);
			cout << "  ";
			SetPos(65 + i * 2, 14);
			cout << "  ";
			SetPos(65 + i * 2, 15);
			cout << "  ";
			SetPos(65 + i * 2, 16);
			cout << "  ";
		}

		SetPos(0, 0);
		Sleep(10);
	}
	SetPos(0, 0);
	Sleep(500);

	system("color F0");
	SetColor(0, 0);
	for (int i = 0; i < 4; ++i)
	{
		SetPos(41, 5 + i);
		cout << "                                        ";
	}

	for (int i = 0; i < 4; ++i)
	{
		SetPos(57, 9 + i);
		cout << "        ";
	}
	
	for (int i = 0; i < 4; ++i)
	{
		SetPos(57, 13 + i);
		cout << "                    ";
	}
	
	for (int i = 0; i < 8; ++i)
	{
		SetPos(57, 17 + i);
		cout << "        ";
	}
	SetPos(0, 0);
	Sleep(1000);

	system("cls");
	system("color F0");
}

void UpArrow(int x, int y)
{
	int color = 10;
	for (int i = 0; i < 1; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (activeFile) Sleep(50);
			else Sleep(0);

			if (j <= 0)
			{
				// 1
				SetPos(x, y - j);
				SetColor(0, 0);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (j <= 1)
			{
				// 2
				SetPos(x, y + 1 - j);
				cout << "   ";
				SetColor(0, color);
				cout << "      ";
				SetColor(0, 0);
				cout << "   ";
			}

			if (j <= 2)
			{
				// 3
				SetPos(x, y + 2 - j);
				SetColor(0, 0);
				cout << "  ";
				SetColor(0, color);
				cout << "        ";
				SetColor(0, 0);
				cout << "  ";
			}

			if (j <= 3)
			{
				// 4
				SetPos(x, y + 3 - j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (j <= 4)
			{
				// 5
				SetPos(x, y + 4 - j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (j <= 5)
			{
				// 6
				SetPos(x, y + 5 - j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (1 <= j && j <= 6)
			{
				// 7
				SetPos(x, y + 6 - j);
				cout << "            ";
			}

			if (2 <= j && j <= 7)
			{
				// 1
				SetPos(x, y + 7 - j);
				SetColor(0, 0);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (3 <= j && j <= 8)
			{
				// 2
				SetPos(x, y + 8 - j);
				cout << "   ";
				SetColor(0, color);
				cout << "      ";
				SetColor(0, 0);
				cout << "   ";
			}

			if (4 <= j && j <= 9)
			{
				// 3
				SetPos(x, y + 9 - j);
				SetColor(0, 0);
				cout << " ";
				SetColor(0, color);
				cout << "          ";
				SetColor(0, 0);
				cout << " ";
			}

			if (5 <= j && j <= 10)
			{
				// 4
				SetPos(x, y + 10 - j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (6 <= j && j <= 11)
			{
				// 5
				SetPos(x, y + 11 - j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (7 <= j && j <= 12)
			{
				// 6
				SetPos(x, y + 12 - j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}
		}
	}

	for (int i = 0; i < 6; ++i)
	{
		SetPos(x + 12, y + i);
		cout << right << setw(24) << " ";
	}

	ShowMostExpensiveProducts();

	SetColor(0, 15);
}

void Coin(int x, int y)
{
	for (int i = 0; i < 1; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (activeFile) Sleep(50);
			else Sleep(0);

			{
		// 1
		SetPos(x, y);
		SetColor(0, 0);
		cout << "   ";
		SetColor(0, 14);
		cout << "      ";
		SetColor(0, 0);
		cout << "   ";

		// 2
		SetPos(x, y + 1);
		SetColor(0, 0);
		cout << "  ";
		SetColor(0, 14);
		cout << "  ";
		SetColor(0, 15);
		cout << "   ";
		SetColor(0, 6);
		cout << " ";
		SetColor(0, 14);
		cout << "  ";
		SetColor(0, 0);
		cout << "  ";

		// 3
		SetPos(x, y + 2);
		SetColor(0, 0);
		cout << "  ";
		SetColor(0, 14);
		cout << " ";
		SetColor(0, 15);
		cout << " ";
		SetColor(0, 14);
		cout << "    ";
		SetColor(0, 6);
		cout << " ";
		SetColor(0, 14);
		cout << " ";
		SetColor(0, 0);
		cout << "  ";

		// 4
		SetPos(x, y + 3);
		SetColor(0, 0);
		cout << "  ";
		SetColor(0, 14);
		cout << " ";
		SetColor(0, 15);
		cout << " ";
		SetColor(0, 14);
		cout << "    ";
		SetColor(0, 6);
		cout << " ";
		SetColor(0, 14);
		cout << " ";
		SetColor(0, 0);
		cout << "  ";

		// 5
		SetPos(x, y + 4);
		SetColor(0, 0);
		cout << "  ";
		SetColor(0, 14);
		cout << "  ";
		SetColor(0, 15);
		cout << " ";
		SetColor(0, 6);
		cout << "   ";
		SetColor(0, 14);
		cout << "  ";
		SetColor(0, 0);
		cout << "  ";

		// 6
		SetPos(x, y + 5);
		SetColor(0, 0);
		cout << "   ";
		SetColor(0, 14);
		cout << "      ";
		SetColor(0, 0);
		cout << "   ";
	}

			SetColor(0, 15);
			if (j == 0)
			{
				SetPos(x + 3, y);
				cout << "   ";
				SetPos(x + 2, y + 1);
				cout << "  ";
				SetPos(x + 2, y + 2);
				cout << " ";
				SetPos(x + 2, y + 3);
				cout << " ";
			}

			if (j == 1)
			{
				SetPos(x + 7, y);
				cout << "  ";
				SetPos(x + 7, y + 1);
				cout << " ";
				SetPos(x + 4, y + 2);
				cout << "   ";
				SetPos(x + 4, y + 3);
				cout << " ";
				SetPos(x + 2, y + 4);
				cout << " ";
			}

			if (j == 2)
			{
				SetPos(x + 8, y + 1);
				cout << "  ";
				SetPos(x + 7, y + 2);
				cout << "  ";
				SetPos(x + 5, y + 3);
				cout << "   ";
				SetPos(x + 4, y + 4);
				cout << "  ";
				SetPos(x + 3, y + 5);
				cout << "  ";
			}

			if (j == 3)
			{
				SetPos(x + 9, y + 2);
				cout << " ";
				SetPos(x + 8, y + 3);
				cout << "  ";
				SetPos(x + 7, y + 4);
				cout << "   ";
				SetPos(x + 6, y + 5);
				cout << "   ";
			}

			SetPos(0, 0);
		}
		SetColor(0, 0);
	}

	for (int i = 0; i < 6; ++i)
	{
		SetPos(x + 12, y + i);
		cout << right << setw(24) << " ";
	}

	ShowTheCostOfAllProducts();

	SetColor(0, 15);
}

void ArrowToDown(int x, int y)
{
	y += 5;
	int color = 4;
	for (int i = 0; i < 1; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (activeFile) Sleep(50);
			else Sleep(0);

			if (j <= 0)
			{
				// 1
				SetPos(x, y + j);
				SetColor(0, 0);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (j <= 1)
			{
				// 2
				SetPos(x, y - 1 + j);
				cout << "   ";
				SetColor(0, color);
				cout << "      ";
				SetColor(0, 0);
				cout << "   ";
			}

			if (j <= 2)
			{
				// 3
				SetPos(x, y - 2 + j);
				SetColor(0, 0);
				cout << "  ";
				SetColor(0, color);
				cout << "        ";
				SetColor(0, 0);
				cout << "  ";
			}

			if (j <= 3)
			{
				// 4
				SetPos(x, y - 3 + j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (j <= 4)
			{
				// 5
				SetPos(x, y - 4 + j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (j <= 5)
			{
				// 6
				SetPos(x, y - 5 + j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (1 <= j && j <= 6)
			{
				// 7
				SetPos(x, y - 6 + j);
				cout << "            ";
			}

			if (2 <= j && j <= 7)
			{
				// 1
				SetPos(x, y - 7 + j);
				SetColor(0, 0);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (3 <= j && j <= 8)
			{
				// 2
				SetPos(x, y - 8 + j);
				cout << "   ";
				SetColor(0, color);
				cout << "      ";
				SetColor(0, 0);
				cout << "   ";
			}

			if (4 <= j && j <= 9)
			{
				// 3
				SetPos(x, y - 9 + j);
				SetColor(0, 0);
				cout << " ";
				SetColor(0, color);
				cout << "          ";
				SetColor(0, 0);
				cout << " ";
			}

			if (5 <= j && j <= 10)
			{
				// 4
				SetPos(x, y - 10 + j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (6 <= j && j <= 11)
			{
				// 5
				SetPos(x, y - 11 + j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}

			if (7 <= j && j <= 12)
			{
				// 6
				SetPos(x, y - 12 + j);
				cout << "     ";
				SetColor(0, color);
				cout << "  ";
				SetColor(0, 0);
				cout << "     ";
			}
		}
	}

	for (int i = 0; i < 6; ++i)
	{
		SetPos(x + 12, y - 5 + i);
		cout << right << setw(24) << " ";
	}

	ShowTheCheapestProducts();

	SetColor(0, 15);
}
