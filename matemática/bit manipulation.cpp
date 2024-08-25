// operators: & = bitwise AND, | = bitwise OR, ^ = bitwise XOR, ~ = bitwise NOT, << = left shift, >> = right shift
// set bit: x |= 1 << n
// clear bit: x &= ~(1 << n)
// toggle bit: x ^= 1 << n

bool is_set(unsigned int number, int x) {
    return (number >> x) & 1;
}

bool isPowerOfTwo(unsigned int n) {
    return n && !(n & (n - 1));
}

int countSetBits(int n) {
        int count = 0;
        while (n > 0) {
            int x = std::bit_width(n) - 1;
            count += x << (x - 1);
            n -= 1 << x;
            count += n + 1;
        }
        return count;
}

