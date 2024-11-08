#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'luckBalance' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. 2D_INTEGER_ARRAY contests
 */

int luckBalance(int k, vector<vector<int>> contests) {
    int totalLuck = 0;
    vector<int> importantContests;

    // Step 1: Separate the important and unimportant contests
    for (const auto& contest : contests) {
        int luck = contest[0];
        int isImportant = contest[1];

        if (isImportant == 0) {
            // Unimportant contest, lose it and gain the luck
            totalLuck += luck;
        } else {
            // Important contest, store the luck values
            importantContests.push_back(luck);
        }
    }

    // Step 2: Sort important contests by luck in descending order
    sort(importantContests.rbegin(), importantContests.rend());

    // Step 3: Lose the top 'k' important contests and win the rest
    for (int i = 0; i < importantContests.size(); i++) {
        if (i < k) {
            // Lose the contest, gain luck
            totalLuck += importantContests[i];
        } else {
            // Win the contest, lose luck
            totalLuck -= importantContests[i];
        }
    }

    return totalLuck;
}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);
    int k = stoi(first_multiple_input[1]);

    vector<vector<int>> contests(n);

    for (int i = 0; i < n; i++) {
        contests[i].resize(2);

        string contests_row_temp_temp;
        getline(cin, contests_row_temp_temp);

        vector<string> contests_row_temp = split(rtrim(contests_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int contests_row_item = stoi(contests_row_temp[j]);
            contests[i][j] = contests_row_item;
        }
    }

    int result = luckBalance(k, contests);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

string rtrim(const string &str) {
    string s(str);
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
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
