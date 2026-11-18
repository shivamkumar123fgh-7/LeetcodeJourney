class Solution {
public:
    long long sumAndMultiply(int n) {
        long long x = 0, sum = 0;
        string s = to_string(n);

        for (char c : s) {
            if (c != '0') {
                int digit = c - '0';
                x = x * 10 + digit;
                sum += digit;
            }
        }

        return x * sum;
    }
};