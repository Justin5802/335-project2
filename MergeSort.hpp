/*
CSCI335 Fall 2023
Assignment 2 – Sorting Algorithms
Name: Justin Chu
Date: 12/16/23
MergeSort.hpp sorts a given vector using the MergeSort algorithm
*/


#include <vector>
#include <chrono>
#include <iostream>

void merge(std::vector<int>& nums, const std::vector<int>& left, const std::vector<int>& right, int& duration){
    auto start = std::chrono::high_resolution_clock::now();
    int i = 0, j = 0, k = 0;
    int leftSize = left.size();
    int rightSize = right.size();
    
    while (i < leftSize && j < rightSize){ //Merge the left and right vectors into the main vector
        if (left[i] <= right[j]){
            nums[k++] = left[i++];
        }
        else{
            nums[k++] = right[j++];
        }
    }
    while (i < leftSize){ //Copy any remaining elements from the left vector
        nums[k++] = left[i++];
    }
    while (j < rightSize){ //Copy any remaining elements from the right vector
        nums[k++] = right[j++];
    }
    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void mergeSortHelper(std::vector<int>& nums, int& duration){
    int length = nums.size();
    if (length < 2){ //Base case: If the vector has fewer than two elements, it is already sorted
        return;
    }
    int middle = length/2; //Calculate the middle index of the vector
    std::vector<int> left(nums.begin(), nums.begin() + middle); //Create left and right vector
    std::vector<int> right(nums.begin() + middle, nums.end());
   
    mergeSortHelper(left, duration); //recursively apply merge sort to the left and right vectors
    mergeSortHelper(right, duration);

    merge(nums, left, right, duration); //merge the sorted left and right vectors back into the original vector
}

int mergeSort(std::vector<int>& nums, int& duration){
    auto startTimer = std::chrono::high_resolution_clock::now();
    mergeSortHelper(nums, duration); //Call the helper function to perform the actual merge sort
    auto endTimer = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - startTimer).count();
    
    int median = nums[nums.size() - 1 / 2]; //Calculate and return the median value of the sorted vector
    return median;
}