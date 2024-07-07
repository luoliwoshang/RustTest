// SPDX-License-Identifier: Apache-2.0

#ifndef SLED_H
#define SLED_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Top-level configuration for the system.
 *
 * # Examples
 *
 * ```
 * let _config = sled::Config::default()
 *     .path("/path/to/data".to_owned())
 *     .cache_capacity(10_000_000_000)
 *     .flush_every_ms(Some(1000));
 * ```
 */
typedef struct SledConfig SledConfig;

/**
 * The `sled` embedded database! Implements
 * `Deref<Target = sled::Tree>` to refer to
 * a default keyspace / namespace / bucket.
 *
 * When dropped, all buffered writes are flushed
 * to disk, using the same method used by
 * `Tree::flush`.
 */
typedef struct SledDb SledDb;

/**
 * Create a new configuration.
 */
SledConfig *sled_create_config(void);

/**
 * Destroy a configuration.
 */
void sled_free_config(SledConfig *config);

/**
 * Set the configured file path. The caller is responsible for freeing the path
 * string after calling this (it is copied in this function).
 */
SledConfig *sled_config_set_path(SledConfig *config, const char *path);

/**
 * Set the configured cache capacity in bytes.
 */
SledConfig *sled_config_set_cache_capacity(SledConfig *config, size_t capacity);

/**
 * Configure the use of the zstd compression library.
 */
SledConfig *sled_config_use_compression(SledConfig *config, unsigned char use_compression);

/**
 * Set the configured IO buffer flush interval in milliseconds.
 */
SledConfig *sled_config_flush_every_ms(SledConfig *config, int flush_every);

/**
 * Open a sled lock-free log-structured tree. Consumes the passed-in config.
 */
SledDb *sled_open_db(SledConfig *config);

/**
 * Close a sled lock-free log-structured tree.
 */
void sled_close(SledDb *db);

/**
 * Free a buffer originally allocated by sled.
 */
void sled_free_buf(char *buf, size_t sz);

/**
 * Set a key to a value.
 */
void sled_set(SledDb *db,
              const unsigned char *key,
              size_t keylen,
              const unsigned char *val,
              size_t vallen);

/**
 * Get the value of a key.
 * Caller is responsible for freeing the returned value with `sled_free_buf` if
 * it's non-null.
 */
char *sled_get(SledDb *db, const char *key, size_t keylen, size_t *vallen);

/**
 * Delete the value of a key.
 */
void sled_del(SledDb *db, const char *key, size_t keylen);

/**
 * Compare and swap.
 * Returns 1 if successful, 0 if unsuccessful.
 * Otherwise sets `actual_val` and `actual_vallen` to the current value,
 * which must be freed using `sled_free_buf` by the caller if non-null.
 * `actual_val` will be null and `actual_vallen` 0 if the current value is not
 * set.
 */
unsigned char sled_compare_and_swap(SledDb *db,
                                    const char *key,
                                    size_t keylen,
                                    const unsigned char *old_val,
                                    size_t old_vallen,
                                    const unsigned char *new_val,
                                    size_t new_vallen,
                                    const unsigned char **actual_val,
                                    size_t *actual_vallen);

#endif /* SLED_H */