class Solution {
public:
    void dfs(vector<vector<int>>& image, int sr, int sc, int oldColor, int newColor) {
        int m = image.size();
        int n = image[0].size();

        if (sr < 0 || sc < 0 || sr >= m || sc >= n || image[sr][sc] != oldColor)
            return;

        image[sr][sc] = newColor;

        dfs(image, sr + 1, sc, oldColor, newColor);
        dfs(image, sr - 1, sc, oldColor, newColor);
        dfs(image, sr, sc + 1, oldColor, newColor);
        dfs(image, sr, sc - 1, oldColor, newColor);
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int oldColor = image[sr][sc];

        if (oldColor == color) return image;

        dfs(image, sr, sc, oldColor, color);

        return image;
    }
};