
## Build

```bash
mkdir build
cd build
conan install .. --output-folder=. --build=missing -d build_type=Debug
cmake .. --preset conan-debug
cmake --build --preset conan-debug
```