class Solution {
public:
    int LOG;
    vector<vector<int>> adj, up;
    vector<int> depth, tin, tout, initialMask;
    vector<int> bit;

    void updateBIT(int idx, int val, int n) {
        idx++;

        while (idx <= n) {
            bit[idx] ^= val;
            idx += idx & -idx;
        }
    }

    int queryBIT(int idx) {
        int ans = 0;
        idx++;

        while (idx > 0) {
            ans ^= bit[idx];
            idx -= idx & -idx;
        }

        return ans;
    }

    void rangeUpdate(int l, int r, int val, int n) {
        updateBIT(l, val, n);

        if (r + 1 < n) {
            updateBIT(r + 1, val, n);
        }
    }

    int getMask(int u) {
        return initialMask[u] ^ queryBIT(tin[u]);
    }

    int lca(int u, int v) {

        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];

        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i)) {
                u = up[i][u];
            }
        }

        if (u == v) {
            return u;
        }

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }

        return up[0][u];
    }

    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {

        LOG = 1;

        while ((1 << LOG) <= n) {
            LOG++;
        }

        adj.assign(n, {});
        up.assign(LOG, vector<int>(n, 0));

        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        initialMask.assign(n, 0);

        bit.assign(n + 1, 0);

        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Iterative DFS / Euler Tour

        int timer = 0;

        vector<tuple<int, int, bool>> st;

        st.push_back({0, 0, false});

        while (!st.empty()) {

            auto [u, p, exiting] = st.back();
            st.pop_back();

            if (!exiting) {

                tin[u] = timer++;

                up[0][u] = p;

                initialMask[u] =
                    (u == 0 ? 0 : initialMask[p])
                    ^ (1 << (s[u] - 'a'));

                st.push_back({u, p, true});

                for (int v : adj[u]) {
                    if (v != p) {
                        depth[v] = depth[u] + 1;
                        st.push_back({v, u, false});
                    }
                }

            } else {
                tout[u] = timer - 1;
            }
        }

        // Build Binary Lifting Table

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                up[j][i] = up[j - 1][up[j - 1][i]];
            }
        }

        vector<bool> ans;

        for (string& q : queries) {

            string type;
            int u, v;

            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {

                char c;
                ss >> c;

                int oldBit = 1 << (s[u] - 'a');
                int newBit = 1 << (c - 'a');

                int change = oldBit ^ newBit;

                rangeUpdate(tin[u], tout[u], change, n);

                s[u] = c;
            }

            else {

                ss >> v;

                int w = lca(u, v);

                int mask =
                    getMask(u) ^
                    getMask(v) ^
                    (1 << (s[w] - 'a'));

                ans.push_back(__builtin_popcount((unsigned int)mask) <= 1);
            }
        }

        return ans;
    }
};