#define ll long long
#define MAXN 1000005

// mod inverse for prime modulo
ll inv(ll a, ll m) {
    return a <= 1 ? a : m - (long long)(m/a) * inv(m % a, m) % m;
}

int invs[MAXN];
// pre-compute inverses
void pre_compute(int m) {
    invs[1] = 1;
    for(int a = 2; a < m; ++a)
        invs[a] = m - (long long)(m/a) * invs[m%a] % m;
}

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

ll mod_inverse(ll a, ll m) {
    ll x, y;
    ll gcd = extended_gcd(a, m, x, y);

    if (gcd != 1) {
        return -1;
    }

    return (x % m + m) % m;
}

