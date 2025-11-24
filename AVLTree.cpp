#include "AVLTree.h"

#include <string>

/**
 * Empty Constructor. constructs an AVL tree with no parameters. Sets root to null.
 */
AVLTree::AVLTree() {
    root = nullptr;
    sz = 0;
    keyIndex = {};
};

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

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}

