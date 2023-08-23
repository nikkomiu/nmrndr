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
