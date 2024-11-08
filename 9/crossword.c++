//https://www.hackerrank.com/challenges/crossword-puzzle/problem

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
//Task is an empty block to be filled with word, either horizontal / vertical
struct taskItem{
    int r;
    int c;
    int len;
    int dir;//hor=0, vert=1, -1 invalid
    string ans;
    taskItem():r(-1),c(-1),len(-1),dir(-1),ans(""){}
    void print(){
        cout << "\n r:"<<r <<",c:"<<c<<",len:"<<len<<",dir:"<<dir << ",ans("<<ans<<")";
    }
};

/*
 * Complete the 'crosswordPuzzle' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY crossword
 *  2. STRING words
 */

//problem given function
string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}
//problem given function
string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

//Function that find the list of horizontal tasks 
void addHorizontalTasks(vector<string>& cw, vector<taskItem>& tasklist){
    for(int row=0;row<(int)cw.size();++row){
        int len = 0;
        taskItem item;
        for(int col=0;col<(int)cw[0].size();++col){
            if(len ==0 && cw[row][col] == '-' ) {
                item.r = row;
                item.c = col;
            }
            
            if(cw[row][col] == '-')
                ++len;
            if(col<(int)cw[0].size()-1&&cw[row][col] == '-' && cw[row][col+1] != '-' && len == 1)
             {
                 len =0;
                 continue;
             }

        }
        
        if(len>1){
            item.len = len;
            item.dir = 0;           
            tasklist.emplace_back(item); 
        }
    }
}

//Function that find the list of vertical tasks 
void addVerticalTasks(vector<string>& cw, vector<taskItem>& tasklist){
    for(int col=0;col<(int)cw[0].size();++col){
        int len = 0;
        taskItem item;
        for(int row=0;row<(int)cw.size();++row){
            if(len ==0 && cw[row][col] == '-' ) {
                item.r = row;
                item.c = col;
            }
            
            if(cw[row][col] == '-')
                ++len;

            if (row < (int)cw.size() - 1 &&
                cw[row][col] == '-' &&
                cw[row + 1][col] != '-' 
                )
            {
                if (len > 1)
                    break;

                len = 0;
                continue;
            }

        }
        
        if(len>1){
            item.len = len;
            item.dir = 1;           
            tasklist.emplace_back(item); 
        }
    }
}

//debug function
void printGrid(const vector<string>& grid){
    cout << "\n";
    for (size_t i = 0; i < grid.size(); i++) {
        cout << grid[i];

        if (i != grid.size() - 1) {
            cout << "\n";
        }
    }
}

//This is a validation if the word can be placed as per task direction
bool canPlace(vector<string> cw,//copy
    string token,
    const vector<taskItem>& tasklist,
    int curr,
    vector<string>& newcw)
{
    newcw = cw;
    auto it = tasklist[curr];
    if (it.dir == 1) {
        int j = 0;
        for (int row = it.r; row < it.r + it.len; ++row) {
            if (cw[row][it.c] != '-' && cw[row][it.c] != token[j])
            {
                newcw = cw;
                return false;
            }
            cw[row][it.c] = token[j++];
        }
    }
    else if (it.dir == 0) //horzontal fill
    {
        int j = 0;
        for (int i = 0; i < it.len; ++i) {
            auto col = it.c + i;
            if (cw[it.r][col] != '-' && cw[it.r][col] != token[j])
            {
                newcw = cw;
                return false;
            }
            cw[it.r][col] = token[j++];
        }
    }
    else {//invlaid direction
        return false;
    }
    newcw = cw;
    return true;
}

//Main solution 
//Recursive for DFS with backtracking, using a stack of all next level nodes
// It will try all next possible words for current level if next level failed.
bool solution(const vector<string>& cw,
    const vector<taskItem>& tasklist,
    vector<string>& tokens,
    vector<int> tu,
    int currtask,
    vector<string>& ans) {
    if (currtask >= (int)tasklist.size())
    {//since we exhausted all tasks, we are done solution obtained.
        ans = cw;
        return true;
    }

    std::stack<string> store; //create dfs current level tree
    //smartness is the length of the word 
    for (int i = 0; i < (int)tu.size(); ++i) {
        if (tu[i] == 0 && tasklist[currtask].len == (int)tokens[i].size())
        {
            store.push(tokens[i]);
        }
    }

//Iterate to all words available at current level if failed 
//backtrack one level up and retry
    while (!store.empty()) {
        string t = store.top();
        assert(t.empty() == false);
        store.pop();
        auto currTokenId = -1;
        for (int i = 0; i < (int)tokens.size(); ++i) {
            if (tokens[i] == t)
            {
                tu[i] = 1;
                currTokenId = i;
                break;
            }
        }

        vector<string> newcw;
        if (canPlace(cw, t, tasklist, currtask, newcw))//success - output is new grid newcw
            if (solution(newcw, tasklist, tokens, tu, currtask + 1, ans))
            {
                return true;
            }
        
        //if failed free the token
        tu[currTokenId] = 0;
    }
    
    //we failed if reached here cannot place all words
    //now backtrack
    return false;
}

vector<string> crosswordPuzzle(vector<string> cw, string words) {

    std::string input = words;
    std::istringstream iss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, ';')) {
        tokens.push_back(token);
    }

    vector<int> tokenUsed(tokens.size(), 0);
    
    vector<taskItem> tasklist;
    addHorizontalTasks(cw, tasklist);
    addVerticalTasks(cw, tasklist);
    
    vector<string> ans;
    solution(cw, tasklist, tokens, tokenUsed, 0, ans );
       
    return ans;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}