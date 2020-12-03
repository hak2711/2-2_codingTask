/*
 * main.c
 *
 * 20493-02 Computer Architecture
 * Term Project on Implentation of Cache Mechanism
 *
 * Skeleton Code Prepared by Prof. HyungJune Lee
 * Nov 13, 2017
 *
 */

#include <stdio.h>
#include <math.h>
#include "cache_impl.h"

int num_cache_hits = 0;
int num_cache_misses = 0;

int num_bytes = 0;
int num_access_cycles = 0;

int global_timestamp = 0;

int retrieve_data(void* addr, char data_type) {
	int value_returned = -1; /* accessed data */
	/* Invoke check_cache_data_hit() */
	value_returned = check_cache_data_hit(addr, data_type);

	/* In case of the cache miss event, access the main memory by invoking access_memory() */
	if (value_returned == -1) {
		value_returned = access_memory(addr, data_type);
	}

	return value_returned;
}

int main(void) {
	FILE* ifp = NULL, * ofp = NULL;
	unsigned long int access_addr; /* byte address (located at 1st column) in "access_input.txt" */
	char access_type; /* 'b'(byte), 'h'(halfword), or 'w'(word) (located at 2nd column) in "access_input.txt" */
	int accessed_data; /* This is the data that you want to retrieve first from cache, and then from memory */

	init_memory_content(); /*initialize memory_array content*/
	init_cache_content(); /*initialize cache_array content*/


	ifp = fopen("access_input2.txt", "r"); /*open input file*/
	if (ifp == NULL) {
		printf("Can't open input file\n");
		return -1;
	}
	ofp = fopen("access_output2-3.txt", "w"); /*open output file*/
	if (ofp == NULL) {
		printf("Can't open output file\n");
		fclose(ifp);
		return -1;
	}

	fprintf(ofp, "[Accessed Data]\n");

	while (1) {
		fscanf(ifp, "%d %c", &access_addr, &access_type);  /*read access_address and access_type from input file*/
		if (feof(ifp)) /*until file ends*/
			break;
		else {
			accessed_data = retrieve_data(access_addr, access_type); /*invoke retrieve_data and save the value of accessed_data*/
			fprintf(ofp, "%d		%c		%#x\n", access_addr, access_type, accessed_data); /*print it on the output file*/
			global_timestamp++; /*increase global timestamp*/
		}
	}

	int num_access = num_cache_hits + num_cache_misses; /*total access number is sum of num_cache_hits and num_cache_misses*/
	double hit_ratio = (double)num_cache_hits / num_access; /*hit ratio is the value of num_cache_hits divide into num_access*/
	double bandwidth = (double)num_bytes / num_access_cycles; /*bandwidth is the value of num_bytes divide into num_access_cycles*/

	fprintf(ofp, "-----------------------------------------------\n");

	if (DEFAULT_CACHE_ASSOC == 1) { /*if it is direct mapped cache*/
		fprintf(ofp, "[Direct mapped cache performance]\n");
	}

	else if (DEFAULT_CACHE_ASSOC == 4) { /*if it is fully associative cache*/
		fprintf(ofp, "[Fully associative cache performance]\n");
	}

	else { /*otherwise, n-way set associative cache*/
		fprintf(ofp, "[%d-way set associative cache performance]\n", DEFAULT_CACHE_ASSOC);
	}

	fprintf(ofp, "Hit ratio = %.2f (%d/%d)\n", hit_ratio, num_cache_hits, num_access);
	fprintf(ofp, "Bandwidth = %.2f (%d/%d)\n", bandwidth, num_bytes, num_access_cycles);

	fclose(ifp);
	fclose(ofp);

	return 0;
}
