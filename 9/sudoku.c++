class Solution {
public:
    bool isSafe(int row,int col,char value,vector<vector<char>>& board){
        // same row mai vo number na ho
        // smae column mai vo number na ho
        // same 3*3 ke matrix mai vo number na ho
        int n=board.size();

        // row check 
        for(int i=0;i<n;i++){
            if(board[row][i]==value){
                return false;
            }
        }
        for(int i=0;i<n;i++){
            if(board[i][col]==value){
                return false;
            }
        }

        //3*3 box ka check
        for(int i=0;i<n;i++){
                // yaha pr hi galti hoti hai
                if(board[3*(row/3)+i/3][3*(col/3)+i%3]==value){
                    return false;
                }
        }
        return true;
    }
    bool solveHelper(vector<vector<char>>& board){
        int n=board.size();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                //empty cell check karo
                if(board[i][j]=='.'){
                    //try karenge -> 1-> 9 insert krne ka
                    for(char ch='1';ch<='9';ch++){
                        if(isSafe(i,j,ch,board)){
                            //place kardo
                            board[i][j]=ch;

                            bool recursionKaAns=solveHelper(board);
                            if(recursionKaAns == true){
                                return true;
                            }else{
                                // recursion ans nahi la paya
                                //iska matlbh jo ch apne insert kiya vo galat tha
                                //iska matlbh backtrack krdo wapas jao
                                board[i][j]='.';
                            }
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) {
        solveHelper(board);
    }
};