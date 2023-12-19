/*
CSCI335 Fall 2023
Assignment 2 – Sorting Algorithms
Name: Justin Chu
Date: 12/16/23
InPlaceMergeSortSort.hpp sorts a given vector using the InPlaceMergeSort algorithm
*/

#include <vector>
#include <chrono>
#include <iostream>

int inPlaceMergeDriver(std::vector<int>& nums, int start, int end){
    if (end - start <= 1){ //Base Case: if the range has one or zero elements, it is already sorted
        return nums[start];
    }
    int mid = start + (end - start)/2; //Caclulate the middle index
    inPlaceMergeDriver(nums, start, mid); //Recursively sort the two halves
    inPlaceMergeDriver(nums, mid, end); //Merge the two sorted halves in place
    std::inplace_merge(nums.begin() + start, nums.begin() + mid, nums.begin() + end);
    return nums[start]; //Return the first element of the merged range
}

int inPlaceMergeSort(std::vector<int>& nums, int& duration){ //Function to call the in-place merge sort driver
    auto startTimer = std::chrono::high_resolution_clock::now(); //Start recording time
    inPlaceMergeDriver(nums, 0, nums.size()); //Call the recursive in-place merge sort function
    auto endTimer = std::chrono::high_resolution_clock::now(); //End recording time
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - startTimer).count(); //Time elapsed
    std::size_t middle = nums.size() / 2; //Calculate the middle index

    return nums.size() % 2 == 0 ? nums[middle - 1] : nums[middle];
}