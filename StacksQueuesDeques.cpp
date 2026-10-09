#include <iostream>
using namespace std;

// Implement a stack using an array-based representation.
class ArrayStack {
//Initialize the array size as well as a null value for the topInd
     int arr[20];
     int topInd = -1;

public:
// push
   void push(int value) {
       // first check if we are still within our set array size, we cant use .size() like java :(
      if (topInd >= 19) {
         cout << "Stack is full\n";
      } else {
          // if we are not above our set size, then add the value into the next index 
         arr[++topInd] = value;
      }
   }
   // isEmpty before pop because I'm going to use it there 
   bool isEmpty() {
       // t or f statement 
      return topInd == -1;
   }

   // pop
   int pop() {
       // check if we have any values in our array
       if (isEmpty()) {
           cout << "Stack Empty";
           return -1;
       } else {
           // if we do then just decrement the index and return the previous value
            return arr[topInd--];
       }
   }
   };

//--------------------------------------------------------------------------------

// Implement a stack using your own linked-list representation.
class LinkedListStack {
   // represents a singular node 
     struct Node {
     // node only needs 2 things, value and the next pointer 
         int value;
         Node* next;
     };
     // assign the top node to a null value so it can be replaced later 
     Node* top = nullptr;

public: 
    // need a destructor 
    ~LinkedListStack() {
         while (!isEmpty()) {
           pop();
         }
    }

   // is empty
   bool isEmpty() {
       // t or f statement 
       return top == nullptr;
   }

   // push
   void push(int value) {
       // creates a new node and then assigns it to the top because we can only access a stack
       // from the top 
       top = new Node{value, top};
   }

   // pop
   int pop() {
       // check if its empty 
       if (isEmpty()) {
          cout << "Stack is empty";
          return -1;
       } else {
         // save the top node's adress
         Node* temp = top;
         // save the top node's value so we can return it later
         int oldTop = temp -> value;
         // put the second value in the linked list to be the new top
         top = top -> next;
         // delete the old too
         delete temp;
         // return the old top
         return oldTop;
       }
   }
};

//--------------------------------------------------------------------------------


// Implement a queue using an array-based representation.
class ArrayQueue {
   // array size
   int arr[20];
   // front for dequeue 
   int front = 0;  
   // back for enqueue 
   int back = -1;
   // # of elements in array
   int elements = 0;

public:
  // isEmpty
  bool isEmpty() {
      return elements == 0;
  }

  // enqueue: adds a value at the end of the queue
  void enqueue(int value) {
      // check if we overflowed it
      if (elements >= 20) {
         cout << "Queue is full";
         return;
      } else {
          // add to the end 
          // rear = rear + 1 would cause an overflow without knowing it, so we add the modulo
          // so that if it gets to 20, we will just wrap around back to the beginning
          back = (back + 1) % 20;
          // now insert the value at the new rear index
          arr[back] = value;
          // increment the element count
          elements++;
      }
  }

   // now dequeue: removes and returns the value at the front of the queue
   int dequeue() {
      // check if it's empty
      if (isEmpty()) {
         cout << "Queue is empty";
         return -1;
      } else {
          // save the front value
          int oldFrontOfTheLine = arr[front];
          // advance the index again using the modulo
          front = (front + 1) % 20;
          // decrement the elements
          elements--;
          // return the old front
         return oldFrontOfTheLine;
      }
   }
};

//--------------------------------------------------------------------------------


// Implement a queue using your own linked-list representation.
class LinkedListQueue {
    struct Node {
        int value;
        Node* next;
    };
    Node* front = nullptr;
    Node* back = nullptr;

public:
   // decstructor
   ~LinkedListQueue() {
        while (!isEmpty()) {
           dequeue();
        }
   }

   // is empty
   bool isEmpty() {
       return front == nullptr;
   }

   // enqueue
   void enqueue(int value) {
       // make the new node with value and nullptr for now
       Node* newNode = new Node{value, nullptr};
       // check if the list is empty first 
       if (isEmpty()) {
         // then the front and back will just be the same node 
         front = back = newNode;
       } else {
          // we insert at the end of the queue
          // assign the pointer and the value to be our new Node 
          back -> next = newNode;
          back = newNode;
       }
   }

   // now dequeue() {
   int dequeue() {
       if (isEmpty()) {
         cout << "Nothing to dequeue, Queue is empty";
         return -1;
       } else {
           // save the front value 
           Node* temp = front;
           // take care of the pointer 
           int value = temp -> value;
           // move the front pointer forward 
           front = front -> next;
           // check for an edge case, if there are no elemenets left 
           if (front == nullptr) {
               back = nullptr;
           }
           // delete it
           delete temp;
           // return the front value
           return value;
       }
   }
};

//--------------------------------------------------------------------------------
           
// Implement a deque using an array-based representation.
class ArrayDeque {
      // initialize array size, front, back, and # of elements 
      int arr[20];
      int front = 0;
      int elements = 0;

public:
     // isEmpty
     bool isEmpty() {
         return elements == 0;
     }

     // push from the front 
     void pushFront(int value) {
         // check if we went over our array size 
         if (elements >= 20)  {
           cout << "Deque is full";
         } else {
             // update the front's index
             front = (front - 1 + 20) % 20;
             // update the value 
             arr[front] = value;
             // update the # of elements
             elements++;
         }
     }

      // push from the back
      void pushBack(int value) {
         // check if we went over our array size 
         if (elements >= 20)  {
           cout << "Deque is full";
         } else {
             // update the back's index, this needs the # of elements since the back index changes
             int backInd = (front + elements) % 20;
             // update the value 
             arr[backInd] = value;
             // update the # of elements
             elements++;
         }
      }

       // now pop from the front
       int popFront() {
           // check if empty
           if (isEmpty()) {
              cout << "Deque is empty";
              return -1;
           } else {
                // save the front value
                int value = arr[front];
                // reassign the index
                front = (front + 1) % 20;
                // decrement # of elements thus getting rid of the value
                elements--;
                // return the value 
                return value;
           }
       }

        // pop from the back
       int popBack() {
           // check if empty
           if (isEmpty()) {
              cout << "Deque is empty";
              return -1;
           } else {
                // reassign the index
                int backInd = (front + elements - 1) % 20;
                // save the back value
                int value = arr[backInd];
                // decrement # of elements thus getting rid of the value
                elements--;
                // return the value 
                return value;
           }
       }
};

             
//--------------------------------------------------------------------------------

// Implement a deque using your own linked-list representation.
class LinkedListDeque {
     struct Node {
        int value;
        Node* next;
        Node* prev;
     };
     Node* head = nullptr;
     Node* tail = nullptr;

public:
  // destructor 
  ~LinkedListDeque() {
      while (!isEmpty()) {
        popFront();
      }
  }

  // is empty
  bool isEmpty() {
      return head == nullptr;
  }

  // push from the front
  void pushFront(int value) {
      // make the new node, it takes the value, head pointer, and tail pointer
      Node* newNode = new Node{value, head, nullptr};
      // check if empty
      if (isEmpty()) {
         // assign the head and tail to be the same value
         head = tail = newNode;
      } else {
         // the head's previous node is now the new node and the new node is the head
         head -> prev = newNode;
         head = newNode;
      }
  }

  // push from the back
  void pushBack(int value) {
      // make the new node, it takes the value, head pointer, and tail pointer
      Node* newNode = new Node{value, nullptr, tail};
      // check if empty
      if (isEmpty()) {
         // assign the head and tail to be the same value
         head = tail = newNode;
      } else {
         // the head's previous node is now the new node and the new node is the head
         tail -> next = newNode;
         tail = newNode;
      }
  }

// pop from the front
int popFront() {
    // check if its empty
    if (isEmpty()) {
       cout << "The Deque is empty";
       return -1;
    } else {
      // save the value and address of the head
      Node* temp = head;
      int value = temp -> value; 
      // reassign the pointer
      head = head -> next;
     // check if this made our list empty or not and assign pointers appropriately 
     // if we have a head node
     if (head != nullptr) {
         // then point the head's prev pointer to null
         head -> prev = nullptr;
     } else {
         // head is null so there are no elements in the list 
         tail = nullptr;
     }
      // delete the old value address and return the value
      delete temp;
      return value;
    }
}

// pop from the back
int popBack() {
    // check if its empty
    if (isEmpty()) {
       cout << "The Deque is empty";
       return -1;
    } else {
      // save the value and address of the head
      Node* temp = tail;
      int value = temp -> value; 
      // reassign the pointer
      tail = tail -> prev;
      // check the same edge case as before just with the tail instead 
      if (tail != nullptr) {
          tail -> next = nullptr;
      } else {
          head = nullptr;
      }
      // delete the old value address and return the value
      delete temp;
      return value;
    }
}
};
