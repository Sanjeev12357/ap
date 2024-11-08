#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'journeyToMoon' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY astronaut
 */


int journeyToMoon(int n, vector<vector<int>> astronaut) {
    vector<vector<int>> adj(n);  // adjacency list for the graph
    for (const auto& pair : astronaut) {
        adj[pair[0]].push_back(pair[1]);
        adj[pair[1]].push_back(pair[0]);
    }

    vector<bool> visited(n, false);
    vector<int> country_sizes;

    // Function to calculate size of each connected component
    function<int(int)> dfs = [&](int node) {
        visited[node] = true;
        int size = 1;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                size += dfs(neighbor);
            }
        }
        return size;
    };

    // Find sizes of all connected components
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            country_sizes.push_back(dfs(i));
        }
    }

    // Calculate the total number of ways to pick two astronauts from different countries
    long long total_ways = 0;
    long long sum_sizes = accumulate(country_sizes.begin(), country_sizes.end(), 0LL);

    for (int size : country_sizes) {
        sum_sizes -= size;
        total_ways += size * sum_sizes;
    }

    return total_ways;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int p = stoi(first_multiple_input[1]);

    vector<vector<int>> astronaut(p);

    for (int i = 0; i < p; i++) {
        astronaut[i].resize(2);

        string astronaut_row_temp_temp;
        getline(cin, astronaut_row_temp_temp);

        vector<string> astronaut_row_temp = split(rtrim(astronaut_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int astronaut_row_item = stoi(astronaut_row_temp[j]);

            astronaut[i][j] = astronaut_row_item;
        }
    }

    int result = journeyToMoon(n, astronaut);

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
