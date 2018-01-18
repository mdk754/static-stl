# Static STL

This aims to be a heapless implementation of C++ STL containers. It is not a
complete replacement due to the limitations of making no heap allocations. Many
STL containers cannot be used without new/malloc.

The goal is to provide an implementation which is portable to small
microcontrollers and doesn't take up too much RAM/ROM.
