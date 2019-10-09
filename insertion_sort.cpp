//
// Created by Chenlin on 4/17/2019.
//
#include "algorithms.h"
void insertion_sort(std::vector<int>& nums){
    for(int i = 0; i < nums.size(); i++){
        int temp = nums[i];
        int j = i;
        while(j > 0 && nums[j-1] > temp){
            nums[j] = nums[j-1];
            j--;
        }
        nums[j] = temp;

    }
}

