#ifndef AVLTREE_H
#define AVLTREE_H

#include "PatientLinkedList.h"

struct AVLNode
{
    char key[15];
    PatientNode *patient;
    int height;
    AVLNode *left;
    AVLNode *right;
};

class AVLTree
{
private:
    AVLNode *root;

    static int nodeHeight(AVLNode *node);
    static int balanceFactor(AVLNode *node);
    static void updateHeight(AVLNode *node);
    static AVLNode* rotateLeft(AVLNode *node);
    static AVLNode* rotateRight(AVLNode *node);
    static AVLNode* rebalance(AVLNode *node);
    static AVLNode* minimumNode(AVLNode *node);
    static void clearNode(AVLNode *node);

    AVLNode* insertNode(AVLNode *node,
                        const char key[],
                        PatientNode *patient,
                        bool &inserted);
    AVLNode* removeNode(AVLNode *node, const char key[], bool &removed);

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

public:
    AVLTree();
    ~AVLTree();

    bool insert(const char key[], PatientNode *patient);
    bool remove(const char key[]);
    PatientNode* search(const char key[]) const;
    bool isEmpty() const;
    void clear();
};

#endif
