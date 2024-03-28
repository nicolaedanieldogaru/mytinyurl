#include <iostream>
#include <string>
#include <random>

using namespace std;

class RandomURLGenerator {
    
private:
    string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<> dis;

public:
    RandomURLGenerator() : gen(rd()), dis(0, charset.size() - 1) {}

    string generateRandomString(int length) {
        string randomString;
        for (int i = 0; i < length; ++i) {
            randomString += charset[dis(gen)];
        }
        return randomString;
    }

    string generateRandomURL(int dimension, const string& url) {
        string randomString = generateRandomString(dimension);
        return url + "/" + randomString;
    }
};
/*
int main() {
    RandomURLGenerator generator;

    int dimension = 8; // Change the dimension as needed
    string url = "https://example.com";

    string randomURL = generator.generateRandomURL(dimension, url);
    cout << "Random URL: " << randomURL << std::endl;

    return 0;
}
*/