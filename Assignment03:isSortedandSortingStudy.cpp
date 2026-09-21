// import files 
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
using namespace std;


// isSorted method 
bool isSorted(const std::vector<int>& values) {
  for (int i = 0; i < static_cast<int>(values.size() - 1); i++) {
      if(values[i] > values[i + 1]) {
        return false;
      }
  }
  return true;
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

// now for the tests themselves 

// generating the random test 
vector<int> makeRandomVector(int len) {
   // initialize an empty vector to store the random values
   vector<int> values;
   // get a random seed
   random_device rd;
   // seed the Mersenne Twister pseudo-random engine
   // I have never heard of this before but hey when I looked it up this is what I was told to use
   mt19937 generator(rd());
   // now define a unifomn range from 1 to 100000
   uniform_int_distribution<int> distribution(1, 100000);

   // now we need to fill it so we use a loop
   for (int i = 0; i < len; i++) {
       values.push_back(distribution(generator));
   }
   // return the vector 
   return values;
}

// now make the sorted test 
vector<int>makeSortedVector(int len) {
   // again initialize the empty vector to store values 
   vector<int> values;
   // loop through to add values in ascending order in the amount of len
   for (int i = 0; i < len; i++) {
       values.push_back(i);
   }
   // return the vector 
   return values;
}


// now make the reverse test
vector<int> makeReverseVector(int len) {
   // initialize the empty vector to store values 
   vector<int> values;
   // now its descending order so we loop backwards
   for (int i = len; i > 0; i--) {
      values.push_back(i);
   }
   return values;
}


// now for timing each of the tests in accordance with a timing table
double timeBubbleSort(const vector<int>& originalVec) {
    // make a copy of the vector that we can use 
    vector<int> values = originalVec;

    // record the current timestamp before sorting 
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(values);
    // then get the end time 
    auto end = chrono::high_resolution_clock::now();

    // implement our isSorted function
    if (!isSorted(values)) {
       cout << "Bubble sort failed bruh :,(" << endl;
    }
    else {
      cout << "Successfully sorted in " << endl;
    }

    // now calculate the elapsed execution time in milliseconds
    chrono::duration<double, milli> time = end - start;
    // return the execution time as a double
    return time.count();
}

// its pretty much just a cookie cutter for the other sorts

// selection test
double timeSelectionSort(const vector<int>& originalVec) {
    // make a copy of the vector that we can use 
    vector<int> values = originalVec;

    // record the current timestamp before sorting 
    auto start = chrono::high_resolution_clock::now();
    selectionSort(values);
    // then get the end time 
    auto end = chrono::high_resolution_clock::now();

    // implement our isSorted function
    if (!isSorted(values)) {
       cout << "Selection sort failed bruh :,(" << endl;
    }
    else {
      cout << "Successfully sorted in " << endl;
    }

    // now calculate the elapsed execution time in milliseconds
    chrono::duration<double, milli> time = end - start;
    // return the execution time as a double
    return time.count();
}


// insertion test

double timeInsertionSort(const vector<int>& originalVec) {
    // make a copy of the vector that we can use 
    vector<int> values = originalVec;

    // record the current timestamp before sorting 
    auto start = chrono::high_resolution_clock::now();
    insertionSort(values);
    // then get the end time 
    auto end = chrono::high_resolution_clock::now();

    // implement our isSorted function
    if (!isSorted(values)) {
       cout << "Insertion sort failed bruh :,(" << endl;
    }
     else {
      cout << "Successfully sorted in " << endl;
    }

    // now calculate the elapsed execution time in milliseconds
    chrono::duration<double, milli> time = end - start;
    // return the execution time as a double
    return time.count();
}


// quick test

double timeQuickSort(const vector<int>& originalVec) {
    // make a copy of the vector that we can use 
    vector<int> values = originalVec;

    // record the current timestamp before sorting 
    auto start = chrono::high_resolution_clock::now();
    // perform a quick check to make sure the vector is not empty
  if(!values.empty()) {
    quickSort(values, 0, static_cast<int>(values.size()) - 1);
  }
    // then get the end time 
    auto end = chrono::high_resolution_clock::now();

    // implement our isSorted function
    if (!isSorted(values)) {
       cout << "Quick sort failed bruh :,(" << endl;
    }
    else {
      cout << "Successfully sorted in " << endl;
    }

    // now calculate the elapsed execution time in milliseconds
    chrono::duration<double, milli> time = end - start;
    // return the execution time as a double 
    return time.count();
}


// now for running the benchmark itself 

void runBenchmark(const vector<int>& values, int len, const string& inputType) {
    // print the current dataset's type and size 
    cout << "\t" << inputType << " - Size " << len << "\n" << endl;

   // printing for bubble sort and running the timer function
   cout << "Bubble sort: " << timeBubbleSort(values) << "ms\n" << endl;

  // printing for selection sort and running the timer function
   cout << "Selection sort: " << timeSelectionSort(values) << "ms\n" << endl;

  // printing for Insertion sort and running the timer function
   cout << "Insertion sort: " << timeInsertionSort(values) << "ms\n" << endl;

  // printing for quick sort and running the timer function
   cout << "Quick sort: " << timeQuickSort(values) << "ms\n" << endl;

  // extra line for formating and such 
  cout << "------------------------------------------------------------\n" << endl;
}




// let the testing commence 
int main() {
  // big enough to show a good pattern
  int lengths[] = {2000, 5000, 10000};

  // loop to store the sizes for iteration
  for (int i = 0; i < 3; i++) {
      int len = lengths[i];

     // generate each vector 
     vector<int> randomValues = makeRandomVector(len);
     vector<int> sortedValues = makeSortedVector(len);
     vector<int> reverseValues = makeReverseVector(len);

     // now run the benchmark for each sort
     runBenchmark(randomValues, len, "Random");
     runBenchmark(sortedValues, len, "Sorted");
     runBenchmark(reverseValues, len, "Reverse Sorted");
  }
   // return 0 to indicate that the program ran all good
   return 0;
}







  
  
