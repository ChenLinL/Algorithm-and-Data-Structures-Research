//
// Created by Chenlin on 4/22/2019.
//
#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <random>
#include <vector>
using namespace std;

int min_num(int ln, int rn){
    if(ln < rn){
        return ln;
    }
    return rn;
}
int max_num(int ln, int rn){
    if(ln > rn){
        return ln;
    }
    return rn;
}
mt19937 get_seed(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    return mt19937(seed);
}
int rand_int(mt19937 mt, int lb, int ub){
    return uniform_int_distribution<int>(lb,ub)(mt);
}
void annealing_sort(std::vector<int>& nums, const std::vector<int>& temps, const std::vector<int>& reps){
    for(int j = 0; j<temps.size(); j++){
        for(int i = 0; i < nums.size()-1; i++){
            for(int k = 0; k < reps[j]; k++ ){
                mt19937 mt = get_seed();
                //out<<"i"<<i+1<<endl;
                //couct<<nums.size()<<endl;
                //cout<<i+temps[j]<<endl;
                //cout<<min_num(nums.size(),i+temps[j])<<endl;
                //std::uniform_int_distribution<> distr(i+1, min_num(nums.size(),i+temps[j]));
                int s = rand_int(mt,i+1, min_num(nums.size(),i+temps[j]));
                //cout<<"s is:"<<s<<endl;
                if(nums[i] > nums[s]) {
                    int temp = nums[i];
                    nums[i] = nums[s];
                    nums[s] = temp;
                }
            }
        }
        for(int i = nums.size(); i >1; i--){
            for(int k = 0; k < reps[j]; k++){
                mt19937 mt = get_seed();
                int s = rand_int(mt,max_num(1, i - temps[j]), i - 1);
                if (nums[s] > nums[i]) {
                    int temp = nums[s];
                    nums[s] = nums[i];
                    nums[i] = temp;

                }
            }
        }
    }
}
