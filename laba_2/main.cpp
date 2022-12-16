#include <iostream>
#include <windows.h>
#include <vector>
#include <iterator>

struct myArray {
	int* storage;
	int size;
	int maxElement;
	int minElement;
	int average;
};

LPTHREAD_START_ROUTINE WINAPI min_max(void* _arr, int size, int& min, int& max) {
	myArray* array = static_cast<myArray*>(_arr);
	min = array->storage[0];
	max = array->storage[0];
	for (int i = 0; i < size; i++) {
		if (array->storage[i] > max) {
			max = array->storage[i];
		}
		Sleep(7);
		if (array->storage[i] < min) {
			min = array->storage[i];
		}
		Sleep(7);
	}
	std::cout << "Min: " << min << "\n";
	std::cout << "Max: " << max << "\n";
	return 0;
}

LPTHREAD_START_ROUTINE WINAPI average(void* _arr, double& avg) {
	myArray* array = static_cast<myArray*>(_arr);
	int sum = 0;
	for (int i = 0; i < array->size; i++) {
		sum += array->storage[i];
		Sleep(12);
	}
	avg = 1. * sum / array->size;
	std::cout << "Average: " << avg << "\n";
	return 0;
}




int main() {

	HANDLE minMaxHThread;
	DWORD minMaxIDThread;
	HANDLE averageHThread;
	DWORD averageIDThread;

	int size;


	std::cout << "Enter size of array:\n";
	std::cin >> size;
	myArray* arr = new myArray();
	arr->storage = new int[size];
	arr->size = size;
	std::cout << "Enter elements of array:\n";

	for (int i = 0; i < size; i = -~i) {
		std::cout << "Input " << -~i << " element of array: ";
		std::cin >> arr->storage[i];

	}
	int min, max; double avg;
	minMaxHThread = CreateThread(NULL, 0, min_max(arr,size,min,max), arr, 0, &minMaxIDThread);
	averageHThread = CreateThread(NULL, 0, average(arr,avg), arr, 0, &averageIDThread);

	WaitForSingleObject(minMaxHThread, INFINITE);
	WaitForSingleObject(averageHThread, INFINITE);

	CloseHandle(minMaxHThread);
	CloseHandle(averageHThread);


	for (int i = 0; i < size; i++) {
		if (arr->storage[i] == min || arr->storage[i] == max) {
			arr->storage[i] = avg;
		}
	}
	for (int i = 0; i < size; i++) {
		std::cout << arr->storage[i] << " ";
	}
	std::cout << "\n";


	return 0;
}