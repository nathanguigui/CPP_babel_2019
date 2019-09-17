# CPP_babel_2019

## Installation

### Linux

```bash
mkdir build
cd build
conan install ..
cmake .. -G "Unix Makefiles"
cmake --build .
```

#### Installation de Qt (30-35min)

```bash
conan install qt/5.13.1@bincrafters/stable --build missing
```