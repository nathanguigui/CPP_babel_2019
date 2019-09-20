# CPP_babel_2019

## Installation

### Linux

#### By moulinette:

```bash
mkdir build
cd build
conan install .. --build missing
cmake .. -G "Unix Makefiles"
cmake --build .
```

#### By guigui:

```bash
conan install . --install-folder build
conan build . --build-folder build
```


#### Installation de Qt (30-35min)

```bash
conan remote add default https://api.bintray.com/conan/bincrafters/public-conan 
conan install qt/5.13.1@bincrafters/stable --build missing
```