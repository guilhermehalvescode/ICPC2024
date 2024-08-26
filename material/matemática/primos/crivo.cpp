int n;

vector<bool> is_prime(n+1, true);
vector<int> primes;

void build(){
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
 // for (int i = 2; i * i <= n; i++) { in case of sieving 'til root
        if (is_prime[i] && (long long)i * i <= n) {
            primes.push_back(i);
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}

//factorize with primes
vector<long long> factorize(long long n) {
    vector<long long> factorization;
    for (long long d : primes) {
        if (d * d > n)
            break;
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}

//factorize without primes
vector<long long> trial_division(long long n) {
    vector<long long> factorization;
    while (n % 2 == 0) {
        factorization.push_back(2);
        n /= 2;
    }
    for (long long d = 3; d * d <= n; d += 2) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}