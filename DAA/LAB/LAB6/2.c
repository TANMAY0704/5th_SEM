#include <stdio.h>
#include <stdlib.h>

#define MAX_ALPHABETS 100

struct Symbol {
    char alphabet;
    int frequency;
};

struct Node {
    struct Symbol symbol;
    struct Node* left;
    struct Node* right;
};

struct MinPriorityQueue {
    struct Node** heap;
    int size;
};

struct Node* createNode(struct Symbol symbol) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node != NULL) {
        node->symbol = symbol;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

struct MinPriorityQueue* createMinPriorityQueue(int capacity) {
    struct MinPriorityQueue* queue = (struct MinPriorityQueue*)malloc(sizeof(struct MinPriorityQueue));
    if (queue != NULL) {
        queue->heap = (struct Node**)malloc(sizeof(struct Node*) * (capacity + 1));
        queue->size = 0;
    }
    return queue;
}

void minHeapify(struct MinPriorityQueue* queue, int index) {
    int smallest = index;
    int left_child = 2 * index;
    int right_child = 2 * index + 1;

    if (left_child <= queue->size && queue->heap[left_child]->symbol.frequency < queue->heap[smallest]->symbol.frequency)
        smallest = left_child;

    if (right_child <= queue->size && queue->heap[right_child]->symbol.frequency < queue->heap[smallest]->symbol.frequency)
        smallest = right_child;

    if (smallest != index) {
        struct Node* temp = queue->heap[index];
        queue->heap[index] = queue->heap[smallest];
        queue->heap[smallest] = temp;
        minHeapify(queue, smallest);
    }
}

void buildMinHeap(struct MinPriorityQueue* queue) {
    for (int i = queue->size / 2; i >= 1; i--)
        minHeapify(queue, i);
}

struct Node* extractMin(struct MinPriorityQueue* queue) {
    if (queue->size == 0)
        return NULL;

    struct Node* minNode = queue->heap[1];
    queue->heap[1] = queue->heap[queue->size];
    queue->size--;
    minHeapify(queue, 1);

    return minNode;
}

void insert(struct MinPriorityQueue* queue, struct Node* node) {
    queue->size++;
    int i = queue->size;
    while (i > 1 && node->symbol.frequency < queue->heap[i / 2]->symbol.frequency) {
        queue->heap[i] = queue->heap[i / 2];
        i /= 2;
    }
    queue->heap[i] = node;
}

struct Node* buildHuffmanTree(struct Symbol symbols[], int num_symbols) {
    struct MinPriorityQueue* queue = createMinPriorityQueue(num_symbols);

    for (int i = 0; i < num_symbols; i++) {
        struct Node* node = createNode(symbols[i]);
        insert(queue, node);
    }

    buildMinHeap(queue);

    while (queue->size > 1) {
        struct Node* leftChild = extractMin(queue);
        struct Node* rightChild = extractMin(queue);

        struct Symbol mergedSymbol = {'M', leftChild->symbol.frequency + rightChild->symbol.frequency}; 
        struct Node* mergedNode = createNode(mergedSymbol);
        mergedNode->left = leftChild;
        mergedNode->right = rightChild;

        insert(queue, mergedNode);
    }

    struct Node* root = extractMin(queue);
    free(queue->heap);
    free(queue);

    return root;
}

void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    if (root->symbol.alphabet != 'M') 
        printf("%c ", root->symbol.alphabet);
    else
        printf("%d ", root->symbol.frequency); 
    inorderTraversal(root->right);
}
int main() {
    int num_alphabets;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &num_alphabets);

    struct Symbol symbols[MAX_ALPHABETS];
    printf("Enter the alphabets: ");
    for (int i = 0; i < num_alphabets; i++)
        scanf(" %c", &symbols[i].alphabet);

    printf("Enter its frequencies: ");
    for (int i = 0; i < num_alphabets; i++)
        scanf("%d", &symbols[i].frequency);

    struct Node* root = buildHuffmanTree(symbols, num_alphabets);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
