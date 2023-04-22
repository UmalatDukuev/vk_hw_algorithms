/*Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. 
Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A,
равного или превосходящего B[i]: A[k] >= B[i]. 
Если такого элемента нет, выведите n. Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000.*/


#include <iostream>

int BinSearch(int masA[], int left, int right, int x) {
	int mid = (left + right) / 2;
	if (left >= right) {
		return mid;
	}
	if (x > masA[mid]) {
		return BinSearch(masA, mid + 1, right, x);
	}
	else  {
		return BinSearch(masA, left, mid , x);
	}

	return 1;
}

int ExpSearch(int n, int masA[], int x) {

	int k = 1;
	if (masA[n - 1] < x)
		return n;
	while (k < n && masA[k] < x) {
		k *= 2;
	}
	if (k > n)
		return BinSearch(masA, k / 2, n, x);
	else
		return BinSearch(masA, k / 2, k, x);
}

int main() {
	int n, m;
	std::cin >> n >> m;

	int* masA = new int[n];
	int* masB = new int[m];

	for (int i = 0; i < n; i++) {
		std::cin >> masA[i];
	}

	for (int i = 0; i < m; i++) {
		std::cin >> masB[i];
	}
	
	for (int i = 0; i < m; i++) {
		int num = ExpSearch(n, masA, masB[i]);
		std::cout << num << " ";
	}
	delete[] masA;
	delete[] masB;
	return 0;
}