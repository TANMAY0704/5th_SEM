#include <stdio.h>

struct Item {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

void heapify(struct Item items[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && items[left].profit_weight_ratio > items[largest].profit_weight_ratio) {
        largest = left;
    }
  
    if (right < n && items[right].profit_weight_ratio > items[largest].profit_weight_ratio) {
        largest = right;
    }

    if (largest != i) {
        struct Item temp = items[i];
        items[i] = items[largest];
        items[largest] = temp;
        heapify(items, n, largest);
    }
}

void build_heap(struct Item items[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(items, n, i);
    }
}

void fractional_knapsack(struct Item items[], int n, float capacity) {
    build_heap(items, n);

    float total_profit = 0.0;
    for (int i = 0; i < n; i++) {
        if (capacity <= 0) {
            break;
        }

        if (items[i].item_weight <= capacity) {
            total_profit += items[i].item_profit;
            capacity -= items[i].item_weight;
            printf("Item No %d Profit %.6f Weight %.6f Amount to be taken 1.000000\n",
                   items[i].item_id, items[i].item_profit, items[i].item_weight);
        } else {
            float fraction = capacity / items[i].item_weight;
            total_profit += fraction * items[i].item_profit;
            printf("Item No %d Profit %.6f Weight %.6f Amount to be taken %.6f\n",
                   items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            capacity = 0;
        }
    }

    printf("Maximum profit: %.6f\n", total_profit);
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct Item items[n];
    for (int i = 0; i < n; i++) {
        int profit, weight;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%d %d", &profit, &weight);
        items[i].item_id = i + 1;
        items[i].item_profit = profit;
        items[i].item_weight = weight;
        items[i].profit_weight_ratio = (float)profit / weight;
    }

    float capacity;
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    fractional_knapsack(items, n, capacity);

    return 0;
}
