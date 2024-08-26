typedef vector<vector<long long>> Matrix;

// Function to multiply two matrices
Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Function to compute matrix exponentiation
Matrix matrix_pow(const Matrix &A, int k) {
    int n = A.size();
    // Initialize the result as the identity matrix
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) result[i][i] = 1;

    // Copy matrix A
    Matrix base = A;

    while (k > 0) {
        if (k % 2 == 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        k /= 2;
    }

    return result;
}