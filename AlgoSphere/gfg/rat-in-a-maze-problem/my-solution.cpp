// Rat in Maze (GeeksforGeeks, Medium)
// https://www.geeksforgeeks.org/problems/rat-in-a-maze-problem/1
// My accepted solution · 2026-11-26 · runtime 0.03 s

class Solution {
  public:
    vector<string> ans;
    bool check(int i, int j, int m, int n) {
      return i >= 0 && i < m && j >= 0 && j < n;
    }
    void solve(vector<vector<int>> &maze, int r, int c, string str,
               vector<vector<bool>>& vis) {
      
      int m = maze.size(), n = maze[0].size();
      if (r == m-1 && c == n-1) {
        ans.push_back(str);
        return;
      }
      if (check(r + 1, c, m, n) && maze[r + 1][c] == 1 && vis[r+1][c] == false) {
        vis[r][c] = true;
        solve(maze, r + 1, c, str+"D",vis);
        vis[r][c] = false;
      }
      if (check(r, c-1, m, n) && maze[r][c - 1] == 1 && vis[r][c-1] == false) {
        vis[r][c] = true;
        solve(maze, r, c - 1,  str+"L",vis);
        vis[r][c] = false;
      }
      if (check(r, c+1, m, n) && maze[r][c + 1] == 1 && vis[r][c+1] == false) {
        vis[r][c] = true;
        solve(maze, r, c + 1,  str+"R",vis);
        vis[r][c] = false;
      }
      if (check(r -1, c, m, n) && maze[r-1][c] == 1 && vis[r-1][c] == false) {
        vis[r][c] = true;
        solve(maze, r - 1, c,  str+"U",vis);
        vis[r][c] = false;
      }
    }
    vector<string> ratInMaze(vector<vector<int>> &maze) {
      // code here
      int m = maze.size(), n = maze[0].size();
      
      vector<vector<bool>> vis(m, vector<bool>(n, false));
      if(maze[0][0]==1)
        solve(maze, 0, 0, "",vis);
      return ans;
    }
};
