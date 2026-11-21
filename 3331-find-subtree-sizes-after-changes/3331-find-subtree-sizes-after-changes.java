class Solution {
    public int[] findSubtreeSizes(int[] parent, String s) {
        int n = parent.length;

        List<List<Integer>> adj = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }

        for (int i = 1; i < n; i++) {
            adj.get(parent[i]).add(i);
        }

        int[] newParent = new int[n];
        int[] last = new int[26];

        Arrays.fill(last, -1);

        dfs(0, adj, s, last, newParent, parent);

        List<List<Integer>> newAdj = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            newAdj.add(new ArrayList<>());
        }

        for (int i = 1; i < n; i++) {
            newAdj.get(newParent[i]).add(i);
        }

        int[] ans = new int[n];
        Arrays.fill(ans, 1);

        dfs2(0, newAdj, ans);

        return ans;
    }

    private void dfs(int u, List<List<Integer>> adj, String s,
                     int[] last, int[] newParent, int[] parent) {

        int c = s.charAt(u) - 'a';
        int prev = last[c];

        if (prev != -1) {
            newParent[u] = prev;
        } else {
            newParent[u] = parent[u];
        }

        last[c] = u;

        for (int v : adj.get(u)) {
            dfs(v, adj, s, last, newParent, parent);
        }

        last[c] = prev;
    }

    private int dfs2(int u, List<List<Integer>> adj, int[] ans) {
        for (int v : adj.get(u)) {
            ans[u] += dfs2(v, adj, ans);
        }

        return ans[u];
    }
}