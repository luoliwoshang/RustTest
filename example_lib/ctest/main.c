#include "example_lib.h"
#include <stdio.h>

int main()
{
    int arr[] = {5, 3, 2, 4, 1};
    sort(arr, 5);

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
