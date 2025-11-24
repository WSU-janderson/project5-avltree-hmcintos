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
    ~AVLTree();
    bool insert(const std::string& key, size_t value);
    bool remove(std::string key);
    bool contains(std::string key);

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;
        AVLNode(const std::string& k, std::size_t v) : left(nullptr), right(nullptr), key(k), value(v) {
            height = 0;
        };
        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;
        size_t size() const;


    };

public:




    private:
    AVLNode* root{};
    size_t sz;
    vector<AVLNode*> keyIndex;

    bool recursiveInsert(AVLNode *&current, const std::string& key, size_t value);




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


