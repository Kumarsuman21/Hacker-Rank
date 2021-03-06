#include <cstdio>
#include <vector>

#define max_4(a, b, c, d) max(max(a, d), max(b, c))

using namespace std;
typedef vector <int> v_int;

int right_product(vector <v_int> &grid, int i, int j)
{
    return (grid[i][j]*grid[i][j + 1]*grid[i][j + 2]*grid[i][j + 3]);
}

int diagonal_product(vector <v_int> &grid, int i, int j)
{
    return (grid[i][j]*grid[i + 1][j + 1]*grid[i  + 2][j + 2]*grid[i + 3][j + 3]);
}

int antidiagonal_product(vector <v_int> &grid, int i, int j)
{
    return (grid[i][j]*grid[i + 1][j - 1]*grid[i  + 2][j - 2]*grid[i + 3][j - 3]);
}

int down_product(vector <v_int> &grid, int i, int j)
{
    return (grid[i][j]*grid[i + 1][j]*grid[i  + 2][j]*grid[i + 3][j]);
}

int main()
{
    const int ROWS = 20, ORIGIN = 5;
    vector<v_int> grid(ROWS + 15,v_int(ROWS + 15, 0));

    for(int i = ORIGIN; i <= ROWS + ORIGIN - 1; i++)
        for(int j = ORIGIN; j <= ROWS + ORIGIN - 1; j++)
            scanf("%d", &grid[i][j]);

    int overall_max = 0;
    vector <v_int> max_starting_from(ROWS + 15, v_int(ROWS + 15, 0));
    for(int i = ORIGIN; i <= ROWS + ORIGIN - 1; i++)
    {
         for(int j = ORIGIN; j <= ROWS + ORIGIN - 1; j++)
        {
            max_starting_from[i][j] = max_4(down_product(grid, i, j), right_product(grid, i, j),
                                            diagonal_product(grid, i, j), antidiagonal_product(grid, i, j));
            overall_max = max(overall_max, max_starting_from[i][j]);
        }
    }

    printf("%d\n", overall_max);
    return 0;
}
