# Static STL

This aims to be a heapless implementation of C++ STL containers. It is not a
complete replacement due to the limitations of making no heap allocations. Many
STL containers cannot be used without new/malloc.

The goal is to provide an implementation which is portable to small micro
controllers and doesn't take up too much RAM/ROM.

# Usage

You can include the entire namespace:

    #include <sstl>

You can also include any of the individual headers.

# Testing

There is a small test setup in the `test` folder which can be run. From that
folder run:

    make

Any cpp files in `tests/src` will be built and run from `src\test.cpp`'s `int main()`
function.

# License

MIT
