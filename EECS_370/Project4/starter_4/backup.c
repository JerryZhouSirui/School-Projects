/*
 * EECS 370, University of Michigan
 * Project 4: LC-2K Cache Simulator
 * Instructions are found in the project spec.
 */

#include <stdio.h>
#include <math.h>
#define MAX_CACHE_SIZE 256
#define MAX_BLOCK_SIZE 256

extern int mem_access(int addr, int write_flag, int write_data);
extern int get_num_mem_accesses();

enum actionType
{
    cacheToProcessor,
    processorToCache,
    memoryToCache,
    cacheToMemory,
    cacheToNowhere
};

typedef struct blockStruct
{
    int data[MAX_BLOCK_SIZE];
    int dirty;
    int lruLabel;
    int set;
    int tag;
    int valid;
} blockStruct;

typedef struct cacheStruct
{
    blockStruct blocks[MAX_CACHE_SIZE];
    int blockSize;
    int numSets;
    int blocksPerSet;
    //this is the stuff that I've added, remove if can't eddit
    int size;
    int offsetbits;
    int setbits;
    int numblocks;
    int tagbits;
    int hits;
    int misses;
    int drtybts;
    int writebacks;
} cacheStruct;

/* Global Cache variable */
cacheStruct cache;

void printAction(int, int, enum actionType);
void printCache();

/*
 * Set up the cache with given command line parameters. This is 
 * called once in main(). You must implement this function.
 */
void cache_init(int blockSize, int numSets, int blocksPerSet){
    //fill struct parameters and shiz ya feel cuz, why did ye do this, he made graduation!
    cache.blockSize = blockSize;
    cache.blocksPerSet = blocksPerSet;
    cache.numSets = numSets;
    cache.numblocks = blocksPerSet * numSets;
    cache.offsetbits = log2(blockSize);
    cache.setbits = log2(numSets);
    cache.tagbits = 32 - cache.offsetbits - cache.setbits;
    cache.hits = 0;
    cache.misses = 0;
    cache.drtybts = 0;
    cache.writebacks = 0;
    //initialize blocks and stuff, access via contiguous structure blocks[set# * blocksperset + int] where int is based on the block per set #
    for(int i = 0; i < numSets; i++){
        for(int j = 0; j < blocksPerSet; j++){
            cache.blocks[blocksPerSet*i + j].dirty = 0;
            cache.blocks[blocksPerSet*i + j].valid = 0;
            cache.blocks[blocksPerSet*i + j].lruLabel = 0;
            cache.blocks[blocksPerSet*i + j].set = i;
            cache.blocks[blocksPerSet*i + j].tag = -1;
        }
    }
    return;
}

/*
 * Access the cache. This is the main part of the project,
 * and should call printAction as is appropriate.
 * It should only call mem_access when absolutely necessary.
 * addr is a 16-bit LC2K word address.
 * write_flag is 0 for reads (fetch/lw) and 1 for writes (sw).
 * write_data is a word, and is only valid if write_flag is 1.
 * The return of mem_access is undefined if write_flag is 1.
 * Thus the return of cache_access is undefined if write_flag is 1.
 */
int cache_access(int addr, int write_flag, int write_data) {
    int set;
    int offset;
    int tag;
    
    set = (addr >> cache.offsetbits) & ((1 << cache.setbits) - 1);
    tag = (addr >> (cache.offsetbits + cache.setbits));
    offset = (addr & ((1 << cache.offsetbits)-1));
    int hit_indx = -1;
    int found = 0;
    //look for tag in set found = 0 miss found = 1 hit
    for(int i = 0; i < cache.blocksPerSet; i++) {
        if((cache.blocks[set * cache.blocksPerSet + i].tag == tag) 
        && (cache.blocks[set * cache.blocksPerSet + i].valid == 1)) {
            found = 1;
            hit_indx = set * cache.blocksPerSet + i;
            cache.hits++;
            break;
        }
    }
    //-------------------------------------------Hit-----------------------------------------------
    if(found == 1){
        
        for(int i = 0; i < cache.blocksPerSet; i++) {
            if((cache.blocks[set * cache.blocksPerSet + i].lruLabel < cache.blocks[hit_indx].lruLabel)
            &&(cache.blocks[set * cache.blocksPerSet + i].valid == 1)){
                //add one to lru if lru of hit was greater than its current lru since hit goes to top
                cache.blocks[set * cache.blocksPerSet + i].lruLabel++;
            }
        }
        cache.blocks[hit_indx].lruLabel = 0;
        if(write_flag == 0){ //-------------------------------read------------------
            printAction(addr, 1, cacheToProcessor);
            return cache.blocks[hit_indx].data[offset];
        }
        else{ //--------------------------------write-------------------------------------
            cache.blocks[hit_indx].dirty = 1;
            cache.blocks[hit_indx].data[offset] = write_data;
            printAction(addr, 1, processorToCache);
            cache.drtybts++;
            return -1;
        }
    }
    else { //------------------------------Miss-------------------------------------------------
        
        cache.misses++;
        int full = 1; //default that it is full for loop breaking reasons
        //check the current set to see if it is full at the moment
        int insert = -1;
        for(int i = 0; i < cache.blocksPerSet; i++){
            if(cache.blocks[set * cache.blocksPerSet + i].valid == 0){
                full = 0;
            }
        }
        if(write_flag == 0) { //-----------------read-------------------------------------------
            if(full == 0){ //-----------------------not full--------------------------------------------
                for(int i = 0; i < cache.blocksPerSet; i++){
                    if(cache.blocks[set * cache.blocksPerSet + i].valid == 0){
                        cache.blocks[set * cache.blocksPerSet + i].valid = 1;
                        cache.blocks[set * cache.blocksPerSet + i].tag = tag;
                        cache.blocks[set * cache.blocksPerSet + i].lruLabel = -1; //set -1 so it can be incremented to zero when we increment all other LRUS
                        insert = set * cache.blocksPerSet + i;
                        break;
                    }
                }
                for(int i = 0; i < cache.blocksPerSet; i++) {
                    cache.blocks[set * cache.blocksPerSet + i].lruLabel++;
                }
                cache.blocks[insert].lruLabel = 0;
                int built = 0;
                built = built << cache.tagbits;
                built += cache.blocks[insert].tag;
                built = built << cache.setbits;
                built += set;
                built = built << cache.offsetbits;
                printAction(built, cache.blockSize, memoryToCache);
                

                for(int i = 0; i < cache.blockSize; i++){
                    cache.blocks[insert].data[i] = mem_access(built, 0, -1);
                    built++;
                }
                printAction(addr, 1, cacheToProcessor);
                return cache.blocks[insert].data[offset];
            } //-----------------------full--------------------------------------------------
            else {
                int max = -1;
                int maxloc = -1;

                for(int i = 0; i < cache.blockSize;i++) {
                    if(cache.blocks[set * cache.blocksPerSet + i].lruLabel > max) {
                        max = cache.blocks[set * cache.blocksPerSet + i].lruLabel;
                        maxloc = i;
                    }
                }
                for(int i = 0; i < cache.blocksPerSet; i++) {
                    cache.blocks[set * cache.blocksPerSet + i].lruLabel++;
                }
                cache.blocks[set*cache.blocksPerSet + maxloc].lruLabel = 0;

                int built = 0;
                built = built << cache.tagbits;
                built += cache.blocks[set*cache.blocksPerSet + maxloc].tag;
                built = built << cache.setbits;
                built += set;
                built = built << cache.offsetbits;

                if(cache.blocks[set*cache.blocksPerSet + maxloc].dirty == 1){
                    cache.blocks[set*cache.blocksPerSet + maxloc].dirty = 0; //reset to zero
                    cache.drtybts--;
                    printAction(built, cache.blockSize, cacheToMemory);
                    for(int i = 0; i < cache.blockSize; i++){
                        //send the cache block bits to memory before completely evicting
                        mem_access(built, 1, cache.blocks[set*cache.blockSize + maxloc].data[i]);
                        built++; //increment block offset adr
                    }
                    cache.writebacks++;
                }
                else {
                    //if the dirty bit is off dup that shiz without writing
                    printAction(built, cache.blockSize, cacheToNowhere);
                }
                //now replace the evicted cache block with the new one
                int replacer = 0;
                replacer = replacer << cache.tagbits;
                replacer += tag;
                replacer = replacer << cache.setbits; //check back here for bug maybe from tag
                replacer += set;
                replacer = replacer << cache.offsetbits;
                printAction(replacer, cache.blockSize, memoryToCache);
                
                for(int i = 0; i < cache.blockSize; i++){
                    cache.blocks[set*cache.blocksPerSet+maxloc].data[i] = mem_access(replacer, 0, -1);
                    cache.blocks[set*cache.blocksPerSet+maxloc].tag = tag;
                    replacer++;
                }
                printAction(addr,1,cacheToProcessor);
                return cache.blocks[set*cache.blocksPerSet + maxloc].data[offset];
            }
            
        } //------------------------------write--------------------------------------------
        else{
            if(full == 0) { //-----------------------not full----------------------------------
                int empty = 0;
                for(int i = 0; i < cache.blocksPerSet; i++){
                    if(cache.blocks[cache.blocksPerSet*set + i].valid == 0){
                        cache.blocks[cache.blocksPerSet*set + i].valid = 1;
                        cache.blocks[cache.blocksPerSet*set + i].tag = tag;
                        cache.blocks[cache.blocksPerSet*set + i].dirty = 1;
                        cache.drtybts++;
                        empty = cache.blocksPerSet*set + i;
                        break;
                    }
                }
                for(int i = 0; i < cache.blocksPerSet; i++){
                    cache.blocks[cache.blocksPerSet*set + i].lruLabel++;
                }
                cache.blocks[empty].lruLabel = 0;

                int built = 0;
                built = built << cache.tagbits;
                built += cache.blocks[empty].tag;
                built = built << cache.setbits;
                built += set;
                built = built << cache.offsetbits;
                printAction(built, cache.blockSize, memoryToCache);
                

                for(int i = 0; i < cache.blockSize; i++) {
                    cache.blocks[empty].data[offset] = mem_access(built, 0, -1);
                    built++;
                }
                printAction(addr, 1, processorToCache);
                cache.blocks[empty].data[offset] = write_data;
                return -1;
            } //----------------------------full--------------------------------------
            else{
                int max = -1;
                int maxloc = -1;

                for(int i = 0; i < cache.blockSize;i++) {
                    if(cache.blocks[set * cache.blocksPerSet + i].lruLabel > max) {
                        max = cache.blocks[set * cache.blocksPerSet + i].lruLabel;
                        maxloc = i;
                    }
                }
                for(int i = 0; i < cache.blocksPerSet; i++) {
                    cache.blocks[set * cache.blocksPerSet + i].lruLabel++;
                }
                cache.blocks[set*cache.blocksPerSet + maxloc].lruLabel = 0;

                int built = 0;
                built = built << cache.tagbits;
                built += cache.blocks[set*cache.blocksPerSet + maxloc].tag;
                built = built << cache.setbits;
                built += cache.blocks[set*cache.blocksPerSet + maxloc].set;
                built = built << cache.offsetbits;

                if(cache.blocks[set*cache.blocksPerSet + maxloc].dirty == 1){
                    cache.blocks[set*cache.blocksPerSet + maxloc].dirty = 0; //reset to zero
                    cache.drtybts--;
                    printAction(built, cache.blockSize, cacheToMemory);
                    for(int i = 0; i < cache.blockSize; i++){
                        //send the cache block bits to memory before completely evicting
                        mem_access(built, 1, cache.blocks[set*cache.blockSize + maxloc].data[i]);
                        built++; //increment block offset adr
                    }
                    cache.writebacks++;
                }
                
                else {
                    //if the dirty bit is off dup that shiz without writing
                    printAction(built, cache.blockSize, cacheToNowhere);
                }
                //now replace the evicted cache block with the new one
                int replacer = 0;
                replacer = replacer << cache.tagbits;
                replacer += tag;
                replacer = replacer << cache.setbits;
                replacer += set;
                replacer = replacer << cache.offsetbits;
                printAction(replacer, cache.blockSize, memoryToCache);
                printAction(addr,1,processorToCache);
                for(int i = 0; i < cache.blockSize; i++){
                    cache.blocks[set*cache.blocksPerSet+maxloc].data[i] = mem_access(replacer, 0, -1);
                    cache.blocks[set*cache.blocksPerSet+maxloc].tag = tag;
                    replacer++;
                }
                cache.blocks[set * cache.blocksPerSet + maxloc].data[offset] = write_data;
                cache.blocks[set * cache.blocksPerSet + maxloc].dirty = 1;
                cache.drtybts++;
                return -1;
            }
        }
    }
    return -1;
}
// return mem_access(addr, write_flag, write_data);

/*
 * print end of run statistics like in the spec. This is not required,
 * but is very helpful in debugging.
 * This should be called once a halt is reached.
 * DO NOT delete this function, or else it won't compile.
 * DO NOT print $$$ in this function
 */
void printStats(){
    printf("Hits %d, Misses %d, Writebacks %d\n", cache.hits, cache.misses, cache.writebacks);
}

/*
 * Log the specifics of each cache action.
 *
 * address is the starting word address of the range of data being transferred.
 * size is the size of the range of data being transferred.
 * type specifies the source and destination of the data being transferred.
 *  -    cacheToProcessor: reading data from the cache to the processor
 *  -    processorToCache: writing data from the processor to the cache
 *  -    memoryToCache: reading data from the memory to the cache
 *  -    cacheToMemory: evicting cache data and writing it to the memory
 *  -    cacheToNowhere: evicting cache data and throwing it away
 */
void printAction(int address, int size, enum actionType type)
{
    printf("$$$ transferring word [%d-%d] ", address, address + size - 1);

    if (type == cacheToProcessor) {
        printf("from the cache to the processor\n");
    }
    else if (type == processorToCache) {
        printf("from the processor to the cache\n");
    }
    else if (type == memoryToCache) {
        printf("from the memory to the cache\n");
    }
    else if (type == cacheToMemory) {
        printf("from the cache to the memory\n");
    }
    else if (type == cacheToNowhere) {
        printf("from the cache to nowhere\n");
    }
}

/*
 * Prints the cache based on the configurations of the struct
 * This is for debugging only and is not graded, so you may
 * modify it, but that is not recommended.
 */
void printCache()
{
    printf("\ncache:\n");
    for (int set = 0; set < cache.numSets; ++set) {
        printf("\tset %i:\n", set);
        for (int block = 0; block < cache.blocksPerSet; ++block) {
            printf("\t\t[ %i ]: {", block);
            for (int index = 0; index < cache.blockSize; ++index) {
                printf(" %i", cache.blocks[set * cache.blocksPerSet + block].data[index]);
            }
            printf(" }\n");
        }
    }
    printf("end cache\n");
}