#include <stdio.h>
#include "../csv_wrapper.h"

int main() {
    // 创建一个 CSV 读取器
    void* reader = csv_reader_new("data.csv");
    if (reader != NULL) {
        const char* record;
        // 循环读取每一行
        while ((record = csv_reader_read_record(reader)) != NULL) {
            printf("%s", record);
            free_string((char*)record); // 释放由 Rust 分配的字符串
        }
        csv_reader_free(reader); // 释放 CSV 读取器
    } else {
        printf("Failed to create CSV reader.\n");
    }
    return 0;
}
