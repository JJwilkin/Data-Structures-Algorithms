#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;
//=============================== CONSTRUCTOR ==============================
// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
    size = 0;
}

// ============================== DECONSTRUCTOR ================================
// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
    DestroyTree(root); //helper function which actually deletes nodes recursively
}

void BinarySearchTree::DestroyTree( BinarySearchTree::TaskItem* n ) const {
    if (n) {
        DestroyTree(n -> left);
        DestroyTree(n -> right);
        delete n;
    }
}
//======================SIZE===============================
// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return recursive_get_size(root);
}

int BinarySearchTree::recursive_get_size (TaskItem * n ) const {
    if (n == NULL) {
        return 0;
    }
    else {
        return (recursive_get_size(n ->left) + 1 + recursive_get_size(n -> right));
    }
}
//==========================MAX VALUE=================================
// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
    if (size == 0) return BinarySearchTree::TaskItem(-1, "N/A");
    TaskItem * temp = root;
    while (temp -> right) { //navigate to the right most element
        temp = temp -> right;
    }
    return BinarySearchTree::TaskItem(temp->priority, temp->description);
}

//==========================MIN VALUE=======================================
// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
    if (size == 0) return BinarySearchTree::TaskItem(-1, "N/A");
    TaskItem * temp = root;
    while (temp -> left) { //navigate to the left most element
        temp = temp -> left;
    }
    return BinarySearchTree::TaskItem(temp->priority, temp->description);
}

BinarySearchTree::TaskItem * BinarySearchTree::find_minimum(BinarySearchTree::TaskItem *n) const {
    if (size == 0) return NULL;
    TaskItem * temp = n;
    while (temp -> left) {
        temp = temp -> left;
    }
    return temp;
}

//=========================TREE HEIGHT ======================================
// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	return max_height(root);
}

int BinarySearchTree::max_height(BinarySearchTree::TaskItem *n) const {
    if (n == NULL) return 0;
    else {
        int left_depth = max_height(n -> left);
        int right_depth = max_height(n -> right);

        if (left_depth > right_depth) return (left_depth + 1);
        else return (right_depth + 1);
    }
}

//========================== PRINT ======================================
// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
    cout << "PRINTING TREE w/ InOrder Traversal" <<endl;
    traverse(root);
}

void BinarySearchTree::traverse(BinarySearchTree::TaskItem *n) const {
    if (n) {
        traverse(n -> left);
        cout << "PRIORITY: " << n ->priority << ", DESCRIPTION: " << n->description << endl;
        traverse(n -> right);

    }
}

//=================================SEARCH FOR VALUE =======================================
// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
    if (find_val(val)) return true;
	return false;
}

BinarySearchTree::TaskItem * BinarySearchTree::find_val(BinarySearchTree::TaskItem val) const {
    TaskItem * temp = root;
    while (temp) { //run until reach end of loop
        if(val.priority < temp->priority) { //if priority is less than current node, go down left tree
            temp = temp ->left;
        }
        else if (val.priority > temp -> priority) {
            temp = temp -> right;
        }
        else if (val == *temp) { //if priority is same, check if there is a match
            return temp;
        }
        else { //if priority is same, and description don't match, there are no matches, return false
            return NULL;
        }
    }
    return NULL;
}

BinarySearchTree::TaskItem * BinarySearchTree::find_parent(BinarySearchTree::TaskItem val) const {
    TaskItem * temp = root;
    if (val == *temp) return NULL; //special case, return root node if val is root
    while (temp) { //run until reach end of loop
        if ((temp->left && *temp -> left == val) || (temp->right && *temp->right == val)) { //if parent of desired value
            return temp;
        }
        if(val.priority < temp->priority) { //if priority is less than current node, go down left tree
            temp = temp ->left;
        }
        else if (val.priority > temp -> priority) {
            temp = temp -> right;
        }

        else { //if val is not in tree
            return NULL;
        }
    }
    return NULL;
}


//================================= OPTIONAL HELPER FUNCTIONS =========================
// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}


// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
return 0;
}


//================================ INSERT ===============================================
// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    if(size == 0) root = new TaskItem (val.priority, val.description);
    else {
        TaskItem * temp = root;
        while (temp) {
            if (val.priority < temp->priority) {
                if (!temp -> left) { //if there is no left child, set val as left child
                    temp -> left = new TaskItem (val.priority, val.description);
                    size++;
                    return true;
                }
                else { //if left child exist, set temp to left child and proceed to compare
                    temp = temp -> left;
                }
            }
            else if (val.priority > temp -> priority){
                if (!temp -> right) { //if there is no right child, set val as right child
                    temp->right = new TaskItem (val.priority, val.description);
                    size++;
                    return true;
                }
                else { //if right child exist, set temp to right child and proceed to compare
                    temp = temp -> right;
                }
            }
            else { //reject duplicate priority
                return false;
            }
        }
    }
    size++;
    return true;
}

//====================================== REMOVE ===============================================
// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
    if (size == 0) return false;
    TaskItem * target = find_val(val);
    if(target == NULL) return false;
    TaskItem * parent = find_parent(val);
    TaskItem * temp ;
    //If val is leaf node
    //======================LEAF NODE=========================
    if (target -> left == NULL && target ->right == NULL) {
        //Check if target is left/right child of parent, then set to null
        if(parent) { //if only one node in the tree parent = NULL
            if (parent -> left == target) parent -> left = nullptr;
            else parent -> right = nullptr;
        }
        else { //if root
            root = nullptr;
        }

        size--;
        delete target;
        return true;
    }
    //=======================ONE CHILD======================
    // If node to be deleted has only one child
    if (target -> left == NULL) { //if target has right child
        //if target is left child of parent, set new left child as target's child
        if (parent) {
            if (parent -> left == target) parent -> left = target -> right;
            else parent -> right = parent ->right = target -> right;
        }
        else {//if root node
            root = target -> right;
        }
    }

    else if (target -> right == NULL){
        if(parent) {
            if (parent -> left == target) parent -> left = target -> left;
            else parent -> right = parent ->right = target -> left;
        }
        else { //if root node
            root = target -> left;
        }
    }
    //========================TWO CHILDREN=======================
    else { //If node to be delete has TWO CHILDREN
        TaskItem * minimum = find_minimum(target->right);
        TaskItem * minimum_parent = find_parent(*minimum);

        if (parent) { //if not root node
            if (parent->left == target) parent->left = minimum;
            else parent->right = minimum;

            if((minimum == target -> right)) {
                 minimum ->left = target ->left;

            }
            else {
                if (minimum -> right) minimum_parent ->left = minimum ->right;
                else minimum_parent -> left = nullptr;

                minimum ->left = target -> left;
                minimum -> right = target -> right;
            }

        }
        else { //if root
            if(minimum == target ->right) {
                minimum ->left = root -> left;
                root = minimum;
            }
            else {
                if (minimum -> right) minimum_parent ->left = minimum ->right;
                else minimum_parent -> left = nullptr;

                minimum ->left = root -> left;
                minimum -> right = root -> right;
                root = minimum;

            }
        }






    }



    size--;
    delete target;
    return true;
}
