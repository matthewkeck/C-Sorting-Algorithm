/*******************************************************************************************
*
*   raylib [core] examples - Mouse wheel input
*
*   This test has been created using raylib 1.1 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <bitset>
#include <iomanip>


using namespace std;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

class Line{
private:
    int startPositionX;
    int startPositionY;

    int endPositionX;
    int endPositionY;

    int red = 230;
    int green = 41;
    int blue = 55;
    int other = 255;

    float theta = 0;
    float radius = 0;
    
public:
    void setStartX(int x) { startPositionX = x; }
    void setStartY(int y) { startPositionY = y; }
    Vector2 start = { (float)startPositionX , (float)startPositionY };

    void setEndX(int x) { endPositionX = x; }
    void setEndY(int y) { endPositionY = y; }
    Vector2 end = { (float)endPositionX, (float)endPositionY };

    void setRed(int r) { red = r; }
    void setBlue(int b) { blue = b; }
    void setGreen(int g) { green = g; }
    void setOther(int o) { other = o; }

    void setTheta(float t) { theta = t; }
    void setRadius(float r) { radius = r; }

    int getStartX() { return startPositionX; }
    int getStartY() { return startPositionY; }

    int getEndX() { return endPositionX; }
    int getEndY() { return endPositionY; }

    int getRed() { return red; }
    int getBlue() { return blue; }
    int getGreen() { return green; }
    int getOther() { return other; }

    float getTheta() { return theta; }
    float getRadius() { return radius; }
};

void sort_func(float temperature[], int size_of_array, float* temp_pointer) { // sort function to sort the temps from high to low

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

void merge_sort(float* current_array, int size_of_array) {

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

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input mouse wheel");

    int startPositionY = screenHeight / 2;
    int startPosititonX = screenWidth / 2;
    int endPositionY = screenHeight / 2;
    int endPositionX = screenWidth / 2;

    Vector2 start = { startPosititonX , startPositionY };
    Vector2 end = { endPositionX, endPositionY };
    float thick = 20.0;
    int red = 230;
    int green = 41;
    int blue = 55;
    int other = 255;
    

    float theta = 0;
    float radius = 0;

    Line spiral[32];
    int getArrayLength = sizeof(spiral) / sizeof(int);

    for (int i = 0; i < 32; i++) {
        Color color = { red, green, blue, other };

        spiral[i].setTheta(theta += .1);
        spiral[i].setRadius(theta * 100);
        spiral[i].setOther(other -= 5);

        spiral[i].setEndX((cos(spiral[i].getTheta()) * spiral[i].getRadius()) + spiral[i].getStartX());
        spiral[i].setEndY((sin(spiral[i].getTheta()) * spiral[i].getRadius()) + spiral[i].getStartY());

    }


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        

        for (int i = 0; i < 32; i++) {
            //std::this_thread::sleep_for(std::chrono::seconds(1));

            Color color = { red, green, blue, other };
            DrawLineEx(start, end, thick, color);
            theta += .1;
            radius = theta * 100;
            end = { (cos(theta) * radius) + startPosititonX , (sin(theta) * radius) + startPositionY };
            other -= 5;
        }
        
        red = 230;
        green = 41;
        blue = 55;
        other = 255;
        theta = 0;

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}