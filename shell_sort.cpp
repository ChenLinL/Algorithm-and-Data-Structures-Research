//
// Created by Chenlin on 4/17/2019.
//
#include "project1.h"
void shell_sort(std::vector<int>& nums, const std::vector<int>& gaps){
    for(int gap = 0; gap < gaps.size(); gap++){
        for(int i = gaps[gap]; i < nums.size(); i++){
            int temp = nums[i];
            int j = i;
            while( j >= gaps[gap] && temp < nums[j - gaps[gap]]) {
                //cout<<"change the number: "<<nums[j]<<" with the number: "<<nums[j -]
                nums[j] = nums[j - gaps[gap]];
                j -= gaps[gap];
            }
            nums[j] = temp;

        }
    }

}
