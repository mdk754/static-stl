# Static STL

This aims to be a heapless implementation of C++ STL containers. It is not a
complete replacement due to the limitations of making no heap allocations. Many
STL containers cannot be used without new/malloc.

The goal is to provide an implementation which is portable to small micro
controllers and doesn't take up too much RAM/ROM.

## Usage

You can include the entire namespace:

    #include <sstl>

You can also include any of the individual headers.

### Design

The classes are designed to be consumed in a manner as similar as possible to
the STL containers they replace. The only difference is the underlying capacity
must be specified at instantiation. In practice, what this means is that typical
use follows a pattern similar to this:

    sstl::array<int, 100> a;

    size_t ExampleSizeOfArray(sstl::array<int>& some_array) {
    	return some_array.size();
    }

    sstl::array<int>& aref = a;

As you can see, after the inital creation/allocation, the capacity is no longer
a necessary template argument for references. This means each container type can
be used in function signatures without requiring the size (unless desired) or
the use of templated functions to accept arbitrary sizes. It is also unnecessary
to pass the size as a distinct parameter along side the container, as this
information is stored internally.

### Compatibility

While the classes operate as closely as possible to their STL counterparts,
sometimes this is not possible due to the constraints of static allocation.

Sometimes, the functionality will diverge to allow for developer conveniences.
A good example is the `sstl::array` class shown above. A `std::array` does not
provide a type-only template variation, requiring any function dealing with an
array to accept a given size at compile time. The example above demonstrates how
this isn't necessary, and can make passing arbitrary length array references
into functions much less painful. A limitation of this approach is that the
array must be passed with it's size template parameter if it is to be passed by
value instead of as a reference.

## Testing

There is a small test setup in the `test` folder which can be run. From that
folder run:

    make

Any cpp files in `tests/src` will be built and run from `src\test.cpp`'s `int main()`
function.

## License

MIT
