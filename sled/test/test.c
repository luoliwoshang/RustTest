#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sled.h"
int main()
{
    // void *config = NULL;
    printf("Creating config...\n");

    void *config = sled_create_config();

    printf("Config created: %p\n", config);
    if (config == NULL)
    {
        printf("Failed to create config\n");
        return 1;
    }

    printf("Setting path...\n");
    const char *path = "./db";
    char *path_copy = strdup(path); // 创建路径的副本
    if (!path_copy)
    {
        fprintf(stderr, "Failed to allocate memory for path\n");
        sled_free_config(config);
        return 1;
    }

    config = sled_config_set_path(config, path_copy);
    printf("Path set, new config: %p\n", config);
    if (config == NULL)
    {
        printf("Failed to set path\n");
        return 1;
    }

    printf("Opening database...\n");

    // free(config); mock error

    void *db = sled_open_db(config);
    printf("Database opened: %p\n", db);
    if (db == NULL)
    {
        printf("Failed to open database\n");
        sled_free_config(config);
        return 1;
    }

    const char *key = "hello";
    const char *value = "world";
    printf("Setting key-value pair...\n");
    sled_set(db, (const unsigned char *)key, strlen(key), (const unsigned char *)value, strlen(value));
    printf("Key-value pair set\n");

    size_t vallen;
    printf("Getting value...\n");
    char *retrieved_value = sled_get(db, key, strlen(key), &vallen);
    if (retrieved_value != NULL)
    {
        printf("Retrieved value: %.*s\n", (int)vallen, retrieved_value);
        printf("Freeing retrieved value...\n");
        sled_free_buf(retrieved_value, vallen);
        printf("Retrieved value freed\n");
    }
    else
    {
        printf("Key not found\n");
    }

    printf("Deleting key...\n");
    sled_del(db, key, strlen(key));
    printf("Key deleted\n");

    printf("Getting value after deletion...\n");
    retrieved_value = sled_get(db, key, strlen(key), &vallen);
    if (retrieved_value == NULL)
    {
        printf("Key successfully deleted\n");
    }
    else
    {
        printf("Deletion failed, value: %.*s\n", (int)vallen, retrieved_value);
        printf("Freeing retrieved value...\n");
        sled_free_buf(retrieved_value, vallen);
        printf("Retrieved value freed\n");
    }

    printf("Closing database...\n");
    sled_close(db);
    printf("Database closed\n");
    return 0;
}