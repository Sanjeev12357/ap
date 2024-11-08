#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */
struct Node {
    int x, y, moves;
};

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    int n = grid.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    queue<Node> q;
    
    // Directions array for up, down, left, right movements
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    // Start BFS from the starting point
    q.push({startX, startY, 0});
    visited[startX][startY] = true;
    
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        
        // Check if the goal is reached
        if (node.x == goalX && node.y == goalY) {
            return node.moves;
        }
        
        // Explore all four directions
        for (auto& dir : directions) {
            int nx = node.x;
            int ny = node.y;
            
            // Move in the current direction until an obstacle or boundary is hit
            while (nx + dir.first >= 0 && nx + dir.first < n && ny + dir.second >= 0 && ny + dir.second < n &&
                   grid[nx + dir.first][ny + dir.second] == '.') {
                nx += dir.first;
                ny += dir.second;
                
                // If this cell hasn't been visited, add it to the queue
                if (!visited[nx][ny]) {
                    visited[nx][ny] = true;
                    q.push({nx, ny, node.moves + 1});
                }
            }
        }
    }
    
    // If the goal is not reachable
    return -1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int startX = stoi(first_multiple_input[0]);

    int startY = stoi(first_multiple_input[1]);

    int goalX = stoi(first_multiple_input[2]);

    int goalY = stoi(first_multiple_input[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
