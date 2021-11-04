#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <stdio.h>

//importuje inne pliki
#include "miner.h"
#include "shop.h"


#define _WIN32_WINNT 0x0601

using namespace std;

//Dodanie mozliwoœci zmiany czcionki przy uzyciu debugera w code block
typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

extern "C" {
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
}

// changing a color of the text
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//utworzenie zaczepu
int color_chg(int color){
    SetConsoleTextAttribute(hConsole, color);
}

// Draws a random material with a random amount
void random_material(){
    int which_material = rand() % 100 + 1;
    int how_many_materials = rand() % 15 +1;

    cout << "You found ";

    if(which_material <= 1){
        color_chg(14);
        cout<<how_many_materials;
        color_chg(11);
        cout<<" GOLD";
        color_chg(15);
    }
    else if(which_material >5 && which_material <= 15){
    	color_chg(10);
        cout<<how_many_materials;
    	color_chg(14);
    	cout<<" SILVER";
    	color_chg(15);
	}
	else if(which_material >15 && which_material <= 50){
		color_chg(11);
        cout<<how_many_materials;
		color_chg(8);
		cout<<" IRON";
		color_chg(15);
	}
	else{
		color_chg(11);
        cout<<how_many_materials;
		color_chg(12);
		cout<<" BRONZE ";
		color_chg(15);
	}
}

//TODO: zmieniic na wieksza liczbe dlugosci
//losuje czas kopania mineralu
int recap_check(int recap){
	if(recap < 2){
    	recap = rand() % 2 + 1;
    	return 0;
	}
	else{
		return 1;
	}
}

//TODO: ulepszyc to funkcje i zamienic ja z system cls
//czysci ekran(odpowiednik cls)
void clearScreen(){
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}


int main()
{
    //zmienne
	string etykieta;
    int recap = 0;
    int check = 0;
    int choice;

	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //fullscreen
	srand(time(NULL)); //uruchomienie funckji zwijanzanej z losowaniem liczb

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);

	etykieta:
    color_chg(15);
	cout << R"(


                            ___  ________ _   _ _____ _   _ _____
                            |  \/  |_   _| \ | |_   _| \ | |  __ \
                            | .  . | | | |  \| | | | |  \| | |  \/
                            | |\/| | | | | . ` | | | | . ` | | __
                            | |  | |_| |_| |\  |_| |_| |\  | |_\ \
                            \_|  |_/\___/\_| \_/\___/\_| \_/\____/
       _____ _                 _       _               _____  __     ___  _       _
      /  ___(_)               | |     | |             |  _  |/  |   / _ \| |     | |
      \ `--. _ _ __ ___  _   _| | __ _| |_ ___  _ __  | |/' |`| |  / /_\ \ |_ __ | |__   __ _
       `--. \ | '_ ` _ \| | | | |/ _` | __/ _ \| '__| |  /| | | |  |  _  | | '_ \| '_ \ / _` |
      /\__/ / | | | | | | |_| | | (_| | || (_) | |    \ |_/ /_| |_ | | | | | |_) | | | | (_| |
      \____/|_|_| |_| |_|\__,_|_|\__,_|\__\___/|_|     \___(_)___/ \_| |_/_| .__/|_| |_|\__,_| by Kacper Kobalczyk i Michal Garnys
                                                                           | |
                                                                           |_|

		)";
    cout << "\n"
        << "Welcome to Mining simulator 0.1.2!\n"
        << "I have a hope u will have a small amount of fun :D "
        << "\n"
        << "\n"
        << "\n1.[MINING]\n"
        << "\n2.[GO TO SHOP]\n"
        << "\n3.[END GAME]\n"
        << "\n";

    cout<< "What do you want to do: ";
    cin >> choice;
    switch(choice){

    	case 1:
	        system("cls");
	        while(check==0){
	        //TODO: zmieniic na wieksza liczbe dlugosci
			recap = rand() % 2 + 1;
			check = recap_check(recap);
			}
	        for (int i = 0; i < recap; i++)
	        {
	            system("cls");
	            color_chg(10);
	            cout << miner_1;
	            Sleep(200);
	            system("cls");
	            Sleep(100);
	            color_chg(11);
	            cout << miner_2;
	            Sleep(200);
	            system("cls");
	            Sleep(100);
	            color_chg(12);
	            cout << miner_3;
	            Sleep(200);
	            system("cls");
	            Sleep(100);
	            color_chg(13);
	            cout << miner_2;
	            Sleep(200);
	            system("cls");
	            Sleep(100);
	        }
	        color_chg(15);
	        system("cls");
	        cout << "\n";
	        random_material();
	        cout<<"\n";
	        cout<<"\nClick any button !";
			getch();
	        system("cls");
	        goto etykieta;
	        break;

	    case 2:
	            system("cls");
	            color_chg(10);
	            cout << shop_1;
	            Sleep(100);
	            system("cls");
	            Sleep(100);
	            cfi.dwFontSize.X = 0;
				cfi.dwFontSize.Y = 20;
				SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	            color_chg(11);
	            cout << shop_2;
	            Sleep(100);
	            system("cls");
	            Sleep(100);
	            cfi.dwFontSize.X = 0;
				cfi.dwFontSize.Y = 24;
				SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	            color_chg(12);
	            cout << shop_3;
	            Sleep(100);
	            system("cls");
	            Sleep(100);
	            cfi.dwFontSize.X = 0;
				cfi.dwFontSize.Y = 28;
				SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	            color_chg(13);
	            cout << shop_4;
	            Sleep(100);
	            system("cls");
	            Sleep(100);
	            cfi.dwFontSize.X = 0;
				cfi.dwFontSize.Y = 32;
				SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	            color_chg(14);
	            cout << shop_5;
	    	getch();
	    	color_chg(15);
	    	system("cls");
	    	cfi.dwFontSize.X = 0;
			cfi.dwFontSize.Y = 16;
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	    	goto etykieta;

		case 3:
			system("cls");
			cfi.dwFontSize.X = 0;
			cfi.dwFontSize.Y = 42;
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
			cout<<"See you again!!";
			exit(0);
    }
    return 0;





}
