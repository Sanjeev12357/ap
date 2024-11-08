#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'camelcase' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int camelcase(string s) {
    int word_count = 1; // Start with 1 as the first word is lowercase
    
    for (char c : s) {
        if (isupper(c)) { // Each uppercase letter marks a new word
            word_count++;
        }
    }
    
    return word_count;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    int result = camelcase(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
