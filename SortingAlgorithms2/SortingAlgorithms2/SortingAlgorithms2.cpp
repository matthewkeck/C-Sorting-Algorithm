// SortingAlgorithms2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>
#include <iomanip>
#include <vector>

using namespace std;

void sort_func(float temperature [],int size_of_array, float* temp_pointer) { // sort function to sort the temps from high to low

    float largest_temp, prev_temp; // local varbles to save the largest temp and the prev temp

    for (int i = 0; i < size_of_array; i = i + 1) { // for loop to iterate the size of temperature and increment by one
        temp_pointer = &temperature[i]; // sets temp_pointer to where i is in the array
        largest_temp = *temp_pointer; // sets largest temp equal to temp pointer at i

        for (int j = i; j < size_of_array; j = j + 1) { // for loop starts at i and iterates the size of temperature again and inrement by one

            if (largest_temp < *temp_pointer) { // if statment to compaire largest temp to temp if pointer is smaller then largest temp it skips the steps

                prev_temp = largest_temp; // saves previous largest temp
                largest_temp = *temp_pointer; // grabs new largest temp
                *(temp_pointer - j + i) = largest_temp; // moves largest temp to the top of the array
                *temp_pointer = prev_temp; // temp pointer takes the smaller temp and moves it to where the larger temp was

            }

temp_pointer++; // increments pointer
        }
    }
}

void bubble_sort(float temperature[], int size_of_array) {
    float prev_temp;
    int comparison;
    for (int i = 0; i < size_of_array - 1; i = i + 1) {
        comparison = 0;
        for (int j = 0; j < size_of_array; j = j + 1) {

            if (temperature[j] < temperature[j + 1]) {
                prev_temp = temperature[j];
                temperature[j] = temperature[j + 1];
                temperature[j + 1] = prev_temp;
                comparison++;

            }

        }
        if (comparison == 0) {
            break;
        }
    }
}

// must fix
void my_swap(float current_array[], int left_pointer, int right_pointer, int pivot) {
    float temp_value = current_array[left_pointer];
    current_array[left_pointer] = current_array[pivot];
    current_array[pivot] = temp_value;
}
// must fix
int my_partion(float current_array[], int left_pointer, int right_pointer, int pivot) {
    while (left_pointer < right_pointer) {

        while (current_array[left_pointer] >= current_array[pivot] && left_pointer < right_pointer) {
            left_pointer = left_pointer + 1;
        }
        while (current_array[right_pointer] <= current_array[pivot] && left_pointer < right_pointer) {
            right_pointer = right_pointer - 1;
        }

        my_swap(current_array, left_pointer, right_pointer, pivot);

    }

    return left_pointer;
}

// add functions partition and swap. add better pivot selection.
void quick_sort(float current_array[], int lower_bound, int upper_bound) {
    
    if (lower_bound >= upper_bound) {
        return;
    }

    int pivot = upper_bound;
    
    int left_pointer = lower_bound;
    int right_pointer = upper_bound;

    float temp_value;
    while (left_pointer < right_pointer) {

        while (current_array[left_pointer] >= current_array[pivot] && left_pointer < right_pointer) {
            left_pointer = left_pointer + 1;
        }
        while (current_array[right_pointer] <= current_array[pivot] && left_pointer < right_pointer) {
            right_pointer = right_pointer - 1;
        }

        temp_value = current_array[right_pointer];
        current_array[right_pointer] = current_array[left_pointer];
        current_array[left_pointer] = temp_value;

    }

    temp_value = current_array[left_pointer];
    current_array[left_pointer] = current_array[pivot];
    current_array[pivot] = temp_value;

    int index = left_pointer;

    quick_sort(current_array, lower_bound, index - 1);
    quick_sort(current_array, index + 1, upper_bound);

}

void merge(float* current_array, int size_of_array, float* left_array, int left_size, float* right_array, int right_size) {
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left_array[i] >= right_array[j]) {
            current_array[k] = left_array[i];
            i++;
        }
        else {
            current_array[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        current_array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_size) {
        current_array[k] = right_array[j];
        j++;
        k++;
    }

}

void merge_sort(float* current_array,int size_of_array) {

    if (size_of_array < 2) {
        return;
    }

    int mid_index = size_of_array / 2;

    float* left_array = new float[mid_index];
    float* right_array = new float[size_of_array - mid_index];

    for (int i = 0; i < mid_index; i++) {
        left_array[i] = current_array[i];
    }

    for (int i = mid_index; i < size_of_array; i++) {
        right_array[i - mid_index] = current_array[i];
    }

    merge_sort(left_array, mid_index);
    merge_sort(right_array, size_of_array - mid_index);

    //Merge
    merge(current_array, size_of_array, left_array, mid_index, right_array, size_of_array - mid_index);
}



int main() // prints results of the array and calls sort function
{
    float temperature[] = { 60.4 , 77.5, 83.1, 89.1, 92.1, 83.2, 72.3, 61.4, 62.4, 60.4, 83.1, // global varable in order to pass the array to functions
                        89.7, 90.1, 80.2, 70.3, 75.5, 77.5, 83.1, 89.1, 92.1, 83.2,
                        72.3, 61.4, 62.4, 75.5, 83.1, 89.7, 90.1, 80.2, 70.3, 89.6 };

    float* temp_pointer = NULL; // declares pointer and sets it to nothing
    temp_pointer = &temperature[0];// sets the pointer adress to temerature indice 0

    for (temp_pointer = &temperature[0]; temp_pointer < &temperature[size(temperature)]; ++temp_pointer) { // for loop to print the adress, value and bitsize of the array
        cout << temp_pointer << "\t" << *temp_pointer << "\t" << bitset<8>(*temp_pointer) << endl;
    }
    cout << endl;

    int size_of_array = sizeof(temperature) / sizeof(int);

    //sort_func(temperature, size_of_array, temp_pointer);
    //bubble_sort(temperature,size_of_array); // calls sort function

    int left = 0;
    int right = sizeof(temperature) / sizeof(int) - 1;

    //quick_sort(temperature, left, right);
    merge_sort(temperature, size_of_array);

    cout << endl; // prints new line to seperate unsorted from sorted

    for (temp_pointer = &temperature[0]; temp_pointer < &temperature[size(temperature)]; ++temp_pointer) {// for loop to print the adress, value and bitsize of the array
        cout << temp_pointer << "\t" << *temp_pointer << "\t" << bitset<8>(*temp_pointer) << endl;
    }
}

