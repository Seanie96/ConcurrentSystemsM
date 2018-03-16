#include <omp.h>
#include <sys/time.h>
#include <bits/stdc++.h>

using namespace std;

vector<int> array(100000);

int linearsearch(int size, int x) {
    int y = -1;
    int i;
    /*
       make the for loop parallel.. static (each thread being assigned a chunk
       of iterations to execute)... with 12 threads to be used.
     */
    /*
       There could be duplicates of the element x in the array, and hence get
       a different value returned some times you run it.
       I create this critical section so that there is no race conditions.
       Since y is a shared variable.
     */
#pragma omp parallel for num_threads(12)
    for(i = 0; i < size; i++) {
        if(array[i] == x) {
#pragma omp parallel
            {
#pragma omp critical
                y = i;
            }
        }
    }   
    return y;
}

int main() {

    /*
       Read in csv file of random numbers.
     */
    ifstream file("100000.csv");
    string value;
    int index = 0;
    while(file.good()) {
        getline(file, value, ',');
        const char* num = value.c_str();
        array[index++] = atoi(num);
    }

    // looking for this value 
    int x = 193;
    long average = 0;
    for(int i = 0; i < 1000; i++) {
        struct timeval start, end;
        /*
           start clock
         */
        gettimeofday(&start, NULL);
        int result = linearsearch(100000, x);

        /*
           end clock
         */
        gettimeofday(&end, NULL);
        average += (((end.tv_sec - start.tv_sec) * 1000000L + end.tv_usec) - start.tv_usec);
        //      printf("\nTime taken %ld ms \n", (((end.tv_sec - start.tv_sec) * 1000000L + end.tv_usec) - start.tv_usec)); 

        if (result == -1) {
            return 1;
        }
    }
    average = average / 1000;
    //    printf("average: %ldms", average);
    return 0;
}
