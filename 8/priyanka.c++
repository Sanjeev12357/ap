#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'toys' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY w as parameter.
 */

int toys(vector<int> w) {
    // Step 1: Sort the array of weights
    sort(w.begin(), w.end());

    // Step 2: Initialize box count and the first toy to consider
    int boxes = 0;
    int n = w.size();
    int i = 0;

    while (i < n) {
        // Start a new box with the current toy
        int box_start = w[i];
        boxes++;  // We need a new box
        // Move i forward to include all toys that fit in the current box
        while (i < n && w[i] - box_start <= 4) {
            i++;
        }
    }

    return boxes;
}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string w_temp_temp;
    getline(cin, w_temp_temp);

    vector<string> w_temp = split(rtrim(w_temp_temp));

    vector<int> w(n);

    for (int i = 0; i < n; i++) {
        int w_item = stoi(w_temp[i]);

        w[i] = w_item;
    }

    int result = toys(w);

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
