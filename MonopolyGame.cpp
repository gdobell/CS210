#include <iostream>
#include <string>
using namespace std;

// Each property stores its name, cost, owner, and next pointer.
struct Property {
   string name;
   int cost;
   string owner;
   Property* next;

   // now assign null values with a constructor 
   Property(const string& propertyName, int propertyCost) {
      name = propertyName;
      cost = propertyCost;
      owner = "Unowned";
      next = nullptr;
   }
};

// Implementing our linked list
class MonopolyBoard {
// declaring the first and last property space on the board 
private: 
    Property* head;
    Property* tail;

// make sure this is public so we can instantiate it in main
public:
// class constructor to initialize 
  MonopolyBoard() {
      head = nullptr;
      tail = nullptr;
  }


//adding
void addProperty(const std::string& name, int cost) {
// create the new property that has a name and cost
  Property* newProperty = new Property(name, cost);

  // if the list is currently empty 
  if (head == nullptr) {
      // set the head and tail to be the new property
      head = newProperty;
      tail = newProperty;
      // close the circular linked list 
      head -> next = head;
      } else {
      // there are properties already in the list 
          // we link the tail to the new node 
          tail -> next = newProperty;
          // the tail is assigned to the newProperty, updated tail pointer 
          tail = newProperty;
          // we set the tail to look at the head so it remains a circular linked list 
          tail -> next = head;
    }
}

    
// searching(a linear search)
Property* searchProperty(const std::string& propertyName) {
     // the list only has one value so we dont need to search
     if (head == nullptr) {
         return nullptr;
     }

     // check the head first 
     if (head -> name == propertyName) {
         return head;
     }

     // now look at the node after the head 
     Property* current = head -> next;

     // while we are looking at a node that is not our head 
     while(current != head) {
          // if it is the property we are looking for, print it 
          if (current -> name == propertyName) {
              return current;
          } 
          // set out current to be the next node, so moving one node forward 
          current = current -> next;
     }
     // we did not find it, so we return our null pointer  
     return nullptr;
}

// removing
bool removeProperty(const std::string& propertyName) {
    // check if we have any nodes in our list 
    if (head == nullptr) {
        // nothing to remove 
        return false;
    }

    // we need to keep track of our current and previous node 
    Property* current = head;
    Property* previous = tail;

   do {
       // now if we only have one value in the list and it is the property we want to remove
       if(current -> name == propertyName) {
          if (current == head && current == tail) {
              // make all of our pointers go to null
              head = nullptr;
              tail = nullptr;
          } else {
              // if there's more than one element, then we set the previous next pointer to be the current next pointer
              // basically just moving one element forward
              previous -> next = current -> next;
    
              // if we ended up deleting the first element, then we set the head to look towards the new first element
              if (current == head) {
                  head = current -> next; 
              }

              // if we deleted the last space, then we set the tail to look at the previous element, which is now the last element 
              if (current == tail) {
                  tail = previous;
              }

              // this keeps our linked list circular 
              tail -> next = head;
         }

         // this frees the node memory to prevent any memory leaks
         delete current;
         // the removal has succeeded 
         return true; 
       }

       // advance both tracking pointers by one node 
       previous = current;
       current = current -> next;
     
     // this will all loop until it wraps back around to head again
   } while (current != head);
     // if the target name was not found, then we just return false 
     return false;
} 

// printing 
void printBoard() {
     // check if the board is empty and print according to that 
     if (head == nullptr) {
         cout << "The board is empty numnuts.\n";
         return;
     }

     Property* current = head;

     // now printing each property with it's cost and owner 

     do { 
        // print the property name, cost, and ownder in the same line
         cout << current -> name << " / Cost: $" 
         << current -> cost << " / Owner: " << current -> owner << "\n";

        // set the new current position
        current = current -> next;
     } while (current != head);
  }
}

// now for the actual movement and actions around the board 
// moving our player 
Property* movePlayer(Property* cuurentPosition, int spaces) {
    // if the player is at the beginning of the board just reutrn the head
    if (currentPosition == nullptr) {
       return head;
    }

    // loop through the whole board for how many spaces there are 
     for (int i = 0; i < spaces; i++) {
         currentPosition = currentPosition -> next;
     }

     // return where they landed 
     return currentPosition;
}

// now purchasing property 
bool purchaseProperty(Property* property, const string& playerName) {
     // base condition again if there is no property on the space the player landed on 
     if (property == nullptr) {
         return false;
     }

     // if the property landed on is already owned
     if (property -> owner != "Unowned") {
        cout << property -> name << " has already been purchased by " << property -> owner << "\n";
        return false;
     }

     // if the property is purchasable 
     // set the new owner name 
     property -> owner = playerName;
     // then print it out 
     cout << playerName << " purchased " << property -> name 
     << " for a whoppin $" << property -> cost << "\n";

     // return true since a property was purchased 
     return true;
}

// since there is no automatic garbage collection like Java we need a destructor 
// we used new which points to dynamic memory so we need to clean up allocated nodes 
// ai disclosure here I used it to help me write one of these because I have never done it before 
~MonopolyBoard() {
    // already all cleaned up
    if (head == nullptr) {
        return;
    }

    // point the tail to null and set the current to head so we can do a loop that will eventually end
    tail -> next = nullptr;
    // tracker 
    Property* current = head;

    while(current != nullptr) {
        // save the address of the next space before we delete the current one so we keep the pointer
        Property* nextproperty = current -> next;
        // free the heap memory
        delete current;
        // advance the pointer
        current = nextProperty;
    }
};

// now create out players 
struct Player {
   string name;
   Property* position;

   Player(const string& playerName, Property* startingPos) {
       name = playerName;
       position = startingPos;
   }
};

// now onto main where we create the details of our board 
int main()
   MonopolyBoard board;
   // start with the go square
   board.addProperty("GO", 0);
   board.addProperty("Sunset Boulevard", 100);
   board.addProperty("Park Place", 150);
   board.addProperty("Baltic Avenue", 125);
   board.addProperty("Rose Court", 350);
   board.addProperty("Lavender Avenue", 200);
   board.addProperty("Nelson Road", 500);
   board.addProperty("Queen Court", 400);
   board.addProperty("Montezuma Road", 100);
   board.addProperty("Mushroom Place", 300);

   // test if our removal function works 
   board.addProperty("Temp", 0);

  // test for search 
  Property* found = board.searchProperty("Temp");
  // if found print out that we found it, if not print that we didnt
  if (found != nullptr) {
    cout << "Search found the property: " << found -> name << "\n";
  } else {
    cout << "Could not find property";
  }

  // test for removal
  bool removed = board.removeProperty("Temp");
  if (tail -> "Temp) {
    return "The Temp was not removed: Test failed";
  } else {
    return "The Temp was removed: Test passed";
  }

  // starting board
  cout<< "\n--------- INITIAL BOARD ---------";
  board.printBoard();

  // now our players!
  Player player1("Dumb", board.getStart());
  Player player2("Dumber", board.getStart());

  int moves[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // now simulate all of thier turns 
  cout<< "\n--------- 10 PLAYER TURNS ---------"
  for (int i = 0; i < 10; i++) {
      Player* currentPlayer;
      // if its even player 1 starts and if its odd then player 2 starts
      // meaning player 1 starts and then player 2 goes alternating turns 
      if (turn % 2 == 0;
        currentPlayer = &player1;
      } else {
          currentPlayer = &player2;
      }

      // set the current position
      int spaces = moves[i];

      // move the player 
      currentPlayer -> position = board.movePlayer(currentPlayer -> position, spaces);

      // print out info 
      cout << "Turn " << i + 1 << ": " << currentP;ayer -> name 
        << " moved " << spaces << " spaces and landed on " << currentPlayer -> position -> name
        << "\n";

     // now call the purchase property function
     board.purchaseProperty(currentPlayer-> position, currentPlayer -> name);
     cout << "\n";
}

// now print the final board to see what happened 
cout<< "\n--------- FINAL BOARD ---------"
board.printBoard();

return 0;

}
