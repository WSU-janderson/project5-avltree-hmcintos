/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;
    AVLTree();
protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;
        AVLNode(KeyType k, ValueType v) : left(nullptr), right(nullptr), key(k), value(v) {
            height = 0;
        };
        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;


    };

public:




    private:
    AVLNode* root{};
    size_t sz;
    vector<AVLNode*> keyIndex;

    size_t size() const {
        return sz;
    }



    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);
    friend std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree);

};

#endif //AVLTREE_H


