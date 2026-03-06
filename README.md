# 🧩 Custom Heap Memory Allocator in C

A custom heap memory allocator built in C that simulates the functionality of `malloc()` and `free()`.  
This project demonstrates low-level memory management using **pointers, linked lists, and metadata tracking**, with support for **First-Fit allocation, block splitting, and free block coalescing**.

---

## 🚀 Features
- **Dynamic Allocation**: Simulates `malloc()` by allocating memory blocks from a custom heap.
- **Freeing Memory**: Simulates `free()` by marking blocks as available again.
- **First-Fit Strategy**: Allocates the first free block large enough for the request.
- **Block Splitting**: Splits larger free blocks into allocated + remaining free blocks.
- **Coalescing**: Merges adjacent free blocks to reduce external fragmentation.
- **Visual Output**: Color-coded logs showing allocations, frees, splits, and coalescing for easy debugging and demo.

---

## ⚙️ How It Works
1. **Initialization**: A large chunk of memory (`heap[]`) is created and represented as a linked list of blocks.
2. **Allocation (`my_malloc`)**:
   - Traverse the list using First-Fit.
   - If block is larger than requested → split it.
   - Return pointer to usable memory.
3. **Freeing (`my_free`)**:
   - Mark block as free.
   - Merge with adjacent free blocks (coalescing).
4. **Metadata**:
   - Each block stores size, free/allocated flag, and pointer to next block.

---

## 📖 Example Output
✔ Allocator initialized with heap size 1024 bytes
✂ Block split: allocated 100 bytes, created new free block of 876 bytes
🔒 Allocated 100 bytes at 0x607d9d279058
✂ Block split: allocated 200 bytes, created new free block of 652 bytes
🔒 Allocated 200 bytes at 0x607d9d2790d4

=== Heap State ===
Block at 0x607d9d279040 | Size: 100 | Allocated
Block at 0x607d9d2790bc | Size: 200 | Allocated
Block at 0x607d9d27919c | Size: 652 | Free
==================
✔ Freed block of 100 bytes at 0x607d9d279058

=== Heap State ===
Block at 0x607d9d279040 | Size: 100 | Free
Block at 0x607d9d2790bc | Size: 200 | Allocated
Block at 0x607d9d27919c | Size: 652 | Free
==================
✂ Block split: allocated 50 bytes, created new free block of 26 bytes
🔒 Allocated 50 bytes at 0x607d9d279058

=== Heap State ===
Block at 0x607d9d279040 | Size: 50 | Allocated
Block at 0x607d9d27908a | Size: 26 | Free
Block at 0x607d9d2790bc | Size: 200 | Allocated
Block at 0x607d9d27919c | Size: 652 | Free
==================
✔ Freed block of 200 bytes at 0x607d9d2790d4
🔗 Coalesced adjacent free blocks
🔗 Coalesced adjacent free blocks
✔ Freed block of 50 bytes at 0x607d9d279058
🔗 Coalesced adjacent free blocks

=== Heap State ===
Block at 0x607d9d279040 | Size: 1000 | Free
==================
