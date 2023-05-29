#include <iostream>
using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

char currenr_marker;
int current_player = 1;

void display()
{
    cout << "     " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "   ------------- \n";
    cout << "     " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "   ------------- \n";
    cout << "     " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << "   =============\n\n\n";
}

bool placeMarker(int slot)
{
    int row = slot / 3;
    int col;

    if (slot % 3 == 0)
    {
        row = row - 1;
        col = 2;
    }
    else
        col = (slot % 3) - 1;

    if (board[row][col] != 'X' && board[row][col] != 'O')
    {
        board[row][col] = currenr_marker;
        return true;
    }
    else
        return false;
}

int winner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return current_player;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return current_player;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return current_player;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return current_player;

    return 0;
}

void swapPlayer()
{
    if (currenr_marker == 'X')
        currenr_marker = 'O';
    else
        currenr_marker = 'X';

    if (current_player == 1)
        current_player = 2;
    else
        current_player = 1;
}

void start()
{

    int won;
    cout << "Select your Agent( X || O): ";
    char markp1;
    cin >> markp1;

    currenr_marker = markp1;

    display();

    for (int i = 0; i < 9; i++)
    {
        cout << "Its Player " << currenr_marker << "'s turn. Enter your position: ";
        int pos;
        cin >> pos;
        if (pos < 1 || pos > 9)
        {
            cout << "\n\n\nSike That's the Wrong Number!!!\n\n\n";
            i--;
            continue;
        }
        if (!placeMarker(pos))
        {
            cout << "\n\n\nSike That's the Wrong Number!!!\n\n\n";
            i--;
            continue;
        }
        display();
        won = winner();

        if (won == 1)
        {
            cout << "Congrates!, Player " << currenr_marker << " Won!!!\n\n\n";
            break;
        }
        if (won == 2)
        {
            cout << "Congrates!, Player " << currenr_marker << " Won!!!\n\n\n";
            break;
        }
        swapPlayer();
    }

    if (won == 0)
        cout << "XO DRAW!!!\n\n\n";
}

int main()
{
    start();
    return 0;
}