#include <cstdio>
#include <vector>

using namespace std;

typedef vector <int> v_int;

inline int minimum_excluding_number(int a, int b, int c)
{
    int mex = 0;
    while(true)
    {
        if(mex == a || mex == b || mex == c)
            mex++;
        else
            return mex;
    }
}

inline int legal(char square)
{
    return (square != 'X');
}

inline int winning(int nim_sum, vector <v_int> &grundy, int i, int j)
{
    int next_move = grundy[i][j];

    return ( (nim_sum^next_move) == 0);
}

void solve()
{
    int n;
    scanf("%d", &n);

    char chessboard[n + 3][n + 3];
    for(int i = 1; i <= n; i++)
        scanf("%s", chessboard[i] + 1);

    const int oo = 1e5;
    vector <v_int> grundy(n + 1, v_int(n + 1, oo));

    int total_nim_sum = 0;

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(chessboard[i][j] == 'X')
            {
                grundy[i][j] = oo;
            }
            else
            {
                grundy[i][j] = minimum_excluding_number(grundy[i - 1][j], grundy[i][j - 1], grundy[i - 1][j - 1]);
            }

            if(chessboard[i][j] == 'K')
                total_nim_sum ^= grundy[i][j];
        }
    }

    int no_of_winning_moves = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(chessboard[i][j] == 'K')
            {
                int nim_sum_without_current_square = total_nim_sum^grundy[i][j];

                no_of_winning_moves += (legal(chessboard[i - 1][j]) && winning(nim_sum_without_current_square, grundy,i - 1,j));
                no_of_winning_moves += (legal(chessboard[i][j - 1]) && winning(nim_sum_without_current_square, grundy,i,j - 1));
                no_of_winning_moves += (legal(chessboard[i - 1][j - 1]) && winning(nim_sum_without_current_square, grundy,i - 1,j - 1));
            }
        }
    }

    if(total_nim_sum == 0)
        printf("LOSE\n");
    else
        printf("WIN %d\n", no_of_winning_moves);
}

int main()
{
    int no_of_queries;
    scanf("%d", &no_of_queries);

    while(no_of_queries--)
        solve();

    return 0;
}
