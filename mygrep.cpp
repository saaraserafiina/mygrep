// Ohjelmoinnin edistyneet piirteet, mygrep-projekti
// Saara Heikkilä

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

struct Options {

    // struct that contains the options

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
    // a part of the larger txt string. Can also be
    // reused in the file function

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


vector<pair<string, int>> findSubstringFile(const string& subtxt, const string& filename, bool ignoreCase, bool reverse) {

    // Takes two parameters from user input, first one is the subtext to look for and
    // another is the filename. Takes also two bool 
    // parameters. Other one is the ignoreCase and other one is reverse. 
    // They tell whether or not the function ignores caps lock letters or does a reverse search.
    // Function opens the file, searches for the subtext and appends 
    // the line in which the subtext was found into a vector. it also saves the row number. 


    ifstream file(filename);
    int lineNum = 0;

    vector<pair<string, int>> lines;

    if (!file) {
        throw - 1;

    }

    string line;
    string lowerSub = subtxt;

    if (ignoreCase == true) { // if ignorecase, turn subtxt to lowercase
        toLower(lowerSub);
    }


    while (getline(file, line)) {

        lineNum++;
        string lowerLine = line;
        if (ignoreCase) {

            toLower(lowerLine);
        }

        vector<int> found = findSubString(lowerLine, lowerSub); // using the findsubstring function

        if (!reverse) {

        if (!found.empty()) {

            lines.push_back({ line , lineNum});
        }
        }
        else if (reverse) { // if reverse is true, appending the lines not containing the subtxt into the vector

            if (found.empty()) {
                lines.push_back({ line, lineNum });
            }
        }
    }

    file.close();

    return lines;
}




Options parseOptions(const string& optString) {

    // This function is meant to help processing the optional command line commands.
    // It processes the user input (which is the optstring parameter) and
    // according to it, it sets some of the optional functionalities as true,
    // so that the program knows which acts the user wants to perform. 
    // if the user gives wrong option arguments, an error is thrown

    Options opts;

    if (optString.length() > 1 && optString[0] == '-' && optString[1] == 'o') {

        for (int i = 2; i < optString.length(); i++) {


            switch (optString[i]) {

            case 'l':
                opts.showLineNumbers = true;
                break;

            case 'o':
                opts.showOccurrences = true;
                break;

            case 'i':
                opts.ignoreCase = true;
                break;

            case 'r':
                opts.reverseSearch = true;
                break;


            default:
                throw invalid_argument(
                    string("Invalid option -- '") + optString[i] + "'"
                );
            }
        }
    }

    else {
        throw invalid_argument("invalid option format");
    }

    return opts;
}

        


  int main(int argc, char* argv[])

      // main function. handles all the cases of different amounts of input arguments
      // also error handling
    {

    try {

        if (argc == 1) {

            // if argc == 1, which means that the user only ran the program, the user can input
            // a string and a substring

            string txt;
            string sub;

            cout << "Give a string from which to search for: ";
            getline(cin, txt);

            cout << "Give a search string: ";
            getline(cin, sub);

            vector<int> found = findSubString(txt, sub); // searching the substring

            if (found.empty()) { // if it is not found
                cout << '"' << sub << "\" NOT found in \""
                    << txt << '"' << endl;
            }

            else {
                for (int i = 0; i < found.size(); i++) { // if it is found, program prints the position

                    cout << '"' << sub << "\" found in \"" << txt << "\" in position " << found[i] << endl;

                }

            }
                    
        }

        else if (argc == 3) {

            // if arcg == 3, it means that the user has input a substring and a file 

            vector<pair<string, int>> fileLines =
                findSubstringFile(argv[1], argv[2], false, false); // using the file function

            for (const auto& entry : fileLines) {
                cout << entry.first << endl;
            }

            if (fileLines.empty()) {
                cout << '"' << argv[1] << "\" NOT found in \""
                    << argv[2] << '"' << endl;
                return 1;  
            }
        }

        else if (argc == 4) {

            // if argc == 4, user has also chosen options

            Options opts = parseOptions(argv[1]); // parsing the options from user input

            vector<pair<string, int>> fileLines =
                findSubstringFile(argv[2], argv[3],
                    opts.ignoreCase,
                    opts.reverseSearch);

            for (const auto& entry : fileLines) {

                if (opts.showLineNumbers) {
                    cout << entry.second << ": ";
                }

                cout << entry.first << endl;
            }

            if (opts.showOccurrences) {
                cout << "\nOccurrences of lines containing "
                    << argv[2] << ": "
                    << fileLines.size() << endl;
            }

            if (fileLines.empty()) {
                return 1;  
            }
        }

        else {
            // if the option input is invalid
            throw - 2;
        }
        
        return 0;  
    }


    // catching exeptions

    catch (int exeptionNumber) {

        cerr << "An exeption occurred. Exeption Nr. " << exeptionNumber << endl;

        if (exeptionNumber == -1 && argc >= 3) {
            cerr << "Could not find out the size of file \"" << argv[argc - 1] << "\"" << endl;
        }

        else if (exeptionNumber == -2) {
            cerr << "Wrong amount of arguments." << endl;
            cerr << "Usage: mygrep [-olori] PATTERN FILE" << endl;

        }

        return 2;
    }

    catch (const invalid_argument& e) {
        cerr << "mygrep: " << e.what() << endl;
        cerr << "Usage: mygrep [-olori] PATTERN FILE" << endl;
        return 2;

        }

    }
