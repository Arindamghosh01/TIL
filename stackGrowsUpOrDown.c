/* 
    https://www.youtube.com/watch?v=V2h_hJ5MSpY

    stack - CPU creates region of memory known as stack frame
    to store local memory.
    In most computer architecture stack grows down or negetive

    Intel architecture the stack grows down.
    We have to write a function to determine if our architecture the 
    stack grows up or down.
 */

#include <stdio.h>
#include <stdbool.h>

// CPU may use optimization here 
bool upordown() {
    // The volatile keyword is intended to prevent the compiler from applying any 
    // optimizations on objects that can change in ways that cannot be determined by the compiler
    volatile int x, y = 0;

    return &x > &y;
}

// Correct approach
// compared the new stack frame to the old one.
bool diff(int *other) {
    int x;

    if (!other) {
        return diff(&x);
    } else {
        return &x > other;
    }
}

int main(int argc, char** argv) {
    printf("%s\n", upordown() ? "Up" : "Down");
    printf("%s\n", diff(NULL) ? "Up" : "Down");
    return 0;
}
