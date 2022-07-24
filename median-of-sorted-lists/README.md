Install CMake 3.22+:

```bash
$ brew install cmake
```

Generate the project build system:

```bash
$ cmake -B build
```

Build the project:

```bash
$ cmake --build build
```

Run the tests:

```bash
$ (cd build && ctest)
# Run a specific test:
$ (cd build && ctest -R HelloTest.BasicAssertions) 
```

The tests run RapidCheck, but it can also be run separately:
```bash
build/solution_rapidcheck
```