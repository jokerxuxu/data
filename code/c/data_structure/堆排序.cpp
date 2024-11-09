#include <stdio.h>

//交换函数
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//堆化函数调整堆
//heapify(int arr[], int n, int i): 调整以 i 为根的子树成为大根堆。
//比较当前节点与左右子节点，确定最大值位置进行交换。
void heapify(int arr[], int n, int i) {
    int largest = i;                         //根节点
    int left = 2 * i + 1;                    //左子树
    int right = 2 * i + 2;                   //右子树

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

//堆排序函数
//首先构建大根堆，然后通过交换和堆化逐步排序。
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);                  //构造堆

    for (int i = n - 1; i > 0; i--) {        
        swap(&arr[0], &arr[i]);              //把根节点和最后节点的交换位置
        heapify(arr, i, 0);                  //重新调整堆化
    }
}

//打印数组函数
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("请输入元素数量: ");
    scanf("%d", &n);

    int arr[n];
    printf("请输入元素: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    heapSort(arr, n);

    printf("排序后的数组: ");
    printArray(arr, n);

    return 0;
}