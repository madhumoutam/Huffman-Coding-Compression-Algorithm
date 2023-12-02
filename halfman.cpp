#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct MinHeapNode {
    char data;
    int freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, int freq)
        : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(MinHeapNode *l, MinHeapNode *r) {
        if (l->freq == r->freq) {
            return l > r; 
        }
        return l->freq > r->freq;
    }
};


void printHuffmanCodes(MinHeapNode *root, string code, unordered_map<char, string> &huffmanCodes);

void buildHuffmanTree(string data, int freq[], int size) {
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, Compare> minHeap;

    for (int i = 0; i < size; ++i) {
        minHeap.push(new MinHeapNode(data[i], freq[i]));
    }

    while (minHeap.size() > 1) {
        MinHeapNode *left = minHeap.top();
        minHeap.pop();

        MinHeapNode *right = minHeap.top();
        minHeap.pop();

        MinHeapNode *newNode = new MinHeapNode('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

   
    unordered_map<char, string> huffmanCodes;
    printHuffmanCodes(minHeap.top(), "", huffmanCodes);

    
    cout << "Huffman codes will be:\n";
    for (auto code : huffmanCodes) {
        cout << "  " << code.first << " : " << code.second << endl;
    }

    
    string inputString;
    cout << "Enter a string to encode: ";
    cin >> inputString;

    
    transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);

    string encodedString;
    for (char c : inputString) {
        if (huffmanCodes.find(c) == huffmanCodes.end()) {
            cerr << "Invalid input character detected. Exiting program.\n";
            exit(EXIT_FAILURE);
        }
        encodedString += huffmanCodes[c];
    }

    cout << "Encoded string: " << encodedString << endl;

    string decodedString;
    MinHeapNode *root = minHeap.top();
    MinHeapNode *current = root;

    for (char bit : encodedString) {
        if (bit == '0') {
            if (current->left) {
                current = current->left;
            }
        } else {
            if (current->right) {
                current = current->right;
            }
        }

        
        if (!current->left && !current->right) {
            decodedString += current->data;
            current = root; 
        }
    }

    cout << "Decoded string: " << decodedString << endl;

    
    cout << "Thank you!" << endl;
}


void printHuffmanCodes(MinHeapNode *root, string code, unordered_map<char, string> &huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }

    printHuffmanCodes(root->left, code + "0", huffmanCodes);
    printHuffmanCodes(root->right, code + "1", huffmanCodes);
}

int main() {
    string S = "abcdef";
    int f[] = {5, 9, 12, 13, 16, 45};
    int N = sizeof(f) / sizeof(f[0]);

    buildHuffmanTree(S, f, N);

    return 0;
}

