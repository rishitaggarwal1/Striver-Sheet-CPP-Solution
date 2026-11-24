// Sudoku Solver (LeetCode, Hard)
// https://leetcode.com/problems/sudoku-solver/
// My accepted solution · 2026-11-24

class Solution {
public:
    vector<vector<bool>> row = vector<vector<bool>>(10, vector<bool>(10, false));
    vector<vector<bool>> col = vector<vector<bool>>(10, vector<bool>(10, false));
    vector<vector<bool>> box = vector<vector<bool>>(10, vector<bool>(10, false));
    bool solve(vector<vector<char>>& board)
    {
       for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(board[i][j]=='.')
                {
                    int z = (i/3)*3 + j/3;
                    for(int k=1;k<=9;k++)
                    {
                        if(col[j][k]==false && row[i][k]==false && box[z][k]==false)
                        {
                            board[i][j]=k + '0';
                            col[j][k] = true;
                            row[i][k] = true; 
                            box[z][k] = true;
                            if(solve(board))
                                return true;
                            board[i][j]='.';
                            col[j][k] = false;
                            row[i][k] = false;
                            box[z][k] = false;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(board[i][j]=='.')    continue;
                int x = board[i][j]-'0';
                row[i][x] = true;
                col[j][x] = true;
                int z = (i/3)*3+j/3;
                box[z][x]=true;
            }
        }
        solve(board);
    }
};
