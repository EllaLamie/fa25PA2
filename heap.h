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

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        int pos = size;
        size++;
        upheap(pos, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) return -1; // placeholder
        int root = data[0];
        data[0] = data[size - 1];
        size--;
        downheap(0, weightArr);
        return root;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int parentPos = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parentPos]]) {
                int temp = data[pos];
                data[pos] = data[parentPos];
                data[parentPos] = temp;
                pos = parentPos;
            }
            else {
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int leftNode = 2 * pos + 1;
            int rightNode = leftNode + 1;
            int smallestPos = pos;

            if (leftNode < size && weightArr[data[leftNode]] < weightArr[data[smallestPos]]) {
                smallestPos = leftNode;
            }
            if (rightNode < size && weightArr[data[rightNode]] < weightArr[data[smallestPos]]) {
                smallestPos = rightNode;
            }
            if (smallestPos != pos) {
                int temp = data[pos];
                data[pos] = data[smallestPos];
                data[smallestPos] = temp;
                pos = smallestPos;
            }
            else {
                break;
            }
        }
    }
};

#endif