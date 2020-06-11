# sfy (pronounced es-phi)

`sfy` is a thin wrapper library (currently in beta) built on top of [fmtlib](https://github.com/fmtlib/fmt) library
 which allows
 you to *`string`i-fy* objects for inspection or debugging purposes. `sfy` implements
  `sfy::to_string`'s overloads for several built-in standard library types and performs resolution using C++20's
   concepts (so you pay no-runtime overhead of plain-old templates and get better error diagnostics).
 
 ### Features
 
 `sfy::to_string` works with:
 
 * Fundamental types e.g `int`, `long`, `double` etc
 * Standard container types `std::vector`, `std::map` etc
 * Custom containers types implementing standard interfaces
 * Old c-style arrays or strings e.g `int[N]`, `char[]`
 * Data types such as `std::pair`, `std::tuple` etc
 * Numeric types such as `std::ratio` and `std::complex`
 * Nested types e.g `std::pair<std::vector, std::unordered_set>`
 
 #### Upcoming
 
 * Support for working with C++20's ranges
 
 ### Examples
 
  ```C++
 std::complex<double> complex(1.0, 2.0);
 sfy::to_string(complex);                  // outputs "1.0 + 2.0i";
  ```
 
 ```C++
auto pair = std::make_pair(5, 10);
auto tuple = std::make_tuple(1, 'a', "Hello world");
sfy::to_string(pair);                   // outputs "(5, 10)";
sfy::to_string(tuple);                  // outputs "(1, 'a', "Hello world")";
 ```

```C++
std::tuple<int, std::string, char> tuples[] = { {1, "hello", 'h'}, {2, "world", 'w'} };
sfy::to_string(tuples);                 // outputs "[(1, "hello", 'h'), (2, "world", 'w')]"
```

```C++
std::chrono::milliseconds dur(500);
sfy::to_string(dur);                    // outputs "500ms"
```

```C++
std::map<char, int> map = { {'a', 97}, {'b', 98} };
sfy::to_string(map);                    // outputs "{'a': 97, 'b': 98}");
```

### Usage

* Copy contents of `./include/` directory to your project's include directory path
* All functions are implemented in a single header file so you can do `#include <sfy/sfy.hppp>`

### Disclaimer

* Currently tested on Clang v10.0.0 only
* Project is in early beta stage so there could be bugs
* Recommendations, bug-fixes and PRs are welcome!