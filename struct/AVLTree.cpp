#include "AVLTree.h"
#include "../utils/InputUtils.h"
#include <algorithm>
#include <cstring>

AVLTree::AVLTree() : root(NULL)
{
}

AVLTree::~AVLTree()
{
    clear();
}

int AVLTree::nodeHeight(AVLNode *node)
{
    return node == NULL ? 0 : node->height;
}

int AVLTree::balanceFactor(AVLNode *node)
{
    return node == NULL ? 0 : nodeHeight(node->left) - nodeHeight(node->right);
}

void AVLTree::updateHeight(AVLNode *node)
{
    if(node != NULL)
    {
        node->height = 1 + std::max(nodeHeight(node->left), nodeHeight(node->right));
    }
}

AVLNode* AVLTree::rotateRight(AVLNode *node)
{
    AVLNode *newRoot = node->left;
    AVLNode *middle = newRoot->right;

    newRoot->right = node;
    node->left = middle;

    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

AVLNode* AVLTree::rotateLeft(AVLNode *node)
{
    AVLNode *newRoot = node->right;
    AVLNode *middle = newRoot->left;

    newRoot->left = node;
    node->right = middle;

    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

AVLNode* AVLTree::rebalance(AVLNode *node)
{
    if(node == NULL)
    {
        return NULL;
    }

    updateHeight(node);
    const int balance = balanceFactor(node);

    if(balance > 1)
    {
        if(balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if(balance < -1)
    {
        if(balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

AVLNode* AVLTree::insertNode(AVLNode *node,
                             const char key[],
                             PatientNode *patient,
                             bool &inserted)
{
    if(node == NULL)
    {
        AVLNode *created = new AVLNode;
        InputUtils::copyToBuffer(created->key, key);
        created->patient = patient;
        created->height = 1;
        created->left = NULL;
        created->right = NULL;
        inserted = true;
        return created;
    }

    const int comparison = std::strcmp(key, node->key);
    if(comparison < 0)
    {
        node->left = insertNode(node->left, key, patient, inserted);
    }
    else if(comparison > 0)
    {
        node->right = insertNode(node->right, key, patient, inserted);
    }
    else
    {
        node->patient = patient;
        inserted = false;
        return node;
    }

    return rebalance(node);
}

AVLNode* AVLTree::minimumNode(AVLNode *node)
{
    AVLNode *current = node;
    while(current != NULL && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

AVLNode* AVLTree::removeNode(AVLNode *node, const char key[], bool &removed)
{
    if(node == NULL)
    {
        return NULL;
    }

    const int comparison = std::strcmp(key, node->key);
    if(comparison < 0)
    {
        node->left = removeNode(node->left, key, removed);
    }
    else if(comparison > 0)
    {
        node->right = removeNode(node->right, key, removed);
    }
    else
    {
        removed = true;
        if(node->left == NULL || node->right == NULL)
        {
            AVLNode *child = node->left != NULL ? node->left : node->right;
            delete node;
            return child;
        }

        AVLNode *successor = minimumNode(node->right);
        InputUtils::copyToBuffer(node->key, successor->key);
        node->patient = successor->patient;
        bool successorRemoved = false;
        node->right = removeNode(node->right, successor->key, successorRemoved);
    }

    return rebalance(node);
}

bool AVLTree::insert(const char key[], PatientNode *patient)
{
    if(key == NULL || patient == NULL || key[0] == '\0')
    {
        return false;
    }

    bool inserted = false;
    root = insertNode(root, key, patient, inserted);
    return inserted;
}

bool AVLTree::remove(const char key[])
{
    bool removed = false;
    root = removeNode(root, key, removed);
    return removed;
}

PatientNode* AVLTree::search(const char key[]) const
{
    AVLNode *current = root;
    while(current != NULL)
    {
        const int comparison = std::strcmp(key, current->key);
        if(comparison == 0)
        {
            return current->patient;
        }
        current = comparison < 0 ? current->left : current->right;
    }
    return NULL;
}

bool AVLTree::isEmpty() const
{
    return root == NULL;
}

void AVLTree::clearNode(AVLNode *node)
{
    if(node == NULL)
    {
        return;
    }
    clearNode(node->left);
    clearNode(node->right);
    delete node;
}

void AVLTree::clear()
{
    clearNode(root);
    root = NULL;
}
