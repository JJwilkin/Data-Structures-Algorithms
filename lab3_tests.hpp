#ifndef LAB3_TESTS_HPP
#define LAB3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include <algorithm>
#include <sstream>
#include <queue>

#include "lab3_priority_queue.hpp"
#include "lab3_binary_search_tree.hpp"

class PriorityQueueTest {
public:
	// PURPOSE: Tests if the new queue is valid
	bool test1() {
		PriorityQueue q(5);
		ASSERT_TRUE( q.empty() );
		ASSERT_TRUE( !q.full() );
		ASSERT_TRUE( q.get_size() == 0 );
		return true;
	}

	// PURPOSE: Tests enqueue of one item and then dequeue of that item
	bool test2() {
        PriorityQueue r(5);
        r.enqueue(PriorityQueue::TaskItem(2, "NULL"));
        ASSERT_TRUE( !r.empty() );
        ASSERT_TRUE( !r.full() );
        ASSERT_TRUE( r.get_size() == 1 );
        r.dequeue();
        ASSERT_TRUE( r.empty() );
        ASSERT_TRUE( !r.full() );
        ASSERT_TRUE( r.get_size() == 0 );
        return true;
	}

	// PURPOSE: Tests enqueue too many
	bool test3() {
        PriorityQueue s(4);
        s.enqueue(PriorityQueue::TaskItem(2, "Item Two"));
        s.enqueue(PriorityQueue::TaskItem(3, "Item Three"));
        s.enqueue(PriorityQueue::TaskItem(7, "Item 7"));
        s.enqueue(PriorityQueue::TaskItem(6, "Item 6"));
        s.print();
        cout << "Max value is: " << s.max().priority << endl;
        ASSERT_TRUE(s.full());
        ASSERT_TRUE(s.get_size() == 4);
        ASSERT_FALSE(s.enqueue(PriorityQueue::TaskItem(4, "NULL")));
        return true;
	}
  
	// PURPOSE: Tests enqueue too many then dequeue too many
	bool test4() {
        PriorityQueue a(2);
        a.enqueue(PriorityQueue::TaskItem(2, "Item Two"));
        a.enqueue(PriorityQueue::TaskItem(3, "Item Three"));
        ASSERT_FALSE(a.enqueue(PriorityQueue::TaskItem(4, "NULL")));
        ASSERT_TRUE( a.get_size() == 2 );
        a.print();
        a.dequeue();
        a.dequeue();
        ASSERT_FALSE(a.dequeue());
        return true;
	}
};

class BinarySearchTreeTest {
public:
	bool insert_nodes(BinarySearchTree &tree, int *in, int nin) {
		for(int i = 0; i < nin; i++) {
			ASSERT_TRUE(tree.insert(BinarySearchTree::TaskItem(in[i],"Test Task")));
		}
		return true;
	}

	// PURPOSE: Traverse the tree using breadth-first traversal
	// Output is as follows: "val1 val2 ... valN"
	std::string level_order(BinarySearchTree::TaskItem* root) {
		if (!root) {
      		return "";
    	}    

		std::stringstream ss;
		std::queue<BinarySearchTree::TaskItem*> node_queue;
		node_queue.push(root);
		while (!node_queue.empty()) {
			BinarySearchTree::TaskItem* cur_node = node_queue.front();
			node_queue.pop();
			ss << cur_node->priority << " ";
			if (cur_node->left) {
				node_queue.push(cur_node->left);
			}
			if (cur_node->right) {
				node_queue.push(cur_node->right);
			}
		}
    
		std::string level_order_str = ss.str();

		return level_order_str.substr(0, level_order_str.size() - 1);
	}

	// PURPOSE: Tests if the new tree is valid
	bool test1() {
		std::string expected_tree_level_order = "";
    
		BinarySearchTree bst;
		ASSERT_TRUE(bst.root == NULL);
		ASSERT_TRUE(bst.size == 0 && bst.get_size() == 0);
    
		// compare the tree's representation to the expected tree
		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
		return true;
	}

	// PURPOSE: Tests a tree with one node
	bool test2() {
        BinarySearchTree bst;
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(2,"test") ));
        ASSERT_TRUE(bst.size == 1 && bst.get_size() ==1);
        ASSERT_TRUE(*bst.root == BinarySearchTree::TaskItem(2,"test"));
		return true;
	}

	// PURPOSE: Tests insert, remove, and size on linear list formation with three elements
	bool test3() {
        BinarySearchTree bst;
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(3,"test")));

        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(2,"test2")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(1,"test1")));
        ASSERT_TRUE(bst.size == 3 && bst.get_size() ==3);
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(2,"test2")));
        ASSERT_TRUE(bst.size == 2 && bst.get_size() ==2);

        return true;
	}

	// PURPOSE: Tests removal of a node with one child
	bool test4() {
        BinarySearchTree bst;
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(5,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(3,"test2")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(8,"test1")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(4,"test1")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(3,"test2")));

        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(2,"test1")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(4,"test1")));

        return true;
	}

	// PURPOSE: Tests insert of multiple elements and remove till nothing remains
	bool test5() {
        BinarySearchTree bst;
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(40,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(20,"test2")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(60,"test1")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(50,"test1")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(55,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(65,"test2")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(70,"test1")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(67,"test1")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(75,"test1")));

        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(67,"test1")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(65,"test2")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(70,"test1")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(75,"test1")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(40,"test")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(50,"test1")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(60,"test1")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(55,"test")));
        ASSERT_TRUE(*bst.root == BinarySearchTree::TaskItem(20,"test2"));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(20,"test2")));

        return true;
	}
 
	// PURPOSE: Tests removal of root node when both children of root have two children
	bool test6() {
        BinarySearchTree bst;
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(20,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(10,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(30,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(5,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(15,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(25,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(35,"test")));

        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(20,"test")));
        ASSERT_TRUE(*bst.root == BinarySearchTree::TaskItem(25,"test"));
        return true;
	}

	// PURPOSE: Tests depth with many inserts and some removes
	bool test7() {
        BinarySearchTree bst;
        ASSERT_TRUE(bst.height() == 0);
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(20,"test")));
        ASSERT_TRUE(bst.height() == 1);
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(10,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(30,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(5,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(15,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(25,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(35,"test")));
        ASSERT_TRUE(bst.height() == 3);

        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(11,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(12,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(14,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(13,"test")));
        ASSERT_TRUE(bst.height() == 7);
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(11,"test")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(14,"test")));
        ASSERT_TRUE(bst.height() == 5);
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(27,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(26,"test")));
        ASSERT_TRUE(bst.height() == 5);

        return true;
	}

	// PURPOSE: Tests lots of inserts and removes
	bool test8() {
        BinarySearchTree bst;
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(50,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(20,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(80,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(1,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(16,"test")));

        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(20,"test")));

        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(30,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(17,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(37,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(55,"test")));

        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(16,"test")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(37,"test")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(80,"test")));

        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(90,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(80,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(99,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(86,"test")));
        ASSERT_FALSE(bst.insert(BinarySearchTree::TaskItem(90,"test")));
        ASSERT_FALSE(bst.insert(BinarySearchTree::TaskItem(1,"test")));
        ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(19,"test")));

        ASSERT_TRUE(bst.min().priority == 1);
        ASSERT_TRUE(bst.max().priority == 99);
        ASSERT_FALSE(bst.remove(BinarySearchTree::TaskItem(14,"test")));
        ASSERT_FALSE(bst.remove(BinarySearchTree::TaskItem(50,"test2")));
        ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(50,"test")));
        ASSERT_TRUE(bst.root->priority == 55);
        ASSERT_TRUE(bst.height() == 5);
		return true;
	}
};
#endif
