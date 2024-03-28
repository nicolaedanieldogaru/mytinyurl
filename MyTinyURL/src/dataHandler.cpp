#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

extern database db;

class dataHandler {
private:
    string filename;

public:

    // Constructor
    dataHandler() {}

    dataHandler(const string& fname) : filename(fname) {}

    // Destructor
    ~dataHandler() {}


    // Mothod to write a new entry in datafile
    bool writeToTextFile(const string& data) {
        ofstream outputFile(filename, ios::app);
        if (outputFile.is_open()) {
            outputFile << data << endl;
            outputFile.close();
            return true;
        } else {
            cerr << "Error opening file for writing.\n";
            return false;
        }
    }

    // Mothod to read datafile
    bool readFromTextFile() {

        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string line;
            cout << "Contents of the datafile:\n";
            while (getline(inputFile, line)) {
                cout << line << endl;

                vector<string> parts;
                stringstream ss(line);
                string part;
                while (getline(ss, part, ' ')) {
                    parts.push_back(part);
                }

                db.insert(parts[0], parts[1]);
            }
            inputFile.close();
            return true;
        } else {
            cerr << "Error opening file for reading.\n";
            return false;
        }
    }
};

/*
// Test case for class Base62Generator
int main() {
    dataHandler file("data.txt");

    if (file.writeToTextFile("short_URL long_URL")) {
        cout << "Data written to file successfully." << endl;
    }

    if (file.readFromTextFile()) {
        cout << "File read successfully." << endl;
    }

    return 0;
}
*/