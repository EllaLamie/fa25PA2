//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    // Takes parameter idx to push into the array and weightArr[] as the array for upheap
    void push(int idx, int weightArr[]) {

        // Check to make sure we are not going over 64 which is almost impossible
        if (size >= 64) {
            cout<<"Heap overflow"<<endl;
            return;
        }

        // Assigning index to the data array at position size
        data[size] = idx;

        //Now setting pos to where ever size is
        int pos = size;

        // Incrementing size
        size++;

        // Using pos to upheap
        upheap(pos, weightArr);
    }

    // Replaces root with last element, then calls downheap() to keep min heap property
    int pop(int weightArr[]) {

        // Case if no items in the array
        if (size == 0) return -1;

        // Assign the first item in the array to the root
        int root = data[0];

        // Now overwrite the root item by assigning it to the last element in the array
        data[0] = data[size - 1];

        // Decreasing the size by 1
        size--;

        // Downheap to maintain min heap order
        downheap(0, weightArr);

        return root;
    }

    //Method to maintain min heap property using iterative traversal and comparisons
    void upheap(int pos, int weightArr[]) {

        // Loops until we have gone through all the elements
        while (pos > 0) {

            // Finding the parent node of the current position
            int parentPos = (pos - 1) / 2;

            // Comparing to see if the child or parent is less
            if (weightArr[data[pos]] < weightArr[data[parentPos]]) {

                // Swapping the two if so by using a temp variable
                int temp = data[pos];
                data[pos] = data[parentPos];
                data[parentPos] = temp;

                // Now assigning the position to the parent to repeat the process
                pos = parentPos;
            }
            else {

                // If not, no swapping needed so break out of loop
                break;
            }
        }
    }

    // Swap parent down while larger than any child
    void downheap(int pos, int weightArr[]) {

        // Loops until break statement is reached
        while (true) {

            // Finding left and right child nodes
            int leftNode = 2 * pos + 1;
            int rightNode = leftNode + 1;

            // Assigning the smallest position to the current position temporarily
            int smallestPos = pos;

            // Setting the smallest position to the left node if less than
            if (leftNode < size && weightArr[data[leftNode]] < weightArr[data[smallestPos]]) {
                smallestPos = leftNode;
            }

            // Setting the smallest position to the right node if less than
            if (rightNode < size && weightArr[data[rightNode]] < weightArr[data[smallestPos]]) {
                smallestPos = rightNode;
            }

            // If smallest position does not equal current position, swap them
            if (smallestPos != pos) {

                // Using a temp to swap the data at the current and smallest positions
                int temp = data[pos];
                data[pos] = data[smallestPos];
                data[smallestPos] = temp;

                // Now setting the current position to the smallest position
                pos = smallestPos;
            }
            else {

                // Breaks out of loop if none of the above conditions were met
                break;
            }
        }
    }
};

#endif