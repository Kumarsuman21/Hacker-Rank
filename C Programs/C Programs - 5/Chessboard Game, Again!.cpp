#include <cstdio>
#include <vector>
#include <set>

using namespace std;

typedef vector <int> v_int;

inline int legal(int x, int y, int SIZE)
{
    return (x >= 1 && x <= SIZE && y >= 1 && y <= SIZE);
}

inline int mex(set <int> &neighbour_grundy)
{
    int mex = 0;

    while(true)
    {
        if(neighbour_grundy.count(mex) == 1)
            mex++;
        else
            return mex;
    }
}

int find(vector <v_int> &grundy, int x, int y, int SIZE)
{
    const int NO_OF_NEIGHBOURS = 4;
    int x_step[NO_OF_NEIGHBOURS] = {-2, -2, 1, -1};
    int y_step[NO_OF_NEIGHBOURS] = {1, -1, -2, -2};

    if(grundy[x][y] == -1)
    {
        set <int> neighbour_grundy;

        for(int neighbour_no = 0; neighbour_no < NO_OF_NEIGHBOURS; neighbour_no++)
        {
            if(legal(x + x_step[neighbour_no], y + y_step[neighbour_no], SIZE))
                neighbour_grundy.insert(find(grundy, x + x_step[neighbour_no], y + y_step[neighbour_no], SIZE));
        }

        grundy[x][y] = mex(neighbour_grundy);
    }

    return grundy[x][y];
}

inline void precompute(vector <v_int> &grundy, int SIZE)
{
    for(int row = 1; row <= SIZE; row++)
    {
        for(int column = 1; column <= SIZE; column++)
        {
            grundy[row][column] = find(grundy, row, column, SIZE);
        }
    }
}

void solve(vector <v_int> &grundy)
{
    int no_of_coins;
    scanf("%d", &no_of_coins);

    int nim_sum = 0;
    for(int i = 1; i <= no_of_coins; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        nim_sum ^= grundy[x][y];
    }

    printf("%s\n", nim_sum == 0 ? "Second" : "First");
}

int main()
{
    const int SIZE = 15;
    vector <v_int> grundy(SIZE + 1, v_int(SIZE + 1, -1));
    precompute(grundy, SIZE);

    int no_of_games;
    scanf("%d", &no_of_games);

    while(no_of_games--)
        solve(grundy);

    return 0;
}

