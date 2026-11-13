using namespace std;

// create a node type and a BinarySearchTree class
class BinarySearchTree {
public: 
    int key;
    BinarySearchTree* right;
    BinarySearchTree* left;

    BinarySearchTree(int nodeKey, BinarySearchTree* rightChild = nullptr, BinarySearchTree* leftChild = nullptr) {
      key = nodeKey;
      right = rightChild;
      left = leftChild;
    }
}

// insert
void insert(BinarySearchTree* newNode) {
// first check if our tree is empty because then we just insert into the root 
  if (root == nullptr) {
     root = newNode;
  } 
// else we still assign the new node to the root, but start looking at the rest of the tree
// if the new node is less than the root then we put it to the right, if its greater than the left
  else {
      BinarySearchTree* currentNode = root;
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
                 currentNode = currentNode -> left
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

// removal 
bool remove(int key) {
  BinarySearchTree* parent = nullptr;
  BinarySearchTree* currentNode = root;

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
                parent -> left = currentNode -> left
           } else {
                // it is a right child 
                parent -> right = currentNode -> left;
           }
           // successfully deleted
           delete currentNode;
           return true; 
          // removing a node that has a right child 
        } else if (currentNode -> left == nullptr && currentNode -> right)
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
       BinarySearchTree* sucessor = currentNode -> right;
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
     return false;
     // if we never found it 
}


               

// inorder traversal

// preorder traversal 

// postorder traversal

// height 
