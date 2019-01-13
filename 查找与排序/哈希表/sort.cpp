#include"pch.h"

void print(Array *a) {
	for (int i = 1; i <= a->length; i++) {
		printf("%d ", a->num[i]);
	}
}

///////////////////////////////InsertSort

void DirectInsertSort(Array *a) {//直接插入排序
	int i, j;
	for (i = 2; i <= a->length; i++) {
		if (a->num[i] < a->num[i - 1]) {//前面的表有序
			a->num[0] = a->num[i];
			for (j = i - 1; a->num[j] > a->num[0]; j--)
				a->num[j + 1] = a->num[j];
			a->num[j + 1] = a->num[0];
		}
	}
}

void BinarySearchDirectInsertSort(Array *a) {
	int i, begin, end, mid, j;
	for (i = 2; i <= a->length; i++) {
		if (a->num[i] < a->num[i - 1]) {//前面的表有序
			a->num[0] = a->num[i];
			for (begin = 1, end = i - 1, mid = (begin + end) / 2; begin <= end; mid = (begin + end) / 2)
				a->num[0] >= a->num[mid] ? begin = mid + 1 : end = mid - 1;// =
			for (j = i - 1; j >= begin; j--)
				a->num[j + 1] = a->num[j];
			a->num[end + 1] = a->num[0];
		}
	}
}

void ShellSort(Array *a) {
	int i, j, gap;
	for (gap = a->length / 2; gap; gap /= 2) {
		for (i = 1 + gap ; i<=a->length ; i++) {//从第二项开始,间隔为gap
			if (a->num[i] < a->num[i - gap]) {
				a->num[0] = a->num[i];
				for (j = i - gap;j>0&&a->num[j] > a->num[0];j-=gap)
						a->num[j + gap] = a->num[j];
				a->num[j + gap] = a->num[0];
			}
		}
	}
}

//////////////////////////////SwapInsert

void BubbleSort(Array *a) {
	for (int i = 1; i < a->length; i++) {
		int flag = 1;
		for (int j = 1; j < a->length - i + 1; j++) {
			if (a->num[j] > a->num[j + 1]) {
				flag = 0;
				a->num[0] = a->num[j], a->num[j] = a->num[j + 1], a->num[j + 1] = a->num[0];
			}
		}
		if (flag)
			break;
	}
}

void qsort(int num[], int begin, int end) {
	if (begin >= end)
		return;
	int left = begin, right = end;
	while (left < right) {
		while (left < right&&num[right] >= num[begin])
			right--;
		while (left < right&&num[left] <= num[begin])
			left++;
		if (left < right)
			num[0] = num[left], num[left] = num[right], num[right] = num[0];
	}
	num[0] = num[right], num[right] = num[begin], num[begin] = num[0];//分界点right
	//if (begin < right - 1)
		qsort(num, begin, right - 1);
	//if (right + 1 < end)
		qsort(num, right + 1, end);
}

void QuickSort(Array *a) {
	qsort(a->num, 1, a->length);
}