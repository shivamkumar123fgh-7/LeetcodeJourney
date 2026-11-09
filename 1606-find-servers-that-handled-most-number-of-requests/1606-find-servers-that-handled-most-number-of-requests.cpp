class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {

        set<int> available;

        // Initially, all servers are available
        for(int i = 0; i < k; i++) {
            available.insert(i);
        }

        // Min Heap: {finishTime, serverID}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busy;

        vector<int> count(k, 0);

        for(int i = 0; i < arrival.size(); i++) {

            // Release servers whose requests have finished
            while(!busy.empty() && busy.top().first <= arrival[i]) {

                int server = busy.top().second;

                busy.pop();

                available.insert(server);
            }

            // If all servers are busy, drop the request
            if(available.empty()) {
                continue;
            }

            // Preferred server
            int target = i % k;

            // Find next available server
            auto it = available.lower_bound(target);

            // Wrap around if necessary
            if(it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign request to server
            available.erase(it);

            count[server]++;

            // Calculate when server becomes available
            busy.push({
                (long long)arrival[i] + load[i],
                server
            });
        }

        // Find maximum requests handled
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for(int i = 0; i < k; i++) {
            if(count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};