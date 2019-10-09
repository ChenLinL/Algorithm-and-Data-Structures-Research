#include <iostream>
#include "algorithms.h"
#include "bubble_sort.cpp"
#include "insertion_sort.cpp"
#include "shell_sort.cpp"
#include "spin_the_bottle_sort.cpp"
#include "annealing_sort.cpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <random>
#include <vector>
#include <math.h>

using namespace std;
struct timing{
    int n;
    double seconds;
};
void create_empty_timings_file(string filename){
    ofstream f;
    f.open(filename, ios::trunc);
    f << "funcname,n,seconds\n";
    f.close();
}
void add_timings_to_file(string funcname, timing t, string filename){
    ofstream f;
    f.open(filename,ios::app);
    f<< funcname <<","<<t.n<<","<<t.seconds<<"\n";
    f.close();
}


mt19937 get_mersenne_twister_genreator_with_current_time_seed(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    return mt19937(seed);
}
uniform_int_distribution<int> get_uniform_int_generator(int lb, int ub){
    return uniform_int_distribution<int>(lb,ub);
}
int randint(mt19937 mt, int lb, int ub){
    return uniform_int_distribution<int>(lb,ub)(mt);
}
void shuffle_vector(vector<int>& nums){
    for(int i = nums.size(); i >= 0; i--){
        mt19937 mt = get_mersenne_twister_genreator_with_current_time_seed();
        int j = randint(mt,0,i);
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}

vector<int> almost_random_generate(int n){
    int pair_num = 2*log2(n);
    vector<int> nums;
    for(int i = 0; i < n; i++){
        nums.push_back(i);
    }
    for(int j = 0; j < pair_num; j++){
        mt19937 mt = get_mersenne_twister_genreator_with_current_time_seed();
        int x = randint(mt,0,n-1);
        mt19937 mt1 = get_mersenne_twister_genreator_with_current_time_seed();
        int y = randint(mt1,0,n-1);
        int temp = nums[x];
        nums[x] = nums[y];
        nums[y] = temp;
    }
    return nums;
}
timing bubble_sort_time(int n, int reps){
    vector<int> nums;
    for(int i = 0; i < n; i++){
        nums.push_back(i);
    }
    shuffle_vector(nums);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        bubble_sort(nums);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
    timing t;
    t.n = n;
    t.seconds = (double)total_time/reps;
   //cout<<t.seconds;
    return t;
}
timing insertion_sort_time(int n, int reps){
    vector<int> nums;
    for(int i = 0; i < n; i++){
        nums.push_back(i);
    }
    shuffle_vector(nums);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        insertion_sort(nums);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
    timing t;
    t.n = n;
    t.seconds = (float)total_time/reps;
    return t;
}
timing shell_1_sort_time(int n, int reps){
    vector<int> nums;
    //vector<int> gaps{511,255,127,63,31,15,7,3,1};
    vector<int> gaps{1073,281,77,23,8,1};
    for(int i = 0; i < n; i++){
        nums.push_back(i);
    }
    shuffle_vector(nums);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        shell_sort(nums,gaps);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
//    for(int i = 0; i<nums.size(); ++i){
//        cout<<nums[i]<<endl;
//    }
    timing t;
    t.n = n;
    t.seconds = (float)total_time/reps;
    return t;
}
timing shell_2_sort_time(int n, int reps){
    vector<int> nums;
    vector<int> gaps{511,255,127,63,31,15,7,3,1};
    //vector<int> gaps{1073,281,77,23,8,1};
    for(int i = 0; i < n; i++){
        nums.push_back(i);
    }
    shuffle_vector(nums);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        shell_sort(nums,gaps);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
//    for(int i = 0; i<nums.size(); ++i){
//        cout<<nums[i]<<endl;
//    }
    timing t;
    t.n = n;
    t.seconds = (float)total_time/reps;
    return t;
}
timing spin_the_bottle_sort_time(int n, int reps){
    vector<int> nums;
    for(int i = 0; i < n; i++){
        nums.push_back(i);
    }
    shuffle_vector(nums);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        spin_the_bottle_sort(nums);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
//    for(int i = 0; i<nums.size(); ++i){
//        cout<<nums[i]<<endl;
//    }
    timing t;
    t.n = n;
    t.seconds = (float)total_time/reps;
    return t;
}
timing annealing_sort_time(int n, int rep){
    vector<int> nums;
    //vector<int> temps{1000,500,250,125,65,33,17,9,5,4,2,1};//first implementation
    vector<int> temps{1024,512,256,128,64,32,16,8,1};//second implementation
    vector<int> reps{2,2,2,2,2,2,2,2,2,2,2,2,2};
    for(int i = 0; i < n; i++){
        nums.push_back(i);
    }
    shuffle_vector(nums);

    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < rep; i++){
        clock_t c_start = clock();
        annealing_sort(nums,temps,reps);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
    int i =0;
//    for(i = 0; i<nums.size(); ++i){
//        cout<<nums[i]<<endl;
//    }
//    cout<<"i: "<<i<<endl;
    timing t;
    t.n = n;
    t.seconds = (float)total_time/rep;
    cout<<t.seconds<<endl;
    return t;
}
timing almost_bubble_sort_time(int n, int reps){
    vector<int> nums;
    nums = almost_random_generate(n);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        bubble_sort(nums);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
    timing t;
    t.n = n;
    t.seconds = (double)total_time/reps;
    //cout<<t.seconds;
    return t;
}
timing almost_insertion_sort_time(int n, int reps){
    vector<int> nums;
    nums = almost_random_generate(n);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        insertion_sort(nums);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
    timing t;
    t.n = n;
    t.seconds = (float)total_time/reps;
    return t;
}
timing almost_shell_1_sort_time(int n, int reps){
    vector<int> nums;
    //vector<int> gaps{511,255,127,63,31,15,7,3,1};
    vector<int> gaps{1073,281,77,23,8,1};
    nums = almost_random_generate(n);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        shell_sort(nums,gaps);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
//    for(int i = 0; i<nums.size(); ++i){
//        cout<<nums[i]<<endl;
//    }
    timing t;
    t.n = n;
    t.seconds = (float)total_time/reps;
    return t;
}
timing almost_shell_2_sort_time(int n, int reps){
    vector<int> nums;
    vector<int> gaps{511,255,127,63,31,15,7,3,1};
    //vector<int> gaps{1073,281,77,23,8,1};
    nums = almost_random_generate(n);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        shell_sort(nums,gaps);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
//    for(int i = 0; i<nums.size(); ++i){
//        cout<<nums[i]<<endl;
//    }
    timing t;
    t.n = n;
    t.seconds = (float)total_time/reps;
    return t;
}
timing almost_spin_the_bottle_sort_time(int n, int reps){
    vector<int> nums;
    nums = almost_random_generate(n);
    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < reps; i++){
        clock_t c_start = clock();
        spin_the_bottle_sort(nums);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
//    for(int i = 0; i<nums.size(); ++i){
//        cout<<nums[i]<<endl;
//    }
    timing t;
    t.n = n;
    t.seconds = (float)total_time/reps;
    return t;
}
timing almost_annealing_sort_time(int n, int rep){
    vector<int> nums;
    //vector<int> temps{1000,500,250,125,65,33,17,9,5,4,2,1};//first implementation
    vector<int> temps{1024,512,256,128,64,32,16,8,1};//second implementation
    vector<int> reps{2,2,2,2,2,2,2,2,2,2,2,2,2};
    nums = almost_random_generate(n);

    double total_time = 0.0;
    vector<int> rvec;
    for(int i = 0; i < rep; i++){
        clock_t c_start = clock();
        annealing_sort(nums,temps,reps);
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start)/CLOCKS_PER_SEC;
    }
    int i =0;
//    for(i = 0; i<nums.size(); ++i){
//        cout<<nums[i]<<endl;
//    }
//    cout<<"i: "<<i<<endl;
    timing t;
    t.n = n;
    t.seconds = (float)total_time/rep;
    cout<<t.seconds<<endl;
    return t;
}
int main() {

//    for(int i = 0; i<numbers.size(); ++i){
//        cout<<numbers[i]<<endl;
//    }


    vector<int> numbers{5,4,2,6,8,7,9,1,3};
    //vector<int> temps{4,4,2,2,1,1};
    //vector<int> reps{2,2,2,2,2,2};
    //bubble_sort(numbers);
    //annealing_sort(numbers,temps,reps);
    std::cout << "Hello, Worvector<int> gaps{3,1};ld!" << std::endl;
    //insertion_sort(numbers);
    //shell_sort(numbers,gaps);
    //spin_the_bottle_sort(numbers);
    //for(int i = 0; i<numbers.size(); ++i){
        //cout<<numbers[i]<<endl;
    //}
    //create_empty_timings_file("bubble_timings.csv");
    //create_empty_timings_file("insert_timings.csv");
    //create_empty_timings_file("shell_1_timings.csv");
    //create_empty_timings_file("shell_2_timings.csv");
    //create_empty_timings_file("spin_timings.csv");
    //create_empty_timings_file("almost_bubble_timings.csv");
    //create_empty_timings_file("almost_insert_timings.csv");
    //create_empty_timings_file("almost_shell_1_timings.csv");
    //create_empty_timings_file("almost_shell_2_timings.csv");
    //create_empty_timings_file("almost_spin_timings.csv");
    create_empty_timings_file("anealing_timings.csv");
    create_empty_timings_file("almost_anealing_timings.csv");
    timing t;
//    annealing_sort_time(10000,3);
    //spin_the_bottle_sort_time(100,1);
    for(int n = 10; n <= 2560; n *= 2){
        t = annealing_sort_time(n,3);
        add_timings_to_file("annealing_sort",t,"anealing_timings.csv");
        t = bubble_sort_time(n,3);
        add_timings_to_file("bubble_sort",t,"bubble_timings.csv");
        t = insertion_sort_time(n,3);
        add_timings_to_file("insertion_sort_time",t,"insert_timings.csv");
        t = shell_1_sort_time(n,3);
        add_timings_to_file("shell_sort",t,"shell_1_timings.csv");
        t = shell_2_sort_time(n,3);
        add_timings_to_file("shell_sort",t,"shell_2_timings.csv");
        t = spin_the_bottle_sort_time(n,3);
        add_timings_to_file("spin_the_bottle_sort",t,"spin_timings.csv");
    }

    for(int n = 10; n <= 2560; n *= 2) { //almost sorted numbers
        t = almostannealing_sort_time(n,3);
        add_timings_to_file("annealing_sort",t,"timings.csv");
        t = almost_bubble_sort_time(n,3);
       add_timings_to_file("bubble_sort",t,"almost_bubble_timings.csv");
       t = almost_insertion_sort_time(n,3);
        add_timings_to_file("insertion_sort_time",t,"almost_insert_timings.csv");
        t = almost_shell_1_sort_time(n,3);
        add_timings_to_file("shell_sort",t,"almost_shell_1_timings.csv");
        t = almost_shell_2_sort_time(n,3);
        add_timings_to_file("shell_sort",t,"almost_shell_2_timings.csv");
        t = almost_spin_the_bottle_sort_time(n,3);
        add_timings_to_file("spin_the_bottle_sort",t,"almost_spin_timings.csv");
        t = almost_annealing_sort_time(n,3);
        add_timings_to_file("anealing_sort",t,"almost_anealing_timings.csv");
    }
    //t = bubble_sort_time(100000,3);
    //cout<<t.seconds<<endl;
    return 0;
}
