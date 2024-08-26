// Functions to use: pollard_rho, is_prime

// Function to calculate the greatest common divisor (GCD) of two numbers
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function for modular multiplication (to avoid overflow)
long long mod_mul(long long a, long long b, long long mod) {
    long long result = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return result;
}

// Function for modular exponentiation
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = mod_mul(result, base, mod);
        base = mod_mul(base, base, mod);
        exp /= 2;
    }
    return result;
}

// Miller-Rabin primality test helper function
bool miller_test(long long d, long long n) {
    long long a = 2 + rand() % (n - 4);
    long long x = mod_pow(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1) {
        x = mod_mul(x, x, n);
        d *= 2;

        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }
    return false;
}

// Miller-Rabin primality test, increment k for higher accuracy
bool is_prime(long long n, int k = 5) {
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    long long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    for (int i = 0; i < k; i++)
        if (!miller_test(d, n))
            return false;

    return true;
}

// Function implementing Pollard's Rho algorithm
long long pollard_rho(long long n) {
    if (n % 2 == 0)
        return 2;

    srand(time(NULL)); // Initialize random seed

    long long x = rand() % (n - 2) + 2;
    long long y = x;
    long long c = rand() % (n - 1) + 1;
    long long d = 1;

    while (d == 1) {
        x = (mod_mul(x, x, n) + c) % n;
        y = (mod_mul(y, y, n) + c) % n;
        y = (mod_mul(y, y, n) + c) % n;
        d = gcd(abs(x - y), n);

        if (d == n)
            return pollard_rho(n); // Retry if the algorithm fails
    }

    return d;
}
