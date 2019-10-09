//
// Created by Chenlin on 4/17/2019.
//
#include "algorithms.h"

void bubble_sort(std::vector<int>& nums){
    for(int i = 0; i < nums.size(); i++ ){
        for(int j = 1; j < nums.size() - i; j++){
            if(nums[j-1] > nums[j]){
                int temp = 0;
                temp = nums[j];
                nums[j] = nums[j-1];
                nums[j-1] = temp;
            }
        }
    }
}
