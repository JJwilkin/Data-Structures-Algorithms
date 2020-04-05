#include <iostream>

using namespace std;

// binary tree node 
struct BinaryTreeNode 
{ 
    int value; 
    BinaryTreeNode *left,*right; 
    BinaryTreeNode(int x) 
    { 
        value = x; 
        left = right = NULL; 
    } 
}; 

void find_and_print_sum_of_nodes (BinaryTreeNode * T, int desired_sum, int cur_sum, string buffer) {

}

int find_max_sum_of_nodes (BinaryTreeNode * T, int & temp_max_sum) {
    
}

int main () {
    cout << "test";
}