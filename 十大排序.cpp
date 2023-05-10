#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<unordered_map>
using namespace std;

void bubbleSort(vector<int>& nums) {
	int n = nums.size();
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (nums[j] > nums[j + 1]) {
				swap(nums[j], nums[j + 1]);
			}
		}
		for (int i = 0; i < n; i++) {
			cout << nums[i] << " ";
		}
		cout << endl;
	}
}

void selectSort(vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n - 1; i++) {
		int tempMin = i;
		for (int j = i + 1; j < n; j++) {
			if (nums[j] < nums[tempMin]) {
				tempMin = j;
			}
		}
		swap(nums[i], nums[tempMin]);
		for (int i = 0; i < n; i++) {
			cout << nums[i] << " ";
		}
		cout << endl;
	}
}

void insertSort(vector<int>& nums) {
	int n = nums.size();
	for (int i = 1; i < n; i++) {
		int temp = nums[i];
		int j = i - 1;
		while (j >= 0 && nums[j]>=temp) {
			nums[j + 1] = nums[j];
			j--;
		}
		nums[j + 1] = temp;
		for (int i = 0; i < n; i++) {
			cout << nums[i] << " ";
		}
		cout << endl;
	}
}

void Merge(vector<int>& nums, int start, int mid, int end) {
	vector<int>temp;
	cout <<"mid=" << mid << " ";
	int n = nums.size();
	int l = start;
	int r = mid + 1;
	while (l <= mid && r <= end) {
		if (nums[l] < nums[r]) {
			temp.emplace_back(nums[l]);
			l++;
		}
		else {
			temp.emplace_back(nums[r]);
			r++;
		}
	}
	if (l == mid + 1) {
		for (int i = r; i <= end; i++) {
			temp.emplace_back(nums[i]);
		}
	}
	else {
		for (int i = l; i <= mid; i++) {
			temp.emplace_back(nums[i]);
		}
	}
	for (int i = start; i <= end; i++) {
		nums[i] = temp[i - start];
	}
	cout << "สýื้ฃบ";
	for (int i = 0; i < n; i++) {
		cout << nums[i] << " ";
	}
	cout << endl;
}
void mergeSort(vector<int>& nums, int start, int end) {
	if (start == end) {
		return;
	}
	int n = nums.size();
	int mid = (start + end) / 2;
	mergeSort(nums, start, mid);
	mergeSort(nums, mid + 1, end);
	Merge(nums, start, mid, end);
}

void countingSort(vector<int>& nums) {
	int n = nums.size();
	int max = *max_element(nums.begin(), nums.end());
	vector<int>count(max + 1);
	for (int i = 0; i < n; i++) {
		count[nums[i]]++;
	}
	int i = 0;
	for (int j = 0; j < count.size(); j++) {
		for (int cnt = count[j]; cnt > 0; cnt--) {
			nums[i++] = j;
		}
	}
}

void radixSort(vector<int>& nums) {
	int n = nums.size();
	int max = *max_element(nums.begin(), nums.end());
	unsigned int base = 1;
	while (base <= max) {
		vector<vector<int>>bucket(20);
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] >= 0) {
				int index = nums[i] / base % 10;
				bucket[index].emplace_back(nums[i]);
			}
			else {
				int index = -1 * (nums[i] + 1) / base % 10;
				bucket[index + 10].emplace_back(nums[i]);
			}
		}
		int i = 0;
		for (int j = 19; j >= 10; j--) {
			for (auto& num : bucket[j]) {
				nums[i++] = num;
			}
		}
		for (int j = 0; j < 10; j++) {
			for (auto& num : bucket[j]) {
				nums[i++] = num;
			}
		}
		base *= 10;
	}
}

int quickSortPivot(vector<int>& nums, int start, int end) {
	int pivot = start;
	int j = start + 1;
	for (int i = start + 1; i <= end; i++) {
		if (nums[i] <= nums[pivot]) {
			swap(nums[j], nums[i]);
			j++;
		}
	}
	swap(nums[pivot], nums[j - 1]);
	pivot = j - 1;
	return pivot;
}
void quickSort(vector<int>& nums, int start, int end) {
	if (start >= end) {
		return;
	}
	int pivot = quickSortPivot(nums, start, end);
	quickSort(nums, start, pivot - 1);
	quickSort(nums, pivot + 1, end);
}

int rquickSortPivot(vector<int>& nums, int start, int end) {
	srand(0);
	int randomIndex = rand() % end + start;
	swap(nums[start], nums[randomIndex]);
	int pivot = start;
	int j = start + 1;
	for (int i = start + 1; i <= end; i++) {
		if (nums[i] <= nums[pivot]) {
			swap(nums[j], nums[i]);
			j++;
		}
	}
	swap(nums[pivot], nums[j - 1]);
	pivot = j - 1;
	return pivot;
}
void rquickSort(vector<int>& nums, int start, int end) {
	if (start >= end) {
		return;
	}
	int pivot = rquickSortPivot(nums, start, end);
	rquickSort(nums, start, pivot - 1);
	rquickSort(nums, pivot + 1, end);
}

void bucketSort(vector<int>& nums) {
	int min = *min_element(nums.begin(), nums.end());
	int max = *max_element(nums.begin(), nums.end());
	int bucketCount = 3;
	vector<vector<int>>bucket(bucketCount);
	int perBucket = (max - min + bucketCount) / bucketCount;
	for (int i = 0; i < nums.size(); i++) {
		int bucketIndex = (nums[i] - min) / perBucket;
		bucket[bucketIndex].emplace_back(nums[i]);
	}
	for (int i = 0; i < bucketCount; i++) {
		quickSort(bucket[i], 0, bucket[i].size() - 1);
	}
	int i = 0;
	for (auto& buc : bucket) {
		for (auto& num : buc) {
			nums[i++] = num;
		}
	}
}

void shellSort(vector<int>& nums) {
	int n = nums.size();
	int gap = n / 2;
	while (gap > 0) {
		for (int i = gap; i < n; i++) {
			int x = nums[i];
			int j = i;
			while (j >= gap && x <= nums[j - gap]) {
				nums[j] = nums[j - gap];
				j -= gap;
			}
			nums[j] = x;
		}
		gap /= 2;
	}
}

void maxHeapify(vector<int>& nums, int len,int index) {
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int maxIdx = index;
	if (left<len && nums[left]>nums[maxIdx]) maxIdx = left;
	if (right<len && nums[right]>nums[maxIdx]) maxIdx = right;
	if (maxIdx != index) {
		swap(nums[maxIdx], nums[index]);
		maxHeapify(nums, len, maxIdx);
	}
}
void heapSort(vector<int>& nums,int len) {
	for (int i = (len - 1) / 2; i >= 0; i--) {
		maxHeapify(nums, len, i);
	}
	for (int i = len - 1; i >= 1; i--) {
		swap(nums[0], nums[i]);
		maxHeapify(nums, i, 0);
	}
}

int main() {
	vector<int> nums{ 5,3,8,6,9,2,1,4,7,10 };
	vector<int>nums2{ 3120,23,1,534,312 };
	vector<int>nums3{ -1,-6,3,0,4 };
	//bubbleSort(nums);
	//selectSort(nums);
	//insertSort(nums);
	//mergeSort(nums, 0, nums.size() - 1);
	//bucketSort(nums);
	//countingSort(nums);
	//radixSort(nums3);
	//quickSort(nums, 0, nums.size() - 1);
	//rquickSort(nums, 0, nums.size() - 1);
	//shellSort(nums);
	//heapSort(nums, nums.size());
	for (auto& p : nums) {
		cout << p << " ";
	}
	return 0;
}