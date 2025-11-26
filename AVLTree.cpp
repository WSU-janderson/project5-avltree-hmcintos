#include "AVLTree.h"

#include <string>

/**
 * Empty Constructor. constructs an AVL tree with no parameters. Sets root to null.
 */
AVLTree::AVLTree() {
    root = nullptr;
    sz = 0;
    keyIndex = {};
}

AVLTree::~AVLTree() {
    if (root != nullptr) {
    }
}

/**
 * Recursively inserts a key value pair into the AVL tree
 * @param key A string value that represents the key or index of our map
 * @param value a size_t value which is stored in connction to our key
 * @return returns true if it was inserted false if there is a duplicate
 */
bool AVLTree::insert(const std::string &key, size_t value) {

    if (recursiveInsert(root,key,value)) {
        //assess balance
        //rotate if necesasry
        //double rotate if necessary
        return true;
    } else {
        return false;
    };

}

bool AVLTree::remove(std::string key) {
    return false;
}

/**
 * Runs a recursive check to find a key within the AVL tree
 * @param key The String key that we are looking for within the AVL tree
 * @return true if it exists false if it doesnt
 */
bool AVLTree::contains(const std::string key) const{
    if (recursiveContains(root,key)) {
        return true;
    } else {
        return false;
    }
}

std::optional<size_t> AVLTree::get( const std::string key) const {
    if (contains(key)) {

    }
    return recursiveGet(root,key);

};


/**
 * Recursively Checks to see if an AVL tree contains a key
 * @param current The current node in the tree we are looking at
 * @param key The key we are searching for
 * @return true if the key exists within the tree. False if the key does not
 *
 */
bool AVLTree::recursiveContains(AVLNode* current, std::string key) const {
    // base case if no AVL tree
    if (current == nullptr) {
        return false;
    }

    if (key > current->key) { //check right
        current = current -> left;
        return recursiveContains(current, key);
    } else if (key < current->key) { //check left
        current = current -> right;
        return recursiveContains(current, key);
    } else if (key == current ->key) { // else the key is found
        return true;
    } else {
        return false;
    };
    // if none of this is true return false. (Should be redundant but I wanted to be doubly sure I had an exit


}

/**
 * Recursively Checks for a key value within the tree. If it fings id we return the value associated with that key
 * @param current a pointer to the current node we are in the tree
 * @param key the string key value we are looking for
 * @return the size_t value that is associated with our key or Nullopt if it failed to find
 *
 */
std::optional<size_t> AVLTree::recursiveGet(const AVLTree::AVLNode *current, std::string key) const{

    std::optional<size_t> returnedValue = 0;
    if (current == nullptr) {
        returnedValue = nullopt;
        return returnedValue;
    }
    //Hunt down the Value by leveraging the BST aspect of an AVL tree
    if (key > current->key) { //check right
        current = current -> left;
        return recursiveGet(current, key);
    } else if (key < current->key) { //check left
        current = current -> right;
        return recursiveGet(current, key);
    } else if (key == current ->key) { // else the key is found
        returnedValue = current->value;
        return returnedValue;
    } else {
        return nullopt;
    };
}


size_t AVLTree::AVLNode::getHeight() const {
    if (isLeaf()) {
        return 0;
    }else {
        return 1 + std::max(AVLNode::getHeight(),AVLNode::getHeight() + 1);
    }
}

/**
 *
 * @return returns a value based off the number of children a node has. Max of 2
 */
size_t AVLTree::AVLNode::numChildren() const {
    if (left == nullptr && right == nullptr) {
        return 0;
    } else if (left != nullptr && right != nullptr) {
        return 2;
    } else {
        return 1;
    }
}

/**
 * CHecks to see if a node is a leaf(Has no children)
 * @return true if node has no children and False if it does.
 */
bool AVLTree::AVLNode::isLeaf() const {
    if (left == nullptr && right == nullptr) {
        return true;
    } else {
        return false;
    }
}

/**
 * Returns the height of the current Node
 * @return parameter Height from the Node class.
 */
size_t AVLTree::getHeight() const {
    if (root == nullptr) {
        return 0;
    } else {
        return root -> height;
    }
}

size_t AVLTree::size() const {
    return sz;
}

bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

/**
 * Inserts a key value pair into the tree using recursion to find where it needs to fit.
 * @param current
 * @param key
 * @param value
 * @return
 */
bool AVLTree::recursiveInsert(AVLNode*& current, const std::string &key, size_t value) {
    AVLNode* newNode = new AVLNode(key, value);
    if (current == nullptr) {

        current = newNode;
        keyIndex.push_back(current);
        sz++;
        return true;
    } else if (key < current->key) {
        current -> height = current->height + 1;
        current = current->left;
        recursiveInsert(current, key, value);

    } else if (key > current->key) {
        current -> height = current -> height + 1;
        current = current->right;
        recursiveInsert(current, key, value);
    } else {
        return false;
    }
    return true;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}

