#include <cstdio>

const int LIMIT = 1e7;

int largest_prime_factor[LIMIT + 1] = {0};
long long no_of_divisors[LIMIT + 1] = {0};
int no_of_pairs_till[LIMIT + 1] = {0};

void sieve_and_precompute()
{
    no_of_divisors[1] = 1;
    for(int i = 2; i <= LIMIT; i++)
    {
        if(largest_prime_factor[i] == 0)
        {
            no_of_divisors[i] = 2;

            for(int multiple = 2*i; multiple <= LIMIT; multiple += i)
                largest_prime_factor[multiple] = i;
        }
        else
        {
            int p = largest_prime_factor[i];
            int reduced_i = i;

            int exponent = 0;

            while(reduced_i%p == 0)
            {
                reduced_i /= p;
                exponent++;
            }

            no_of_divisors[i] = (exponent + 1)*no_of_divisors[reduced_i];
        }
    }

    for(int i = 2; i + 1 <= LIMIT;i++)
        no_of_pairs_till[i] = no_of_pairs_till[i - 1] + (no_of_divisors[i] == no_of_divisors[i + 1]);

    no_of_pairs_till[LIMIT] = no_of_pairs_till[LIMIT - 1];
}

int main()
{
    sieve_and_precompute();

    int no_of_test_cases;
    scanf("%d", &no_of_test_cases);

    while(no_of_test_cases--)
    {
        int n;
        scanf("%d", &n);

        printf("%d\n", no_of_pairs_till[n - 1]);
    }

    return 0;
}

