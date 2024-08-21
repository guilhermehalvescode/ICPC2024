#define NMAX 100000

int bit[NMAX], n;

int sum(int idx){
    int res = 0;
    while(idx){
        res += bit[idx];
        idx -= idx & -idx;
    }
    return res;
}

int sum(int x, int y){
    return sum(y) - sum(x-1);
}

void add(int idx, int val){
    while(idx <= n){
        bit[idx] += val;
        idx += idx & -idx;
    }
}