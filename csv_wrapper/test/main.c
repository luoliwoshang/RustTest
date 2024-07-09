#include <stdio.h>
#include "csv_wrapper.h"

int main() {
    const char* result = read_csv("data.csv");
    if (result != NULL) {
        printf("CSV Content:\n%s\n", result);
        free_string((char*)result);
    } else {
        printf("Failed to read CSV file.\n");
    }
    return 0;
}
