# NM Rndr

Ray Traced Renderer

## Development

### Dependencies

- Clang
- Ninja Build
- CMake v3.27
- curl
- zip
- unzip
- tar
- cppcheck

#### Installing on Arch Linux

```bash
pacman -S cmake ninja clang curl zip unzip tar cppcheck llvm
```

### Submodules

This project uses git submodules to include the vcpkg dependency.

After cloning make sure that the submodules have been cloned as well:

```bash
git submodule update --init --recursive
```

### Cobertura Report Generation (Optional)

Generation of Cobertura reports outside of GitLab CI is not required. However, if you'd like to test with it or you're testing
the GitLab CI pipeline locally, you'll need to install the tool used to generate the Cobertura report.

Cobertura coverage report generation requires the [lcov-to-cobertura-xml](https://github.com/eriwen/lcov-to-cobertura-xml) tool:

```bash
wget -O /usr/local/bin/lcov_cobertura https://raw.github.com/eriwen/lcov-to-cobertura-xml/master/lcov_cobertura/lcov_cobertura.py
chmod +x /usr/local/bin/lcov_cobertura
```
