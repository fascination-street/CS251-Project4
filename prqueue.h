#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using namespace std;

template <typename T>
class prqueue {
   private:
    struct NODE {
        int priority;
        T value;
        NODE* parent;
        NODE* left;
        NODE* right;
        NODE* link;  // Link to duplicates -- Part 2 only
    };

    NODE* root;
    size_t sz;

    // Utility pointers for begin and next.
    NODE* curr;
    NODE* temp;  // Optional

    //Recursive function to convert each node to a string format
    //Moves to the left-most node, saves right nodes for last. Understood order is node->left, node, node->right
    //Will go through links in order (link left and right ptrs are always null)
    void convertToString(ostringstream& as, NODE* n) const {
        if (n != nullptr) {
            convertToString(as, n->left);
            as << n->priority << " value: " << n->value << endl;
            convertToString(as, n->link);
            convertToString(as, n->right);
        }
    }

    //recursive algorithm to copy nodes. repurposing enqueue was too annoying
    //passes the nNode through as par(ent) so the pointer can be updated
    NODE* copyNode(NODE* current, NODE* par) const {
        //end recursion when we reach nullptr
        if (current == nullptr) {
            return nullptr;
        }

        //allocate new node and populate it
        NODE* nNode = new NODE;
        nNode->value = current->value;
        nNode->priority = current->priority;
        nNode->parent = par;

        //recursive calls to copy links, left, and right
        nNode->link = copyNode(current->link, nullptr);
        nNode->left = copyNode(current->left, nNode);
        nNode->right = copyNode(current->right, nNode);
        
        //returns the root node, along with the entire BST that is attached to it
        return nNode;
    }

    //recursive algorithm to determine equality of trees
    //first, it checks node memory addresses, if they're both null or if one isn't we can finish there
    //if both aren't null, then we check priority and value. if they differ we can stop there and return false
    //if those are the same, then we recursively call the function on their linked lists and left & right subtrees
    bool nodeEq(NODE* n1, NODE* n2) const {
        //this should only ever go true if they're both nullptr or they're the same node in memory
        //if they are both nullptr, return true
        if (n1 == n2) {
            return true;
        }
        // n1 XOR n2 return false
        else if ((n1 == nullptr && n2 != nullptr) ||
                 (n1 != nullptr && n2 == nullptr)) {
            return false;
        }
        //otherwise, check the values of each node
        else {
            //check if val and priorities are equal
            bool valEq = (n1->value == n2->value);
            bool priEq = (n1->priority == n2->priority);

            //if either are false, return false to prevent redundant recursive calls
            if (!priEq || !valEq) {
                return false;
            }

            //recursively check if each subtree is equal 
            bool linkEq = nodeEq(n1->link, n2->link);
            bool leftEq = nodeEq(n1->left, n2->left);
            bool rightEq = nodeEq(n1->right, n2->right);

            if (linkEq && leftEq && rightEq) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    

   public:
    /// Creates an empty `prqueue`.
    ///
    /// Runs in O(1).
    prqueue() {
        root = nullptr;
        sz = 0;
    }

    /// Copy constructor.
    ///
    /// Copies the value-priority pairs from the provided `prqueue`.
    /// The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N), where N is the number of values in `other`.
    prqueue(const prqueue& other) {
        this->root = copyNode(other.root, nullptr);
        this->sz = other.sz;
    }

    /// Assignment operator; `operator=`.
    ///
    /// Clears `this` tree, and copies the value-priority pairs from the
    /// provided `prqueue`. The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N + O), where N is the number of values in `this`, and O is
    /// the number of values in `other`.
    prqueue& operator=(const prqueue& other) {
        if (*this == other) {
            return *this;
        }

        this->clear();

        this->root = copyNode(other.root, nullptr);
        this->sz = other.sz;

        return *this;
    }

    /// Empties the `prqueue`, freeing all memory it controls.
    ///
    /// Runs in O(N), where N is the number of values.
    void clear() {
        //just dequeue the entire tree
        while (this->sz != 0) {
            this->dequeue();
        }
    }

    /// Destructor, cleans up all memory associated with `prqueue`.
    ///
    /// Runs in O(N), where N is the number of values.
    ~prqueue() {
        //just dequeue the entire tree
        while (this->sz != 0) {
            this->dequeue();
        }
    }

    /// Adds `value` to the `prqueue` with the given `priority`.
    ///
    /// Uses the priority to determine the location in the underlying tree.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    void enqueue(T value, int priority) {
        //establish new node
        NODE* enq = new NODE;
        enq->value = value;
        enq->priority = priority;
        enq->right = nullptr;
        enq->left = nullptr;
        enq->parent = nullptr;
        enq->link = nullptr;
        
        //the root is empty then make it the root
        if (root == nullptr) {
            root = enq;
        }
        //otherwise go through the tree to place the new node
        else {
            NODE* current = root;
            while (current != nullptr) {
                //if it's lower than the current node
                if (enq->priority < current->priority) {
                    //place it in the tree if the left node is empty
                    if (current->left == nullptr) {
                        current->left = enq;
                        enq->parent = current;
                        current = nullptr;
                    }
                    //otherwise continue through the tree
                    else {
                        current = current->left;
                    }
                }
                //if it's greater than the node
                else if (enq->priority > current->priority) {
                    //if the right node is empty, place it in the tree
                    if (current->right == nullptr) {
                        current->right = enq;
                        enq->parent = current;
                        current = nullptr;
                    }
                    //otherwise continue through the tree
                    else {
                        current = current->right;
                    }
                }
                //it's equal to the current priority
                else {
                    //iterate through the linked list until last node
                    NODE* head = current; //save current node address

                    while (current->link != nullptr) {
                        current = current->link;
                        
                    }
                    //add node to list
                    current->link = enq;
                    enq->parent = head; //extremely helpful for next
                    break;
                }
            }
            
        }
        //increase the size of the tree
        ++sz;
    }

    /// Returns the value with the smallest priority in the `prqueue`, but does
    /// not modify the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T peek() const {
        //return default if the tree is empty
        if (root == nullptr) {
            return T{};
        }

        NODE* curr = root;
        
        //go through the tree to reach the lowest value
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        //return its value
        return curr->value;
    }

    /// Returns the value with the smallest priority in the `prqueue` and
    /// removes it from the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T dequeue() {
        //return default if it's empty
        if (root == nullptr) {
            return T{};
        }

        NODE* current = root;

        //go through the tree to reach the lowest value
        while (current->left != nullptr) {
            current = current->left;
        }

        T val = current->value;

        --sz;
        
        //if the lowest value has a link
        if (current->link != nullptr) {
                current->link->right = current->right;
                current->link->left = current->left;
                
                if (current == root) {
                    root = current->link;
                    root->parent = nullptr;
                }
                else {
                    current->link->parent = current->parent;
                    current->parent->left = current->link;
                }

                if (current->right != nullptr) {
                    current->right->parent = current->link;
                }

                delete current;
                return val;
            }
        //if the lowest value is the root
        if (current == root) {
            //deal with link, if it exists
            //deal with changing the root node around if there's anything to its right
            if (current->right != nullptr) {
                root = root->right;
                root->parent = nullptr;
                delete current;
                return val;
            }
            
            //otherwise clear the tree, if it's here then the root node is the only one in the tree
            root = nullptr;
            delete current;
            return val;
        }

        //if we're not at the root and there's something to current's right
        //then adjust the pointers (right's parent points to curr's parent, curr's parent's left points to right)
        if (current->right != nullptr) {
            current->right->parent = current->parent;
            current->parent->left = current->right;
            delete current;
            return val;
        }
        //otherwise if the node is a leaf, just make the parent's left point to nullptr
        else {
            current->parent->left = nullptr;
            delete current;
            return val;
        }
    }

    /// Returns the number of elements in the `prqueue`.
    ///
    /// Runs in O(1).
    size_t size() const {
        return sz;
    }

    /// Resets internal state for an iterative inorder traversal.
    ///
    /// See `next` for usage details.
    ///
    /// O(H), where H is the maximum height of the tree.
    void begin() {
        //ensuring curr isn't some crap value
        curr = root;

        //make sure no nullptr silliness occurs
        if (root == nullptr) {
            return;
        }

        //move to the lowest possible value 
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        temp = curr;
    }

    /// Uses the internal state to return the next in-order value and priority
    /// by reference, and advances the internal state. Returns true if the
    /// reference parameters were set, and false otherwise.
    ///
    /// Example usage:
    ///
    /// ```c++
    /// pq.begin();
    /// T value;
    /// int priority;
    /// while (pq.next(value, priority)) {
    ///   cout << priority << " value: " << value << endl;
    /// }
    /// ```
    ///
    /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
    /// H is the height of the tree, and M is the number of duplicate
    /// priorities.
    bool next(T& value, int& priority) {
        
        if (root == nullptr) {
            return false;
        }

        //if we're at the end of the queue
        if (curr == nullptr || (curr == root && curr->priority < priority && value != T{})) {
            //if we're at the beginning and root just so happens to be the lowest priority in the tree...
            //catch it here so we can continue. otherwise return false
            if (curr == root && root->right == nullptr) {}
            else {return false;}
        }

        value = curr->value;
        priority = curr->priority;

    /*  MY SUPER COOL BST w/ DUPES IN-ORDER TRAVERSAL ALGORITHM PSEUDOCODE!!!
        //if curr is a link
            //if curr has a link
                //go to next link
            //else
                //return to head, then proceed with moving
        //if curr is root
            //go right, then as left as possible
        //if curr is a left node with NO right nodes
            //go to parent
        //if curr has a right node
            //go right
            //if curr has a left node
                //go as left as possible
        //if curr is a right node
            //go up parents until curr is a left node, then go up once more
        //if you're here, it means you're at the last node
            //curr = nullptr, return true
                                                                                */

        //Giving the root node the special case it INSISTS it must have.
        if (curr == root) { 
            if (curr->link != nullptr) {
                curr = curr->link;
                return true;
            }
        } 
        //prioritize head->link above all else (except the root node -_-)
        //link node parents always point to list head; if curr->par->priority == curr->priority, then curr is a link
        else if (curr->parent->priority != curr->priority) {
            //nested to prevent normal nodes from entering the else statement
            if (curr->link != nullptr) {
                curr = curr->link;
                return true;
            }
        }
        //if curr is a link:
        else { 
            //if there's more to the list, continue down the list
            if (curr->link != nullptr) {
                curr = curr->link;
                return true;
            }
            //otherwise, go back to parent then proceed with moving
            else {
                curr = curr->parent;
            }
        }  

        if (curr == root) {
            //if curr->right exists, then go to it
            if (curr->right != nullptr) {
                curr = curr->right;
            }
            //otherwise return true
            else {return true;}
            
            //then go as left as possible
            while (curr->left != nullptr) {
                curr = curr->left;
            }
            temp = curr;
            return true;
        }
        //if curr is a left node with NO right node
        else if (curr == curr->parent->left && curr->right == nullptr) {
            //go to the parent node
            curr = curr->parent;
            temp = curr;
            return true;
        }
        //if curr has a right node
        else if (curr->right != nullptr) {
            //go right,
            curr = curr->right;
            //then go as left as you possibly can
            while (curr->left != nullptr) {
                curr = curr->left;
            }

            temp = curr;
            return true;
        }
        //if curr is a right node
        else if (curr == curr->parent->right) {
            //then go up parent nodes until the parent is the root node OR curr is a left node
            while (curr != curr->parent->left && curr->parent != root) {
                curr = curr->parent;
            }
            //then go up one more time
            curr = curr->parent;
            temp = curr;
            return true;
        }
        //if you're here, then it means you're at the last node of the tree
        curr = nullptr;
        return true;
        
    }

    /// Converts the `prqueue` to a string representation, with the values
    /// in-order by priority.
    ///
    /// Example:
    ///
    /// ```c++
    /// prqueue<string> names;
    /// names.enqueue("Gwen", 3);
    /// names.enqueue("Jen", 2);
    /// names.enqueue("Ben", 1);
    /// names.enqueue("Sven", 2);
    /// ```
    ///
    /// Calling `names.as_string()` would return the following multi-line
    /// string:
    ///
    /// ```text
    /// 1 value: Ben
    /// 2 value: Jen
    /// 2 value: Sven
    /// 3 value: Gwen
    /// ```
    ///
    /// Runs in O(N), where N is the number of values.
    string as_string() const {
        ostringstream as;
        NODE* current = root;

        convertToString(as, current);

        return as.str();
    }

    /// Checks if the contents of `this` and `other` are equivalent.
    ///
    /// Two `prqueues` are equivalent if they have the same priorities and
    /// values, as well as the same internal tree structure.
    ///
    /// These two `prqueue`s would be considered equivalent, because
    /// they have the same internal tree structure:
    ///
    /// ```c++
    /// prqueue<string> a;
    /// a.enqueue("2", 2);
    /// a.enqueue("1", 1);
    /// a.enqueue("3", 3);
    /// ```
    ///
    /// and
    ///
    /// ```c++
    /// prqueue<string> b;
    /// a.enqueue("2", 2);
    /// a.enqueue("3", 3);
    /// a.enqueue("1", 1);
    /// ```
    ///
    /// While this `prqueue`, despite containing the same priority-value pairs,
    /// would not be considered equivalent, because the internal tree structure
    /// is different.
    ///
    /// ```c++
    /// prqueue<string> c;
    /// a.enqueue("1", 1);
    /// a.enqueue("2", 2);
    /// a.enqueue("3", 3);
    /// ```
    ///
    /// Runs in O(N) time, where N is the maximum number of nodes in
    /// either `prqueue`.
    ///
    bool operator==(const prqueue& other) const {
        return nodeEq(this->root, other.root);
    }

    /// Returns a pointer to the root node of the BST.
    ///
    /// Used for testing the internal structure of the BST. Do not edit or
    /// change.
    ///
    /// Runs in O(1).
    void* getRoot() {
        return root;
    }
};
