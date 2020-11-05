#include "bitset.h"

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {

    struct bitset* result = malloc(sizeof(struct bitset));
    result->size_in_words = (int)((size / 64) + 1);
    result->universe_size = size;
    result->bits = malloc(result->size_in_words * sizeof(uint64_t));
    for(int i = 0; i < result->size_in_words; i++)
    {
        result->bits[i] = 0;
    }
    return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset* this) {
    return this->universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
    unsigned int result = 0;
    unsigned int count = 0;
    for(int i = 0; i < this->size_in_words; i++)
    {
        for(int j = 0; j < 64; j++)
        {
            if(((this->bits[i] >> j) & 1) == 1)
            {
                result++;
            }
            count++;
            if(count == this->universe_size)
            {
                break;
            }
        }
    }
    return result;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
    if(item > this->universe_size) { return 0;}
    uint64_t index = (uint64_t)((item / 64));
    int result = (this->bits[index] >> (item % 64)) & 1;
    return result;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
    uint64_t index = (uint64_t)((item / 64));
    this->bits[index] = this->bits[index] | ((uint64_t)1 << (item % 64));
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
    uint64_t index = (uint64_t)((item / 64));
    int offset = item % 64;
    this->bits[index] = (this->bits[index] | ((uint64_t)1 << offset)) ^ ((uint64_t)1 << offset);
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
    
    if(src1->universe_size == src2->universe_size && src1->universe_size == dest->universe_size)
    {
        for(int i = 0; i < dest->size_in_words; i++)
        {
            dest->bits[i] = src1->bits[i] | src2->bits[i];
        }
        return;
    }
    printf("[ERROR]: Universe Sizes passed to bitset_union do not match");
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
    
    if(src1->universe_size == src2->universe_size && src1->universe_size == dest->universe_size)
    {
        for(int i = 0; i < dest->size_in_words; i++)
        {
            dest->bits[i] = src1->bits[i] & src2->bits[i];
        }
        return;
    }
    printf("[ERROR]: Universe Sizes passed to bitset_intersect do not match");
}
