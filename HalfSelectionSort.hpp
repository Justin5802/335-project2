/*
CSCI335 Fall 2023
Assignment 2 – Sorting Algorithms
Name: Justin Chu
Date: 12/16/23
HalfSelectionSort.hpp sorts a given vector using the HalfSelectionSort algorithm
*/

#include <vector>
#include <chrono>
#include <iostream>

int halfSelectionSort(std::vector<int>& nums, int& duration){
    auto startTimer = std::chrono::high_resolution_clock::now(); //start recording time
    if (nums.size() > 50000){  //check if the input size is larger than 50000
        std::cout << "Input is larger than 50,000. Please insert a small input." << std::endl;
        return -1; //return 
    } 
    
    auto middle = nums.begin() + nums.size()/2; //declare the middle iterator
    
    if (nums.size() % 2 == 0){ //if the total size of the input is even, set the middle to the lesser of two elements
        middle = (nums.begin() + nums.size() / 2) - 1;
    }
    //Perform half-selection sort
    for (auto index = nums.begin(); index <= middle; index++){ //Find the minimum element in the remaining unsorted part
        auto minElement = std::min_element(index, nums.end());
        std::iter_swap(index, minElement);
    }
    auto endTimer = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds> (endTimer - startTimer).count();
    
    if (nums.size() % 2 == 0){ //determine the middle element based on input size
        return *(nums.begin() + nums.size() / 2 - 1);
    }
    else{
        return *(nums.begin() + nums.size() / 2);
    }
}
