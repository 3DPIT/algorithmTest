#include <stdio.h>
#include <algorithm>
using namespace std;
int arr[20] = { 0, };
int a_size = 0;
void MergeTwoArea(int arr[], int left, int mid, int right)
{
	int fidx = left;
	int ridx = mid + 1;
	int sidx = left;
	int temp[100] = { 0, };
	while (fidx <= mid && ridx <= right) {
		if (arr[fidx] < arr[ridx]) {
			temp[sidx++] = arr[fidx++];
		}
		else
			temp[sidx++] = arr[ridx++];
	}
	if (fidx > mid) {
		for (int i = ridx; i <= right;i++, sidx++) {
			temp[sidx] = arr[i];
		}
	}
	else {
		for (int i = fidx; i <= mid; i++, sidx++) {
			temp[sidx] = arr[i];
		}
	}
	for (int i = left; i <= right; i++) {
		arr[i] = temp[i];
	}
}
void MergeSort(int arr[], int left, int right)
{
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		MergeTwoArea(arr, left, mid, right);
	}
}
int main(void)
{
	scanf("%d", &a_size);
	for (int i = 0; i < a_size; i++)scanf("%d", &arr[i]);
	MergeSort(arr,0, a_size-1);\
	for (int i = 0; i < a_size; i++) printf("%d ", arr[i]);
}