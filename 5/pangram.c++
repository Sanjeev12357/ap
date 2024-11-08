#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'pangrams' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string pangrams(string s) {
    // Convert string to lowercase
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    
    // Use a set to keep track of unique letters
    unordered_set<char> letters;
    
    for (char c : s) {
        if (isalpha(c)) { // Only consider alphabetic characters
            letters.insert(c);
        }
    }

    // If we have 26 unique letters, it's a pangram
    return letters.size() == 26 ? "pangram" : "not pangram";
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = pangrams(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
