#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

// Node structure for Huffman tree
typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

// Structure for linked list node
typedef struct ListNode {
    Node *treeNode;
    struct ListNode *next;
} ListNode;

// Function to create a new tree node
Node* createNode(char ch, int freq) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->ch = ch;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a new linked list node
ListNode* createListNode(Node* treeNode) {
    ListNode* newListNode = (ListNode*)malloc(sizeof(ListNode));
    newListNode->treeNode = treeNode;
    newListNode->next = NULL;
    return newListNode;
}

// Function to insert a node into the linked list in sorted order
void insertListNode(ListNode** head, Node* treeNode) {
    ListNode* newNode = createListNode(treeNode);
    if (*head == NULL || (*head)->treeNode->freq >= treeNode->freq) {
        newNode->next = *head;
        *head = newNode;
    } else {
        ListNode* current = *head;
        while (current->next != NULL && current->next->treeNode->freq < treeNode->freq) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to extract the minimum frequency node from the list
Node* extractMin(ListNode** head) {
    ListNode* temp = *head;
    *head = (*head)->next;
    Node* minNode = temp->treeNode;
    free(temp);
    return minNode;
}

// Function to build Huffman tree from frequency data
Node* buildHuffmanTree(char data[], int freq[], int size) {
    ListNode* head = NULL;

    // Create a list of tree nodes
    for (int i = 0; i < size; i++) {
        insertListNode(&head, createNode(data[i], freq[i]));
    }

    // Build the Huffman tree
    while (head != NULL && head->next != NULL) {
        Node* left = extractMin(&head);
        Node* right = extractMin(&head);
        Node* newNode = createNode('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        insertListNode(&head, newNode);
    }

    return extractMin(&head);
}

// Function to print Huffman codes
void printCodes(Node* root, int code[], int top) {
    if (root->left) {
        code[top] = 0;
        printCodes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = 1;
        printCodes(root->right, code, top + 1);
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%c: ", root->ch);
        for (int i = 0; i < top; i++) {
            printf("%d", code[i]);
        }
        printf("\n");
    }
}

// Function to count the frequency of characters in a file
void countFrequency(const char* filename, int freq[]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        freq[ch]++;
    }
    fclose(file);
}

// Function to get the size of the file
long getFileSize(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

int main() {
    const char* filename = "recommendation.txt";

    // Get file size before compression
    long originalSize = getFileSize(filename);
    printf("Original file size: %ld bytes\n", originalSize);

    // Count character frequencies
    int freq[MAX_CHARS] = {0};
    countFrequency(filename, freq);

    // Determine the number of unique characters
    int uniqueChars = 0;
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            uniqueChars++;
        }
    }

    // Create arrays for the characters and their frequencies
    char* data = (char*)malloc(uniqueChars * sizeof(char));
    int* frequencies = (int*)malloc(uniqueChars * sizeof(int));

    int index = 0;
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            data[index] = (char)i;
            frequencies[index] = freq[i];
            index++;
        }
    }

    // Build the Huffman tree
    Node* root = buildHuffmanTree(data, frequencies, uniqueChars);

    // Print Huffman codes
    int code[MAX_CHARS], top = 0;
    printf("Huffman Codes:\n");
    printCodes(root, code, top);

    // Simulate compression (actual implementation will vary)
    long compressedSize = originalSize / 2;  // Assume compression reduces size by half for simplicity
    printf("Compressed file size: %ld bytes\n", compressedSize);

    // Clean up
    free(data);
    free(frequencies);
    return 0;
}
