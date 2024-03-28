#include <string>
#include <algorithm>

using namespace std;

extern database db;

class Base62Generator {
    
private:
    string charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string base62string;
    int code_length = 8;
    int database_entry = db.size() + 1;

public:
    // Constructor
    Base62Generator() {}
    
    // Destructor
    ~Base62Generator() {}

    // Method to generate a base 62 code
    string generate() {

    int div, rest;
    
    // Convert database_entry into a base 62 code with length = code_length
    while (code_length || database_entry) {

        div = database_entry / 62;
        rest = database_entry % 62;

        base62string += charset[rest];

        database_entry = div;
        --code_length;
    }

    reverse(base62string.begin(), base62string.end());

    return base62string;
    }

};
/*
// Test case for class Base62Generator
int main() {

    Base62Generator base62Generator;

    string random = base62Generator.generate();
    
    cout << "Base62Code: " << random << endl;

    return 0;
}
*/