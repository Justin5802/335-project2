/*
CSCI335 Fall 2023
Assignment 2 – Sorting Algorithms
Name: Justin Chu
Date: 12/16/23
HalfHeapSort.hpp sorts a given vector using the HalfHeapSort algorithm
*/


#include <vector>
#include <chrono>


void percDown(std::vector<int>& nums, int i) {
    int child;
    int tmp = std::move(nums[i]);

    for (; i * 2 <= nums.size() - 1; i = child) {
        child = i * 2;
        if (child != nums.size() - 1 && nums[child + 1] < nums[child]) {
            ++child;
        }
        if (nums[child] < tmp) {
            nums[i] = std::move(nums[child]);
        } else {
            break;
        }
    }
    nums[i] = std::move(tmp);
}

void buildHeap(std::vector<int>& nums) {
    for (int i = nums.size() / 2; i > 0; --i) {
        percDown(nums, i);
    }
}



int halfHeapSort(std::vector<int>& nums, int& duration){
    auto startTimer = std::chrono::high_resolution_clock::now(); //start recording time
    nums.push_back(nums[0]); //duplicate the first element to simplify indexing
    buildHeap(nums); 
    int mid = (nums.size() - 2 / 2);
    for (int i = 0; i < mid; i++){
        nums[0] = nums[nums.size() - 1]; //Swap the root with the lat element
        percDown(nums, 1); //Restore the heap properly
    }
    auto endTimer = std::chrono::high_resolution_clock::now(); //end recording time
    duration = std::chrono::duration_cast <std::chrono::milliseconds>(endTimer - startTimer).count();
    return nums[1]; //Return the second smallest element, as the smallest is duplicated
}
