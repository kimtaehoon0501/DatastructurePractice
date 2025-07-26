#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

// element ����ü : �� ���ڿ� ���� �� �ε����� �Բ� ����( ������ �������� Ȯ���ϱ� ���ؼ�)
typedef struct {
	char data;
	int key;
} element;

// element �迭�� �����ϴ� ����ü : �迭�� �ּҸ� ����Ű�� �����Ϳ� ���̸� ����
typedef struct {
	element* data;
	int length;
} element_array;


// N���� element_array�� ���� ����. �� ���ڿ��� ���̴� 1~20 ���̷� ����.
element_array* makeArray(int N) {
	srand(time(NULL)); // �õ� �ʱ�ȭ
	element_array* array = malloc(N * sizeof(element_array));
	for (int i = 0; i < N; i++) {
		int len = rand() % 20 + 1;
		array[i].data = malloc(len * sizeof(element));
		array[i].length = len;
		for (int j = 0; j < len; j++) {
			array[i].data[j].data = 'a' + (rand() % 26);
			array[i].data[j].key = j;
		}
	}
	return array;
}

// �迭 ���� �Լ� : ���� �迭�κ��� ��ü element_array ����
element_array* copyArray(element_array* original, int N) {
	element_array* copy = malloc(N * sizeof(element_array));
	for (int i = 0; i < N; i++) {
		int len = original[i].length;
		copy[i].length = len;
		copy[i].data = malloc(len * sizeof(element));
		for (int j = 0; j < len; j++) {
			copy[i].data[j] = original[i].data[j];
		}
	}
	return copy;
}

// ���� ����
void BubbleSort(element* array, int n, int* compnum, int* swapnum) {
	element temp;
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (array[j].data > array[j + 1].data) {
				SWAP(array[j], array[j + 1], temp);
				(*swapnum)++;
			}
			(*compnum)++;
		}
	}
}

// ���� ����
void InsertionSort(element* array, int n, int* compnum, int* swapnum) {
	element key;
	int i, j;
	for (i = 1; i < n; i++) {
		key = array[i];
		j = i - 1;
		while (j >= 0 && array[j].data > key.data) {
			(*compnum)++;
			array[j + 1] = array[j];
			(*swapnum)++;
			j--;
		}
		if (j >= 0) (*compnum)++;
		array[j + 1] = key;
		(*swapnum)++;
	}
}

// �� ����: �����ϰ� �����ϵ��� ������ partition �Լ�
int partition(element* array, int left, int right, int* compnum, int* swapnum) {
	element pivot = array[left], temp;
	int low = left + 1;
	int high = right;

	while (1) {
		while (low <= right && array[low].data < pivot.data) {
			low++;
			(*compnum)++;
		}
		while (high >= left + 1 && array[high].data > pivot.data) {
			high--;
			(*compnum)++;
		}
		if (low > high) break;
		SWAP(array[low], array[high], temp);
		(*swapnum)++;
		low++;
		high--;
	}
	SWAP(array[left], array[high], temp);
	(*swapnum)++;
	return high;
}

// �� ����
void QuickSort(element* array, int left, int right, int* compnum, int* swapnum) {
	if (left < right) {
		int q = partition(array, left, right, compnum, swapnum);
		QuickSort(array, left, q - 1, compnum, swapnum);
		QuickSort(array, q + 1, right, compnum, swapnum);
	}
}

// ���� ������ ���� �ܰ� - �ӽ� �迭 ����
typedef struct {
	element* buffer;
	int size;
} MergeContext;

void merge(element* array, int left, int mid, int right, int* compnum, int* swapnum, MergeContext* ctx) {
	int i = left, j = mid + 1, k = 0;
	element* temp = ctx->buffer;
	while (i <= mid && j <= right) {
		(*compnum)++;
		if (array[i].data <= array[j].data) {
			temp[k++] = array[i++];
		}
		else {
			temp[k++] = array[j++];
			(*swapnum)++;
		}
	}
	while (i <= mid) temp[k++] = array[i++];
	while (j <= right) temp[k++] = array[j++];
	for (int m = 0; m < k; m++) array[left + m] = temp[m];
}

// ���� ���� (�ӽ� ���� ����)
void MergeSort(element* array, int left, int right, int* compnum, int* swapnum, MergeContext* ctx) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(array, left, mid, compnum, swapnum, ctx);
		MergeSort(array, mid + 1, right, compnum, swapnum, ctx);
		merge(array, left, mid, right, compnum, swapnum, ctx);
	}
}

// ���� ������ Ȯ�� �Լ�
int StableCheck(element_array* array, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < array[i].length; j++) {
			for (int k = j + 1; k < array[i].length; k++) {
				if (array[i].data[j].data == array[i].data[k].data &&
					array[i].data[j].key > array[i].data[k].key) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int main() {
	int N = 50000;
	element_array* original = makeArray(N);
	clock_t start, end;
	double time;
	int compnum, swapnum, stable;

	element_array* arr;

	// Bubble Sort
	arr = copyArray(original, N);
	compnum = swapnum = 0;
	start = clock();
	for (int i = 0; i < N; i++) BubbleSort(arr[i].data, arr[i].length, &compnum, &swapnum);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	stable = StableCheck(arr, N);
	printf("Bubble Sort    | %.3f   | %7d | %5d | %s\n", time, compnum, swapnum, stable ? "YES" : "NO");
	for (int i = 0; i < N; i++) free(arr[i].data);
	free(arr);

	// Insertion Sort
	arr = copyArray(original, N);
	compnum = swapnum = 0;
	start = clock();
	for (int i = 0; i < N; i++) InsertionSort(arr[i].data, arr[i].length, &compnum, &swapnum);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	stable = StableCheck(arr, N);
	printf("Insertion Sort | %.3f   | %7d | %5d | %s\n", time, compnum, swapnum, stable ? "YES" : "NO");
	for (int i = 0; i < N; i++) free(arr[i].data);
	free(arr);

	// Quick Sort
	arr = copyArray(original, N);
	compnum = swapnum = 0;
	start = clock();
	for (int i = 0; i < N; i++) QuickSort(arr[i].data, 0, arr[i].length - 1, &compnum, &swapnum);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	stable = StableCheck(arr, N);
	printf("Quick Sort     | %.3f   | %7d | %5d | %s\n", time, compnum, swapnum, stable ? "YES" : "NO");
	for (int i = 0; i < N; i++) free(arr[i].data);
	free(arr);

	// Merge Sort (with buffer reuse)
	arr = copyArray(original, N);
	compnum = swapnum = 0;
	MergeContext ctx;
	ctx.buffer = malloc(20 * sizeof(element)); // �ִ� ���� 20�� ���� �ӽ� ���� �ѹ��� �Ҵ�
	ctx.size = 20;
	start = clock();
	for (int i = 0; i < N; i++) MergeSort(arr[i].data, 0, arr[i].length - 1, &compnum, &swapnum, &ctx);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	stable = StableCheck(arr, N);
	printf("Merge Sort     | %.3f   | %7d | %5d | %s\n", time, compnum, swapnum, stable ? "YES" : "NO");
	free(ctx.buffer);
	for (int i = 0; i < N; i++) free(arr[i].data);
	free(arr);

	// �޸� ����
	for (int i = 0; i < N; i++) free(original[i].data);
	free(original);
	return 0;
}
