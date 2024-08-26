#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000

int segTree[4 * MAXN];
int arr[MAXN];

void build(int node, int start, int end) {
    if (start == end) {
        segTree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        segTree[node] = segTree[2 * node] + segTree[2 * node + 1];
    }
}

void update(int node, int start, int end, int idx, int value) {
    if (start == end) {
        arr[idx] = value;
        segTree[node] = value;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, value);
        } else {
            update(2 * node + 1, mid + 1, end, idx, value);
        }
        segTree[node] = segTree[2 * node] + segTree[2 * node + 1];
    }
}

int query(int node, int start, int end, int L, int R) {
    if (R < start || end < L) {
        return 0;
    }
    if (L <= start && end <= R) {
        return segTree[node];
    }
    int mid = (start + end) / 2;
    int leftSum = query(2 * node, start, mid, L, R);
    int rightSum = query(2 * node + 1, mid + 1, end, L, R);
    return leftSum + rightSum;
}
