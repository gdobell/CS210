#include <iostream>
#include <algorithm>
using namespace std;

// create a node type 
class Node {
public:
   int key;
   Node* left;
   Node* right;

   Node(int nodeKey, Node* rightChild = nullptr, Node* leftChild = nullptr) {
      key = nodeKey;
      right = rightChild;
      left = leftChild;
    }
};

// and a BinarySearchTree class
class BinarySearchTree {
private:
  Node* root = nullptr;

public: 
// insert
void insert(Node* newNode) {
// first check if our tree is empty because then we just insert into the root 
  if (root == nullptr) {
     root = newNode;
  } 
// else we still assign the new node to the root, but start looking at the rest of the tree
// if the new node is less than the root then we put it to the right, if its greater than the left
  else {
      Node* currentNode = root;
      while(currentNode) {
          // if the new node is less than the current node(root node)
          if (newNode -> key < currentNode -> key) {
             // and if there is no left child 
             if (currentNode -> left == nullptr) {
                // we insert the node at the left child spot 
                 currentNode -> left = newNode;
                 currentNode = nullptr;
             } 
             else {
                 // the left spot is already taken so we move our currentNode to that left child
                 // so we can do this loop all over again if needed 
                 currentNode = currentNode -> left;
             }
          }
          // the newNode key is not less than the current node so we have to go to the right 
          // according to the laws of a binary tree 
          else {
            // the right spot is open so we can put it there! And in doing so we assign currentNode
            // to null since we dont need it anymore
            if (currentNode -> right == nullptr) {
                currentNode -> right = newNode;
                currentNode = nullptr;
            } else {
                  // the right child is taken so we move the current pointer to that child
                  currentNode = currentNode -> right;
            }
         }
      }
   }
}


// search 
Node* search (int searchKey) {
    Node* currentNode = root;
    while(currentNode) {
        // if the node we are searching for is the root
        if (currentNode -> key == searchKey) {
            return currentNode;
        }
        // if the search key is less than the current node's key, then we go to the left
        else if (searchKey < currentNode -> key) {
            currentNode = currentNode -> left;
        }
        // else its greater so we go to the left 
        else {
            currentNode = currentNode -> right;
        }
    }
    // if we did not find the key 
    return nullptr;
}


// removal 
bool remove(int key) {
  Node* parent = nullptr;
  Node* currentNode = root;

  while(currentNode) {
     // check if the first currentNode is the key we are looking for 
     if (currentNode -> key == key) {
        if (currentNode -> left == nullptr && currentNode -> right == nullptr) {
         // if it has no children, then we can remove it easier. removing a leaf node
           if (parent == nullptr) {
              // the node we are removing is the root 
              root = nullptr;
           } 
           else if (parent -> left == currentNode) {
              // the node is the left child of the currentNode
              parent -> left = nullptr;
           }
           else {
             // the node is the right child of the currentNode
             parent -> right = nullptr;
           }
           // delete the node and return true if we found it and deleted it  
           delete currentNode;
           return true;
        }
        // now removing a node that just has a left child 
        else if (currentNode -> left && currentNode -> right == nullptr) {
           // if the node we are removing is the root 
           if (parent == nullptr) {
               // shift the left child there 
               root = currentNode -> left;
            // if current node is a left child 
           } else if (parent -> left == currentNode) {
                // reassign pointers 
                parent -> left = currentNode -> left;
           } else {
                // it is a right child 
                parent -> right = currentNode -> left;
           }
           // successfully deleted
           delete currentNode;
           return true; 
          // removing a node that has a right child 
        } else if (currentNode -> left == nullptr && currentNode -> right) {
          // it is the root node
          if (parent == nullptr) {
              root = currentNode -> right;
          } else if (parent -> left == currentNode) {
              parent -> left = currentNode -> right;
          } else {
              parent -> right = currentNode -> right;
          }
          delete currentNode;
          return true;
     } 
     // removing a node with 2 kids 
     else {
       // find the sucessor which is the most left child of the right subtree
       Node* sucessor = currentNode -> right;
       // while we go to the left 
       while (sucessor -> left) {
            // keep going left 
            successor = sucessor -> left;
       }
       // copy the key 
       currentNode -> key = sucessor -> key;
       parent = currentNode;

       // reassign currentNode and the key so that the loop will continue 
       currentNode = currentNode -> right;
       key = successor -> key;
     }
  } 
  // search the right
  else if (currentNode -> key < key)
     parent = currentNode;
     currentNode = currentNode -> right;
     } else {
         // we search left 
         parent = currentNode;
         currentNode = currentNode -> left;
     }
  }
  return false;
  // if we never found it 
}


// inorder traversal
// visits all nodes from smallest to largest so sorted order 
void inorderTrv(Node* node) {
    if (node == nullptr) {
        return;
    }
    inorderTrv(node -> left);
    cout << node -> key << " ";
    inorderTrv(node -> right);
}
// later in the testing stage we call inorderTrv() even though it needs an argument, 
// so we need to make a wrapper function so we are able to call it later 
void inorderTrv() {
  inorderTrv(root);
}

// preorder traversal 
// visits a node, then that node's left subtree, then the right subtree
void preorderTrv(Node* node) {
    if(node == nullptr) {
       return;
    }
    cout << node -> key << " ";
    // left subtree and then right subtree
    preorderTrv(node -> left);
    preorderTrv(node -> right);
}
// same as in order, we need the wrapper function
void preorderTrv() {
  preorderTrv(root);
}

// postorder traversal
// visits the node's left subtree, then the right subtree, then the node itself
void postorderTrv(Node* node) {
    if (node == nullptr) {
       return;
    }
    postorderTrv(node -> left);
    postorderTrv(node -> right);
    // then the node itself
    cout << node -> key << " ";
}
// wrapper function 
void postorderTrv() {
  postorderTrv(root);
}

// height 
int height(Node* node) {
    // check for empty tree again
    if (node == nullptr) {
       return -1;
    }
    // calculate the height for the left subtree
    int leftHeight = height(node -> left);
    // calculate the height for the right subtree
    int rightHeight = height(node -> right);

    // see which subtree has a larger height, and then add one to that 
    // to account for the currentNode's level
    return 1 + std::max(leftHeight, rightHeight);
};
// wrapper function again 
int height() {
  return height(root);
}

};

// now testing!
int main() {
    BinarySearchTree bst;

    int values[] = {22, 99, 55, 48, 72, 69, 11, 5, 101, 33};
    // insert them all
    for (int val : values) {
        bst.insert(new Node(val));
    }

    // run each traversal and height 
    // we cant chain them because they return void 
    cout << "Initial Inorder Traversal: ";
    bst.inorderTrv() ;
    cout << "\n";
    
    cout << "Initial Preorder Traversal: " 
    bst.preorderTrv() 
    cout << "\n";
    
    cout << "Initial Postorder Traversal: "
    bst.postorderTrv() 
    cout << "\n";
    
    cout << "Initial height: " 
    bst.height() 
    cout << "\n";

    // search for one key that is in the list and one that is not there
    int realKey = 69;
    int fakeKey = 88;
    cout << "Searching for " << realKey << ": " 
        << (bst.search(realkey) != nullptr ? "Found it!" : "Didn't find it :(") << "\n";

    cout << "Searching for " << fakeKey << ": " 
        << (bst.search(fakeKey) != nullptr ? "Found it!" : "Didn't find it :(") << "\n";

    // 3 removal cases 
    // we need to show that inorderTrv is still sorted after removing 
    // so I printed them in the cout statements 
    // leaf
    bst.remove(5);
    cout << "After removing 5 (leaf node) our new tree is: " << bst.inorderTrv() << "\n";

    // 1 child
    bst.remove(72);
    cout << "After removing 72 (has one left child) our new tree is: " << bst.inorderTrv() << "\n";

    // 2 children
    bst.remove(99);
    cout << "After removing 99 (has 2 children) our new tree is: " << bst.inorderTrv() << "\n";


    return 0;
}







