#include <iostream>
#include<string>
#include <vector>
using namespace std;

// binary tree node
struct BinaryTreeNode {
    int value;
    BinaryTreeNode *left, *right;
    BinaryTreeNode(int x) {
        value = x;
        left = right = NULL;
    }
};

void find_and_print_sum_of_nodes_helper(BinaryTreeNode* T, int desired_sum, int cur_sum, string buffer, vector <string> &previous_output) {
    // exit if T is NULL
    if (!T) return;
		
    // update the ongoing sum with the current value for T
    int new_sum = cur_sum + T->value;

    // update the current path string
    string new_buffer = buffer + " " + to_string(T->value);
    // if the desired sum is found, print the corresponding path
  
  	bool valid_output = true;
  	for(int i = 0; i < previous_output.size(); i++) {
      if (previous_output[i].compare(new_buffer) == 0) {
        valid_output = false;
      }
    }
  
    if (new_sum == desired_sum && valid_output) {
        previous_output.push_back(new_buffer);
        cout << new_buffer << endl;
    }
        
    // TODO: continue down the left subtree
    find_and_print_sum_of_nodes_helper( T ->left, desired_sum, new_sum, new_buffer, previous_output);
      
    // TODO: continue down the right subtree
    find_and_print_sum_of_nodes_helper( T ->right, desired_sum, new_sum, new_buffer, previous_output);

    // TODO: restart from the left sub tree if buffer = “”
    find_and_print_sum_of_nodes_helper( T ->left, desired_sum, 0, "", previous_output);

    // TODO: restart from the right sub tree if buffer = “”
    find_and_print_sum_of_nodes_helper( T ->right, desired_sum, 0,"", previous_output);
}

void find_and_print_sum_of_nodes(BinaryTreeNode* T, int desired_sum, int cur_sum, string buffer) {
  	vector <string> previous_output;
    find_and_print_sum_of_nodes_helper(T, desired_sum, cur_sum, buffer, previous_output);
}

// PART 2
int find_max_sum_of_nodes (BinaryTreeNode* T, int &temp_max_sum) {
    // exit if T is NULL
    if (!T) return 0;
    // cout << "Val " << T ->value << "  ";
    
    // derive the maximum sum for the left subtree
    int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);  
    
    // derive the maximum sum for the right subtree
    int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);  

    // TODO: compare T->value, left_sum + T->value, and right_sum + T->value; store as max1
    int max1;
    if (T->value >= left_sum + T->value && T->value >= right_sum + T->value) max1 = T->value;
    else if (left_sum + T->value >= T->value && left_sum + T->value >= right_sum + T->value) max1 = left_sum + T->value;
    else max1 = right_sum + T->value;
    // TODO: compare max1, left_sum + right_sum + T->value; store as max2
    int max2;
    if (max1 > left_sum + right_sum + T->value) max2 = max1;
    else max2 = left_sum + right_sum + T->value;
    
    // TODO: update temp_max_sum with the new max
    if(max2 >temp_max_sum ) temp_max_sum = max2;
// cout << "temp max sum: " << temp_max_sum << endl << endl ;
    
    // TODO: return max1
    return max1;
}

int find_max_sum_of_nodes(BinaryTreeNode *T) {
    int temp_max_sum = INT_MIN;
    find_max_sum_of_nodes(T, temp_max_sum);
    return temp_max_sum;
}

void test_1() {
    BinaryTreeNode * test = new BinaryTreeNode(5);
    test ->left = new BinaryTreeNode(3);
    test ->left ->left= new BinaryTreeNode(-1);
    test ->left ->left ->left = new BinaryTreeNode(18);
    
    test ->left ->right= new BinaryTreeNode(8);
    test ->left ->right -> left= new BinaryTreeNode(6);

    test -> right = new BinaryTreeNode(1);
    test -> right -> right = new BinaryTreeNode(11);
    cout << "=========== TEST 1 =============" << endl;
    cout << "Desired Sum: 17" << endl;
    cout << "EXPECTED OUTPUT: " << endl << "-1 18, " << "5 1 11, " << "3 8 6" << endl << endl;
    cout << "OUPUT: " << endl;
  	find_and_print_sum_of_nodes(test, 17, 0, "");

}
void test_2() {
    BinaryTreeNode * test = new BinaryTreeNode(7);
    test ->left = new BinaryTreeNode(-1);
    test ->left ->left= new BinaryTreeNode(8);
    test ->left ->right= new BinaryTreeNode(4);
    test ->left ->left ->right = new BinaryTreeNode(2);
    test ->left ->left ->left = new BinaryTreeNode(3);

    test -> right = new BinaryTreeNode(3);
    test -> right -> right = new BinaryTreeNode(5);
    test -> right -> left = new BinaryTreeNode(-2);
    test -> right -> left -> right = new BinaryTreeNode(2);
    test -> right -> right ->left = new BinaryTreeNode(2);
    test -> right -> right ->right = new BinaryTreeNode(-1);
    cout << "=========== TEST 2 =============" << endl;
    cout << "Desired Sum: 10" << endl;
    cout << "EXPECTED OUTPUT: " << endl;

    cout << "  7 -1 4 , 8 2, 7 3, 7 3 -2 2, -1 8 3, 3 5 2 " << endl << endl;
    
    cout << "OUPUT: " << endl;
  	find_and_print_sum_of_nodes(test, 10, 0, "");

}
void test_3() {
    BinaryTreeNode * test = new BinaryTreeNode(5);
    test ->left = new BinaryTreeNode(-3);
    test ->left ->left = new BinaryTreeNode(1);
    test ->left ->left ->right = new BinaryTreeNode(2);
    test ->left ->left ->left = new BinaryTreeNode(-3);
    test ->left -> right= new BinaryTreeNode(2);

    test ->right = new BinaryTreeNode(0);
    test ->right -> left = new BinaryTreeNode(-5);
    test ->right -> right = new BinaryTreeNode(-1);
    test ->right -> right ->left = new BinaryTreeNode(-4);

    
    cout << "=========== TEST 3 =============" << endl;
    cout << "Desired Sum: 0" << endl;
    cout << "EXPECTED OUTPUT: " << endl;

    cout << "5 -3 1 -3 , 5 0 -5, 5 0 -1 -4, -3 1 2, 0" << endl << endl;
    
    cout << "OUPUT: " << endl;
  	find_and_print_sum_of_nodes(test, 0, 0, "");
}

void test_step_one() {
    cout << "=========== TESTING STEP 1 =============" << endl;
    test_1();
    test_2();
    test_3();
}

void test_4() {
 BinaryTreeNode * test = new BinaryTreeNode(5);
 test ->left = new BinaryTreeNode(6);
 test ->left -> left = new BinaryTreeNode(15);
 test ->left -> right = new BinaryTreeNode(10);
 test ->left -> right -> right = new BinaryTreeNode(-5);

 test ->right = new BinaryTreeNode(-15);
 test ->right -> right = new BinaryTreeNode(9);
 test ->right -> left = new BinaryTreeNode(-12);
 cout << "=========== TEST 4 =============" << endl;
 cout << "EXPECTED OUTPUT: 31" << endl << endl;
 cout << "OUPUT: " << endl << find_max_sum_of_nodes(test) << endl;
}

void test_5() {
    BinaryTreeNode * test = new BinaryTreeNode(6);
    test ->left = new BinaryTreeNode(10);
    test ->left -> right = new BinaryTreeNode(-5);
    test ->left -> right -> right= new BinaryTreeNode(4);

    test ->right = new BinaryTreeNode(4);
    test ->right -> right = new BinaryTreeNode(-6);
    test ->right -> right -> right = new BinaryTreeNode(7);
    cout << "=========== TEST 5 =============" << endl;
    cout << "EXPECTED OUTPUT: 21" << endl << endl;
    cout << "OUPUT: " << endl << find_max_sum_of_nodes(test) << endl;
}

void test_6() {
    BinaryTreeNode * test = new BinaryTreeNode(5);
    test ->left = new BinaryTreeNode(3);
    test ->left ->left= new BinaryTreeNode(-1);
    test ->left ->left ->left = new BinaryTreeNode(18);
    
    test ->left ->right= new BinaryTreeNode(8);
    test ->left ->right -> left= new BinaryTreeNode(6);

    test -> right = new BinaryTreeNode(1);
    test -> right -> right = new BinaryTreeNode(11);
    cout << "=========== TEST 6 =============" << endl;
    cout << "EXPECTED OUTPUT: 37" << endl << endl;
    cout << "OUPUT: " << endl << find_max_sum_of_nodes(test) << endl;
}
void test_step_two() {
    cout << "=========== TESTING STEP 2 =============" << endl;
    test_4();
    test_5();
    test_6();
}
int main() {
    test_step_one();
    test_step_two();
};