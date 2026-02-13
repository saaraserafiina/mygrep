// Ohjelmoinnin edistyneet piirteet, mygrep-projekti
// Saara Heikkilä

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


void toLower(string& s) {

    // Changes a string to lowercase

    for (auto& x : s) {
        x = tolower(x);
    }
}

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


void findSubstringFile(const string& subtxt, const string& filename ) {

    // Takes two parameters from user input, first one is the subtext to look for and
    // another is the filename. Function opens the file, searches for the subtext and prints
    // the lines the text is found in. 

    ifstream file(filename);

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    string lowerSub = subtxt;

    toLower(lowerSub);

    while (getline(file, line)) {

        string lowerLine = line;
        toLower(lowerLine);

        vector<int> found = findSubString(lowerLine, lowerSub);

        if (!found.empty()) {

            cout << line << endl;
        }
    }

    file.close();

    return;
}


int main(int argc, char*argv[])

{

    if (argc == 1) {

    

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

        }


    else if (argc == 3) {
        findSubstringFile(argv[1], argv[2]);
   }




    return 0;
}
