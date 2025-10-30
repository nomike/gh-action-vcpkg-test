# vcpkg Test Project with GitHub Actions Caching

This project demonstrates how to set up a C++ application using vcpkg for dependency management with efficient caching in GitHub Actions.

## Project Structure

- `CMakeLists.txt` - CMake configuration file
- `vcpkg.json` - vcpkg manifest file defining dependencies
- `src/main.cpp` - Simple test application using lib3mf
- `.github/workflows/` - GitHub Actions workflows with caching

## Dependencies

- **lib3mf**: A C++ library for reading and writing 3MF files

## Caching Strategy

This project uses `lukka/run-vcpkg@v11` which provides several caching mechanisms:

### 1. Built-in vcpkg Caching
The `run-vcpkg` action automatically caches:
- vcpkg tool itself
- Downloaded source archives
- Built packages (binary caching)

### 2. GitHub Actions Binary Caching
By setting the environment variable:
```yaml
env:
  VCPKG_BINARY_SOURCES: 'clear;x-gha,readwrite'
```

This enables vcpkg to use GitHub Actions cache as a binary cache backend, meaning:
- ✅ First run: Downloads and compiles dependencies (~5-10 minutes)
- ✅ Subsequent runs: Reuses cached binaries (~1-2 minutes)

### 3. Cache Key Strategy
The cache keys are automatically generated based on:
- vcpkg.json content (dependencies and versions)
- Target triplet (x64-windows, x64-windows-static, etc.)
- vcpkg baseline/commit

## Workflows

### Basic Build (`build.yml`)
- Simple workflow for Windows with MSVC
- Uses default caching provided by `run-vcpkg`
- Builds and tests the application

### Advanced Build (`build-advanced.yml`)
- Matrix build strategy (multiple triplets)
- Advanced binary caching with GitHub Actions
- Artifact uploads
- Parallel building

## Usage

1. **First Run**: Will be slow as it builds lib3mf from source
2. **Subsequent Runs**: Will be fast as it reuses cached binaries
3. **Cache Invalidation**: Only happens when dependencies change in vcpkg.json

## Local Development

To build locally with vcpkg:

```bash
# Clone vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat  # Windows
./bootstrap-vcpkg.sh   # Linux/macOS

# Configure and build
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Cache Performance

Expected performance improvements:
- **Without caching**: 8-12 minutes per build
- **With caching**: 1-3 minutes per build (after first run)
- **Cache hit ratio**: ~95% for unchanged dependencies

## Troubleshooting

### Cache Miss Issues
If you're experiencing cache misses:
1. Check if `vcpkg.json` was modified
2. Verify the baseline hash is consistent
3. Ensure triplet hasn't changed

### Build Failures
1. Check vcpkg baseline compatibility
2. Verify MSVC version compatibility
3. Review dependency constraints in vcpkg.json

## Advanced Configuration

### Custom Triplets
You can create custom triplets in `triplets/` directory for specific build configurations.

### Binary Caching Backends
vcpkg supports multiple binary cache backends:
- GitHub Actions Cache (used here)
- Azure Blob Storage
- AWS S3
- Local filesystem
- HTTP(S) servers

See [vcpkg binary caching documentation](https://github.com/microsoft/vcpkg/blob/master/docs/users/binarycaching.md) for more options.