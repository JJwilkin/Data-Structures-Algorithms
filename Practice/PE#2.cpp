void find_and_print_sum_of_nodes (BinaryTreeNode* T, int desired_sum, int cur_sum, string buffer) {
    // exit if T is NULL
    if (!T) return;

    // update the ongoing sum with the current value for T
    int new_sum = cur_sum + T->value;

    // update the current path string
    string new_buffer = buffer + " " + int2ascii(T->value);

    // if the desired sum is found, print the corresponding path
    if (new_sum == desired_sum)
        cout << new_buffer << endl;

    // TODO: continue down theleft subtree

    // TODO: continue down theright subtree

    // TODO: restart from the left subtreeif buffer = “”

    // TODO: restart from the right subtreeif buffer = “”
}