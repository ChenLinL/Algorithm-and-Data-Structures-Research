//
// Created by Chenlin on 4/17/2019.
//
#include "algorithms.h"
#include <iostream>
#include <chrono>
#include <random>

using namespace std;
bool sorted(const std::vector<int>& nums){
    for(int i = 0; i < nums.size(); i++){
        if((i+1 < nums.size()) && (nums[i] > nums[i+1])){
            return false;
        }
        else{
            if(i+1 >= nums.size()){
                continue;
            }
        }
    }
    return true;
}
mt19937 get_the_seed(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    return mt19937(seed);
}
int randInt(mt19937 mt, int lb, int ub){
    return uniform_int_distribution<int>(lb,ub)(mt);
}
void spin_the_bottle_sort(std::vector<int>& nums){
    while(!sorted(nums)) {
        for (int i = 0; i < nums.size(); i++) {
            mt19937 mt = get_the_seed();
            //std::uniform_int_distribution<> distr(0, nums.size());
            int n =  randInt(mt,0, nums.size());
            if ((i < n && nums[i] > nums[n]) || (i > n && nums[i] < nums[n])) {
                int temp = nums[i];
                nums[i] = nums[n];
                nums[n] = temp;
            }
        }
    }
}
