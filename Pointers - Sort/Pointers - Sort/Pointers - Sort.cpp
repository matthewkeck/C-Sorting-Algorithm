// Pointers - Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
// matthew r keck

#include <iostream>
#include <iostream>
#include <bitset>
#include <iomanip>

using namespace std; 

float temperature[] = { 62.5, 77.5, 83.1, 89.1, 92.1, 83.2, 72.3, 61.4, 62.4, 75.5, 83.1, // global varable in order to pass the array to functions
                        89.7, 90.1, 80.2, 70.3, 60.4, 77.5, 83.1, 89.1, 92.1, 83.2,
                        72.3, 61.4, 62.4, 75.5, 83.1, 89.7, 90.1, 80.2, 70.3, 60.4 };

void sort_func(float* temp_pointer) { // sort function to sort the temps from high to low

    float largest_temp, prev_temp; // local varbles to save the largest temp and the prev temp

    for (int i = 0; i < sizeof(temperature) / 4; i = i + 1) { // for loop to iterate the size of temperature and increment by one
        temp_pointer = &temperature[i]; // sets temp_pointer to where i is in the array
        largest_temp = *temp_pointer; // sets largest temp equal to temp pointer at i
        
        for (int j = i; j < (sizeof(temperature) / 4); j = j + 1) { // for loop starts at i and iterates the size of temperature again and inrement by one

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

int main() // prints results of the array and calls sort function
{
    
    float* temp_pointer = NULL; // declares pointer and sets it to nothing
    temp_pointer = &temperature[0];// sets the pointer adress to temerature indice 0

    for (temp_pointer = &temperature[0]; temp_pointer < &temperature[size(temperature)]; ++temp_pointer) { // for loop to print the adress, value and bitsize of the array
        cout << temp_pointer << "\t" << *temp_pointer << "\t" << bitset<8>(*temp_pointer) << endl;
    }

    sort_func(temp_pointer); // calls sort function

    cout << endl; // prints new line to seperate unsorted from sorted

    for (temp_pointer = &temperature[0]; temp_pointer < &temperature[size(temperature)]; ++temp_pointer) {// for loop to print the adress, value and bitsize of the array
        cout << temp_pointer << "\t" << *temp_pointer << "\t" << bitset<8>(*temp_pointer) << endl;
    }
}
