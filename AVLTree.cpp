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
}

bool AVLTree::contains(std::string key) {
    if (recursiveContains(root,key)) {
        return true;
    } else {
        return false;
    }
};

bool AVLTree::recursiveContains(AVLNode*& current, std::string key) {
    // base case if no AVL tree
    if (current == nullptr) {
        return false;
    }
    // if youve found the key end the recursion
    if (current->key == key) {
        return true;
    }
    // set current to the left most node
    //if its not null and contains the key then return true
    if (recursiveContains(current -> left,key)) {
        return true;
    }
    // else set current to the right node and check again
    if (recursiveContains(current ->right,key)) {
        return true;
    }
    // if none of this is true return false. (Should be redundant but I wanted to be doubly sure I had an exit
    return false;

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
size_t AVLTree::AVLNode::getHeight() const {
    return AVLNode::height;
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

bool AVLTree::recursiveInsert(AVLNode*& current, const std::string &key, size_t value) {
    AVLNode* newNode = new AVLNode(key, value);
    if (current == nullptr) {

        current = newNode;
        keyIndex.push_back(current);
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

