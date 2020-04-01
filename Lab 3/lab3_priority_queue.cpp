#include "lab3_priority_queue.hpp"
#include <iostream>

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
    heap = new TaskItem *[n_capacity +1];
    capacity = n_capacity;
    size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
//    for (int i = 0; i < size; i++) {
//        if (heap[i]) {
            delete heap;
            heap = nullptr;
//        }
//    }
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size ;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
    return size == 0;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    return size == capacity;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
    for (int i = 1; i <= size; i++) {
        cout << "ITEM " << i << ": Task Priority is: " << heap[i]->priority
                             << ". Item Description is: " << heap[i]->description << endl;
    }
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    if (empty()) return TaskItem(-1, "NULL");
    else {
        int max = 0;
        int max_element = 0;
        for (int i = 1; i <= size; i++) {
            if (heap[i]->priority > max) {
                max = heap[i]->priority;
                max_element = i;
            }
        }
        return *heap[max_element];
    }
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	if (size == capacity) return false;

	if (size == 0) heap[1] = new TaskItem(val.priority, val.description);

	else {
		int i = size + 1;
        heap[i] = new TaskItem(val.priority, val.description);
        // Strt at bottom right of heap, traverse up, swapping parents with children if children > parent
		while (i > 1 && heap[i/2]->priority < heap[i]->priority) {
			TaskItem * temp = heap[i];
			heap[i] = heap[i/2];
			heap[i/2] = temp;
			i /= 2;
		}

    }
	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if (size == 0) return false;
	else {
		int i = size;
		TaskItem * temp = heap[1]; // Store first element
		heap[1] = heap[i];
		heap[i] = temp;
		//delete heap[i];
		//heap[i] = nullptr;
		int j = 1;
		while (j < size && (2*j+1) < size && (heap[j] -> priority < heap[2*j] -> priority || heap[j] -> priority < heap[2*j +1] -> priority)) {
			TaskItem * swap = heap[j];
			if (heap[2*j] -> priority > heap[2*j + 1] -> priority) { //if left node > right node swap left nope

				heap[j] = heap[2*j];
				heap [2*j] = swap;
			}
			else {
				heap[j] = heap[2*j +1];
				heap [2*j +1] = swap;
			}
		}
	}
	size--;
	return true;
}
