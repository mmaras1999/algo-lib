namespace LinearSieve
{
    vector <int> sieve;
    vector <int> primes;

    void init(int N)
    {
        ++N;
        sieve.resize(N, 0);

        FOR(i, 2, N) 
        {
            if (!sieve[i]) 
            {
                sieve[i] = i;
                primes.PB(i);
            }

            for (int j = 0; j < SIZE(primes) && primes[j] <= sieve[i] && i * primes[j] <= N; ++j)
                sieve[i * primes[j]] = primes[j];
        }
    }
}