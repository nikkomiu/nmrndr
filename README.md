# NM Rndr

Ray Traced Renderer

## Development

### Dependencies

- CMake v3.27
- Ninja Build

#### Installing on Arch Linux

```bash
pacman -S cmake ninja clang curl zip unzip tar cppcheck
```

### Submodules

This project uses git submodules to include the vcpkg dependency.

After cloning make sure that the submodules have been cloned as well:

```bash
git submodule update --init --recursive
```
