#include <sys/time.h>
#include <bits/stdc++.h>

using namespace std;

vector<int> array(100000);

int linearsearch(int size, int x) {
    int y = -1;
    /*  
        I did not break out of the for loop when the element is found, because 
        in the parallel version, when an element is found it is impossible
        to break out of the for loop. Hence I wanted to make this a consistent feature
        and hence get a better read on the elapsed times.
     */
    int i;
    for(i = 0; i < size; i++) {
        if(array[i] == x) {
            y = i;
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

        //printf("\nTime taken %ld ms \n", (((end.tv_sec - start.tv_sec) * 1000000L + end.tv_usec) - start.tv_usec)); 

        /*
           if element not found then there was an error, and program stops.
         */
        if (result == -1) {
            return 1;
        }
    }
    average = average / 1000;
    //printf("average: %ldms", average);
    return 0;
}
