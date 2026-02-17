// Ohjelmoinnin edistyneet piirteet, mygrep-projekti
// Saara Heikkilä

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Options {
    bool showLineNumbers = false;
    bool showOccurrences = false;
    bool reverseSearch = false;
    bool ignoreCase = false;

};

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


vector<pair<string, int>> findSubstringFile(const string& subtxt, const string& filename ) {

    // Takes two parameters from user input, first one is the subtext to look for and
    // another is the filename. Function opens the file, searches for the subtext and appends 
    // the line in which the subtext was found into a vector. it also saves the row number

    ifstream file(filename);
    int lineNum = 0;

    vector<pair<string, int>> lines;

    if (!file) {
        cout << "Error opening file!" << endl;
        return lines;
    }

    string line;
    string lowerSub = subtxt;

    toLower(lowerSub);

    while (getline(file, line)) {

        lineNum++;
        string lowerLine = line;
        toLower(lowerLine);

        vector<int> found = findSubString(lowerLine, lowerSub);

        if (!found.empty()) {

            lines.push_back({ line , lineNum});
        }
    }

    file.close();

    return lines;
}

Options parseOptions(const string& optString) {

    // This function is meant to help processing the optional command line commands.
    // It processes the user input (which is the optstring parameter) and
    // according to it, it sets some of the optional functionalities as true,
    // so that the program knows which acts the user wants to perform

    Options opts;
    if (optString.length() > 1 && optString[0] == '-' && optString[1] == 'o') {

        for (int i = 2; i < optString.length(); i++) {

            if (optString[i] == 'l') {
                opts.showLineNumbers = true;

            } if (optString[i] == 'o') {
                opts.showOccurrences = true;
            }
        }
    }

    return opts;
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
        vector<pair<string, int>> fileLines = findSubstringFile(argv[1], argv[2]);
        
        for (const auto& entry : fileLines) {
            cout << entry.first << endl;
        }
        
   }


    else if (argc == 4) {

        Options opts = parseOptions(argv[1]);


        vector<pair<string, int>> fileLines = findSubstringFile(argv[2], argv[3]);

        if (opts.showLineNumbers) {
            for (const auto& entry : fileLines) {
                cout << entry.second << ": " << entry.first << endl;
            }
        }

        if (opts.showOccurrences) {

            if (!opts.showLineNumbers) {

            for (const auto& entry : fileLines) {
                cout << entry.first << endl;
            }
            }

            cout << "Occurrences of lines containing " << argv[2] << ": " << fileLines.size() << endl;
        }



    }

        return 0;

    }