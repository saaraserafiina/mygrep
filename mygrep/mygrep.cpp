// Ohjelmoinnin edistyneet piirteet, mygrep-projekti
// Saara Heikkilä

#include <iostream>
#include <vector>
#include <string>
using namespace std;



vector<int> findSubString(const string& txt, const string& subtxt) {

    // Function takes two strings as parameters
    // It finds out whether or not the subtxt string is
    // a part of the larger txt string. 
    
    vector<int> indexes;


    int n = txt.length();
    int m = subtxt.length();

    if (m == 0 || n < m) return indexes;



    for (int i = 0; i <= n - m; i++) {

        int j;
        for (j = 0; j < m; j++) {

            if (txt[i + j] != subtxt[j]) {
                break;
            }
        }

        if (j == m) {
            indexes.push_back(i);
        }

    }
    return indexes;
}


void toLower(string& s) {

    // Changes a string to lowercase

    for (auto& x : s) {
        x = tolower(x);
    }
}



int main()

{

    string txt;
    string sub;

    cout << "Give a string from which to search for: ";
    getline(cin, txt);

    cout << "Give a search string: ";
    getline(cin, sub);


    toLower(txt);
    toLower(sub);


    vector<int> found = findSubString(txt, sub);

    if (found.empty()) {
        cout << '"' << sub << "\" NOT found in \""
            << txt << '"' << endl;
    }
    else {
        for (int i = 0; i < found.size(); i++) {

        
        cout << '"' << sub << "\" found in \"" << txt << "\" in position " << found[i] << endl;
    }

    }



    return 0;
}
