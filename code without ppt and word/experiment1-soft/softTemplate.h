#pragma once

namespace soft {
	template<typename T>
	void selection_soft(T* arr, int len) {
		int max;
		int end;
		int index;
		/*for (int i = 0; i < len; i++) {
			max = 0;
			end = len - i;
			for (int j = 1; j < end; j++)
				if (arr[max] < arr[j])
					max = j;
			swap(arr[max], arr[len - i - 1]);
		}*/  // 数组查询花销过大，手动注释

		for (int i = 0; i < len; i++) { 
			max = arr[0]; // 使用直接赋值减少后续比较时数组查询花销
			index = 0;
			end = len - i;
			for (int j = 1; j < end; j++)
				if (max < arr[j]) {
					max = arr[j];
					index = j;
				}
			swap(arr[index], arr[len - i - 1]);
		}
	}

	template<typename T>
	void bubble_soft(T* arr, int len) {
		int end;
		for (int i = 0; i < len; i++) {
			end = len - i -1 ;
			for (int j = 0; j < end; j++) {
				if(arr[j] > arr[j + 1]) 
					swap(arr[j], arr[j + 1]); //条件控制语句转条件传输语句 但很遗憾，在自己的机器上没跑出效果 
				/*T a = arr[j];
				T b = arr[j + 1];
				int t = a < b;
				arr[j] = t ? a : b;
				arr[j + 1] = t ? b : a;*/
			}
		}
	}

	template<typename T>
	void _merge(T* arr, int left_index, int mid, int right_index) {
		T *tmp = new T[right_index - left_index + 1];
		int left_start = left_index;
		int right_start = mid + 1;
		// copy the arr to tmp as the compare
		for (int i = left_index; i <= right_index; i++) {
			tmp[i - left_index] = arr[i];
		}
		// start merge
		for (int j = left_index; j <= right_index; j++) {
			if (left_start > mid) {
				arr[j] = tmp[right_start - left_index];
				right_start++;
			}
			else if (right_index < right_start) {
				arr[j] = tmp[left_start - left_index];
				left_start++;
			}
			else if (tmp[left_start - left_index] < tmp[right_start - left_index]) {
				arr[j] = tmp[left_start - left_index];
				left_start++;
			}
			else {
				arr[j] = tmp[right_start - left_index];
				right_start++;
			}
		}
		delete[] tmp;
	}
	template<typename T>
	void _merge_soft(T* arr, int left_index, int right_index) {
		if (left_index >= right_index)
			return;
		int mid = (left_index + right_index) / 2;
		_merge_soft(arr, left_index, mid);
		_merge_soft(arr, mid + 1, right_index);
		if (arr[mid] <= arr[mid + 1])
			return;
		_merge(arr, left_index, mid, right_index);
	}
	template<typename T>
	void merge_soft(T* arr, int len) {
		_merge_soft(arr, 0, len - 1);
	}
	
	template<typename T>
	void _quick_soft(T *arr, int left_index, int right_index) {
		if (left_index >= right_index)
			return;
		int l = left_index;
		int r = right_index;
		T base = arr[left_index];
		// 设定基准数字为base
		// 设定坑
		while (l < r) {
			while (l < r && arr[r] > base) 
				r--;
			if (l < r) {
				arr[l] = arr[r];
				l++;
			}

			while (l < r && arr[l] < base)
				l++;
			if (l < r) {
				arr[r] = arr[l];
				r--;
			}
		}
		arr[l] = base;
		_quick_soft(arr, left_index, l - 1);
		_quick_soft(arr, l + 1, right_index);
	}
	template<typename T>
	void quick_soft(T* arr, int len) {
		_quick_soft(arr, 0, len - 1);
	}
	
	template<typename T>
	void insert_soft(T* arr, int len) {
		for (int i = 1; i < len; i++) {
			T insert = arr[i];
			int j = i - 1;
			while (insert < arr[j] && j >= 0) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j+1] = insert;
		}
	}
}