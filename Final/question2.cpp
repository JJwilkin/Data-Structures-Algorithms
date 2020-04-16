#include <iostream>
#include <string>
#include <vector>

// PURPOSE: STL libraries to be included if needed
//#include <vector>
//#include <list>
//#include <stack>
//#include <queue>
using namespace std;

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

// PURPOSE: Models a generic binary tree node
class BinaryTreeNode {
    int val; // key value stored inside each node
    BinaryTreeNode* left; // pointer to the left child node
    BinaryTreeNode* right; // pointer to the right child node
public:
    // parametric constructor
    BinaryTreeNode(int new_val) : val(new_val), left(NULL), right(NULL) {} 
    // friend declarations
    friend class BinaryTree;
    friend class BinaryTreeTest;
};

// PURPOSE: Provides specified binary tree functionality
class BinaryTree{
    // PURPOSE: Private helper for conversion of integers to strings
    string int2ascii(int val) {
        if (val < 0) // handle negative values
            return '-' + int2ascii(-val);
        else if (val <= 9) // check for single digits
            return std::string(1, '0' + val);
        else // recursive case
            return int2ascii(val / 10) + char('0' + val % 10);
    }
    // Can also use to_string(val) if C++11 extensions are enabled
    // To enable C++11 extensions, add -std=c++11 under Tools->Compiler Options

public:
    // PURPOSE: Implementation for the required function
    void paths_with_odd_nodes(BinaryTreeNode* T, string buffer) {
        // TODO (PART A) Insert your code here
        vector <string> previous_paths;
        paths_with_odd_nodes_helper(T, buffer, previous_paths);
    }
    void paths_with_odd_nodes_helper(BinaryTreeNode* T, string buffer, vector <string> &previous_paths) {
        if (!T) return;

        string new_buffer;
        if (T ->val % 2!=0) {
            new_buffer = buffer + " " + int2ascii(T->val);
            
            // bool valid_output = true;
  	        // for(int i = 0; i < previous_paths.size(); i++) {
            // if (previous_paths[i].compare(new_buffer) == 0) {
            //     valid_output = false;
            //     }
            // }
            
            paths_with_odd_nodes(T->left, new_buffer);
            paths_with_odd_nodes(T->right, new_buffer);
            // if(valid_output) {
                // previous_paths.push_back(new_buffer);
                cout << new_buffer << endl;
            // }
            
        }
        else {
            // bool valid_output = true;
            // for(int i = 0; i < previous_paths.size(); i++) {
            // if (previous_paths[i].compare(buffer) == 0) {
            //     valid_output = false;
            //     }
            // }
            // if(valid_output) {
              cout << buffer << endl;
            // }
            
            paths_with_odd_nodes(T->left, "");
            paths_with_odd_nodes(T->right, "");
        }


    }
    // PURPOSE: Clean up of the created node values
    void clean_up(BinaryTreeNode* T) {
        if (T == NULL) return;
        clean_up(T->left);
        clean_up(T->right);
        delete T;
    }
};

// PURPOSE: Implements demonstrative test cases
class BinaryTreeTest {
public:
    void test_scenario1() {
        // step1. create a test tree
        BinaryTreeNode* root = new BinaryTreeNode(6);
        root->left = new BinaryTreeNode(1);
        root->right = new BinaryTreeNode(3);
        root->left->left = new BinaryTreeNode(2);
        root->left->left->left = new BinaryTreeNode(5);
        // TODO (PART A) Add more nodes here
        
        // step2. call the function
        cout << "Expected output: (1) (5) (3)" << endl;
        cout << "Actual output: " << endl;
        BinaryTree test_object;        
        test_object.paths_with_odd_nodes(root, "");
        
        // step3. clean up the node values
        test_object.clean_up(root);    
    }    
    
    void test_scenario2() {
        // TODO (PART A) Add another test case here
        // step1. create a test tree
        BinaryTreeNode* root = new BinaryTreeNode(3);
        root->left = new BinaryTreeNode(11);
        root->right = new BinaryTreeNode(8);
        root->left->right = new BinaryTreeNode(20);
        root->right->left = new BinaryTreeNode(5);
        // TODO (PART A) Add more nodes here
        
        // step2. call the function
        cout << "Expected output: (3 11) (5)" << endl;
        cout << "Actual output: " << endl;
        BinaryTree test_object;        
        test_object.paths_with_odd_nodes(root, "");
        
        // step3. clean up the node values
        test_object.clean_up(root);   
    }    

    void test_scenario3() {
        // TODO (PART A) Add another test case here
                // TODO (PART A) Add another test case here
        // step1. create a test tree
        BinaryTreeNode* root = new BinaryTreeNode(8);
        root->left = new BinaryTreeNode(7);
        root->right = new BinaryTreeNode(5);
        root->left->right = new BinaryTreeNode(3);
        root->right->left = new BinaryTreeNode(3);
        // TODO (PART A) Add more nodes here
        
        // step2. call the function
        cout << "Expected output: (7 5 3) (7 3)" << endl;
        cout << "Actual output: " << endl;
        BinaryTree test_object;        
        test_object.paths_with_odd_nodes(root, "");
        
        // step3. clean up the node values
        test_object.clean_up(root);   
    }    

    void run_tests() {
        // TODO (PART B) List at least six test cases / equivalence classes here
        test_scenario1();
        test_scenario2();    
        test_scenario3();
        // test 4:  all even numbers
        // Test 5: all all numbers odd
        // test 6 : emptry tree

        
        
        
        
        
    }
};

int main() {
    // invoke the test runner
    BinaryTreeTest test1;
    test1.run_tests();
}