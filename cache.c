/*
 * cache.c
 *
 * 20493-02 Computer Architecture
 * Term Project on Implentation of Cache Mechanism
 *
 * Skeleton Code Prepared by Prof. HyungJune Lee
 * Nov 13, 2017
 *
 */


#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cache_impl.h"

extern int num_cache_hits;
extern int num_cache_misses;

extern int num_bytes;
extern int num_access_cycles;

extern int global_timestamp;

cache_entry_t cache_array[CACHE_SET_SIZE][DEFAULT_CACHE_ASSOC];
int memory_array[DEFAULT_MEMORY_SIZE_WORD];


/* DO NOT CHANGE THE FOLLOWING FUNCTION */
void init_memory_content() { /*memory_array initialization*/
    unsigned char sample_upward[16] = {0x001, 0x012, 0x023, 0x034, 0x045, 0x056, 0x067, 0x078, 0x089, 0x09a, 0x0ab, 0x0bc, 0x0cd, 0x0de, 0x0ef};
    unsigned char sample_downward[16] = {0x0fe, 0x0ed, 0x0dc, 0x0cb, 0x0ba, 0x0a9, 0x098, 0x087, 0x076, 0x065, 0x054, 0x043, 0x032, 0x021, 0x010};
    int index, i=0, j=1, gap = 1;
    
    for (index=0; index < DEFAULT_MEMORY_SIZE_WORD; index++) {
        memory_array[index] = (sample_upward[i] << 24) | (sample_upward[j] << 16) | (sample_downward[i] << 8) | (sample_downward[j]);
        if (++i >= 16)
            i = 0;
        if (++j >= 16)
            j = 0;
        
        if (i == 0 && j == i+gap)
            j = i + (++gap);
            
        printf("mem[%d] = %#x\n", index, memory_array[index]);
    }
}   

/* DO NOT CHANGE THE FOLLOWING FUNCTION */
void init_cache_content() { /*cache_array initialization*/
    int i, j;
    
    for (i=0; i<CACHE_SET_SIZE; i++) {
        for (j=0; j < DEFAULT_CACHE_ASSOC; j++) {
            cache_entry_t *pEntry = &cache_array[i][j];
            pEntry->valid = 0;
            pEntry->tag = -1;
            pEntry->timestamp = 0;
        }
    }
}

/* DO NOT CHANGE THE FOLLOWING FUNCTION */
/* This function is a utility function to print all the cache entries. It will be useful for your debugging */
void print_cache_entries() {
    int i, j, k;
    
    for (i=0; i<CACHE_SET_SIZE; i++) {
        printf("[Set %d] ", i);
        for (j=0; j <DEFAULT_CACHE_ASSOC; j++) {
            cache_entry_t *pEntry = &cache_array[i][j];
            printf("V: %d Tag: %#x Time: %d Data: ", pEntry->valid, pEntry->tag, pEntry->timestamp);
            for (k=0; k<DEFAULT_CACHE_BLOCK_SIZE_BYTE; k++) {
                printf("%#x(%d) ", pEntry->data[k], k);
            }
            printf("\t");
        }
        printf("\n");
    }
}


int check_cache_data_hit(void *addr, char type) {
	num_access_cycles += CACHE_ACCESS_CYCLE; /*increase access cycle as much as cache access cycle*/

	int block_addr = (int)addr / DEFAULT_CACHE_BLOCK_SIZE_BYTE;
	int byte_offset = (int)addr % DEFAULT_CACHE_BLOCK_SIZE_BYTE;
	int set = block_addr % CACHE_SET_SIZE;
	int tag = block_addr / CACHE_SET_SIZE;
	int entry = 0;
	int accessed_data = 0; /*accessed data*/
	int data_size = 0; /*size of a data that program should read*/

	/*determine data size according to datatype*/
	if (type == 'b') {
		data_size = 1;
	}

	else if (type == 'h') {
		data_size = 2;
	}

	else {
		data_size = 4;
	}

	num_bytes += data_size; /*increase num of bytes as much as data size*/

	/*Find any matching data in the cache*/
	for (int entry = 0; entry < DEFAULT_CACHE_ASSOC; entry++) { /*for all entries*/
		cache_entry_t* cache = &cache_array[set][entry];
		if (cache->valid) { /*if cache is valid, if it has a data*/
			if (cache->tag == tag) { /*show the cache tag, and if it is matched to current tag, then hit!*/
				memcpy(&accessed_data, &(cache->data[byte_offset]), data_size);  /*Copy the data to accessed_data*/
				cache->timestamp = global_timestamp;
				num_cache_hits++; /*increase num of cache hits*/
				return accessed_data; /*return data*/
			}
		}
	}

	return -1; /*if miss, return -1*/
}

int find_entry_index_in_set(int cache_index) {
    int entry_index;

	if (DEFAULT_CACHE_ASSOC == 1) { /*if it is a direct mapped cache, return 0*/
		return 0;
	}

    /* Check if there exists any empty cache space by checking 'valid' */
	for(entry_index = 0; entry_index < DEFAULT_CACHE_ASSOC; entry_index++) {
		if (cache_array[cache_index][entry_index].valid == 0)
			return entry_index;
	}

    /* Otherwise, search over all entries to find the least recently used entry by checking 'timestamp' */
	int lru_entry_index = 0;
	int min_timestamp = cache_array[cache_index][0].timestamp;

	for (entry_index = 1; entry_index < DEFAULT_CACHE_ASSOC; entry_index++) {
		if (cache_array[cache_index][entry_index].timestamp < min_timestamp) {
			min_timestamp = cache_array[cache_index][entry_index].timestamp;
			lru_entry_index = entry_index;
		}
	}

    return lru_entry_index; /*return least recently used entry index*/
}

int access_memory(void *addr, char type) {
	num_access_cycles += MEMORY_ACCESS_CYCLE; /*increase access cycle as much as memory access cycle*/
	num_cache_misses++; /*if this function is executed, it means cache miss occurs, so increase num of cache misses*/

	int word_address = (int)addr / WORD_SIZE_BYTE;
	int word_offset = (int)addr % WORD_SIZE_BYTE;
	int data_size = 0;
	int accessed_data = 0; /*accessed_data which will be returned*/

	int block_addr = (int)addr / DEFAULT_CACHE_BLOCK_SIZE_BYTE;
	int byte_offset = (int)addr % DEFAULT_CACHE_BLOCK_SIZE_BYTE;
	int start_address = block_addr * DEFAULT_CACHE_BLOCK_SIZE_BYTE / WORD_SIZE_BYTE; /*start of the block. we save memory data at block(2 word) size*/
	int set = block_addr % CACHE_SET_SIZE;
	int tag = block_addr / CACHE_SET_SIZE;
	int entry = find_entry_index_in_set(set);

	/*determine data_size according to data type*/
	switch (type) {
	case 'b':
		data_size = 1;
		break;
	case 'h':
		data_size = 2;
		break;
	default:
		data_size = 4;
	}
	
	/* Fetch the data from the main memory and copy them to the cache */
	cache_entry_t *cache = &cache_array[set][entry];
	memcpy(cache->data, &memory_array[start_address], DEFAULT_CACHE_BLOCK_SIZE_BYTE); /*copy memory from memory_array to cache->data by cache block size*/

	cache->tag = tag;
	cache->valid = 1;
	cache->timestamp = global_timestamp;

	memcpy(&accessed_data, &(cache->data[byte_offset]), data_size); /*copy memory from cache->data to accessed data by data size*/

    return accessed_data;
}
