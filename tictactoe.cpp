#include <iostream>
#include<conio.h>
#include<math.h>
#include<fstream>
using namespace std;

const int size = 30;
char board[size][size];
int grid = 0;
void boarda()
{
    for(int i = 0; i < grid; i++)
    {
        for(int j = 0; j < grid; j++)
        {
            board[i][j] = '-';
        }
    }
}
char turn = ' ';
char winner = ' ';

void displayBoard()
{
    system("cls");
    cout << "\n\n\n";
    for(int i = 0; i < grid; i++)
    {
        cout << "\t\t\t\t|";
        for(int j = 0; j < grid; j++)
        {
            cout << board[i][j ]<< "|";
        }
        cout << endl;
    }
    cout << "\n\n";
}

int calculateCount()
{
    int count = 0;
    for (int i = 0; i < grid; i++)
    {
        for (int j = 0; j < grid; j++)
        {
            if (board[i][j] != '-')
            {
                count++;
            }
        }
    }
    return count;
}
void updateBoard(int row, int col)
{
    board[row][col] = turn;
}

bool validateInput(int row, int col)
{
    bool firstCheck = false;
    if ((row >= 0 && row < grid) && (col >= 0 && col < grid))
    {
        firstCheck = true;
    }
    else
    {
        return false;
    }

    if (firstCheck == true)
    {
        if (board[row][col] != '-')
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
void input()
{
    char x, y = ' ';
    int inRow, inCol = 0;
    cout << "Enter row: ";
    cin >> x;
    cout << "Enter coloumn: ";
    cin >> y;

    inRow = x - 48;
    inCol = y - 48;

    while (!(validateInput(inRow, inCol)))
    {
        cout << "Enter Valid Input." << endl;
        cout << "Enter row: ";
        cin >> x;
        cout << "Enter coloumn: ";
        cin >> y;

        inRow = x - 48;
        inCol = y - 48;
    }
    updateBoard(inRow, inCol);
}

bool findWinner(char a)
{
    int c = 0;
    for (int i = 0; i < grid; i++)
    {
        for (int j = 0; j < grid; j++)
        {
            if (board[i][j] == a)
            {
                c++;
            }
        }
        if (c == grid)
        {
            return true;
        }

        c = 0;

        for (int j = 0; j < grid; j++)
        {
            if (board[j][i] == a)
            {
                c++;
            }
        }

        if (c == grid)
        {
            return true;
        }

        c = 0;
    }

    for (int i = 0; i < grid; i++)
    {
        for (int j = 0; j < grid; j++)
        {
            if (i == j)
            {
                if (board[i][j] == a)
                {
                    c++;
                }
            }
        }
    }

    if (c == grid)
    {
        return true;
    }

    c = 0;

    for (int i = 0; i < grid; i++)
    {
        for (int j = 0; j < grid; j++)
        {
            if (i + j == grid - 1)
            {
                if (board[i][j] == a)
                {
                    c++;
                }
            }
        }
    }

    if (c == grid)
    {
        return true;
    }

    c = 0;

    return false;
}
bool checkWinner()
{
    if (findWinner('X'))
    {
        winner = 'X';
        return true;
    }
    else if (findWinner('O'))
    {
        winner = 'O';
        return true;
    }
    return false;
}

int convert(string n)
{
    if(n == "0")
    {
        return 0;
    }
    float num = 0;
    int x;
    for(int i = 0; i < n.length(); i++)
    {
        x = (n[n.length()-i-1]) - 48;
        num = num + x*pow(10,i);
    }

    return num;
}

void store()
{
    fstream file;
    file.open("tictactoe.txt",ios::out);
    file << grid << endl;
    for (int i = 0; i < grid; i++)
    {
        for (int j = 0; j < grid; j++)
        {
            file << board[i][j];
        }
        file << endl;
    }
}
void load()
{
    fstream file;
    string line;
    string temp;
    file.open("tictactoe.txt",ios::in);
    getline(file, temp);
    grid = convert(temp);
    for(int i = 0; i < grid; i++)
    {
        getline(file, line);
        for(int j = 0; j < grid; j++)
        {
            board[i][j] = line[j];
        }
    }
}
main()
{
    char response;
    cout << "Load Previous Game? (Y/N)" << endl;
    cin >> response;
    if(response == 'Y')
    {
        load();
    }
    else
    {
        cout << "Enter board size (1-30): ";
        cin >> grid;
        boarda();
    }
    int count = calculateCount();
    while (count < (grid * grid) - 1)
    {
        store();
        displayBoard();
        count = calculateCount();
        if (count % 2 == 0)
        {
            cout << "Player X's turn:" << endl;
            turn = 'X';
        }
        else
        {
            cout << "Player O's turn:" << endl;
            turn = 'O';
        }
        input();

        if (checkWinner())
        {
            displayBoard();
            cout << winner << " won.\nGame Ended." << endl;
            return 0;

        }
    }
    displayBoard();
    cout << "Its a Tie";
    getch();
}
