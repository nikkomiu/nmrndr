FROM archlinux:latest

RUN pacman -Sy --noconfirm \
    base cmake ninja \
    git zip unzip curl tar \
    clang glibc pkg-config cppcheck llvm
