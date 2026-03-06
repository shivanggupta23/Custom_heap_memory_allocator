#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ANSI colors for visual vibe
#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

// Simulated heap size
#define HEAP_SIZE 1024

// Metadata for each block
typedef struct Block {
    size_t size;           // size of the block
    bool free;             // free or allocated
    struct Block* next;    // pointer to next block
} Block;

static char heap[HEAP_SIZE];   // simulated heap
static Block* free_list;       // linked list of blocks

// Initialize heap
void init_allocator() {
    free_list = (Block*)heap;
    free_list->size = HEAP_SIZE - sizeof(Block);
    free_list->free = true;
    free_list->next = NULL;
    printf(GREEN "✔ Allocator initialized with heap size %d bytes\n" RESET, HEAP_SIZE);
}

// Split block if larger than needed
void split_block(Block* block, size_t size) {
    if (block->size >= size + sizeof(Block) + 1) {
        Block* new_block = (Block*)((char*)block + sizeof(Block) + size);
        new_block->size = block->size - size - sizeof(Block);
        new_block->free = true;
        new_block->next = block->next;
        block->size = size;
        block->next = new_block;
        printf(YELLOW "✂ Block split: allocated %zu bytes, created new free block of %zu bytes\n" RESET, size, new_block->size);
    }
}

// First-Fit allocation
void* my_malloc(size_t size) {
    Block* current = free_list;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            current->free = false;
            split_block(current, size);
            printf(CYAN "🔒 Allocated %zu bytes at %p\n" RESET, size, (void*)(current+1));
            return (void*)(current+1); // return pointer after metadata
        }
        current = current->next;
    }
    printf(RED "✘ Allocation failed: not enough memory\n" RESET);
    return NULL;
}

// Coalesce adjacent free blocks
void coalesce() {
    Block* current = free_list;
    while (current != NULL && current->next != NULL) {
        if (current->free && current->next->free) {
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
            printf(YELLOW "🔗 Coalesced adjacent free blocks\n" RESET);
        } else {
            current = current->next;
        }
    }
}

// Free memory
void my_free(void* ptr) {
    if (ptr == NULL) return;
    Block* block = (Block*)ptr - 1;
    block->free = true;
    printf(GREEN "✔ Freed block of %zu bytes at %p\n" RESET, block->size, ptr);
    coalesce();
}

// Print memory state
void print_heap() {
    Block* current = free_list;
    printf("\n" CYAN "=== Heap State ===\n" RESET);
    while (current != NULL) {
        printf("Block at %p | Size: %zu | %s\n",
               (void*)current,
               current->size,
               current->free ? GREEN "Free" RESET : RED "Allocated" RESET);
        current = current->next;
    }
    printf(CYAN "==================\n" RESET);
}

// Demo
int main() {
    init_allocator();

    void* p1 = my_malloc(100);
    void* p2 = my_malloc(200);
    print_heap();

    my_free(p1);
    print_heap();

    void* p3 = my_malloc(50);
    print_heap();

    my_free(p2);
    my_free(p3);
    print_heap();

    return 0;
}
