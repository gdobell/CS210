// import files 
#include <iostream>
#include <vector>
using namespace std;


// isSorted method 
bool isSorted(const std::vector<int>& values) {
  for (int i = 0; i < static_cast<int>(values.size()); i++) {
      if(values[i] - 1 > values[i]) {
        return false;
          cout << "That vector is not at all sorted babe yikes";
      }
  }
  return true;
  cout << "Your vector is all sorted and perfect babe"
}

// bubble sort 
void bubbleSort(std::vector<int>& values) {
  int len = static_cast<int>(values.size());
// first check if anything was swapped at all. this is also our stopping condition
// last element is already in place so we dont need to check it for both loops
  for (int i = 0; i < len - 1; i++) {
      bool swapped = false;
    
      for (int j = 0; j < len - 1 - i; j++) {
          if (values[j] > values [j+1]) {
             int temp = values[j];
             values[j] = values[j + 1];
             values[j + 1] = temp;
            // we did swap it so update the boolean flag 
             swapped = true;
          }
      }
      // now check the stopping condition
      if (!swapped) {
          break;
      }
  }
}

// selectionSort
void selectionSort(std::vector<int>& values) {
int len = static_cast<int>(values.size());
// last element is assumed to be sorted so again - 1
  for (int i = 0; i < len - 1; i++) {
      // checking for smaller values so we assume the current i is the smallest element 
      int smolInd = i;
      for (int j = i + 1; j < len; j++) {
          if (values[j] < values[smolInd]) {
              smolInd = j;
          }
      }

      // now perform the swap
      int temp = values[i];
      values[i] = values[smolInd];
      values[smolInd] = temp;
  }
}

// insertionSort
void insertionSort(std::vector<int>& values) {
  int len = static_cast<int>(values.size());

  // we assume the first element is sorted so we start at 1 vs 0 index
  for (int i = 1; i < len; i++) {
      // we reassign here because i holds the outer loop's position, so then j can do 
      // all the comparison inner work
      int j = i;
      // making sure that we are still in range and if j < j -1 because if it is 
      // then we need to swap them
      while (j > 0 && values[j] < values[j - 1]) {
            // we swap the numbers 
            int temp = values[j];
            values[j] = values[j - 1];
            values[j - 1] = temp;
            j--;
      }
  }
}


// quickSort
// partition first 
int Partition(std::vector<int>& values, int lowInd, int highInd) {
    // pick the middle element as the pivot 
    int mid = (lowInd + highInd) / 2;
    int piv = values[mid];

    // bool flag
    bool done = false;
    while(!done) {
    // when sorting the lower half we move closer to the pivot so we increment
         while(values[lowInd] < piv) {
               lowInd++;
         }
         // when sorting the upper half, we move down to the pivot so we decrement 
         while(piv < values[highInd]) {
               highInd--;
         }

         // check if lowInd and highInd overlapped at all
         if (lowInd >= highInd) {
         // if they have, then we are good because it should be sorted
            done = true;
         }
         else {
             // they havent crossed so we need to swap stuff 
             int temp = values[lowInd];
             values[lowInd] = values[highInd];
             values[highInd] = temp;

            // then update the new low and high ind to go sort recursively again
            lowInd++;
            highInd--;
        }
    }
  // highInd represents the partition that we should use for the quicksort
    return highInd;
}

// now the quickSort function itself 
void quickSort(std::vector<int>& values, int lowInd, int highInd) {
  // base case, if the array contains zero or only one element, then we just return it 
  if (highInd <= lowInd) {
     return;
  }

  // if there is more than one value in the array, then we recursively call quickSort 
  // call partition first to get out pivot point which is the lower end of the vector's index 
  int lowEndInd = Partition(values, lowInd, highInd);
  // then we call quickSort on each half of the vector that we partitioned 
  quickSort(values, lowInd, lowEndInd);
  quickSort(values, lowEndInd + 1, highInd);
}

// now for all the testing 
int main() {
  // check each function with isSorted: 3 tests total

  int randomTest = {3, 1, 9, 8, 2, 12, 11, 4, 20, 15, 2, 5, 13};
  int alreadySortedTest = {15, 17, 19, 50, 52, 69, 71, 80};
  // large input size to show a trend 
  int reverseSorted = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

 // tests themselves 
  cout<< bubbleSort(randomTest));
  isSorted(bubbleSort(randomTest));
  

  







  
  
