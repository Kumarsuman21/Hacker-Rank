#include <cstdio>
#include <vector>

using namespace std;

int get_no_of_digits(int n)
{
    int no_of_digits = 0;
    while(n)
    {
        no_of_digits++;
        n /= 10;
    }

    return no_of_digits;
}

int rotate(int n)
{
    int last_digit = n%10;

    n = n/10;
    int no_of_digits = get_no_of_digits(n);

    while(no_of_digits--)
        last_digit *= 10;

    return (last_digit + n);
}

void precompute(vector <int> &sum_of_circular_primes_till, int LIMIT)
{
    vector <int> is_prime(LIMIT + 1, true);
    vector <int> primes;
    is_prime[0] = is_prime[1] = false;

    for(int i = 2; i <= LIMIT; i++)
    {
        if(is_prime[i])
            primes.push_back(i);

        for(int j = 0; j < primes.size() && i*primes[j] <= LIMIT; j++)
        {
            is_prime[i*primes[j]] = false;

            if(i%primes[j] == 0) break;
        }
    }

    for(int i = 1; i <= LIMIT; i++)
    {
        int is_circular_prime = true;
        int rotation = i;

        do
        {
            if(!is_prime[rotation])
                is_circular_prime = false;

            rotation = rotate(rotation);

        }while(rotation != i && is_circular_prime);

        sum_of_circular_primes_till[i] = sum_of_circular_primes_till[i - 1] + i*(is_circular_prime);
    }
}

int main()
{
    int LIMIT = 1e6;
    vector <int> sum_of_circular_primes_till(LIMIT + 1, 0);
    precompute(sum_of_circular_primes_till, LIMIT);

    int n;
    scanf("%d", &n);
    printf("%d\n", sum_of_circular_primes_till[n]);

    return 0;
}
