
[lib/cef download](https://cef-builds.spotifycdn.com/index.html)

```bash
mkdir build
cd build
conon install .. --output-folder=. --build=missing
cmake .. --preset=conan-release
make
./demo
# two windows should be running.
# one's background is white and the other's background is light blue.
```