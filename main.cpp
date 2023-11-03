#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;



void enter();
void report();
void trans();
void closeAcc();
void maxminbal();
int menu();



struct customer
{
    int stat;           //feild status rec
    char name[21];      //name
    int bal;            //balance
    int accId;          //account num
    int kind;           //acc type
};
int menu()
{
    cout << "===================|main menu|===================" <<endl;
    cout << "|              1.Enter data:" <<"                    |"<<endl;
    cout << "|              2.Transaction:" <<"                   |"<<endl;
    cout << "|              3.Maximum and minimum balance:"<<"   |"<<endl;
    cout << "|              4.Close customer acc:" <<"            |"<<endl;
    cout << "|              5.Report info:" <<"                   |"<<endl;
    cout << "|              6.terminate:" <<"                     |"<<endl;
    cout << "=================================================" <<endl;


    cout << "|     Enter your selection: " <<"    |"<<endl;
    int p;
    cin>>p;
    cin.get();

    return p;
}
int main()
{
    int menuChoice;
    do
    {
        system("cls");
        menuChoice = menu();
        switch(menuChoice)
        {
            case 1: enter();break;
            case 2: trans();break;
            case 3: maxminbal();break;
            case 4: closeAcc();break;
            case 5: report();break;
            default: cout << "Pls enter a valid num from 1-6 ...! \npress a key to continue..." <<endl;getch();break;

        }

    }while(menuChoice != 6);


    return 0;
}
COORD coord = {0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
// func of creating new acc>>
void enter()
{
    system("cls");
    customer cust;
    fstream file;
    file.open("text.abc",ios::out | ios::in | ios::binary );
    if(!file)
    {
        file.open("text.abc",ios::out | ios::binary );
        if(!file)

            cout<<"Err for file..."<<endl;
            else cout<<"file successfully created!"<<endl;
    }
    else
    {
        cout<<"name:            blance:         #Account:           kind ( 1 or 2) :"<<endl;
        gotoxy(1,2);
        cin.getline(cust.name,20);
        gotoxy(20,2);
        cin>> cust.bal;
        gotoxy(40,2);
        cin>>cust.accId;
        gotoxy(60,2);
        cin>>cust.kind;
        //opening of new acc
        cust.stat = 1;

        file.seekp(sizeof(struct customer) * cust.accId , ios::beg);
        file.write((char*)&cust , sizeof(struct customer));
        file.close();

    }
    cout<<"press a key to continue...";
    getch();

}
// func of showing info>>
void report()
{
    system("cls");
    cout<<"name:            blance:         #Account:           kind ( 1 or 2) :"<<endl;
    fstream file;
    file.open("text.abc", ios::in | ios::binary);
    if(!file)
    {
        cout<<"err opening file..."<<endl;
    }
    else
    {
        customer cust;
        int row = 2;
        while (file.read((char *)&cust , sizeof(struct customer)))
        {
            if(cust.stat == 1)
            {
            gotoxy(1,row);
            cout<<cust.name;
            gotoxy(20,row);
            cout<< cust.bal;
            gotoxy(40,row);
            cout<<cust.accId;
            gotoxy(60,row);
            cout<<cust.kind;
            row++;
            }

        }
        file.close();
    }
        cout<<"\npress a key to continue..."<<
        getch();
}

void trans()
{
    int accId , bala;
    char tran;
    customer cust;
    system("cls");
    cout << "enter id number to change transaction :";

    cin >> accId;

    fstream file;
    file.open("text.abc", ios::in | ios::out | ios::binary);
    if(!file)
    {
        cout << "Error opening file..." << endl;
    }
    else
    {
        file.seekg(sizeof(struct customer) * accId , ios::beg);
        file.read((char*)&cust , sizeof(struct customer));

        cout << "Do you want to deposite (d) or withdraw (w) : ";
        cin >> tran;
        cout << "Enter amount of deposite or withdraw : ";
        cin >> bala;
        int dosave = 0;
        switch(tran)
        {
            case 'd':
                cust.bal += bala;
                dosave =1;
                break;
            case 'w':
                cust.bal -= bala;
                dosave = 1;
                break;
            default: "Error:Please choose d for deposite or w for withdraw"; break;
        }
        if(dosave == 1)
        {
            file.seekp(sizeof(struct customer) * accId , ios::beg);
            file.write((char*)&cust , sizeof(struct customer));
            cout << "successfully done."<<endl;
        }
        cout << "Press a key to continue ... "<< endl;
    }
    getch();
}

// func of closeacc>>
void closeAcc()
{
    system("cls");
    int acnum;
    customer cust;
    cout<< "Enter an account ID for close ..."<<endl;
    cin>>acnum;
    fstream file;
    file.open("text.abc", ios::out | ios::in | ios::binary );
    if(!file)
    {
        cout<<"err opening file..."<<endl;
    }
    else
    {
        file.seekg(sizeof(struct customer)* acnum, ios::beg);
        file.read((char *)&cust , sizeof(struct customer));
        if(cust.stat == 1)
        {
            cust.stat = 0;
            file.seekp(sizeof(struct customer)* acnum, ios::beg);
            file.write((char *)&cust,sizeof(struct customer));
            cout<<"acc successfully deleted!"<<endl;
        }
        else cout<<"this acc not existed..."<<endl;
        file.close();
    }
    getch();
}
// func of showing max and min bal
void maxminbal()
{
    system("cls");
    customer cust,cust1,cust2;
    cust1.bal = -1;
    cust2.bal = 0;
    fstream file;
    file.open("text.abc", ios::out  |  ios::in | ios::binary);
    if(!file)
    {
        cout << "Error opening file..." << endl;
    }
    else
    {
        while(file.read((char*)&cust , sizeof(struct customer)))
        {
            if(cust.stat == 1)
            {
                if(cust1.bal > -1)
                {
                   if(cust.bal < cust1.bal)
                   {
                       cust2 = cust;
                   }
                }
                if(cust.bal > cust1.bal)
                {
                    cust1 = cust;
                }


            }
        }
    }
    cout << "Maximum balance:"<< endl;
    int row =2;
    cout << "name:            blance:         #Account:           kind ( 1 or 2) :"<<endl;
    gotoxy(1,row);
    cout<<cust1.name;
    gotoxy(20,row);
    cout<< cust1.bal;
    gotoxy(40,row);
    cout<<cust1.accId;
    gotoxy(60,row);
    cout<<cust1.kind<<endl;
    row = row+4;

    cout << "\nMinimum balance"<< endl;
    cout << "name:            blance:         #Account:           kind ( 1 or 2) :"<<endl;
    gotoxy(1,row);
    cout<<cust2.name;
    gotoxy(20,row);
    cout<< cust2.bal;
    gotoxy(40,row);
    cout<<cust2.accId;
    gotoxy(60,row);
    cout<<cust2.kind;
    row++;
    getch();

}
