# HighwayHashLibrary

HighwayHashLibrary is a C++ library that provides efficient hashing for trivially copyable types using the HighwayHash algorithm. It includes serialization functions, custom equality operators, and a convenient hasher class template for easy integration into your projects.

## Features

- **Trivially Copyable Type Support**: Ensures that only trivially copyable types can be used with the library functions.
- **Serialization**: Convert objects to byte arrays and back, facilitating easy serialization.
- **Custom Hashing**: Utilizes the HighwayHash algorithm for fast and secure hashing.
- **Equality Operators**: Overloaded equality operators for easy comparison of objects.

## Requirements

- C++20 or later
- HighwayHash library (available at [HighwayHash GitHub repository](https://github.com/Google/HighwayHash))

## Installation

It's a header-only library but you must also install HighwayHash.

1. **Clone the repository**:

   ```bash
   git clone https://github.com/yourusername/HighwayHashLibrary.git
   cd HighwayHashLibrary
   ```

2. **Install the HighwayHash library** (if not already installed):

   Follow the instructions in the [HighwayHash repository](https://github.com/Google/HighwayHash) to build and install the library.

3. **Include the header file in your project**:

   Ensure that you include `HighwayHashLibrary.hpp` in your source files where you want to use the library.

## Usage

See [`Example.cpp`](https://github.com/agentlans/HighwayHashLibrary/blob/master/Example.cpp) for a simple example demonstrating how to use the `HighwayHashLibrary`.

### Compilation

To compile your code with the HighwayHashLibrary:

```bash
g++ -fconcepts -o example main.cpp -I/path/to/highwayhash/include -L/path/to/highwayhash/lib -lhighwayhash
```

Replace `/path/to/highwayhash/include` and `/path/to/highwayhash/lib` with the actual paths where you have installed the HighwayHash library.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to Google for developing and maintaining the HighwayHash algorithm.
