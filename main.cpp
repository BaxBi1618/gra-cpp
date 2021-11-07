#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include <string>
// ascii art file import
#include "miner.h"
#include "shop.h"


#define _WIN32_WINNT 0x0601

using namespace std;

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

// Changing a color of the text
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//utworzenie zaczepu
int color_chg(int color){
    SetConsoleTextAttribute(hConsole, color);
}

// Draws a random material with a random amount
struct Foo
{
     string value1;
     int value2;
};

Foo random_material(){
    int which_material = rand() % 100 + 1;
    int how_many_materials = rand() % 15 +1;
    string material_1;
    cout << "You found ";

    if(which_material <= 5){
        color_chg(14);
        cout<<how_many_materials;
        color_chg(11);
        cout<<" GOLD";
        color_chg(15);
        material_1 = "gold";
    }
    else if(which_material >5 && which_material <= 15){
    	color_chg(10);
        cout<<how_many_materials;
    	color_chg(14);
    	cout<<" SILVER";
    	color_chg(15);
        material_1 = "silver";
	}
	else if(which_material >15 && which_material <= 50){
		color_chg(11);
        cout<<how_many_materials;
		color_chg(8);
		cout<<" IRON";
		color_chg(15);
        material_1 =  "iron";
	}
	else{
		color_chg(11);
        cout<<how_many_materials;
		color_chg(12);
		cout<<" BRONZE ";
		color_chg(15);
        material_1 = "bronze";
	}
	Foo result = {material_1,how_many_materials};
	return result;
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

	// change font size function
    void font_size(int f_size){
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.dwFontSize.X = 0;
        cfi.dwFontSize.Y = f_size;
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    }

// prints a ascii art function
void print_art(string art, int color,int first_sleep,int second_sleep,bool cls)
{
    color_chg(color);
    cout << art;
    if(cls == true){
        Sleep(first_sleep);
        system("cls");
        Sleep(second_sleep);
    }
}

//TODO: ulepszyc to funkcje i zamienic ja z system cls
//czysci ekran(odpowiednik cls)
void clearScreen(){
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

int main(void)
{
    //zmienne
	string etykieta,line,material,sure,bank;
	Foo result;
    int recap = 0;
    int check = 0;
    int choice,gold,silver,iron,bronze,liczba,czynnsoc_bank,czynnosc_sklep;

	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //fullscreen
	srand(time(NULL)); //uruchomienie funckji zwijanzanej z losowaniem liczb

	etykieta:
    //sprawdza stan ekwipunku (matera³y)
	//zawartoœæ pliku powinna byæ taka
	//1 linijka gold
	//2 linijka silver
	//3 linijka iron
	//4 bronze
    char filename[ ] = "Ekwipunek.txt";
    fstream ekwipunek;
    ekwipunek.open(filename, std::fstream::in | std::fstream::out);


    // If file does not exist, Create new file
    if (!ekwipunek )
    {
        ekwipunek.open(filename,  fstream::in | fstream::out | fstream::trunc);
        ekwipunek <<"0\n";
        ekwipunek <<"0\n";
        ekwipunek <<"0\n";
        ekwipunek <<"0\n";
        ekwipunek.close();
        goto etykieta;

    }
    else
    {    // use existing file
        int i=0;
        while(getline(ekwipunek,line))
        {
            if(i==0){
                gold= stoi(line);
            }
            else if(i==1){
                silver = stoi(line);
            }
            else if(i==2){
                iron = stoi(line);
            }
            else if(i==3){
                bronze = stoi(line);
            }
            i++;
        }

        ekwipunek.close();
        cout<<"\n";
    }
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
        << "\n3.[BANK]\n"
        << "\n4.[END GAME]\n"
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
	            print_art(miner_1, 10, 200, 100,true);
	            print_art(miner_2, 12, 200, 100,true);
	            print_art(miner_3, 13, 200, 100,true);
	            print_art(miner_2, 11, 200, 100,true);
	        }
	        color_chg(15);
	        system("cls");
	        cout << "\n";
            result = random_material();
            material = result.value1;
            liczba = result.value2;
            ekwipunek.open(filename, std::fstream::in | std::fstream::out);
            if(material == "gold"){
                ekwipunek<<gold+liczba<<"\n";
                ekwipunek<<silver<<"\n";
                ekwipunek<<iron<<"\n";
                ekwipunek<<bronze<<"\n";
            }
            else if(material == "silver"){
                ekwipunek<<gold<<"\n";
                ekwipunek<<silver<<"\n";
                ekwipunek<<iron<<"\n";
                ekwipunek<<bronze<<"\n";
            }
            else if(material == "iron"){
                ekwipunek<<gold<<"\n";
                ekwipunek<<silver<<"\n";
                ekwipunek<<iron+liczba<<"\n";
                ekwipunek<<bronze<<"\n";
            }
            else if(material == "bronze"){
                ekwipunek<<gold<<"\n";
                ekwipunek<<silver<<"\n";
                ekwipunek<<iron<<"\n";
                ekwipunek<<bronze+liczba<<"\n";
            }
            ekwipunek.close();
	        cout<<"\n";
	        cout<<"\nClick any button !";
			getch();
	        system("cls");
	        goto etykieta;
	        break;

	    case 2:

                system("cls");
                print_art(shop_1,10,100,100,true);
                font_size(20);
				print_art(shop_2,11,100,100,true);
	            font_size(24);
				print_art(shop_3,12,100,100,true);
	            font_size(28);
				print_art(shop_4,13,100,100,true);
	            font_size(32);
                print_art(shop_5,14,100,100,true);
                font_size(18);
                print_art(shop_6,15,1,1,false);
                cout<<"\n\n\n---------------------------------------------------------\n\n\n";
                color_chg(10);
                cout<<"1.Buy new tools\n";
                color_chg(11);
                cout<<"2.Sell materials\n";
                color_chg(12);
                cout<<"3.Sell tools\n";
                color_chg(14);
                cout<<"4.Leave shop\n";
                color_chg(15);
                cout<<"What do you want to do: ";
                cin>>czynnosc_sklep;
                if(czynnosc_sklep==1){
                    color_chg(15);
                    system("cls");
                    font_size(18);
                    goto etykieta;
                }
                else if(czynnosc_sklep == 4){
                    color_chg(15);
                    system("cls");
                    font_size(18);
                    goto etykieta;
                }
                else{
                    color_chg(15);
                    system("cls");
                    font_size(18);
                    goto etykieta;
                }


        case 3:
            bank:
            system("cls");
            font_size(50);
            color_chg(11);
            cout<<"Gold: "<<gold<<endl;
            color_chg(14);
            cout<<"Silver: "<<silver<<endl;
            color_chg(8);
            cout<<"Iron: "<<iron<<endl;
            color_chg(12);
            cout<<"Bronze: "<<bronze<<endl;
            color_chg(15);
            cout<<"\n1.Leave bank\n"
                <<"2.Clear the sejf\n\n"
                <<"What do you want to do: ";
            cin>>czynnsoc_bank;
            if(czynnsoc_bank == 1){
                color_chg(15);
                system("cls");
                font_size(18);
                goto etykieta;
            }
            else if(czynnsoc_bank == 2){
                    color_chg(12);
                    cout<<"\nAre you sure? You will lost all your minerals!! [T/N]\n\n";
                    color_chg(15);
                    cout<<"And what: ";
                    cin>>sure;
                    if(sure == "T" || sure =="t"){
                        ekwipunek.open(filename, std::fstream::in | std::fstream::out);
                        for(int i = 0; i < 4;i++){
                            ekwipunek<<"0\n";
                        }
                        ekwipunek.close();
                        color_chg(15);
                        system("cls");
                        font_size(18);
                        goto etykieta;
                    }
                    else if(sure == "N" || sure == "n"){
                        goto bank;
                    }
                    else{
                        goto bank;
                    }

            }
            else{
                goto etykieta;
            }
		case 4:
			system("cls");
			font_size(42);
			cout<<"Hope to see you again!!";
			exit(0);
    }
    return 0;





}
