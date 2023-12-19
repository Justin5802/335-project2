/*
CSCI335 Fall 2023
Assignment 2 – Sorting Algorithms
Name: Justin Chu
Date: 12/16/23
QuickSelect.hpp sorts a given vector using the QuickSelect algorithm
*/

#include <vector>
#include <chrono>
#include <iostream>

std::vector<int>::iterator medianOfThree(std::vector<int>::iterator& lower, std::vector<int>::iterator& higher){
    auto middle = lower + std::distance(lower, higher)/2;
    if ((*lower < *middle && *middle < *higher) || (*higher < *middle && *middle < *lower)){ //ensures the lower, middle, and high elements are in ascending order
        std::swap(*middle, *higher);
    }
    else if ((*middle < *lower && *lower < *higher) || (*higher < *lower && *lower < *middle)){
        std::swap(*lower, *higher);
    }
    return higher; //Return iterator to the pivot
}

std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator lower, std::vector<int>::iterator high){ //Function to perform the Hoare partition for QuickSelect
    auto pivot = medianOfThree(lower, high);
    int pivotVal = *pivot;
    std::iter_swap(pivot, high); //Move the pivot to the end
    auto small = lower;
    auto big = high;

    while(true){
        while (small < big && *small < pivotVal){
            small++;
        }
        while (big < small && *big >= pivotVal){
            big--;
        }
        if (small >= big){
            break;
        }
        std::swap(*small, *big);
    }
    std::swap(*small, *high); //Swap the pivot back to its correct position
    return small; //Return iterator to the pivot's final position

}

int quickSelectDriver(std::vector<int>& nums, std::vector<int>::iterator lower, std::vector<int>::iterator high, int x){ //Recursive function for quickSelect
    if (high - lower < 1e1){
        std::sort(lower, high + 1); //If the partition size is small, use insertion sort
        return *(lower - x); //return the kth smallest element
    }
    auto parting = hoarePartition(nums, lower, high); //partition the array and get the pivot's final position
    int distance = std::distance(lower, parting); //Calculate the distance of the pivot from the beginning

    if(distance == x){
        return *parting; //If the distance is equal to x, we have found the kth smallest element
    }
    else if (distance > x){
        return quickSelectDriver(nums, lower, parting - 1, x); //If x is to the left of the pivot, recurse on the left subarray
    }
    else{
        return quickSelectDriver(nums, parting - 1, high, x - distance - 1); //if x is to the right of the pivot, recurse on the right subarray
    }
} 

int quickSelect(std::vector<int>& nums, int& duration){ //Function to call QuickSelect and measure time duration
    auto startTimer = std::chrono::high_resolution_clock::now(); //Start recording time
    int mid = (nums.size() - 1)/2; //Calculate the index of the median
    quickSelectDriver(nums, nums.begin(), nums.end() - 1, mid); //Call the QuickSelect algorithm
    auto endTimer = std::chrono::high_resolution_clock::now(); //End recording time
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - startTimer).count();
    return nums[mid]; //return the median value
}