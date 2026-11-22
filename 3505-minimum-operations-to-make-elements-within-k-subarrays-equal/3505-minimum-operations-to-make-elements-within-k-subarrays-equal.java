import java.util.*;

class Solution {
    TreeMap<Integer, Integer> left = new TreeMap<>();
    TreeMap<Integer, Integer> right = new TreeMap<>();

    int leftSize = 0, rightSize = 0;
    long leftSum = 0, rightSum = 0;

    void addLeft(int v) {
        left.merge(v, 1, Integer::sum);
        leftSize++;
        leftSum += v;
    }

    void addRight(int v) {
        right.merge(v, 1, Integer::sum);
        rightSize++;
        rightSum += v;
    }

    void remove(TreeMap<Integer, Integer> map, int v) {
        int c = map.get(v);
        if (c == 1) map.remove(v);
        else map.put(v, c - 1);
    }

    void removeLeft(int v) {
        remove(left, v);
        leftSize--;
        leftSum -= v;
    }

    void removeRight(int v) {
        remove(right, v);
        rightSize--;
        rightSum -= v;
    }

    void add(int v) {
        if (left.isEmpty() || v <= left.lastKey())
            addLeft(v);
        else
            addRight(v);
    }

    void erase(int v) {
        if (left.containsKey(v))
            removeLeft(v);
        else
            removeRight(v);
    }

    void balance(int x) {
        int target = (x + 1) / 2;

        while (leftSize > target) {
            int v = left.lastKey();
            removeLeft(v);
            addRight(v);
        }

        while (leftSize < target && rightSize > 0) {
            int v = right.firstKey();
            removeRight(v);
            addLeft(v);
        }
    }

    long getCost() {
        long median = left.lastKey();

        return median * leftSize - leftSum
                + rightSum - median * rightSize;
    }

    public long minOperations(int[] nums, int x, int k) {
        int n = nums.length;
        int m = n - x + 1;

        long[] cost = new long[m];

        left.clear();
        right.clear();
        leftSize = rightSize = 0;
        leftSum = rightSum = 0;

        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x)
                erase(nums[i - x]);

            if (i >= x - 1) {
                balance(x);
                cost[i - x + 1] = getCost();
            }
        }

        long INF = Long.MAX_VALUE / 4;

        long[] prev = new long[n + 1];
        long[] curr = new long[n + 1];

        for (int j = 1; j <= k; j++) {
            Arrays.fill(curr, INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i - 1];

                if (i >= x && prev[i - x] != INF) {
                    curr[i] = Math.min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            long[] temp = prev;
            prev = curr;
            curr = temp;
        }

        return prev[n];
    }
}