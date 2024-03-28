#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <stdexcept>

using namespace std;

class MD5Utils {
    
public:
    static int SHORT_URL_CHAR_SIZE;
    static string convert(const std::string& longURL);
    static string generateRandomShortUrl(const string& longURL);
};

int MD5Utils::SHORT_URL_CHAR_SIZE = 8;

string MD5Utils::convert(const string& longURL) {
    // Create MD5 Hash
    hash<string> hasher;
    size_t hash = hasher(longURL);

    // Convert hash to hex string
    stringstream ss;
    ss << hex << setw(16) << setfill('0') << hash;
    return ss.str();
}

string MD5Utils::generateRandomShortUrl(const string& longURL) {
    string hash = convert(longURL);
    int numberOfCharsInHash = hash.length();
    unordered_set<string> database;

    // Simulating the database check
    auto exists = [&database](const string& s) { return database.find(s) != database.end(); };

    // Generate random indices to start searching for a unique substring
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, numberOfCharsInHash - SHORT_URL_CHAR_SIZE);

    int counter = 0;
    while (counter < numberOfCharsInHash - SHORT_URL_CHAR_SIZE) {
        string substr = hash.substr(dis(gen), SHORT_URL_CHAR_SIZE);
        if (!exists(substr)) {
            return substr;
        }
        counter++;
    }

    throw runtime_error("Unable to generate a short URL for: " + longURL);
}

/*
int main() {
    const string longURL = "https://www.example.com";
    string shortURL = MD5Utils::generateRandomShortUrl(longURL);
    cout << "Short URL: " << shortURL << endl;
    return 0;
}
*/