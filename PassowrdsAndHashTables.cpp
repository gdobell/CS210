#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdint> 
#include <iomanip>
#include <utility>
using namespace std;

//Create a hash table that holds username keys and user records
// monthly subscription to a rage room 

//Given hash function
uint64_t demoHash(const std::string& s) {
    uint64_t h = 1469598103934665603ULL;
    for (unsigned char c : s) {
        h = (h ^ c) * 1099511628211ULL;
    }
    return h;
}

// structure for user data 
struct userRecords {
    string username;
    uint64_t passwordHash;
    string salt;
};

// pepper that is used for all passwords
const string pepper = "SmashThatShit!!!";

// parameterized constructor and calling the hash function
userRecords makeUser(string name, string password, string salt) {
    return {name, demoHash(salt + password + pepper), salt};
}


// first the chaining collision strategy hash table: this stores elements in a vector of doubly linked lists
class ChainingHash {
private:
    vector<list<userRecords>> buckets;
    // using type size_t and this is needed for load factor later 
    size_t count = 0;

    // hash the string key into an actual array index using the given demo
    size_t ind(const string& key) const {
       return demoHash(key) % buckets.size();
    }

    // handle the rehash here, this is used when the table fills up and it adjusts the size
    void rehash(size_t capacity) {
       // moves the bucket vector into a temp var so buckets is empty now
       auto old = move(buckets);
       // now resize the array with capacity amount of buckets 
       buckets.resize(capacity);
       // now loop through to reassign stuff; outside loops through indexs
       for (size_t i = 0; i < old.size(); i++) {
            // need a nested for loop for the list itself 
            // ai disclosure here I was not sure of the correct syntax and such 
            // it is the iterator and old[i].begin() gets you the first element of the old[i] list
            // keep going until you hit the end of the list 
            for (auto j = old[i].begin(); j != old[i].end(); j++) {
                 // dereference the iterator so we can get a reference to the userRecords object
                 // does not copy it in memory making the space complexity smaller
                 const userRecords& user = *j;
                 // get the user/s new bucket index with user.username and then insert
                 // the user into the end of the list with push_back
                 buckets[ind(user.username)].push_back(user);
            }
       }

       // just a clean cout statement
       cout << "HERE HERE REHASH EVENT: " << old.size() << " buckets to " << capacity << " buckets\n";
    }

    // now handle load factor, insert, find, remove 
public:
  // make my hash table with explicit so c++ doesnt automatically convert anything
  explicit ChainingHash(size_t capacity = 5) {
      // loop through and add a new empty linked list into the vector, we add 5 in this case 
     for (size_t i = 0; i < capacity; i++) {
          buckets.push_back(list<userRecords>());
     }
  }

     // now calculate the load factor 
     // use const here so the object's internal state doesn't get modified or anything and only has data read
     double loadFactor() const {
         return double(count) / buckets.size();
     }

     // function for count as well
     size_t size() const {
         return count;
     }

     // now our find function 
     const userRecords* find(const string& key) const {
        // calculate index 
        size_t bucketInd = ind(key);
        // calculate the specific list that the user will be stored in 
        const list<userRecords>& chain = buckets[bucketInd];

        // now our loop to search 
        for (auto i = chain.begin(); i != chain.end(); ++i) {
            // dereference the iterator into a reference: ai disclosure here I didnt know I had to do this
            // now go searching 
            if (i -> username == key) {
                // returns the address of the user 
                return &(*i);
            }
        }
        // if u cant find the user 
        return nullptr;
     }

            
    // now insert which just has a bool return type 
    bool insert(const userRecords& user) {
      // use find function here to check if its already in the vector
       if(find(user.username)) {
          return false;
       }

       // check if we need to rehash at all to make room
       // I looked it up and if the ratio of the elements to buckets in a list is over 75%,
       // linked lists become too long which slows down runtime. so we use this as our cap
       if (double(count + 1) / buckets.size() > 0.75) {
          // then rehash
          rehash(buckets.size() * 2 + 1);
       }

       // if we are all chillin then we can actually insert the user now
       buckets[ind(user.username)].push_back(user);
       // increase the count 
       ++count;
       // return true since we did insert something 
       return true;
    }

    // now handling removing
    bool remove(const string& key) {
      // find the target bucket
      auto& chain = buckets[ind(key)];
      // loop through the bucket's list to find the specific element 
      for (auto i = chain.begin(); i != chain.end(); i++) {
          if (i -> username == key) {
             // we delete it using the erase keyword
             chain.erase(i);
             // decerase the count and return true for a successful deletion
             -- count;
             return true;
          }
      } 
      // return false if it did not work or we did not find the element 
      return false;
    }
};
      

// now moving on to the rest of the collision strategies
enum class CollisionStrategies {
     linearProbing,
     quadraticProbing, 
     doubleHashing
};

// so I can print out Linear probing instead of a 0 index
string strategyName(CollisionStrategies strat) {
   switch(strat) {
       case CollisionStrategies::linearProbing: return "Linear Probing";
       case CollisionStrategies::quadraticProbing: return "Quadratic Probing";
       case CollisionStrategies::doubleHashing: return "Double Hashing";
   }
   return "Idk man";
}
          
          
          
// hash table implementation
class collTable {
private: 
   // not a user struct but a slot struct which represents a single slot in the array 
   struct slot {
      string key;
      // keep track of actions
      bool occupied = false; 
      bool deleted = false; 

      // default constructor and the parametrized constructor
      slot() = default;
      slot(string k, bool o, bool d) : key(k), occupied(o), deleted(d) {}
   };

   // declare the array that stores the table 
   vector<slot> slotArray;
   // so we can specifically pick a certain collision strategy
   CollisionStrategies method;
   // keeping track of the elements 
   size_t count = 0;

   // method for calculating the array index for a given key based on the strategy chosen
   size_t pos(const string& key, size_t step) const {
       // base hash: so the ideal slot
       size_t base = demoHash(key) % slotArray.size();

       // now calculate for each specific strategy
       // linear probing: just goes step by step forward
       if (method == CollisionStrategies::linearProbing) {
           return (base + step) % slotArray.size();
       }

       // quadratic probing: triangular sequence of (step * (step + 1) / 2
       if (method == CollisionStrategies::quadraticProbing) {
           return (base + step * (step + 1) / 2) % slotArray.size();
       }

       // double hashing: we calculate a second hash value to determine how many steps we go forward 
       size_t bigStep = 1 + (demoHash("second hash: " + key) % (slotArray.size() - 1));
       // ai disclosure here. I had no idea what to do but apparently bitwise forces our bigStep
       // to be odd and table capacity is even. we want an odd step size to we visit all slots 
       // this will do that :)
       bigStep |= 1;

       // then just return whatever index it is
       return (base + step * bigStep) % slotArray.size();
   }

public:
    // make sure we have a capacity of 26 slots for the sake of our quadratic probing: 2^4 = 16
    // it is the min amoutn of buckets we need for our code to properly work
    explicit collTable(CollisionStrategies strat)
        : method(strat) {
         for (size_t i = 0; i < 16; i++) {
              slotArray.push_back(slot());
         }
   }

    // now handle insert: same base logic as for the chaining method function 
    bool insert(const string&key) {
        // if key is found no need to insert it
        if(find(key) || count == slotArray.size()) {
           return false;
        }

         // ai disclosure here in all honestly i didnt know what i was doing
        // check where the first deleted index is 
        size_t firstDeleted = slotArray.size();       

        // loop through the slots 
        for (size_t i = 0; i < slotArray.size(); i++) {
             // use our position method from earlier 
             size_t p = pos(key, i);

             // record the first deleted index encountered because we could insert there 
             if(slotArray[p].deleted && firstDeleted == slotArray.size()) {
               // then we found one and assign it to firstDeleted
               firstDeleted = p;
             }

             // or there isnt one deleted index slot 
             if(!slotArray[p].occupied && !slotArray[p].deleted) {
                // we want to ideally choose a firstdeleted slot though so handle that 
                if (firstDeleted != slotArray.size()) 
                    p = firstDeleted;
                // pass in appropriate parameters 
                slotArray[p] = slot(key, true, false);
                // update appropriate stuff
                ++count;
                return true;
             }
        }

        // we need to overwrite the first deleted if the cycle finished without finding an empty slot 
        if (firstDeleted != slotArray.size()) {
            // insert still executes so same as earlier 
            slotArray[firstDeleted] = {key, true, false};
            ++count;
            return true;
        }
        // if we dont insert it then we return false
        return false;
    }

     // now our find function 
     bool find(const string& key) const {
        // loop through the array
         for (size_t i = 0; i < slotArray.size(); i++) {
              // looking at a specific slot
              const auto& s = slotArray[pos(key, i)];

              // an empty slot that has been never filled so we know that the key will not be past it
              // so we stop when we hit a slot that has never been filled
              if (!s.occupied && !s.deleted) {
                  return false;
              }

              // we found a match!
              if (s.occupied && s.key == key) {
                  return true;
              }
         }
         return false;
     }

    // now the remove method 
    bool remove(const string& key) {
        for (size_t i = 0; i < slotArray.size(); i++) {
             auto& s = slotArray[pos(key, i)];

             // if never occupied and never deleted then theres nothing to remove
             if (!s.occupied && !s.deleted) {
                 return false;
             }

             // target key located and mark it as deleted 
             if (s.occupied && s.key == key) {
                 // update everthing 
                 s.occupied = false;
                 s.deleted = true;
                 --count;
                 return true;
             }
        }
         // return false 
        return false;
     }
 };

// now the login stuff! a helper function 
bool login(const ChainingHash& table,
           const string& name,
           const string& password) {
     
     // look for the user by name 
     const userRecords* user = table.find(name);

     // return the user name and a bool representing whether the password is correct 
     return user && demoHash(user->salt + password + pepper) == user -> passwordHash;
}
        
// now the main function!
int main() {
    // specifically for chaining 
    ChainingHash table;

    // now the 5 users 
    const vector<userRecords> users = {
       makeUser("WreckItRalph", "ImGonnaSmashIt100", "salty1"),
       makeUser("DonkeyKong", "RAHRAHRAH10101010", "salty2"),
       makeUser("TasmanianDevil", "SnarlSnarlGrr10", "salty3"),
       makeUser("TimmyTurner", "WhatCouldPossiblyGoWrong?", "salty4"),
       makeUser("Kirby", "EatItAllYummy", "salty5")
};

// fill the table
for (size_t i = 0; i < users.size(); i++) {
     table.insert(users[i]);
}

// bool alpha to make sure bools print properly as true and false 
cout << boolalpha;

// print the stored users, load factor, successful login, wrong password, unknown user not in the system
// removal as well as a rehash event 
cout << "# of users stored: " << table.size() << "\n";
cout << "Load factor: " << table.loadFactor() << "\n";
cout << "Successful login: " << login(table, "Kirby", "EatItAllYummy") << "\n";
cout << "Wrong password bruh: " << login(table, "DonkeyKong", "thatsincorrect") << "\n";
cout << "Unknown user: " << login(table, "nobaadyy", "nuthinnn") << "\n";
cout << "Remove WreckItRalph: " << table.remove("WreckItRalph") << "\n";
cout << "WreckItRalph has been found after thought to have gone turbo: " 
    << (table.find("WreckItRalph") != nullptr) << "\n";

// now onto testing the rest of the collision strategies 
// assigning each to a number to make looping through easier 
CollisionStrategies methods[3] = {
    CollisionStrategies::linearProbing, 
    CollisionStrategies::quadraticProbing, 
    CollisionStrategies::doubleHashing,
};

// loop through each
for (size_t i = 0; i < 3; i++) {
     // get the method # and then pass it into probe, which is an instance of colltable
     CollisionStrategies method = methods[i];
     collTable probe(method);

     // fill up the table 
     for (size_t j = 0; j < users.size(); j++) {
          probe.insert(users[j].username);
     }

     // for removing and finding specifically
     bool before = probe.find("TimmyTurner");
     bool removed = probe.remove("TimmyTurner");
     bool after = probe.find("TimmyTurner");

     // output for each different strategy
     cout << "Probe strategy: " << strategyName(method)
         << ": find = " << before << ", remove = " << removed
         << ", after = " << after << "\n";
}
// as always a return 0
return 0;
}     
