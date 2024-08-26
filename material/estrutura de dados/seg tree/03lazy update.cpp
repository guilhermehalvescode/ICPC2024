#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
int segTree[4 * MAXN];
int lazy[4 * MAXN];
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

void updateRange(int node, int start, int end, int L, int R, int value) {
    if (lazy[node] != 0) {
        segTree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (start > end || start > R || end < L) {
        return;
    }

    if (start >= L && end <= R) {
        segTree[node] += (end - start + 1) * value;
        if (start != end) {
            lazy[2 * node] += value;
            lazy[2 * node + 1] += value;
        }
        return;
    }

    int mid = (start + end) / 2;
    updateRange(2 * node, start, mid, L, R, value);
    updateRange(2 * node + 1, mid + 1, end, L, R, value);
    segTree[node] = segTree[2 * node] + segTree[2 * node + 1];
}

int queryRange(int node, int start, int end, int L, int R) {
    if (lazy[node] != 0) {
        segTree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (start > end || start > R || end < L) {
        return 0;
    }

    if (start >= L && end <= R) {
        return segTree[node];
    }

    int mid = (start + end) / 2;
    int leftSum = queryRange(2 * node, start, mid, L, R);
    int rightSum = queryRange(2 * node + 1, mid + 1, end, L, R);
    return leftSum + rightSum;
}