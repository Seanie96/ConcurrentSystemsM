#include <bits/stdc++.h>
#include <sys/time.h>
#include <omp.h>

using namespace std;

void merge_together(int array[], int left, int middle, int right);
void merge_sort(int array[], int left, int right);

int main(int argc, char **argv) {

    /* 
       Read in csv file of random numbers.
     */
    ifstream file("100000.csv");
    string value;
    int array[100000];
    int index = 0;
    while(file.good()) {
        getline(file, value, ',');
        const char* num = value.c_str();
        array[index++] = atoi(num);
    }

    long average = 0;
    /*
       Run the algorithm a 1000 times and then divide by
       1000 afterwards to get averagei time taken.
     */
    for(int i = 0; i < 1000; i++) { 
        struct timeval start_t, end_t;
        /*
           Start clock
         */
        gettimeofday(&start_t, NULL);
        int array_size = sizeof(array)/sizeof(array[0]);
        /*
           Merge-sort algorithm
         */ 
        merge_sort(array, 0, array_size - 1);

        /*
           End clock
         */

        gettimeofday(&end_t, NULL);
        /*
           add elapsed time to average variable
         */
        average += ((end_t.tv_sec * 1000000 + end_t.tv_usec) - (start_t.tv_sec * 1000000 + start_t.tv_usec));
        //printf("\nTime taken: %ld ms\n", ((end_t.tv_sec * 1000000 + end_t.tv_usec)
        //            - (start_t.tv_sec * 1000000 + start_t.tv_usec))); 
        for(int i = 0; i < 100000; i++) {
            if(!(array[i - 1] <= array[i])) {
                /*  exit if the array is not sorted correctly   */
                return 1;
            }
        }
    }
    average = average / 1000;
    //cout << "average: " << average << endl;
    return 0;
}

void merge_together(int array[], int left, int middle, int right) {
    int x = 0;
    int y = 0;
    int a = middle - left + 1;
    int b =  right - middle;
    int left_arr[a], right_arr[b];
    for (x = 0; x < a; x++) {
        left_arr[x] = array[left + x];
    }
    for (y = 0; y < b; y++) {
        right_arr[y] = array[middle + y + 1];
    }

    int i = 0;
    int j = 0;
    int k = left; 
    while (i < a && j < b) {
        if (left_arr[i] <= right_arr[j]) {
            array[k] = left_arr[i];
            i++;
        }   else    {
            array[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < a)  {
        array[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < b)  {
        array[k] = right_arr[j];
        j++;
        k++;
    }
}

void merge_sort(int array[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);
        merge_together(array, left, middle, right);
    }
}
