#include <string>
#include <unordered_map>

using namespace std;

class database {
    
private:
    unordered_map<string, string> map;

public:
    // Constructor
    database() {}

    // Destructor
    ~database() {}

    // Method to insert key-value pair into the map
    // key   - short URL   
    // value - long URL
    void insert(const string& key, const string& value) {
        map[key] = value;
    }

    // Method to retrieve value corresponding to a given key
    string getValue(const string& key) {
        if (map.find(key) != map.end()) {
            return map[key];
        } else {
            return ""; // Return empty string if key not found
        }
    }

    // Method to check if a key exists in the map
    bool containsKey(const string& key) {
        return map.find(key) != map.end();
    }

    // Method to remove a key-value pair from the map
    void remove(const string& key) {
        map.erase(key);
    }

    //Method to get map size
    int size() {
        return map.size();
    }
};