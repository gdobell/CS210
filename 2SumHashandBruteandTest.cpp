// loading in libraries 
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


class Solution {
public:

// this is the brute force method 
std::pair<int, int> twoSumBruteForce(const std::vector<int>& nums, int target) {
    // nested for loop
// I was struggling here and Im new to C++ so I looked it up and static_cast converts the size
// into a standard int vs an unsigned integer called size_t 
  for (int i = 0; i < static_cast<int>(nums.size()); i++) {
     for (int j = i + 1; j < static_cast<int>(nums.size()); ++j) {
       
        // now checking if adding the indices will add up to the target
         if(nums[i] + nums[j] == target) {
          
           // if correct then return the correct pair of indices 
            return {i, j};
         }
     }
  }
       // if the answer does not exist, print out a vector of -1, -1 meaning no solution
       return {-1, -1};
}



// This is the hash table method 
// defining the method signature, in c++ its called a function signature
// method signature needs: parameter type, name of the method, return type  
    std::pair<int, int> twoSumHash(const std::vector<int>& nums, int target) {
        // return type, method name, parameter list 

        // & means pass by reference: not passing a copy of it, but using the object itself
        // by passing in a reference to where the object is in memory

        // this declares an empty hash table. it acts as a memory bamk for numbers we alreayd looked at
        // this was in the class example so ill keep it here 
        std::unordered_map<int, int> index;
        // index is the variable name and the type is an unordered_map from int to int

    // we use the static cast again
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            // look for the needed number vs adding and looking for the target itself 
            int needed = target - nums[i];
            // if we want 10 and we are looking at 4, then our needed is 6
            // now we know what we need

            // if the number is what we need 
            if (index.count(needed)) {
                // then we return 
                return {index[needed], i};
                // if it finds it, then it returns a pair of the index of the needed value and current index
            }
          
            index[nums[i]] = i;
            // to make sure we dont lose the values we just looked that we input them into our empty hash table index 
        }

        return {-1, -1}; // no solution found 
        // {} is a vector literal 
        // boolean literal = true 
        // boolean variable = a name that points to something that will be T or F
        // int literal is 7 or 9 
        // int variable is a variable that could be assigned 7 or 9
        // > is a boolean expression  
    }
};

// now testing 
    int main() {
      // make an instance of solution to call its methods 
      Solution execution;
      
      // test case #1
      // individual variables per test case so I know what is 
    
        std::vector<int> nums1 = {15, 4, 18, 8, 19, 22, 24, 59, 59, 20, 18, 12, 36, 42, 9};
        int target1 = 24;
        std::pair<int, int> answer1Hash = execution.twoSumHash(nums1, target1);
      

      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer1Hash.first != -1 && answer1Hash.second != -1) {
            std::cout << "Test 1 passed for twoSumHash using values " << nums1[answer1Hash.first] << " and " << nums1[answer1Hash.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer1Hash.first << ", " << answer1Hash.second << "]\n";
          // boolean for checking validity 
      bool isItValid1 = (nums1[answer1Hash.first] + nums1[answer1Hash.second] == target1);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid1 ? "true" : "false") << "\n\n";
        } else {
          // extra new line for formatting
          std::cout << "Test 1 Failed, no pair\n\n";
        }
      
      // now brute force 
      std::pair<int, int> answer1Brute = execution.twoSumBruteForce(nums1, target1);
      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer1Brute.first != -1 && answer1Brute.second != -1) {
            std::cout << "Test 1 passed for twoSumBruteForce using values " << nums1[answer1Brute.first] << " and " << nums1[answer1Brute.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer1Brute.first << ", " << answer1Brute.second << "]\n";
          // boolean for checking validity 
      bool isItValid1 = (nums1[answer1Brute.first] + nums1[answer1Brute.second] == target1);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid1 ? "true" : "false") << "\n\n";
        } else {
          // extra new line for formatting
          std::cout << "Test 1 Failed, no pair\n\n";
        }
          
      // now adding 4 more test cases
      // test case #2
        vector<int> nums2 = {11, 3, 2, 9, 6, 7, 18, 21, 10, 1};
        int target2 = 13;
        std::pair<int, int> answer2Hash = execution.twoSumHash(nums2, target2);
      

      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer2Hash.first != -1 && answer2Hash.second != -1) {
            std::cout << "Test 2 passed for twoSumHash using values " << nums2[answer2Hash.first] << " and " << nums2[answer2Hash.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer2Hash.first << ", " << answer2Hash.second << "]\n";
          // boolean for checking validity 
      bool isItValid2 = (nums2[answer2Hash.first] + nums2[answer2Hash.second] == target2);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid2 ? "true" : "false") << "\n\n";
        } else {
          std::cout << "Test 2 Failed, no pair\n\n";
        }

      // now brute force 
      std::pair<int, int> answer2Brute = execution.twoSumBruteForce(nums2, target2);
      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer2Brute.first != -1 && answer2Brute.second != -1) {
            std::cout << "Test 2 passed for twoSumBruteForce using values " << nums2[answer2Brute.first] << " and " << nums2[answer2Brute.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer2Brute.first << ", " << answer2Brute.second << "]\n";
          // boolean for checking validity 
      bool isItValid2 = (nums2[answer2Brute.first] + nums2[answer2Brute.second] == target2);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid2 ? "true" : "false") << "\n\n";
        } else {
          // extra new line for formatting
          std::cout << "Test 2 Failed, no pair\n\n";
        }

      // test case #3
        vector<int> nums3 = {50, 100, 25, 75, 10, 5};
        int target3 = 105;
        std::pair<int, int> answer3Hash = execution.twoSumHash(nums3, target3);

      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer3Hash.first != -1 && answer3Hash.second != -1) {
            std::cout << "Test 3 passed for twoSumHash using values " << nums3[answer3Hash.first] << " and " << nums3[answer3Hash.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer3Hash.first << ", " << answer3Hash.second << "]\n";
          // boolean for checking validity 
      bool isItValid3 = (nums3[answer3Hash.first] + nums3[answer3Hash.second] == target3);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid3 ? "true" : "false") << "\n\n";
        } else {
          std::cout << "Test 3 Failed, no pair\n\n";
        }
    
      // now brute force 
      std::pair<int, int> answer3Brute = execution.twoSumBruteForce(nums3, target3);
      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer3Brute.first != -1 && answer3Brute.second != -1) {
            std::cout << "Test 3 passed for twoSumBruteForce using values " << nums3[answer3Brute.first] << " and " << nums3[answer3Brute.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer3Brute.first << ", " << answer3Brute.second << "]\n";
          // boolean for checking validity 
      bool isItValid3 = (nums3[answer3Brute.first] + nums3[answer3Brute.second] == target3);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid3 ? "true" : "false") << "\n\n";
        } else {
          // extra new line for formatting
          std::cout << "Test 3 Failed, no pair\n\n";
        }
      

        // this should fail
      // test case #4
        vector<int> nums4 = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
        int target4 = 11;
        std::pair<int, int> answer4Hash = execution.twoSumHash(nums4, target4);

      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer4Hash.first != -1 && answer4Hash.second != -1) {
            std::cout << "Test 4 passed for twoSumHash using values " << nums4[answer4Hash.first] << " and " << nums4[answer4Hash.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer4Hash.first << ", " << answer4Hash.second << "]\n";
          // boolean for checking validity 
      bool isItValid4 = (nums4[answer4Hash.first] + nums4[answer4Hash.second] == target4);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid4 ? "true" : "false") << "\n\n";
        } else {
          std::cout << "Test 4 Failed, no pair\n\n";
        }
     
      // now brute force 
      std::pair<int, int> answer4Brute = execution.twoSumBruteForce(nums4, target4);
      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer4Brute.first != -1 && answer4Brute.second != -1) {
            std::cout << "Test 4 passed for twoSumBruteForce using values " << nums4[answer4Brute.first] << " and " << nums4[answer4Brute.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer4Brute.first << ", " << answer4Brute.second << "]\n";
           // boolean for checking validity 
      bool isItValid4 = (nums4[answer4Brute.first] + nums4[answer4Brute.second] == target4);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid4 ? "true" : "false") << "\n\n";
        } else {
          // extra new line for formatting
          std::cout << "Test 4 Failed, no pair \n\n";
        }

      // tets case #5
      vector<int> nums5 = {0, 0, 0, 0, 0};
        int target5 = 1;
        std::pair<int, int> answer5Hash = execution.twoSumHash(nums5, target5);

      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer5Hash.first != -1 && answer5Hash.second != -1) {
            std::cout << "Test 5 passed for twoSumHash using values " << nums5[answer5Hash.first] << " and " << nums5[answer5Hash.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer5Hash.first << ", " << answer5Hash.second << "]\n";
           // boolean for checking validity 
      bool isItValid5 = (nums5[answer5Hash.first] + nums5[answer5Hash.second] == target5);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid5 ? "true" : "false") << "\n\n";
        } else {
          std::cout << "Test 5 Failed, no pair\n\n";
        }
      
      // now brute force 
      std::pair<int, int> answer5Brute = execution.twoSumBruteForce(nums5, target5);
      // no solution for a pair is (-1, -1) so we can check for that 
        if (answer5Brute.first != -1 && answer5Brute.second != -1) {
            std::cout << "Test 5 passed for twoSumBruteForce using values " << nums5[answer5Brute.first] << " and " << nums5[answer5Brute.second]
              << "\n"; 
          std::cout << "Test passed with indices: [" << answer5Brute.first << ", " << answer5Brute.second << "]\n";
          // boolean for checking validity 
      bool isItValid5 = (nums5[answer5Brute.first] + nums5[answer5Brute.second] == target5);
          // ternary operator here to make it more condensed 
          std::cout << "Valid sum? " << (isItValid5 ? "true" : "false") << "\n\n";
        } else {
          // extra new line for formatting
          std::cout << "Test 5 Failed, no pair\n\n";
        }
      return 0;
    }
