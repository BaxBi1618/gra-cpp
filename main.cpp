
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

string shop_item_buy(int number,int item_lvl,string item){

    if(item_lvl == 0){
        cout<<number<<". good "<<item<<" [lvl 1]\n";
    }
    else if(item_lvl == 1){
        cout<<number<<". strong "<<item<<" [lvl 2]\n";
    }
    else if(item_lvl == 2){
        cout<<number<<". ultra strong "<<item<<" [lvl 3]\n";
    }
}

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
	string etykieta,line,material,sure,bank,shop;
	Foo result;
    int recap = 0;
    int check = 0;
    int choice,gold,silver,iron,bronze,money;

    //zmienne bank
    int czynnsoc_bank;

    //narzedzia
    int wiadro,kilof,latarka;

    //zmienne sklep
    int czynnosc_sklep,buy_tools_czynnosc_sklep;
        //sprzedaż materiałów
        int total_sell,liczba;
            //minerały
                int money_gold,money_silver,money_iron,money_bronze;

	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //fullscreen
	srand(time(NULL)); //uruchomienie funckji zwijanzanej z losowaniem liczb

	etykieta:
    //sprawdza stan ekwipunku (matera³y)
	//zawartoœæ pliku powinna byæ taka
	//1 linijka gold
	//2 linijka silver
	//3 linijka iron
	//4 bronze
    char filename_1[ ] = "Ekwipunek.txt";
    char filename_2[ ] = "Portfel.txt";
    char filename_3[ ] = "Narzedzia.txt";
    fstream ekwipunek,portfel,narzedzia;
    ekwipunek.open(filename_1, std::fstream::in | std::fstream::out);
    portfel.open(filename_2, std::fstream::in | std::fstream::out);
    narzedzia.open(filename_3,std::fstream::in | std::fstream::out);

    // If file does not exist, Create new file
    if(!ekwipunek )
    {
        ekwipunek.open(filename_1,  fstream::in | fstream::out | fstream::trunc);
        ekwipunek <<"0\n";
        ekwipunek <<"0\n";
        ekwipunek <<"0\n";
        ekwipunek <<"0\n";
        ekwipunek.close();
        goto etykieta;

    }
    if(!portfel){
        portfel.open(filename_2,  fstream::in | fstream::out | fstream::trunc);
        portfel <<"0\n";
        portfel.close();
        goto etykieta;
    }
    if(!narzedzia){
        narzedzia.open(filename_3,  fstream::in | fstream::out | fstream::trunc);
        narzedzia<<"0\n";
        narzedzia<<"0\n";
        narzedzia<<"0\n";
        narzedzia.close();
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
        while(getline(portfel,line))
        {
            money = stoi(line);
        }
        i=0;
        while(getline(narzedzia,line))
        {
            if(i==0){
                wiadro = stoi(line);
            }
            else if(i==1){
                kilof = stoi(line);
            }
            else if(i==2){
                latarka = stoi(line);
            }
            i++;
        }
        portfel.close();
        ekwipunek.close();
        narzedzia.close();
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
            if(material == "gold"){
                gold = gold+liczba;
            }
            else if(material == "silver"){
                silver=silver+liczba;
            }
            else if(material == "iron"){
                iron=iron+liczba;
            }
            else if(material == "bronze"){
                bronze= bronze+liczba;
            }
            ekwipunek.open(filename_1, std::fstream::in | std::fstream::out);
            ekwipunek<<gold<<"\n";
            ekwipunek<<silver<<"\n";
            ekwipunek<<iron<<"\n";
            ekwipunek<<bronze<<"\n";
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
                shop:
                font_size(18);
                print_art(shop_6,15,1,1,false);


                cout<<"\n\n\n---------------------------------------------------------\n\n\n";
                color_chg(10);
                cout<<"1.Buy new tools\n";
                color_chg(11);
                cout<<"2.Sell materials\n";
                color_chg(14);
                cout<<"3.Leave shop\n";
                color_chg(15);
                cout<<"What do you want to do: ";
                cin>>czynnosc_sklep;
                if(czynnosc_sklep == 1){
                    system("cls");
                    font_size(50);
                    color_chg(12);
                    cout<<"Stuff for sell\n\n";
                    color_chg(11);
                    if(wiadro > 2 && kilof > 2 && latarka > 2){
                        cout<<"You already have the best tools\n\n";
                    }
                    else{
                        shop_item_buy(1,wiadro,"bucket");
                        shop_item_buy(2,kilof,"pickaxe");
                        shop_item_buy(3,latarka,"torch");
                    }
                    color_chg(12);
                    cout<<"Other options\n\n";
                    color_chg(11);
                    cout<<"4.guide\n";
                    cout<<"5.back\n\n";
                    color_chg(14);
                    cout<<"What do you want to do: ";
                    cin>>buy_tools_czynnosc_sklep;
                    narzedzia.open(filename_3, std::fstream::in | std::fstream::out);
                    if(buy_tools_czynnosc_sklep == 1){
                        if(wiadro < 3){
                            wiadro = wiadro+1;
                            narzedzia<<wiadro<<endl;
                            narzedzia<<kilof<<endl;
                            narzedzia<<latarka<<endl;
                            narzedzia.close();
                        }
                        else if(wiadro >2){
                            system("cls");
                            color_chg(12);
                            cout<<"\nYou already have the best bucket\n";
                            cout<<"\nClick any button\n";
                            getch();
                        }
                        system("cls");
                        goto shop;
                    }
                    else if(buy_tools_czynnosc_sklep == 2){
                        if(kilof < 3){
                            kilof= kilof+1;
                            narzedzia<<wiadro<<endl;
                            narzedzia<<kilof<<endl;
                            narzedzia<<latarka<<endl;
                            narzedzia.close();
                        }
                        else if(kilof >2){
                            system("cls");
                            color_chg(12);
                            cout<<"\nYou already have the best pickaxe\n";
                            cout<<"\nClick any button\n";
                            getch();
                        }
                        system("cls");
                        goto shop;

                    }
                    else if(buy_tools_czynnosc_sklep == 3){
                        if(latarka < 3){
                            latarka = latarka+1;
                            narzedzia<<wiadro<<endl;
                            narzedzia<<kilof<<endl;
                            narzedzia<<latarka;
                            narzedzia.close();
                        }
                        else if(latarka >2){
                            system("cls");
                            color_chg(12);
                            cout<<"\nYou already have the best torch\n";
                            cout<<"\nClick any button\n";
                            getch();
                        }

                        system("cls");
                        goto shop;

                    }
                    else if(buy_tools_czynnosc_sklep == 4){

                    }
                    else if(buy_tools_czynnosc_sklep == 5){
                        color_chg(15);
                        system("cls");
                        goto shop;
                    }
                    else{
                        color_chg(15);
                        system("cls");
                        font_size(18);
                        goto etykieta;
                    }
                }
                else if(czynnosc_sklep == 2){
                    system("cls");
                    ekwipunek.open(filename_1, std::fstream::in | std::fstream::out);
                    font_size(50);
                    color_chg(14);
                    cout<<"Sold\n";
                    money_gold =(gold * 10);
                    if(money_gold > 0){
                        color_chg(11);
                        cout<<gold<<" gold for "<<money_gold<<endl;
                        gold = 0;
                    }
                    money_silver = silver*6;
                    if(money_silver > 0){
                        color_chg(14);
                        cout<<silver<<" silver for "<<money_silver<<endl;
                        silver = 0;
                    }
                    money_iron = iron*2;
                    if(money_iron > 0){
                        color_chg(8);
                        cout<<iron<<" iron for "<<money_iron<<endl;
                        iron=0;
                    }
                    money_bronze = bronze*1;
                    if(money_bronze > 0){
                        color_chg(12);
                        cout<<bronze<<" bronze for "<<money_bronze<<endl;
                        bronze=0;
                    }
                    ekwipunek<<gold<<endl;
                    ekwipunek<<silver<<endl;
                    ekwipunek<<iron<<endl;
                    ekwipunek<<bronze<<endl;
                    ekwipunek.close();
                    if(money_bronze == 0 && money_iron == 0 && money_silver ==0 && money_bronze == 0){
                        color_chg(14);
                        system("cls");
                        cout<<"You can't sell anything\n";
                    }
                    else{
                        color_chg(14);
                        total_sell= money_bronze+money_iron+money_silver+money_gold;
                        cout<<"Total earned "<<total_sell<<"$\n";
                        portfel.open(filename_2, std::fstream::in | std::fstream::out);
                        money = money + total_sell;
                        portfel<<money;
                        portfel.close();
                    }
                    color_chg(15);
                    cout<<"\n";
                    cout<<"\nClick any button !";
                    getch();
                    font_size(18);
                    system("cls");
                    goto etykieta;

                }
                else if(czynnosc_sklep == 3){
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
            color_chg(13);
            cout<<"Money: "<<money<<endl;
            color_chg(15);
            cout<<"\n1.Leave bank\n"
                <<"2.Clear the safe (Material)\n"
                <<"3.Clear the safe (Money)\n\n"
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
                        ekwipunek.open(filename_1, std::fstream::in | std::fstream::out);
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
            else if(czynnsoc_bank == 3){
                color_chg(12);
                cout<<"\nAre you sure? You will lost all your money!! [T/N]\n\n";
                color_chg(15);
                cout<<"And what: ";
                cin>>sure;
                if(sure == "T" || sure =="t"){
                    portfel.open(filename_2, std::fstream::in | std::fstream::out);
                    portfel<<"0\n";
                    portfel.close();
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
