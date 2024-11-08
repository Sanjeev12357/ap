class Solution {
public:
    unordered_map<int,bool> rowCheck;
    unordered_map<int,bool> topDiagnol;
    unordered_map<int,bool> bottomDiagnol;

    bool isSafe(int row,int col,vector<vector<char>>& board){
        if(rowCheck[row]==true){
            return false;

        }
        if(topDiagnol[col-row]==true){
            return false;

        }
        if(bottomDiagnol[row+col]==true){
            return false;
        }

        return true;
    }

    void storeSolution(vector<vector<char>>& board,vector<vector<string>>& ans){
        vector<string> tempSol;
        for(auto vec:board){
            string temp="";
            for(auto ch:vec){
                temp.push_back(ch);
            }

            tempSol.push_back(temp);
        }
        ans.push_back(tempSol);
    }

    void solve(vector<vector<char>>& board,vector<vector<string>>& ans,int n,int col){
        if(col>=n){
            storeSolution(board,ans);
            return ;
        }
        // main logic
        //is column k hr row pr queen place krke dekoh
        for(int row=0;row<n;row++){
            if(isSafe(row,col,board)){
                board[row][col]='Q';
                

                // mark all the three direction that q is placed here
                rowCheck[row]=true;
                topDiagnol[col-row]=true;
                bottomDiagnol[row+col]=true;

                //recursion 
                solve(board,ans,n,col+1);

                //back track
                board[row][col]='.';
                rowCheck[row]=0;
                topDiagnol[col-row]=0;
                bottomDiagnol[row+col]=0;


            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<vector<char>>board(n,vector<char>(n,'.'));
        int col=0;
        solve(board,ans,n,col);
        return ans;
    }
};