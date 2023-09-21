// Program: Priority Queue
// System: Vs Code on windows 10 dell
// Author: Taria Reese

/// @file priorityqueue.h

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)
    
/*************Private Helper Functions*************/

/*******************************************/
/* Function that recursively traverses tree
/* in order including duplicates           */
/*******************************************/
    void _recursiveInOrder(NODE* node, ostream& output) {
        if (node == nullptr) {
            return;
        }
        _recursiveInOrder(node->left, output);
        // output needs to be in the form of:
        // 1 value: Ben\n

        if (node->dup) {
            NODE *temp = node;
            while (temp != nullptr) {
                output << temp->priority << " value: " << temp->value << endl;
                temp = temp->link;
            }
        } else {
            output << node->priority << " value: " << node->value << endl;
        }

        _recursiveInOrder(node->right, output);

    }

/*******************************************/
/* Recursive helper function for clear()
/*******************************************/
    void _recursiveClear(NODE* node) {
        if (node == nullptr) {
            return;
        }
        _recursiveClear(node->left);
        if (node->dup) {
            NODE *temp = node->link;
            while (temp != nullptr) {
                NODE *temp2 = temp;
                temp = temp->link;
                delete temp2;
            }
        }
        _recursiveClear(node->right);
        delete node;
    }

/*******************************************/
/* Function that recursively copies tree
/* helper function for operator=           */
/*******************************************/
    void _recursiveCopy(NODE* node) {
        if (node == nullptr) {
            return;
        }
        if (node->dup) {
            NODE *temp = node;
            while (temp != nullptr) {
                enqueue(temp->value, temp->priority);
                temp = temp->link;
            }
        } else {
            enqueue(node->value, node->priority);
        }
        _recursiveCopy(node->left);
        _recursiveCopy(node->right);
    }

/*******************************************/
/* Recursive helper function for operator==
/*******************************************/
    bool _recursiveEqual(NODE* node1, NODE* node2) const {
        if (node1 == nullptr && node2 == nullptr) {
            return true;
        }
        if (node1 == nullptr || node2 == nullptr) {
            return false;
        }
        if (node1->priority != node2->priority) {
            return false;
        }
        if (node1->value != node2->value) {
            return false;
        }

        if (node1->dup && node2->dup) {
            NODE *temp1 = node1->link;
            NODE *temp2 = node2->link;
            while (temp1 != nullptr && temp2 != nullptr) {
                if (temp1->priority != temp2->priority) {
                    return false;
                }
                if (temp1->value != temp2->value) {
                    return false;
                }
                temp1 = temp1->link;
                temp2 = temp2->link;
            }
            if (temp1 != nullptr || temp2 != nullptr) {
                return false;
            }
        } else if (node1->dup || node2->dup) {
            return false;
        }

        return _recursiveEqual(node1->left, node2->left) && _recursiveEqual(node1->right, node2->right);
    }

/*******************************************/
/* Helper Function that recursively returns
/* the minimum element         */
/*******************************************/
    NODE * _recursiveMinElement(NODE *node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->left == nullptr) {
            return node;
        }
        return _recursiveMinElement(node->left);
    }
/**********************************************************/

public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = nullptr;
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        
        if (this != &other) {
            clear();
            root = nullptr;
            curr = nullptr;
            size = 0;
            _recursiveCopy(other.root);
            return *this;
        }
        return *this;
        
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        _recursiveClear(root);
        root = nullptr;
        size = 0;
        curr = nullptr;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        _recursiveClear(root);
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        curr = nullptr;
        NODE *newNode = new NODE{priority, value, false, nullptr, nullptr, nullptr, nullptr};

        if (root == nullptr) {
            root = newNode;
            size++;
            return;
        }

        NODE *currtemp = root;

        while (currtemp != nullptr) {
            if (priority < currtemp->priority) {
                if (currtemp->left == nullptr) {
                    currtemp->left = newNode;
                    newNode->parent = currtemp;
                    size++;
                    return;
                }
                currtemp = currtemp->left;
            } else if (priority > currtemp->priority) {
                if (currtemp->right == nullptr) {
                    currtemp->right = newNode;
                    newNode->parent = currtemp;
                    size++;
                    return;
                }
                currtemp = currtemp->right;
            } else {
                // dupe priority
                currtemp->dup = true;
                NODE *temp = currtemp;
                while (temp->link != nullptr) {
                    temp = temp->link;
                }

                temp->link = newNode;
                newNode->parent = temp;
                size++;
                return;
            }
        }

        return;

    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T dequeue() {

        curr = nullptr;

        // if only root exists
        if (size == 1) {
            T value = root->value;
            delete root;
            root = nullptr;
            size--;
            return value;
        }

        NODE *currtemp = root;

        while (currtemp->left != nullptr) {
            currtemp = currtemp->left;
        }

        T value = currtemp->value;

        // if smallest node is on root
        if (currtemp == root) {
            // if root has dupes
            if (currtemp->dup) {
                root = currtemp->link;
                root->parent = nullptr;
                if (root->link != nullptr){
                    root->dup = true;
                }
                if (currtemp->right != nullptr) {
                    currtemp->right->parent = root;
                    root->right = currtemp->right;
                }
                delete currtemp;
                size--;
                return value;
            } else {
                if (currtemp->right == nullptr) {
                    delete currtemp;
                    root = nullptr;
                    size--;
                    return value;
                } else {
                    root = currtemp->right;
                    root->parent = nullptr;
                    delete currtemp;
                    size--;
                    return value;
                }
            }
        }

        if (currtemp->dup) {
            currtemp->parent->left = currtemp->link;
            currtemp->link->parent = currtemp->parent;
            if (currtemp->link->link != nullptr) {
                currtemp->link->dup = true;
            }
            if (currtemp->right != nullptr) {
                currtemp->right->parent = currtemp->link;
                currtemp->link->right = currtemp->right;
            }
            delete currtemp;
            size--;
            return value;
        } else {
            if (currtemp->right == nullptr) {
                currtemp->parent->left = nullptr;
                delete currtemp;
                size--;
                return value;
            } else {
                currtemp->parent->left = currtemp->right;
                currtemp->right->parent = currtemp->parent;
                delete currtemp;
                size--;
                return value;
            }
        }

    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;        
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {     
        curr = _recursiveMinElement(root);
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
        if (curr == nullptr) {
            return false;
        }

        value = curr->value;
        priority = curr->priority;
        // if dupe, go in
        if (curr->link != nullptr) {
            curr = curr->link;
            return curr;
        }
        // if at the end of dupe list, go up
        while (curr->parent != nullptr && curr->parent->link == curr) {
            curr = curr->parent;
        }

        // if right exists, go right
        if (curr->right != nullptr) {
            curr = _recursiveMinElement(curr->right);
            return curr;
        }

        // if right doesn't exist, go up
        NODE* tempParent = curr->parent;
        while (tempParent != nullptr && tempParent->right == curr) {
            curr = tempParent;
            tempParent = tempParent->parent;
        }
        curr = tempParent;
        return curr;
        
    }
    


    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        
        stringstream ss;
        string str;

        _recursiveInOrder(root, ss);

        str = ss.str();
        
        return str; // TO DO: update this return
        
        
    }


    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
        return _recursiveMinElement(root)->value;
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        return _recursiveEqual(root, other.root);
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
