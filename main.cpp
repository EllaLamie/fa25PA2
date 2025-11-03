//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {

    // Opening file to read from
    ifstream file(filename);

    // Check to make sure file is able to open. If not, will exit program
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;

    // While loop to read from the file until the end
    while (file.get(ch)) {

        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }

    // Closing file after reading is done
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Using an iterative traversal to assign the characters to charArr, frequency to weightArr,
// and the children of each to -1. This creates our leaf nodes
int createLeafNodes(int freq[]) {

    // Assigning the nextFree node to 0
    int nextFree = 0;

    // Iterative traversal to find the number of leaf nodes
    for (int i = 0; i < 26; ++i) {

        // Making sure we have items in the array
        if (freq[i] > 0) {

            // Assigning the nextFreeth node to a letter using ASCII code
            charArr[nextFree] = 'a' + i;

            // Now assign the frequency of an element to weightArray
            weightArr[nextFree] = freq[i];

            // Now assign the indices to -1 because they have no children
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;

            // Move up nextFree to next free node
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {

    // Create a MinHeap object.
    MinHeap minHeap;

    // Push all leaf node indices into the heap.
    for (int i = 0; i < nextFree; i++) {
        minHeap.push(i, weightArr);
    }

    // While the heap size is greater than 1, use Huffman coding to find roots
    // by continuously adding the two top nodes into one parent node and setting
    // the two top nodes as the parent node's children. Then, when pushing the
    // parent back into the heap, we get the Huffman coding tree
    while (minHeap.size > 1) {

        // Pop two smallest nodes
        int first = minHeap.pop(weightArr);
        int second = minHeap.pop(weightArr);

        // Create a new parent node with combined weight of first and second
        weightArr[nextFree] = weightArr[first] + weightArr[second];

        // Set left/right pointers of the new parent node
        leftArr[nextFree] = first;
        rightArr[nextFree] = second;

        // Push new parent index back into the heap
        minHeap.push(nextFree, weightArr);

        // Increment nextFree
        nextFree++;
    }

    // Return the index of the last remaining node (root)
    int root = minHeap.pop(weightArr);
    return root;
}

// Use an STL stack to generate codes. We can use this to access the top and pop from there.
// We also use a while loop to assign the info and position to a node. When we are in the
// process of trying to reach a node, we add 0 for every left node and 1 for every right node
void generateCodes(int root, string codes[]) {
    // Make sure we have a heap
    if (root == -1) {
        return;
    }

    // Use stack<pair<int, string>> to simulate DFS traversal.
    stack<pair<int, string>> stack;

    // Push the root of the tree into the stack
    stack.push({root, ""});

    // While the stack is not empty, assign the info and position to the top and pop it
    while (!stack.empty()) {

        // Assign the top of the stack to temp
        pair<int, string> temp = stack.top();

        // Now assign the position and info to second and first
        int position = temp.first;
        string info = temp.second;

        // Pop that from the stack
        stack.pop();

        // Record code (AKA info in my code) when a leaf node is reached
        if (leftArr[position] == -1 && rightArr[position] == -1) {
            codes[charArr[position] - 'a'] = info;
        }
        else {

            // Left edge adds '0', right edge adds '1'.
            if (rightArr[position] != -1) {
                stack.push({rightArr[position], info + "1"});
            }
            if (leftArr[position] != -1) {
                stack.push({leftArr[position], info + "0"});
            }
        }
    }
}

// Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";

    // Loop for every letter in the alphabet
    for (int i = 0; i < 26; ++i) {

        // Use codes to find if we have that letter
        if (!codes[i].empty())

            // Use ASCII to find letter and print the code
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    // Use file to find the characters
    ifstream file(filename);
    char ch;

    // While loop for all the characters in the file
    while (file.get(ch)) {

        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // If they are lowercase
        if (ch >= 'a' && ch <= 'z')

            // Prints binary code for whichever letter
            cout << codes[ch - 'a'];
    }
    cout << "\n";

    // Close the file after done reading
    file.close();
}