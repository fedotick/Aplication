#pragma once
#include <Windows.h>

struct Products
{
	int   Id;
	char  Name[256];            // 1 
	char  UnitsOfMeasure[8];    // 2
	int   CategoryCode;         // 3
	float Quantity;             // 4
	int   DateOfManufacture[3]; // 5
	int   ExpiryDate[3];        // 6
	float Price;                // 7
};

struct Categories
{
	int   CategoryCode;         // 1
	char  Name[256];            // 2
};

extern Products product[102];
extern Products productCheap[102];
extern Products productExpensive[102];
extern Products oneCategory[102];
extern Categories category[102];
extern float newPrice[102];
extern int n, nn, nnn;

void CreateNew(int x);
void Menu();
char* GetFileName(char* path);
char* ShortenTheFileName(char* fileName, int symbols);
bool CheckIfItIsATextFile();
bool ReadFirstFile();
bool ReadSecondFile();
void Show(int x);
void Clear(int y);
void Edit(int pos);
int  CodeSelection(int x, int y, int amount);                                  // Выбор кода
void ShowCodeList(int x, int y, int amount, int beginningWith);                // Показать список кодов
void OverwritingProductCode(int code, int newCode); 
void CategoryNotFound();
void Add(int pos);
void ShowAllCategory(int pos);
bool CheckIfThereIsACode(int cod);
void Cut(char* str, int simbols);
void Delete(int y);
void TheCostOfAllProducts();
void ShowTheCostOfAllProducts();
bool Attention(int elementToBeRemoved);                                        // Подтверждение удаления
bool CheckingIfTheDateIsCorrect(int dd, int mm, int yyyy);
int  NumberOfDaysBetweenDates(int d1, int m1, int y1, int d2, int m2, int y2); // Проверка последовательности дат
void NextDate(int& d, int& m, int& y);
bool DateSequenceCheck(int d1, int m1, int y1, int d2, int m2, int y2);
void CreateNewFile();
void Save();
void Logics(int x, int y, int m);

////
void CalculationOfNewPrices();
void MostExpensiveProducts();
void ShowMostExpensiveProducts();
void TheCheapestProducts();
void ShowTheCheapestProducts();
void SortProductsByName(int inOrder);
void SortProductsByUnitsOfMeasure(int inOrder);
void SortProductsByCategoryCode(int inOrder);
void SortProductsByQuantity(int inOrder);
void SortProductsByDateOfManufacture(int inOrder);
void SortProductsByExpiryDate(int inOrder);
void SortProductsByPrice(int inOrder);
void SortCategoriesByCategoryCode(int inOrder);
void SortCategoriesByName(int inOrder);
////

/////////////////////////////////////
/////////////////////////////////////

void SetColor(int text, int bg);
void SetPos(int x, int y);
void SetOpenFileParams(HWND hwnd);

///////////////////////////////
///////////////////////////////

void Logo();
void UpArrow(int x, int y);
void ArrowToDown(int x, int y);
void Coin(int x, int y);