// import libraries
#include <iostream>
#include <vector>
using namespace std;

// iterative binary search 
//Pass a const reference so there's no copying 
int binarySearchIterative(const std:: vector<int>& sortedVector, int target, int& iterativeCount) {
  //Reset the referenced counter passed
  iterativeCount = 0;
  int low = 0;
  int high = static_cast<int>(sortedVector.size()) - 1;

  // making sure that it is sorted with a while loop 
  while (high >= low) {
    int mid = (high + low) / 2;

    // count this first comparison
    iterativeCount++;
    // if the mid is less than the target, then we make the low value mid + 1 so we can 
    // look through the upper half of the vector 
    if (sortedVector[mid] < target) {
      low = mid + 1;
    } else { 
      // count the next comparison; make sure it's before the next if statement since 
      // we want each iteration counted even if it's false 
      iterativeCount++;
      // if the mid is greater than the target, then we make an upper limit lower so that 
      // we can check the lower half of the vector 
      if (sortedVector[mid] > target) {
      high = mid - 1; 
      } else {
        // if neither of those apply, then we already found the value because it is the midpoint
          return mid;
      }
    }
  }
  // if not found at all, then it is not in the vector at all, so we return a -1 index 
  // indicating that it isn't in there at all
  return -1;
}

// recursive binary search
// pass vector by const reference to avoid copying and increasing the time complexity
int binarySearchRecursive(const std::vector<int>& sortedVector, int low, int high, int target, int& recursiveCount) { 
  // right off the bat elimination if it is not sorted and if the vector is empty
  // base case 
   if ((low > high) || (sortedVector.empty())) {
      return -1;
      std::cout << target << " and was not found in the vector,  ";
   }
   // if all is well then we continue 
   int mid = (low + high) / 2;

   // firstcomparison
   recursiveCount++;
   // if the mid value is less than the target, then we call the recursive function for the top
   // half of the vector, so we add one to mid and call again with high 
   if (sortedVector[mid] < target) {
       return binarySearchRecursive(sortedVector, mid + 1, high, target, recursiveCount);
   } else { 
     // third comparison
     recursiveCount++;
     // if the mid value is greater than the target, then we call the recursive function for the 
     // bottom half of the vector, so we subtract one from mid and call again with low 
     if (sortedVector[mid] > target) {
       return binarySearchRecursive(sortedVector, low, mid - 1, target, recursiveCount);
     } else {
       // if not either of those two options, then the mid point is the target value
         return mid;
     }
   }
}



// for testing 
int main() {
  int iterativeCount = 0;
  // tests for the iterative 
  // first element
  std::vector<int> test1 = {2, 7, 11, 15};
  int target1 = 2;
  std::cout << "Iterative test #1:\n The index of the target is " 
    << binarySearchIterative(test1, target1, iterativeCount) 
    << ". The iteration was performed " << iterativeCount << " times. \n";

  // last element
  std::vector<int> test2 = {1, 18, 35, 51, 69};
  int target2 = 69;
  std::cout << "Iterative test #2:\n The index of the target is " 
    << binarySearchIterative(test2, target2, iterativeCount) 
    << ". The iteration was performed " << iterativeCount << " times. \n";

  // middle element
  std::vector<int> test3 = {4, 5, 6, 7, 8, 9, 10};
  int target3 = 7;
  std::cout << "Iterative test #3:\n The index of the target is " 
    << binarySearchIterative(test3, target3, iterativeCount) 
    << ". The iteration was performed " << iterativeCount << " times. \n";

  // below the range of elements 
  std::vector<int> test4 = {2000, 3000, 4000, 5000, 6000};
  int target4 = 1000;
  std::cout << "Iterative test #4:\n The index of the target is " 
    << binarySearchIterative(test4, target4, iterativeCount) 
    << ". The iteration was performed " << iterativeCount << " times. \n";

  // in the range but not in the list 
  std::vector<int> test5 = {3, 6, 9, 12, 15};
  int target5 = 7;
  std::cout << "Iterative test #5:\n The index of the target is " 
    << binarySearchIterative(test5, target5, iterativeCount) 
    << ". The iteration was performed " << iterativeCount << " times. \n\n";

  
  // recursive testing using the same vectors and targets as above 
  // we need to reset the recursiveCount before every test 
  int recursiveCount = 0;
  std::cout << "Recursive test #1:\n The index of the target is " 
     << binarySearchRecursive(test1, 0, static_cast<int>(test1.size()) - 1, target1, recursiveCount) 
     << ". The recursion was performed " << recursiveCount << " times. \n";

  recursiveCount = 0;
  std::cout << "Recursive test #2:\n The index of the target is " 
     << binarySearchRecursive(test2, 0, static_cast<int>(test2.size()) - 1, target2, recursiveCount) 
     << ". The recursion was performed " << recursiveCount << " times. \n";

  recursiveCount = 0;
  std::cout << "Recursive test #3:\n The index of the target is " 
     << binarySearchRecursive(test3, 0, static_cast<int>(test3.size()) - 1, target3, recursiveCount) 
     << ". The recursion was performed " << recursiveCount << " times. \n";

  recursiveCount = 0;
  std::cout << "Recursive test #4:\n The index of the target is " 
     << binarySearchRecursive(test4, 0, static_cast<int>(test4.size()) - 1, target4, recursiveCount) 
     << ". The recursion was performed " << recursiveCount << " times. \n";

  recursiveCount = 0;
  std::cout << "Recursive test #5:\n The index of the target is " 
     << binarySearchRecursive(test5, 0, static_cast<int>(test5.size()) - 1, target5, recursiveCount) 
     << ". The recursion was performed " << recursiveCount << " times. \n\n";

  return 0;
}
