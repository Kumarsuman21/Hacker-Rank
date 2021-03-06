#include <cstdio>
#include <vector>

using namespace std;

#define all(v) (v).begin(), (v).end()

const int MAX_VERTICES = 1e5 + 1, BLACK = 1, WHITE = 0, NO_OF_COLOURS = 2;
vector <int> tree[MAX_VERTICES];
int colour[MAX_VERTICES], visited[MAX_VERTICES] = {false};
int maximum_strangeness[MAX_VERTICES][NO_OF_COLOURS];
vector <int> solution[MAX_VERTICES][NO_OF_COLOURS];

inline int other(int colour)
{
    return colour^1 ;
}

void dfs(int v, int parent)
{
    visited[v] = true;
    int v_colour = colour[v], other_colour = other(colour[v]);

    maximum_strangeness[v][v_colour] = 1;
    solution[v][v_colour].push_back(v);

    maximum_strangeness[v][other_colour] = -1;
    solution[v][other_colour].push_back(v);

    for(int i = 0; i < tree[v].size(); i++)
    {
        int child = tree[v][i];

        if(visited[child]) continue;

        dfs(child, v);

        if(maximum_strangeness[child][v_colour] > 0)
        {
            maximum_strangeness[v][v_colour] += maximum_strangeness[child][v_colour];
            solution[v][v_colour].insert(solution[v][v_colour].end(), all(solution[child][v_colour]) );
        }

        if(maximum_strangeness[child][other_colour] > 0)
        {
            maximum_strangeness[v][other_colour] += maximum_strangeness[child][other_colour];
            solution[v][other_colour].insert(solution[v][other_colour].end(), all(solution[child][other_colour]));
        }
    }
}

int main()
{
    int no_of_nodes;
    scanf("%d", &no_of_nodes);

    for(int i = 1; i <= no_of_nodes; i++)
        scanf("%d", &colour[i]);

    for(int i = 1; i <= no_of_nodes - 1; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    for(int i = 1; i <= no_of_nodes; i++)
        if(!visited[i])
            dfs(i, 0);

    int strangest_vertex, strangest_colour, max_strangeness = 0;
    for(int i = 1; i <= no_of_nodes; i++)
    {
        if(maximum_strangeness[i][BLACK] > max_strangeness)
            strangest_vertex = i, strangest_colour = BLACK, max_strangeness = maximum_strangeness[i][BLACK];

        if(maximum_strangeness[i][WHITE] > max_strangeness)
            strangest_vertex = i, strangest_colour = WHITE, max_strangeness = maximum_strangeness[i][WHITE];
    }

    printf("%d\n%u\n", max_strangeness, solution[strangest_vertex][strangest_colour].size());
    for(int i = 0; i < solution[strangest_vertex][strangest_colour].size(); i++)
        printf("%d ", solution[strangest_vertex][strangest_colour][i]);

    return 0;
}

