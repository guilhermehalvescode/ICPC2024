#include <iostream>
#include <vector>
using namespace std;

const int N = 1000; 
int seg[4 * N][4 * N];
int arr[N][N];
int n, m;

void buildY(int nodeX, int lx, int rx, int nodeY, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) {
            seg[nodeX][nodeY] = arr[lx][ly];
        } else {
            seg[nodeX][nodeY] = seg[2 * nodeX + 1][nodeY] + seg[2 * nodeX + 2][nodeY];
        }
    } else {
        int my = (ly + ry) / 2;
        buildY(nodeX, lx, rx, 2 * nodeY + 1, ly, my);
        buildY(nodeX, lx, rx, 2 * nodeY + 2, my + 1, ry);
        seg[nodeX][nodeY] = seg[nodeX][2 * nodeY + 1] + seg[nodeX][2 * nodeY + 2];
    }
}

void buildX(int nodeX, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        buildX(2 * nodeX + 1, lx, mx);
        buildX(2 * nodeX + 2, mx + 1, rx);
    }
    buildY(nodeX, lx, rx, 0, 0, m - 1);
}

int sumY(int nodeX, int nodeY, int ly, int ry, int qly, int qry) {
    if (qly > ry || qry < ly) return 0;
    if (qly <= ly && qry >= ry) return seg[nodeX][nodeY];
    int my = (ly + ry) / 2;
    return sumY(nodeX, 2 * nodeY + 1, ly, my, qly, qry) + sumY(nodeX, 2 * nodeY + 2, my + 1, ry, qly, qry);
}

int sumX(int nodeX, int lx, int rx, int qlx, int qrx, int qly, int qry) {
    if (qlx > rx || qrx < lx) return 0;
    if (qlx <= lx && qrx >= rx) return sumY(nodeX, 0, 0, m - 1, qly, qry);
    int mx = (lx + rx) / 2;
    return sumX(2 * nodeX + 1, lx, mx, qlx, qrx, qly, qry) + sumX(2 * nodeX + 2, mx + 1, rx, qlx, qrx, qly, qry);
}

void updateY(int nodeX, int lx, int rx, int nodeY, int ly, int ry, int y, int val) {
    if (ly == ry) {
        if (lx == rx) {
            seg[nodeX][nodeY] = val;
        } else {
            seg[nodeX][nodeY] = seg[2 * nodeX + 1][nodeY] + seg[2 * nodeX + 2][nodeY];
        }
    } else {
        int my = (ly + ry) / 2;
        if (y <= my) {
            updateY(nodeX, lx, rx, 2 * nodeY + 1, ly, my, y, val);
        } else {
            updateY(nodeX, lx, rx, 2 * nodeY + 2, my + 1, ry, y, val);
        }
        seg[nodeX][nodeY] = seg[nodeX][2 * nodeY + 1] + seg[nodeX][2 * nodeY + 2];
    }
}

void updateX(int nodeX, int lx, int rx, int x, int y, int val) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx) {
            updateX(2 * nodeX + 1, lx, mx, x, y, val);
        } else {
            updateX(2 * nodeX + 2, mx + 1, rx, x, y, val);
        }
    }
    updateY(nodeX, lx, rx, 0, 0, m - 1, y, val);
}

int main() {
    n = 4;
    m = 4;
    arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3; arr[0][3] = 4;
    arr[1][0] = 5; arr[1][1] = 6; arr[1][2] = 7; arr[1][3] = 8;
    arr[2][0] = 9; arr[2][1] = 10; arr[2][2] = 11; arr[2][3] = 12;
    arr[3][0] = 13; arr[3][1] = 14; arr[3][2] = 15; arr[3][3] = 16;

    buildX(0, 0, n - 1);

    cout << sumX(0, 0, n - 1, 1, 2, 1, 2) << endl;

    updateX(0, 0, n - 1, 1, 1, 20);

    cout << sumX(0, 0, n - 1, 1, 2, 1, 2) << endl;

    return 0;
}
