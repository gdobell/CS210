#import <iostream>
using namespace std;

//Create a hash table that holds username keys and user records
// monthly subscription to a rage room 

// pepper that is used for all passwords
const string pepper = "SmashThatShit!!!";

// given hash function
uint64_t demoHash(const std::string& s) {
    uint64_t h = 1469598103934665603ULL;
    for (unsigned char c : s) {
        h = (h ^ c) * 1099511628211ULL;
    }
    return h;
}

// helper function that puts the pepper, salt, and password together 
// and computes the hash using the above function
// same type as above since we're using it to return the same type of value 
uint64_t createPassWordHashFunc(const string& password, const string& salt) {
    // hash itself with the salt and PEPPAH
    string combo = salt + password + pepper;
    // call the hash function 
    return demoHash(combo);
}


// structure for user data 
struct userRecords {
    string username;
    string phoneNumber;
    string salt;
    uint64_t passwordHash;

    // default constructor 
    userRecords() = default;

    // parameterized constructor 
    userRecords(string user, string phone, string salt, uint64_t passHash) :
        username(user), phoneNumber(phone), salt(salt), passwordHash(passHash) {
          // no data needed here
        }
};

// first the chaining hash table: this stores elements in a vector of doubly linked lists
class Chaining {
private:
    vector<list<pair<string, userRecords>>> buckets;
    // using type size_t
    size_t capacity;
    size_t count;
    float max_load_factor;

    // hash the string key into an actual array indez using the given demo
    size_t hash(const string& key, size_t cap) const {
       return hash<string>{} (key) % cap;
    



class Client {
public:
   string username;
   string passowrd;
