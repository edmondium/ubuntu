# Ubuntu Image Fetcher

## Overview
Ubuntu Image Fetcher is a C++ command-line utility that fetches Ubuntu Cloud image metadata from Canonical's Simplestreams API. It provides the following functionality:
- List all currently supported Ubuntu releases.
- Retrieve the latest Ubuntu LTS version.
- Fetch the SHA256 checksum of the `disk1.img` file for a given Ubuntu release.

## Features
- Uses **libcurl** for HTTP requests.
- Parses JSON data using **nlohmann/json**.
- Designed for **cross-platform compatibility** (Linux, macOS, Windows).
- Built using **CMake**.

## Prerequisites
Before building the project, ensure you have the following dependencies installed:

### Ubuntu/Debian
```sh
sudo apt update
sudo apt install -y cmake g++ libcurl4-openssl-dev nlohmann-json3-dev
```

### macOS (Using Homebrew)
```sh
brew install cmake curl nlohmann-json
```

### Windows (Using vcpkg)
```sh
vcpkg install curl nlohmann-json
```

## Build Instructions
1. Clone the repository:
   ```sh
   git clone https://github.com/edmondium/ubuntu.git
   cd ubuntu
   ```
2. Create a build directory:
   ```sh
   mkdir build && cd build
   ```
3. Run CMake and compile:
   ```sh
   cmake ..
   make
   ```

## Usage
After building, you can run the tool with the following commands:

- **List all supported Ubuntu releases:**
  ```sh
  ./UbuntuFetcher --list
  ```
- **Get the latest Ubuntu LTS version:**
  ```sh
  ./UbuntuFetcher --latest-lts
  ```
- **Retrieve the SHA256 checksum of `disk1.img` for a given release (e.g., focal):**
  ```sh
  ./UbuntuFetcher --sha256 focal
  ```

## Example Output
```sh
$ ./UbuntuFetcher --latest-lts
Latest LTS: 24.04

$ ./UbuntuFetcher --sha256 focal
SHA256: a1b2c3d4e5...
```

## Notes
- The tool only considers **amd64** architecture.
- If a release is not found, it will return `Not found`.

## License
This project is licensed under the MIT License.


