/**\ file project1
 *\brief this is the project1 for programming 2
  *\details done
  *\author Valeria SpaK
  *\date 09/04/25
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const char minesymbol = '*';
const char hiddensymbol = '#';

// Function Declarations
void initboard(bool mines[10][10], bool revealed[10][10], int boardsize);
void placeminesonboard(bool mines[10][10], int boardsize, int minecount);
void showboard(bool mines[10][10], bool revealed[10][10], int boardsize);
int countminesnearby(bool mines[10][10], int boardsize, int row, int col);
void getmove(int &row, int &col, int boardsize, bool revealed[10][10]);
bool rungame(int boardsize, int minecount);

int main()
{
    srand(time(0));

    int boardsize;
    int difficulty;
    int minecount = 0;

    cout << "Choose board size (between 3 and 10): ";
    cin >> boardsize;

    if (boardsize < 3 || boardsize > 10) {
        cout << "Invalid size, try again" << endl;
        return boardsize;
    }

    cout << "Choose difficulty:" << endl;
    cout << "1. Easy (10% mines)" << endl;
    cout << "2. Medium (20% mines)" << endl;
    cout << "3. Hard (30% mines)" << endl;
    cin >> difficulty;

    if (difficulty == 1)
    {
        minecount = (boardsize * boardsize) * 0.1;
    }
    else
    {
        if (difficulty == 2)
        {
            minecount = (boardsize * boardsize) * 0.2;
        }
        else
        {
            if (difficulty == 3)
            {
                minecount = (boardsize * boardsize) * 0.3;
            }
            else
            {
                cout << "Invalid option, setting to Easy" << endl;
                minecount = (boardsize * boardsize) * 0.1;
            }
        }
    }

    char playagain;
    do
    {
        bool gamewon = rungame(boardsize, minecount);
        if (gamewon)
        {
            cout << "Congrats! You won the game!" << endl;
        }
        else
        {
            cout << "Oh no! You hit a mine! Game over!" << endl;
        }

        cout << "Want to play again? (y/n): ";
        cin >> playagain;

        if (playagain != 'y' && playagain != 'Y')
        {
            if (playagain == 'n' || playagain == 'N')
            {
                cout << "BYE!" << endl;
            }
            else
            {
                cout << "Invalid input, please write y for yes or n for no" << endl;
            }
        }

    } while (playagain == 'y' || playagain == 'Y');

    return 0;
}

bool rungame(int boardsize, int minecount)
{
    bool mines[10][10];
    bool revealed[10][10];

    initboard(mines, revealed, boardsize);
    placeminesonboard(mines, boardsize, minecount);

    int revealedcells = 0;
    int totalsafecells = (boardsize * boardsize) - minecount;

    while (true)
    {
        showboard(mines, revealed, boardsize);

        int row, col;
        getmove(row, col, boardsize, revealed);

        if (mines[row][col])
        {
            revealed[row][col] = true;
            showboard(mines, revealed, boardsize);
            return false;
        }
        else
        {
            if (revealed[row][col])
            {
                cout << "This cell is already revealed!" << endl;
            }
            else
            {
                revealed[row][col] = true;
                revealedcells++;
                if (revealedcells == totalsafecells)
                {
                    showboard(mines, revealed, boardsize);
                    return true;
                }
            }
        }
    }
}

void initboard(bool mines[10][10], bool revealed[10][10], int boardsize)
{
    for (int i = 0; i < boardsize; i++)
    {
        for (int j = 0; j < boardsize; j++)
        {
            mines[i][j] = false;
            revealed[i][j] = false;
        }
    }
}

void placeminesonboard(bool mines[10][10], int boardsize, int minecount)
{
    int placed = 0;

    while (placed < minecount)
    {
        int row = rand() % boardsize;
        int col = rand() % boardsize;

        if (mines[row][col] == false)
        {
            mines[row][col] = true;
            placed++;
        }
        else
        {
            if (mines[row][col] == true)
            {
                continue;
            }
            else
            {
                cout << "Error while placing mines!" << endl;
            }
        }
    }
}

int countminesnearby(bool mines[10][10], int boardsize, int row, int col)
{
    int count = 0;

    if (row < 0 || row >= boardsize || col < 0 || col >= boardsize)
    {
        cout << "Error!! Row or Column out of board" << endl;
        return -1;
    }

    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (i >= 0 && i < boardsize && j >= 0 && j < boardsize)
            {
                if (mines[i][j])
                {
                    count++;
                }
            }
            else
            {
                cout << "Skipped out of bounds during mine count!" << endl;
            }
        }
    }

    return count;
}

void showboard(bool mines[10][10], bool revealed[10][10], int boardsize)
{
    cout << endl << "   ";

    for (int i = 0; i < boardsize; i++)
    {
        if (i < 10)
        {
            cout << " " << i << " ";
        }
        else
        {
            cout << i << " ";
        }
    }

    cout << endl;

    for (int i = 0; i < boardsize; i++)
    {
        if (i < 10)
        {
            cout << " " << i << "  ";
        }
        else
        {
            cout << i << "  ";
        }

        for (int j = 0; j < boardsize; j++)
        {
            if (revealed[i][j])
            {
                if (mines[i][j])
                {
                    cout << minesymbol << " ";
                }
                else
                {
                    int adjmines = countminesnearby(mines, boardsize, i, j);
                    if (adjmines == 0)
                    {
                        cout << "  " << " ";
                    }
                    else
                    {
                        cout << adjmines << " ";
                    }
                }
            }
            else
            {
                cout << hiddensymbol << " ";
            }
        }

        cout << endl;
    }
}

void getmove(int &row, int &col, int boardsize, bool revealed[10][10])
{
    while (true)
    {
        cout << "Enter row and column(0-" << boardsize - 1 << "): ";
        cin >> row >> col;

        if (row < 0 || row >= boardsize || col < 0 || col >= boardsize)
        {
            cout << "Wrong coordinates, write it again" << endl;
            continue;
        }
        else
        {
            if (revealed[row][col] == true)
            {
                cout << "That cell was already revealed! try again!!" << endl;
            }
            else
            {
                return;
            }
        }
    }
}
